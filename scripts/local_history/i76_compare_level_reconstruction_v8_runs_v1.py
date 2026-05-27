#!/usr/bin/env python3
"""
i76_compare_level_reconstruction_v8_runs_v1.py

Compare two i76_level_reconstruction_export_v8 output directories or tar archives,
typically miss8 vs miss16.  The comparison is table-driven and avoids relying on
absolute paths, so equivalent records from different color-depth trees can be
matched by mission, parent tag, index, chunk offset, label/name, class, and/or
RSEG indices.

Outputs:
    manifest.json
    notes.txt
    tables/mission_summary.tsv
    tables/object_record_diffs.tsv
    tables/resource_policy_diffs.tsv
    tables/rseg_record_diffs.tsv
    tables/rseg_point_diffs.tsv
    tables/file_inventory_diffs.tsv

Example:
    python3 i76_compare_level_reconstruction_v8_runs_v1.py \
      --left /path/to/i76_level_reconstruction_export_v8_...miss8.tar \
      --right /path/to/i76_level_reconstruction_export_v8_...miss16.tar \
      --left-name miss8 --right-name miss16 \
      --out-dir /media/neon-remote/prj/i76/scratch_data \
      --make-tar
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import math
import os
import shutil
import tarfile
import tempfile
from collections import Counter, defaultdict
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

TSV_TABLES = {
    "obj": "obj_records.tsv",
    "odef": "odef_obj_records.tsv",
    "resolution": "object_resource_resolution.tsv",
    "sdf_child": "sdf_child_candidates.tsv",
    "unresolved": "unresolved_resources.tsv",
    "rseg_records": "rdef_rseg_records.tsv",
    "rseg_points": "rdef_rseg_points.tsv",
}

EPS_FLOAT = 1.0e-5


def now_stamp() -> str:
    return datetime.now().strftime("%Y%m%d_%H%M%S")


def mkdirp(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)


def is_tar_path(path: Path) -> bool:
    suffixes = "".join(path.suffixes).lower()
    return path.is_file() and (suffixes.endswith(".tar") or suffixes.endswith(".tar.gz") or suffixes.endswith(".tgz"))


def safe_extract_tar(tar_path: Path, dest: Path) -> Path:
    mkdirp(dest)
    root = dest.resolve()
    with tarfile.open(tar_path, "r:*") as tf:
        for member in tf.getmembers():
            target = (dest / member.name).resolve()
            if not str(target).startswith(str(root) + os.sep) and target != root:
                raise RuntimeError(f"refusing unsafe tar member path: {member.name}")
        tf.extractall(dest)
    children = [p for p in dest.iterdir() if p.is_dir()]
    if len(children) == 1:
        # Uploaded tars can occasionally be extracted under an extra wrapper dir.
        return find_run_root(children[0])
    return find_run_root(dest)


def find_run_root(path: Path) -> Path:
    path = path.resolve()
    if (path / "tables").is_dir():
        return path
    candidates = [p for p in path.rglob("tables") if p.is_dir()]
    if not candidates:
        raise FileNotFoundError(f"could not find tables/ under {path}")
    candidates.sort(key=lambda p: (len(p.parts), str(p)))
    return candidates[0].parent


@dataclass
class InputRun:
    name: str
    original: Path
    root: Path
    cleanup_dir: Optional[Path]


def prepare_input(name: str, original: Path, temp_parent: Path) -> InputRun:
    original = original.resolve()
    if is_tar_path(original):
        extract_dir = temp_parent / f"extract_{name}"
        root = safe_extract_tar(original, extract_dir)
        return InputRun(name=name, original=original, root=root, cleanup_dir=extract_dir)
    return InputRun(name=name, original=original, root=find_run_root(original), cleanup_dir=None)


def read_tsv(path: Path) -> List[Dict[str, str]]:
    if not path.exists():
        return []
    with path.open("r", newline="", encoding="utf-8", errors="replace") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def write_tsv(path: Path, rows: Sequence[Dict[str, object]], fields: Sequence[str]) -> None:
    mkdirp(path.parent)
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=list(fields), delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for row in rows:
            w.writerow({k: row.get(k, "") for k in fields})


def norm_path(p: str) -> str:
    s = (p or "").replace("\\", "/")
    low = s.lower()
    for token in ["/miss8/", "/miss16/"]:
        idx = low.find(token)
        if idx >= 0:
            return "<miss>/" + s[idx + len(token):]
    for token in ["/resources/"]:
        idx = low.find(token)
        if idx >= 0:
            return "<resources>/" + s[idx + len(token):]
    return Path(s).name.lower() if s else ""


def basename_lower(p: str) -> str:
    return Path((p or "").replace("\\", "/")).name.lower()


def fnum(value: str) -> Optional[float]:
    try:
        if value is None or value == "":
            return None
        x = float(value)
        if math.isnan(x) or math.isinf(x):
            return None
        return x
    except Exception:
        return None


def float_same(a: str, b: str, eps: float = EPS_FLOAT) -> bool:
    fa, fb = fnum(a), fnum(b)
    if fa is None or fb is None:
        return (a or "") == (b or "")
    return abs(fa - fb) <= eps


def basis_same(a: str, b: str, eps: float = EPS_FLOAT) -> bool:
    av = [(x.strip()) for x in (a or "").split(",") if x.strip() != ""]
    bv = [(x.strip()) for x in (b or "").split(",") if x.strip() != ""]
    if len(av) != len(bv):
        return False
    return all(float_same(x, y, eps) for x, y in zip(av, bv))


def row_hash(row: Dict[str, str], ignore_fields: Iterable[str] = ()) -> str:
    ignore = set(ignore_fields)
    parts = []
    for k in sorted(row):
        if k in ignore:
            continue
        v = row.get(k, "")
        if k.endswith("path") or k == "path" or k == "resolved_path":
            v = norm_path(v)
        parts.append(f"{k}={v}")
    return hashlib.sha1("\n".join(parts).encode("utf-8", "replace")).hexdigest()


def multimap(rows: Sequence[Dict[str, str]], key_fields: Sequence[str]) -> Dict[Tuple[str, ...], List[Dict[str, str]]]:
    out: Dict[Tuple[str, ...], List[Dict[str, str]]] = defaultdict(list)
    for row in rows:
        key = []
        for f in key_fields:
            if f == "norm_path":
                key.append(norm_path(row.get("path", "")))
            elif f == "resolved_basename":
                key.append(basename_lower(row.get("resolved_path", "")))
            else:
                key.append(row.get(f, ""))
        out[tuple(key)].append(row)
    return out


def count_by(rows: Sequence[Dict[str, str]], field: str) -> Counter:
    c = Counter()
    for row in rows:
        c[row.get(field, "")] += 1
    return c


def mission_set(rows: Sequence[Dict[str, str]]) -> List[str]:
    return sorted({r.get("mission", "") for r in rows if r.get("mission", "")})


def table_path(run: InputRun, table_name: str) -> Path:
    return run.root / "tables" / TSV_TABLES[table_name]


def load_run_tables(run: InputRun) -> Dict[str, List[Dict[str, str]]]:
    return {name: read_tsv(table_path(run, name)) for name in TSV_TABLES}


def summarize_missions(left: Dict[str, List[Dict[str, str]]], right: Dict[str, List[Dict[str, str]]], left_name: str, right_name: str) -> List[Dict[str, object]]:
    missions = sorted(set(mission_set(left["obj"])) | set(mission_set(right["obj"])) | set(mission_set(left["rseg_records"])) | set(mission_set(right["rseg_records"])))
    rows = []
    for m in missions:
        def filt(table, side):
            return [r for r in side[table] if r.get("mission", "") == m]
        l_obj = filt("obj", left)
        r_obj = filt("obj", right)
        l_res = filt("resolution", left)
        r_res = filt("resolution", right)
        l_rseg = filt("rseg_records", left)
        r_rseg = filt("rseg_records", right)
        l_pts = filt("rseg_points", left)
        r_pts = filt("rseg_points", right)
        l_sdf = sum(1 for r in l_res if r.get("resource_kind") == "sdf" and r.get("resolved") == "True")
        r_sdf = sum(1 for r in r_res if r.get("resource_kind") == "sdf" and r.get("resolved") == "True")
        l_vcf = sum(1 for r in l_res if r.get("resource_kind") == "vcf" and r.get("resolved") == "True")
        r_vcf = sum(1 for r in r_res if r.get("resource_kind") == "vcf" and r.get("resolved") == "True")
        rows.append({
            "mission": m,
            f"{left_name}_objects": len(l_obj),
            f"{right_name}_objects": len(r_obj),
            "objects_delta": len(r_obj) - len(l_obj),
            f"{left_name}_resolved_sdf": l_sdf,
            f"{right_name}_resolved_sdf": r_sdf,
            "resolved_sdf_delta": r_sdf - l_sdf,
            f"{left_name}_resolved_vcf": l_vcf,
            f"{right_name}_resolved_vcf": r_vcf,
            "resolved_vcf_delta": r_vcf - l_vcf,
            f"{left_name}_rseg_records": len(l_rseg),
            f"{right_name}_rseg_records": len(r_rseg),
            "rseg_records_delta": len(r_rseg) - len(l_rseg),
            f"{left_name}_rseg_points": len(l_pts),
            f"{right_name}_rseg_points": len(r_pts),
            "rseg_points_delta": len(r_pts) - len(l_pts),
        })
    return rows


def compare_objects(left_rows: List[Dict[str, str]], right_rows: List[Dict[str, str]], left_name: str, right_name: str) -> List[Dict[str, object]]:
    key_fields = ["mission", "parent_tag", "index", "chunk_offset_hex"]
    lm = multimap(left_rows, key_fields)
    rm = multimap(right_rows, key_fields)
    rows = []
    all_keys = sorted(set(lm) | set(rm))
    for key in all_keys:
        llist = lm.get(key, [])
        rlist = rm.get(key, [])
        n = max(len(llist), len(rlist))
        for i in range(n):
            l = llist[i] if i < len(llist) else None
            r = rlist[i] if i < len(rlist) else None
            if l is None or r is None:
                side = f"only_{right_name}" if l is None else f"only_{left_name}"
                src = r if l is None else l
                rows.append({
                    "diff_kind": side,
                    "mission": key[0], "parent_tag": key[1], "index": key[2], "chunk_offset_hex": key[3],
                    f"{left_name}_name": "" if l is None else l.get("name", ""),
                    f"{right_name}_name": "" if r is None else r.get("name", ""),
                    f"{left_name}_class_hex": "" if l is None else l.get("class_hex", ""),
                    f"{right_name}_class_hex": "" if r is None else r.get("class_hex", ""),
                    "pos_changed": "", "basis_changed": "", "path_left": norm_path(src.get("path", "")), "path_right": "",
                })
                continue
            changes = []
            if l.get("name", "") != r.get("name", ""):
                changes.append("name")
            if l.get("class_hex", "") != r.get("class_hex", ""):
                changes.append("class")
            pos_changed = not (float_same(l.get("pos_x", ""), r.get("pos_x", "")) and float_same(l.get("pos_y", ""), r.get("pos_y", "")) and float_same(l.get("pos_z", ""), r.get("pos_z", "")))
            if pos_changed:
                changes.append("position")
            basis_changed = not basis_same(l.get("basis", ""), r.get("basis", ""))
            if basis_changed:
                changes.append("basis")
            if l.get("dispatch_valid", "") != r.get("dispatch_valid", ""):
                changes.append("dispatch_valid")
            if l.get("tail_dwords_hex", "") != r.get("tail_dwords_hex", ""):
                changes.append("tail")
            if changes:
                rows.append({
                    "diff_kind": "+".join(changes),
                    "mission": key[0], "parent_tag": key[1], "index": key[2], "chunk_offset_hex": key[3],
                    f"{left_name}_name": l.get("name", ""),
                    f"{right_name}_name": r.get("name", ""),
                    f"{left_name}_class_hex": l.get("class_hex", ""),
                    f"{right_name}_class_hex": r.get("class_hex", ""),
                    f"{left_name}_pos": f"{l.get('pos_x','')},{l.get('pos_y','')},{l.get('pos_z','')}",
                    f"{right_name}_pos": f"{r.get('pos_x','')},{r.get('pos_y','')},{r.get('pos_z','')}",
                    "pos_changed": pos_changed,
                    "basis_changed": basis_changed,
                    "path_left": norm_path(l.get("path", "")),
                    "path_right": norm_path(r.get("path", "")),
                })
    return rows


def compare_resolution(left_rows: List[Dict[str, str]], right_rows: List[Dict[str, str]], left_name: str, right_name: str) -> List[Dict[str, object]]:
    key_fields = ["mission", "parent_tag", "index", "chunk_offset_hex"]
    lm = multimap(left_rows, key_fields)
    rm = multimap(right_rows, key_fields)
    rows = []
    for key in sorted(set(lm) | set(rm)):
        llist = lm.get(key, [])
        rlist = rm.get(key, [])
        n = max(len(llist), len(rlist))
        for i in range(n):
            l = llist[i] if i < len(llist) else None
            r = rlist[i] if i < len(rlist) else None
            if l is None or r is None:
                src = r if l is None else l
                rows.append({
                    "diff_kind": f"only_{right_name}" if l is None else f"only_{left_name}",
                    "mission": key[0], "parent_tag": key[1], "index": key[2], "chunk_offset_hex": key[3],
                    f"{left_name}_label": "" if l is None else l.get("label", ""),
                    f"{right_name}_label": "" if r is None else r.get("label", ""),
                    "path": norm_path(src.get("path", "")),
                })
                continue
            changes = []
            fields = ["label", "class_hex", "policy", "resource_kind", "expected_name", "resolved", "hit_count"]
            for f in fields:
                if l.get(f, "") != r.get(f, ""):
                    changes.append(f)
            if basename_lower(l.get("resolved_path", "")) != basename_lower(r.get("resolved_path", "")):
                changes.append("resolved_path")
            if changes:
                rows.append({
                    "diff_kind": "+".join(changes),
                    "mission": key[0], "parent_tag": key[1], "index": key[2], "chunk_offset_hex": key[3],
                    f"{left_name}_label": l.get("label", ""),
                    f"{right_name}_label": r.get("label", ""),
                    f"{left_name}_class_hex": l.get("class_hex", ""),
                    f"{right_name}_class_hex": r.get("class_hex", ""),
                    f"{left_name}_policy": l.get("policy", ""),
                    f"{right_name}_policy": r.get("policy", ""),
                    f"{left_name}_expected_name": l.get("expected_name", ""),
                    f"{right_name}_expected_name": r.get("expected_name", ""),
                    f"{left_name}_resolved_path": norm_path(l.get("resolved_path", "")),
                    f"{right_name}_resolved_path": norm_path(r.get("resolved_path", "")),
                    "path_left": norm_path(l.get("path", "")),
                    "path_right": norm_path(r.get("path", "")),
                })
    return rows


def compare_rseg_records(left_rows: List[Dict[str, str]], right_rows: List[Dict[str, str]], left_name: str, right_name: str) -> List[Dict[str, object]]:
    key_fields = ["mission", "rseg_index"]
    lm = multimap(left_rows, key_fields)
    rm = multimap(right_rows, key_fields)
    rows = []
    for key in sorted(set(lm) | set(rm)):
        l = lm.get(key, [None])[0]
        r = rm.get(key, [None])[0]
        if l is None or r is None:
            src = r if l is None else l
            rows.append({"diff_kind": f"only_{right_name}" if l is None else f"only_{left_name}", "mission": key[0], "rseg_index": key[1], "path": norm_path(src.get("path", ""))})
            continue
        changes = []
        for f in ["kind", "count", "payload_size", "expected_payload_size", "size_matches"]:
            if l.get(f, "") != r.get(f, ""):
                changes.append(f)
        if changes:
            rows.append({
                "diff_kind": "+".join(changes), "mission": key[0], "rseg_index": key[1],
                f"{left_name}_kind": l.get("kind", ""), f"{right_name}_kind": r.get("kind", ""),
                f"{left_name}_count": l.get("count", ""), f"{right_name}_count": r.get("count", ""),
                f"{left_name}_payload_size": l.get("payload_size", ""), f"{right_name}_payload_size": r.get("payload_size", ""),
            })
    return rows


def compare_rseg_points(left_rows: List[Dict[str, str]], right_rows: List[Dict[str, str]], left_name: str, right_name: str, max_rows: int) -> List[Dict[str, object]]:
    key_fields = ["mission", "rseg_index", "point_index"]
    lm = multimap(left_rows, key_fields)
    rm = multimap(right_rows, key_fields)
    rows = []
    numeric = ["kind", "left_x", "left_z", "aux_z_or_mid", "right_x", "height_or_y", "right_z", "center_x", "center_z", "width"]
    for key in sorted(set(lm) | set(rm)):
        if len(rows) >= max_rows:
            rows.append({"diff_kind": f"truncated_after_{max_rows}", "mission": "", "rseg_index": "", "point_index": ""})
            break
        l = lm.get(key, [None])[0]
        r = rm.get(key, [None])[0]
        if l is None or r is None:
            src = r if l is None else l
            rows.append({"diff_kind": f"only_{right_name}" if l is None else f"only_{left_name}", "mission": key[0], "rseg_index": key[1], "point_index": key[2], "path": norm_path(src.get("path", ""))})
            continue
        changes = []
        for f in numeric:
            if not float_same(l.get(f, ""), r.get(f, "")):
                changes.append(f)
        if changes:
            rows.append({
                "diff_kind": "+".join(changes), "mission": key[0], "rseg_index": key[1], "point_index": key[2],
                f"{left_name}_center": f"{l.get('center_x','')},{l.get('center_z','')}",
                f"{right_name}_center": f"{r.get('center_x','')},{r.get('center_z','')}",
                f"{left_name}_width": l.get("width", ""), f"{right_name}_width": r.get("width", ""),
            })
    return rows


def inventory_files(root: Path) -> Dict[str, str]:
    out = {}
    for p in root.rglob("*"):
        if p.is_file():
            rel = p.relative_to(root).as_posix()
            # Tables are compared semantically elsewhere; still include generated objs/manifests.
            try:
                stat = p.stat()
                out[rel] = str(stat.st_size)
            except OSError:
                pass
    return out


def compare_file_inventory(left_root: Path, right_root: Path, left_name: str, right_name: str) -> List[Dict[str, object]]:
    li = inventory_files(left_root)
    ri = inventory_files(right_root)
    rows = []
    for rel in sorted(set(li) | set(ri)):
        lsize = li.get(rel)
        rsize = ri.get(rel)
        if lsize is None:
            rows.append({"diff_kind": f"only_{right_name}", "file": rel, f"{left_name}_size": "", f"{right_name}_size": rsize})
        elif rsize is None:
            rows.append({"diff_kind": f"only_{left_name}", "file": rel, f"{left_name}_size": lsize, f"{right_name}_size": ""})
        elif lsize != rsize:
            rows.append({"diff_kind": "size", "file": rel, f"{left_name}_size": lsize, f"{right_name}_size": rsize})
    return rows


def write_notes(path: Path, manifest: Dict[str, object]) -> None:
    lines = []
    lines.append("I76 level reconstruction run comparison")
    lines.append("")
    lines.append(f"left:  {manifest['left']['name']} -> {manifest['left']['root']}")
    lines.append(f"right: {manifest['right']['name']} -> {manifest['right']['root']}")
    lines.append("")
    lines.append("Key counts:")
    for k, v in manifest["comparison_counts"].items():
        lines.append(f"  {k}: {v}")
    lines.append("")
    lines.append("Interpretation guidance:")
    lines.append("  - mission_summary.tsv is the first-pass aggregate check.")
    lines.append("  - object_record_diffs.tsv lists aligned ODEF/LDEF record differences by mission/index/offset.")
    lines.append("  - resource_policy_diffs.tsv shows whether class-specific SDF/VCF policy resolution differs.")
    lines.append("  - rseg_* diffs should usually be empty or near-empty for color-depth-only variants.")
    lines.append("  - absolute paths are normalized so miss8/miss16 directory names do not appear as false diffs.")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def make_tar(out_dir: Path) -> Path:
    tar_path = out_dir.with_suffix(".tar")
    if tar_path.exists():
        tar_path.unlink()
    with tarfile.open(tar_path, "w") as tf:
        tf.add(out_dir, arcname=out_dir.name)
    return tar_path


def main(argv: Optional[Sequence[str]] = None) -> int:
    ap = argparse.ArgumentParser(description="Compare two i76 level reconstruction exporter output dirs/tars.")
    ap.add_argument("--left", required=True, type=Path, help="Left run directory or .tar, e.g. miss8.")
    ap.add_argument("--right", required=True, type=Path, help="Right run directory or .tar, e.g. miss16.")
    ap.add_argument("--left-name", default="left")
    ap.add_argument("--right-name", default="right")
    ap.add_argument("--out-dir", required=True, type=Path)
    ap.add_argument("--run-name", default="miss8_vs_miss16")
    ap.add_argument("--max-rseg-point-diffs", type=int, default=50000)
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args(argv)

    out_dir = args.out_dir / f"i76_compare_level_reconstruction_v8_runs_v1_{args.run_name}_{now_stamp()}"
    mkdirp(out_dir / "tables")
    temp_parent = Path(tempfile.mkdtemp(prefix="i76_compare_v8_"))
    try:
        left = prepare_input(args.left_name, args.left, temp_parent)
        right = prepare_input(args.right_name, args.right, temp_parent)
        lt = load_run_tables(left)
        rt = load_run_tables(right)

        mission_summary = summarize_missions(lt, rt, args.left_name, args.right_name)
        object_diffs = compare_objects(lt["obj"], rt["obj"], args.left_name, args.right_name)
        policy_diffs = compare_resolution(lt["resolution"], rt["resolution"], args.left_name, args.right_name)
        rseg_record_diffs = compare_rseg_records(lt["rseg_records"], rt["rseg_records"], args.left_name, args.right_name)
        rseg_point_diffs = compare_rseg_points(lt["rseg_points"], rt["rseg_points"], args.left_name, args.right_name, args.max_rseg_point_diffs)
        file_diffs = compare_file_inventory(left.root, right.root, args.left_name, args.right_name)

        lf = args.left_name
        rf = args.right_name
        write_tsv(out_dir / "tables" / "mission_summary.tsv", mission_summary, [
            "mission", f"{lf}_objects", f"{rf}_objects", "objects_delta",
            f"{lf}_resolved_sdf", f"{rf}_resolved_sdf", "resolved_sdf_delta",
            f"{lf}_resolved_vcf", f"{rf}_resolved_vcf", "resolved_vcf_delta",
            f"{lf}_rseg_records", f"{rf}_rseg_records", "rseg_records_delta",
            f"{lf}_rseg_points", f"{rf}_rseg_points", "rseg_points_delta",
        ])
        write_tsv(out_dir / "tables" / "object_record_diffs.tsv", object_diffs, [
            "diff_kind", "mission", "parent_tag", "index", "chunk_offset_hex",
            f"{lf}_name", f"{rf}_name", f"{lf}_class_hex", f"{rf}_class_hex",
            f"{lf}_pos", f"{rf}_pos", "pos_changed", "basis_changed", "path_left", "path_right",
        ])
        write_tsv(out_dir / "tables" / "resource_policy_diffs.tsv", policy_diffs, [
            "diff_kind", "mission", "parent_tag", "index", "chunk_offset_hex",
            f"{lf}_label", f"{rf}_label", f"{lf}_class_hex", f"{rf}_class_hex",
            f"{lf}_policy", f"{rf}_policy", f"{lf}_expected_name", f"{rf}_expected_name",
            f"{lf}_resolved_path", f"{rf}_resolved_path", "path_left", "path_right", "path",
        ])
        write_tsv(out_dir / "tables" / "rseg_record_diffs.tsv", rseg_record_diffs, [
            "diff_kind", "mission", "rseg_index", f"{lf}_kind", f"{rf}_kind", f"{lf}_count", f"{rf}_count", f"{lf}_payload_size", f"{rf}_payload_size", "path",
        ])
        write_tsv(out_dir / "tables" / "rseg_point_diffs.tsv", rseg_point_diffs, [
            "diff_kind", "mission", "rseg_index", "point_index", f"{lf}_center", f"{rf}_center", f"{lf}_width", f"{rf}_width", "path",
        ])
        write_tsv(out_dir / "tables" / "file_inventory_diffs.tsv", file_diffs, [
            "diff_kind", "file", f"{lf}_size", f"{rf}_size",
        ])

        manifest = {
            "script": Path(__file__).name,
            "generated_at": datetime.now().isoformat(timespec="seconds"),
            "left": {"name": args.left_name, "input": str(args.left), "root": str(left.root)},
            "right": {"name": args.right_name, "input": str(args.right), "root": str(right.root)},
            "input_counts": {
                args.left_name: {name: len(rows) for name, rows in lt.items()},
                args.right_name: {name: len(rows) for name, rows in rt.items()},
            },
            "comparison_counts": {
                "mission_summary_rows": len(mission_summary),
                "object_record_diff_rows": len(object_diffs),
                "resource_policy_diff_rows": len(policy_diffs),
                "rseg_record_diff_rows": len(rseg_record_diffs),
                "rseg_point_diff_rows": len(rseg_point_diffs),
                "file_inventory_diff_rows": len(file_diffs),
            },
        }
        (out_dir / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        write_notes(out_dir / "notes.txt", manifest)

        tar_path = None
        if args.make_tar:
            tar_path = make_tar(out_dir)
        print(f"wrote: {out_dir}")
        if tar_path:
            print(f"tar:   {tar_path}")
        print("comparison_counts=" + json.dumps(manifest["comparison_counts"], sort_keys=True))
        return 0
    finally:
        shutil.rmtree(temp_parent, ignore_errors=True)


if __name__ == "__main__":
    raise SystemExit(main())
