#!/usr/bin/env python3
"""
Interstate '76 resource acquisition index probe v9.

Binary-truth policy:
  ODEF dispatch-valid record -> label.vcf
  LDEF OBJ/string record       -> label.sdf
  ODEF spawn/regen             -> special markers
  ODEF blank/class0            -> invalid/special diagnostic rows

v9 changes:
  * Treat full-corpus as normal; --mission-filter remains optional.
  * Distinguish real loose-file matches from manifest/index text hits.
  * Exclude .json/.tsv/.md/.txt report files from container byte scanning by default.
  * Parse zfs_records.tsv / zfs_extract_manifest.json when present and report archive-record
    matches separately from loose-file matches.
  * Keep Open76 ODEF .sdf comparison rows separate and diagnostic-only.
"""

from __future__ import annotations

import argparse, csv, dataclasses, hashlib, json, os, re, struct, tarfile
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple, Set

PAGE_W = 128

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""
    @property
    def end(self) -> int: return self.offset + self.size

def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]

def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]

def fourcc(data: bytes, off: int) -> str:
    return data[off:off+4].decode("ascii", errors="replace")

def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out = []
    off = start
    while off + 8 <= end:
        tag = fourcc(data, off)
        size = u32(data, off + 4)
        if size < 8 or off + size > end:
            break
        out.append(Chunk(tag, off, size, off + 8, size - 8, parent))
        off += size
    return out

def parse_tree(data: bytes) -> List[Chunk]:
    roots = parse_flat(data, 0, len(data), "")
    out: List[Chunk] = []
    def rec(chs: List[Chunk]) -> None:
        for c in chs:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                kids = parse_flat(data, c.payload_offset, c.end, c.tag)
                if kids: rec(kids)
    rec(roots)
    return out

def label8(raw: bytes) -> Tuple[str, int]:
    s = []
    high = 0
    for i, b in enumerate(raw[:8]):
        if b == 0: break
        if b & 0x80:
            high |= (1 << i)
        c = b & 0x7f
        if c == 0: break
        s.append(chr(c))
    return "".join(s).strip(), high

@dataclasses.dataclass
class ObjRec:
    corpus: str
    mission: str
    offset_hex: str
    parent: str
    label: str
    highbits: int
    cls: int
    pos_x: float
    pos_y: float
    pos_z: float

def decode_odef_obj(data: bytes, c: Chunk, corpus: str, mission: str) -> Optional[ObjRec]:
    if c.parent != "ODEF" or c.tag != "OBJ\x00" or c.payload_size < 0x64:
        return None
    p = c.payload_offset
    label, high = label8(data[p:p+8])
    cls = data[p+0x5c] if p+0x5c < c.end else 0
    return ObjRec(corpus, mission, f"0x{c.offset:08x}", "ODEF", label, high, cls, f32(data,p+0x2c), f32(data,p+0x30), f32(data,p+0x34))

def decode_ldef_obj(data: bytes, c: Chunk, corpus: str, mission: str) -> Optional[ObjRec]:
    if c.parent != "LDEF" or c.tag != "OBJ\x00" or c.payload_size < 8:
        return None
    p = c.payload_offset
    label, high = label8(data[p:p+8])
    return ObjRec(corpus, mission, f"0x{c.offset:08x}", "LDEF", label, high, -1, 0.0, 0.0, 0.0)

def find_files(root: Path) -> List[Path]:
    if not root.exists():
        return []
    if root.is_file():
        return [root]
    return [p for p in root.rglob("*") if p.is_file()]

@dataclasses.dataclass
class AssetIndex:
    by_name: Dict[str,List[Path]]
    all_files: List[Path]
    record_names: Set[str]
    record_sources: Dict[str,List[str]]

def build_asset_index(roots: List[Path]) -> AssetIndex:
    by_name: Dict[str,List[Path]] = {}
    all_files: List[Path] = []
    record_names: Set[str] = set()
    record_sources: Dict[str,List[str]] = {}

    for root in roots:
        for p in find_files(root):
            all_files.append(p)
            by_name.setdefault(p.name.lower(), []).append(p)

    # Parse known extraction records if available.
    for p in all_files:
        lname = p.name.lower()
        try:
            if lname == "zfs_records.tsv":
                with p.open("r", encoding="utf-8", errors="replace", newline="") as f:
                    r = csv.DictReader(f, delimiter="\t")
                    for row in r:
                        # Try common column names from previous extractors.
                        nm = (row.get("name") or row.get("record_name") or row.get("filename") or row.get("path") or "").strip()
                        if nm:
                            key = Path(nm).name.lower()
                            record_names.add(key)
                            record_sources.setdefault(key, []).append(str(p))
            elif lname == "zfs_extract_manifest.json":
                j = json.loads(p.read_text(encoding="utf-8", errors="replace"))
                stack = [j]
                while stack:
                    x = stack.pop()
                    if isinstance(x, dict):
                        for k, v in x.items():
                            if k.lower() in {"name","record_name","filename","path","output","resource"} and isinstance(v, str):
                                bn = Path(v).name.lower()
                                if "." in bn:
                                    record_names.add(bn)
                                    record_sources.setdefault(bn, []).append(str(p))
                            else:
                                stack.append(v)
                    elif isinstance(x, list):
                        stack.extend(x)
        except Exception:
            pass

    return AssetIndex(by_name, all_files, record_names, record_sources)

def candidate_for(rec: ObjRec) -> Tuple[str,str]:
    if rec.parent == "ODEF":
        if not rec.label or rec.cls == 0:
            return "odef_invalid_or_special_blank_class0", ""
        if rec.label.lower() == "spawn":
            return "odef_spawn_marker", ""
        if rec.label.lower() == "regen":
            return "odef_regen_marker", ""
        return "binary_odef_vcf", rec.label + ".vcf"
    if rec.parent == "LDEF":
        if not rec.label:
            return "ldef_blank", ""
        return "binary_ldef_sdf", rec.label + ".sdf"
    return "unknown", ""

def sha1_64k(p: Path) -> str:
    h = hashlib.sha1()
    with p.open("rb") as f:
        h.update(f.read(65536))
    return h.hexdigest()[:16]

def write_tsv(path: Path, rows: Iterable[dict], fieldnames: List[str]) -> int:
    rows = list(rows)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)
    return len(rows)

def scan_containers(files: List[Path], candidates: Set[str], max_bytes: int, include_reports: bool) -> List[dict]:
    report_exts = {".json",".tsv",".csv",".txt",".md",".html",".log"}
    container_exts = {".pak",".pix",".zfs",".zix",".dat",".mw2",".res",".bin"}
    rows = []
    lower_cands = {c.lower() for c in candidates if c}
    base_cands = {Path(c).stem.lower() for c in candidates if c}
    for p in files:
        ext = p.suffix.lower()
        if not include_reports:
            if ext in report_exts:
                continue
        if ext not in container_exts and p.stat().st_size < 1024*1024:
            # Avoid scanning every loose resource as a "container"; direct matches are indexed elsewhere.
            continue
        try:
            data = p.read_bytes()
            if max_bytes and len(data) > max_bytes:
                data = data[:max_bytes]
            low = data.lower()
            for cand in sorted(lower_cands | base_cands):
                b = cand.encode("ascii", errors="ignore")
                if not b or len(b) < 4:
                    continue
                off = low.find(b)
                if off >= 0:
                    rows.append({"candidate": cand, "container": str(p), "offset": off, "offset_hex": f"0x{off:x}", "container_size": p.stat().st_size, "scan_kind": "binary_container_scan"})
        except Exception:
            continue
    return rows

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--miss8", type=Path, required=True)
    ap.add_argument("--miss16", type=Path, required=True)
    ap.add_argument("--asset-root", type=Path, action="append", required=True)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--scan-containers", action="store_true")
    ap.add_argument("--include-report-file-container-scan", action="store_true")
    ap.add_argument("--max-container-bytes", type=int, default=0, help="0 = scan whole file")
    ap.add_argument("--make-tar", action="store_true")
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)
    idx = build_asset_index(args.asset_root)

    records: List[ObjRec] = []
    for corpus, root in [("miss8", args.miss8), ("miss16", args.miss16)]:
        for p in sorted(find_files(root)):
            if p.suffix.lower() not in {".msn",".spc",".lvl"}:
                continue
            if args.mission_filter and args.mission_filter.lower() not in p.name.lower() and args.mission_filter.lower() not in p.stem.lower():
                continue
            data = p.read_bytes()
            chunks = parse_tree(data)
            for c in chunks:
                if c.tag == "OBJ\x00" and c.parent == "ODEF":
                    r = decode_odef_obj(data,c,corpus,p.name)
                    if r: records.append(r)
                elif c.tag == "OBJ\x00" and c.parent == "LDEF":
                    r = decode_ldef_obj(data,c,corpus,p.name)
                    if r: records.append(r)

    cand_rows=[]; match_rows=[]; unres_rows=[]; zfs_record_rows=[]; alt_rows=[]; open_rows=[]
    candidate_names=set()
    for r in records:
        policy, cand = candidate_for(r)
        base = {
            "corpus": r.corpus, "mission": r.mission, "chunk_offset_hex": r.offset_hex,
            "parent": r.parent, "label": r.label, "label_highbits": r.highbits,
            "class_hex": "" if r.cls < 0 else f"0x{r.cls:02x}",
            "policy": policy, "candidate_name": cand,
            "pos_x": f"{r.pos_x:.6f}", "pos_y": f"{r.pos_y:.6f}", "pos_z": f"{r.pos_z:.6f}",
        }
        cand_rows.append(base)
        if cand:
            candidate_names.add(cand)
            loose = idx.by_name.get(cand.lower(), [])
            rec_hit = cand.lower() in idx.record_names
            if loose:
                for p in loose:
                    row = dict(base)
                    row.update({"matched_path": str(p), "matched_ext": p.suffix.lower(), "size": p.stat().st_size, "sha1_64k": sha1_64k(p), "match_kind": "loose_file"})
                    match_rows.append(row)
            elif rec_hit:
                row = dict(base)
                row.update({"record_name": cand.lower(), "record_sources": ";".join(idx.record_sources.get(cand.lower(), [])), "match_kind": "zfs_record_index"})
                zfs_record_rows.append(row)
            else:
                unres_rows.append(base)
            stem = Path(cand).stem.lower()
            for key, paths in idx.by_name.items():
                if Path(key).stem.lower() == stem and key != cand.lower():
                    for p in paths:
                        row=dict(base)
                        row.update({"alternative_name": key, "alternative_path": str(p), "alternative_ext": p.suffix.lower(), "alternative_size": p.stat().st_size, "diagnostic_only": "true"})
                        alt_rows.append(row)
        else:
            unres_rows.append(base)

        if r.parent == "ODEF" and r.label and r.cls != 0 and r.label.lower() not in {"spawn","regen"}:
            ocand = r.label + ".sdf"
            paths = idx.by_name.get(ocand.lower(), [])
            row = dict(base)
            row.update({"comparison_policy": "open76_odef_sdf_comparison_only", "open76_candidate_name": ocand, "found_count": len(paths), "matched_paths": ";".join(str(p) for p in paths)})
            open_rows.append(row)

    write_tsv(out/"binary_candidate_names.tsv", cand_rows, ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","pos_x","pos_y","pos_z"])
    write_tsv(out/"binary_resource_matches.tsv", match_rows, ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","matched_path","matched_ext","size","sha1_64k","match_kind"])
    write_tsv(out/"binary_zfs_record_index_matches.tsv", zfs_record_rows, ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","record_name","record_sources","match_kind"])
    write_tsv(out/"binary_resource_unresolved.tsv", unres_rows, ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","pos_x","pos_y","pos_z"])
    write_tsv(out/"basename_alternative_matches.tsv", alt_rows, ["corpus","mission","chunk_offset_hex","parent","label","label_highbits","class_hex","policy","candidate_name","alternative_name","alternative_path","alternative_ext","alternative_size","diagnostic_only"])
    write_tsv(out/"open76_comparison_odef_sdf.tsv", open_rows, ["corpus","mission","chunk_offset_hex","label","class_hex","comparison_policy","open76_candidate_name","found_count","matched_paths"])

    inv = []
    ext_counts: Dict[str,int] = {}
    for p in idx.all_files:
        ext_counts[p.suffix.lower() or "<none>"] = ext_counts.get(p.suffix.lower() or "<none>",0)+1
    for ext, count in sorted(ext_counts.items()):
        inv.append({"extension": ext, "count": count})
    write_tsv(out/"asset_extension_inventory.tsv", inv, ["extension","count"])

    container_rows=[]
    if args.scan_containers:
        container_rows = scan_containers(idx.all_files, candidate_names, args.max_container_bytes, args.include_report_file_container_scan)
    write_tsv(out/"container_name_hits.tsv", container_rows, ["candidate","container","offset","offset_hex","container_size","scan_kind"])

    manifest = {
        "format": "i76_resource_acquisition_index_probe",
        "version": 9,
        "mission_filter": args.mission_filter,
        "asset_roots": [str(p) for p in args.asset_root],
        "indexed_files": len(idx.all_files),
        "zfs_record_names_indexed": len(idx.record_names),
        "object_records": len(records),
        "binary_candidates": len(cand_rows),
        "binary_loose_file_matches": len(match_rows),
        "binary_zfs_record_index_matches": len(zfs_record_rows),
        "binary_unresolved": len(unres_rows),
        "basename_alternatives": len(alt_rows),
        "open76_comparison_rows": len(open_rows),
        "container_hits": len(container_rows),
        "policy": "ODEF label.vcf; LDEF label.sdf; spawn/regen special; Open76 ODEF label.sdf comparison-only",
        "container_scan_note": "By default v9 excludes report files such as .json/.tsv from byte scans to avoid false positives from extraction manifests."
    }
    (out/"manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = out.with_suffix(".tar")
        with tarfile.open(tar_path, "w") as tf:
            tf.add(out, arcname=out.name)
    print(json.dumps(manifest, indent=2))
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
