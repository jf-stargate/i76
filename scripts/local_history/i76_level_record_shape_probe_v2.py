#!/usr/bin/env python3
"""
Interstate '76 level record shape probe, v2.

This is a corpus-side companion to the Ghidra descriptor-table trace.  It does
not claim final semantics.  It extracts the record layouts that are now strongly
suggested by the mission corpus:

  * WRLD fixed-width resource fields at stable offsets.
  * ODEF OBJ records as name[8] + 3x3 float basis + float position + tail bytes.
  * RDEF RSEG records as uint32 kind + uint32 point_count + 24-byte point records.
  * LDEF OBJ records as a wider object/light-like payload for missions that have it.
  * ADEF FSM payload string tokens for missions with non-empty actor scripts.

Outputs TSV/JSON files for correlation with i76.exe descriptor handlers.
"""
from __future__ import annotations

import argparse
import csv
import dataclasses
import json
import math
import os
import re
import struct
import subprocess
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

CONTAINERS = {"BWD2", "WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}
TOP_SECTIONS = {"WDEF", "TDEF", "RDEF", "ODEF", "LDEF", "ADEF"}

WRLD_FIELDS = [
    (30, 13, "palette_act"),
    (43, 13, "luma_lum"),
    (56, 13, "translucency_tbl"),
    (69, 13, "objective_npt"),
    (82, 13, "sky_texture"),
    (95, 13, "scrounge_or_screen_sdf"),
    (108, 13, "surface_texture"),
    (121, 13, "level_map_texture"),
    (134, 13, "hazard_hzd"),
]


def u32(data: bytes, off: int) -> int:
    return struct.unpack_from("<I", data, off)[0]


def f32(data: bytes, off: int) -> float:
    return struct.unpack_from("<f", data, off)[0]


def fourcc(data: bytes, off: int) -> str:
    return data[off:off + 4].decode("ascii", errors="replace")


@dataclasses.dataclass
class Chunk:
    tag: str
    offset: int
    size: int
    payload_offset: int
    payload_size: int
    parent: str = ""

    @property
    def end(self) -> int:
        return self.offset + self.size


def parse_flat(data: bytes, start: int, end: int, parent: str) -> List[Chunk]:
    out: List[Chunk] = []
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

    def rec(chunks: List[Chunk]) -> List[Chunk]:
        out: List[Chunk] = []
        for c in chunks:
            out.append(c)
            if c.tag in CONTAINERS and c.payload_size >= 8:
                out.extend(rec(parse_flat(data, c.payload_offset, c.end, c.tag)))
        return out

    return rec(roots)


def clean_cstr(raw: bytes) -> str:
    s = raw.split(b"\0", 1)[0]
    return s.decode("ascii", errors="replace").strip()


def sane_float(x: float) -> str:
    if not math.isfinite(x):
        return "nan"
    return f"{x:.9g}"


def mission_files(root: Path) -> List[Path]:
    return sorted([p for p in root.rglob("*") if p.is_file() and p.suffix.lower() in {".msn", ".spc", ".lvl"}])


def write_tsv(path: Path, fieldnames: List[str], rows: Iterable[dict]) -> int:
    path.parent.mkdir(parents=True, exist_ok=True)
    n = 0
    with path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, delimiter="\t", extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)
            n += 1
    return n


def payload(data: bytes, c: Chunk) -> bytes:
    return data[c.payload_offset:c.end]


def section_payload(data: bytes, chunks: List[Chunk], section: str) -> Optional[bytes]:
    for c in chunks:
        if c.parent == "" and c.tag == section:
            return payload(data, c)
    return None


def nested_chunks(chunks: List[Chunk], parent: str, tag: Optional[str] = None) -> List[Chunk]:
    return [c for c in chunks if c.parent == parent and (tag is None or c.tag == tag)]


def decode_wrld_rows(corpus: str, msn: Path, data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows: List[dict] = []
    for c in nested_chunks(chunks, "WDEF", "WRLD"):
        p = payload(data, c)
        rev = u32(p, 0) if len(p) >= 4 else None
        for off, width, name in WRLD_FIELDS:
            val = clean_cstr(p[off:off + width]) if off + width <= len(p) else ""
            rows.append({
                "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(),
                "wrld_chunk_offset": f"0x{c.offset:08x}", "wrld_payload_size": len(p),
                "wrld_revision_or_flags": rev if rev is not None else "",
                "field": name, "payload_offset": off, "width": width, "value": val,
            })
    return rows


def decode_odef_obj_rows(corpus: str, msn: Path, data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows: List[dict] = []
    for idx, c in enumerate(nested_chunks(chunks, "ODEF", "OBJ\0")):
        p = payload(data, c)
        if len(p) < 56:
            continue
        name = clean_cstr(p[0:8])
        basis = [f32(p, 8 + i * 4) for i in range(9)]
        pos = [f32(p, 44 + i * 4) for i in range(3)]
        tail = p[56:]
        # Tail as u32s helps identify parent/index/flags fields later.
        tail_u32 = []
        for off in range(0, min(len(tail), 44), 4):
            if off + 4 <= len(tail):
                tail_u32.append(f"{u32(tail, off):08x}")
        rows.append({
            "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(), "index": idx,
            "chunk_offset": f"0x{c.offset:08x}", "chunk_size": c.size, "payload_size": len(p),
            "name8": name,
            "basis00": sane_float(basis[0]), "basis01": sane_float(basis[1]), "basis02": sane_float(basis[2]),
            "basis10": sane_float(basis[3]), "basis11": sane_float(basis[4]), "basis12": sane_float(basis[5]),
            "basis20": sane_float(basis[6]), "basis21": sane_float(basis[7]), "basis22": sane_float(basis[8]),
            "pos_x": sane_float(pos[0]), "pos_y": sane_float(pos[1]), "pos_z": sane_float(pos[2]),
            "tail_u32_hex": " ".join(tail_u32),
            "tail_ascii": re.sub(r"[^ -~]", ".", tail[:44].decode("latin1", errors="replace")),
        })
    return rows


def decode_rdef_rseg_rows(corpus: str, msn: Path, data: bytes, chunks: List[Chunk]) -> Tuple[List[dict], List[dict]]:
    seg_rows: List[dict] = []
    point_rows: List[dict] = []
    for seg_idx, c in enumerate(nested_chunks(chunks, "RDEF", "RSEG")):
        p = payload(data, c)
        if len(p) < 8:
            continue
        kind = u32(p, 0)
        count = u32(p, 4)
        remaining = len(p) - 8
        stride24_ok = remaining == count * 24
        stride16_ok = remaining == count * 16
        seg_rows.append({
            "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(), "segment_index": seg_idx,
            "chunk_offset": f"0x{c.offset:08x}", "chunk_size": c.size, "payload_size": len(p),
            "kind_u32": kind, "count_u32": count, "remaining_bytes": remaining,
            "stride24_ok": stride24_ok, "stride16_ok": stride16_ok,
        })
        if stride24_ok:
            for i in range(min(count, 16)):  # sample first 16 points per segment, enough for layout inference.
                off = 8 + i * 24
                vals = [f32(p, off + j * 4) for j in range(6)]
                point_rows.append({
                    "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(), "segment_index": seg_idx,
                    "point_index": i, "chunk_offset": f"0x{c.offset:08x}",
                    "f0": sane_float(vals[0]), "f1": sane_float(vals[1]), "f2": sane_float(vals[2]),
                    "f3": sane_float(vals[3]), "f4": sane_float(vals[4]), "f5": sane_float(vals[5]),
                })
    return seg_rows, point_rows


def decode_ldef_obj_rows(corpus: str, msn: Path, data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows: List[dict] = []
    for idx, c in enumerate(nested_chunks(chunks, "LDEF", "OBJ\0")):
        p = payload(data, c)
        name = clean_cstr(p[0:16]) if p else ""
        floats = []
        for off in range(0, min(len(p), 96), 4):
            floats.append(sane_float(f32(p, off)))
        rows.append({
            "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(), "index": idx,
            "chunk_offset": f"0x{c.offset:08x}", "chunk_size": c.size, "payload_size": len(p),
            "name_guess": name,
            "first_24_floats": " ".join(floats[:24]),
            "ascii_preview": re.sub(r"[^ -~]", ".", p[:96].decode("latin1", errors="replace")),
        })
    return rows


def decode_adef_fsm_rows(corpus: str, msn: Path, data: bytes, chunks: List[Chunk]) -> List[dict]:
    rows: List[dict] = []
    for c in nested_chunks(chunks, "ADEF", "FSM\0"):
        p = payload(data, c)
        strings = []
        for m in re.finditer(rb"[A-Za-z_][A-Za-z0-9_]{2,31}", p):
            s = m.group(0).decode("ascii", errors="replace")
            strings.append((m.start(), s))
        for off, s in strings[:256]:
            rows.append({
                "corpus": corpus, "mission": msn.name, "stem": msn.stem.lower(),
                "fsm_chunk_offset": f"0x{c.offset:08x}", "payload_size": len(p),
                "string_offset": off, "string": s,
            })
    return rows


def run(args: argparse.Namespace) -> dict:
    inputs = []
    if args.miss8:
        inputs.append(("miss8", args.miss8))
    if args.miss16:
        inputs.append(("miss16", args.miss16))
    if not inputs:
        inputs.append(("input", args.input))

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)

    wrld_rows: List[dict] = []
    odef_rows: List[dict] = []
    rseg_rows: List[dict] = []
    rpoint_rows: List[dict] = []
    ldef_rows: List[dict] = []
    fsm_rows: List[dict] = []

    mission_count = 0
    warnings: List[str] = []

    for corpus, root in inputs:
        for msn in mission_files(root):
            if args.mission_filter and args.mission_filter.lower() not in msn.name.lower() and args.mission_filter.lower() not in msn.stem.lower():
                continue
            mission_count += 1
            try:
                data = msn.read_bytes()
                chunks = parse_tree(data)
                wrld_rows.extend(decode_wrld_rows(corpus, msn, data, chunks))
                odef_rows.extend(decode_odef_obj_rows(corpus, msn, data, chunks))
                sr, pr = decode_rdef_rseg_rows(corpus, msn, data, chunks)
                rseg_rows.extend(sr)
                rpoint_rows.extend(pr)
                ldef_rows.extend(decode_ldef_obj_rows(corpus, msn, data, chunks))
                fsm_rows.extend(decode_adef_fsm_rows(corpus, msn, data, chunks))
            except Exception as e:
                warnings.append(f"{corpus}:{msn}: {type(e).__name__}: {e}")

    outputs = {}
    outputs["wrld_fixed_fields.tsv"] = write_tsv(out / "wrld_fixed_fields.tsv", ["corpus","mission","stem","wrld_chunk_offset","wrld_payload_size","wrld_revision_or_flags","field","payload_offset","width","value"], wrld_rows)
    outputs["odef_obj_transform_probe.tsv"] = write_tsv(out / "odef_obj_transform_probe.tsv", ["corpus","mission","stem","index","chunk_offset","chunk_size","payload_size","name8","basis00","basis01","basis02","basis10","basis11","basis12","basis20","basis21","basis22","pos_x","pos_y","pos_z","tail_u32_hex","tail_ascii"], odef_rows)
    outputs["rdef_rseg_header_probe.tsv"] = write_tsv(out / "rdef_rseg_header_probe.tsv", ["corpus","mission","stem","segment_index","chunk_offset","chunk_size","payload_size","kind_u32","count_u32","remaining_bytes","stride24_ok","stride16_ok"], rseg_rows)
    outputs["rdef_rseg_point_sample.tsv"] = write_tsv(out / "rdef_rseg_point_sample.tsv", ["corpus","mission","stem","segment_index","point_index","chunk_offset","f0","f1","f2","f3","f4","f5"], rpoint_rows)
    outputs["ldef_obj_probe_v2.tsv"] = write_tsv(out / "ldef_obj_probe_v2.tsv", ["corpus","mission","stem","index","chunk_offset","chunk_size","payload_size","name_guess","first_24_floats","ascii_preview"], ldef_rows)
    outputs["adef_fsm_string_tokens.tsv"] = write_tsv(out / "adef_fsm_string_tokens.tsv", ["corpus","mission","stem","fsm_chunk_offset","payload_size","string_offset","string"], fsm_rows)

    manifest = {
        "format": "i76_level_record_shape_probe",
        "version": 2,
        "inputs": [str(p) for _, p in inputs],
        "mission_filter": args.mission_filter,
        "mission_count": mission_count,
        "outputs": outputs,
        "warnings": warnings,
        "notes": [
            "ODEF OBJ decode is a record-shape probe: name[8], 9 floats, 3 position floats, then tail fields.",
            "RDEF RSEG decode is a record-shape probe: u32 kind, u32 count, then apparent 24-byte point records.",
            "LDEF/ADEF probes are not final semantic decodes."
        ],
    }
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")

    if args.make_tar:
        tar_path = out.with_suffix(".tar")
        subprocess.run(["tar", "-cf", str(tar_path), "-C", str(out.parent), out.name], check=False)

    print(json.dumps({"out_dir": str(out), "mission_count": mission_count, "outputs": outputs, "warnings": len(warnings)}, indent=2))
    if args.fail_empty and mission_count == 0:
        raise SystemExit("no missions processed")
    return manifest


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", nargs="?", type=Path, help="single mission root, unless --miss8/--miss16 are used")
    ap.add_argument("--miss8", type=Path)
    ap.add_argument("--miss16", type=Path)
    ap.add_argument("--out-dir", type=Path, required=True)
    ap.add_argument("--mission-filter", default="")
    ap.add_argument("--make-tar", action="store_true")
    ap.add_argument("--fail-empty", action="store_true")
    args = ap.parse_args()
    if not args.input and not (args.miss8 or args.miss16):
        ap.error("provide input or --miss8/--miss16")
    run(args)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
