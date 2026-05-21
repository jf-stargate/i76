#!/usr/bin/env python3
"""
Bounded palette scanner for Interstate '76 / MW2-style DATABASE.MW2 packs.

This replaces an intentionally broad first-pass scanner that could emit hundreds
of thousands of sliding-window candidates. This version ranks candidates first and
only writes a capped set of high-confidence palette files.

DATABASE.MW2 container:
    u32 record_count
    u32 record_offsets[record_count]   # absolute offsets from file start
    record data...

Palette candidates considered:
    - Whole-record or near-header RGB triplets: 768 bytes, likely VGA 6-bit or 8-bit.
    - Whole-record/near-header RGBA/BGRA quads: 1024 bytes.
    - RIFF PAL / LOGPALETTE-like structures.
    - Optional sparse embedded scan, stride-limited and capped.

Outputs:
    summary.json
    records.tsv
    palette_candidates.tsv
    top_candidates.tsv
    palettes/*.pal
    palettes/*_vga6_scaled_rgb768.pal where appropriate
"""

from __future__ import annotations

import argparse
import json
import math
import os
import struct
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Iterable, List, Optional, Sequence, Tuple


@dataclass
class Record:
    record_id: int
    start: int
    end: int
    size: int
    data: bytes


@dataclass
class Candidate:
    record_id: int
    offset: int
    kind: str
    byte_len: int
    order: str
    score: float
    max_channel: int
    min_channel: int
    unique_colors: int
    grayish_fraction: float
    zero_fraction: float
    monotonic_run_score: float
    reason: str
    emit_name: str = ""


def read_u32le(buf: bytes, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def load_database(path: Path) -> List[Record]:
    blob = path.read_bytes()
    if len(blob) < 8:
        raise ValueError("File too small for DATABASE.MW2 header")
    count = read_u32le(blob, 0)
    table_end = 4 + count * 4
    if count <= 0 or count > 100000 or table_end > len(blob):
        raise ValueError(f"Implausible record count/table: count={count}, table_end={table_end:#x}")
    offsets = [read_u32le(blob, 4 + i * 4) for i in range(count)]
    if any(o < table_end or o > len(blob) for o in offsets):
        raise ValueError("One or more record offsets are outside the file or before table end")
    records: List[Record] = []
    for i, start in enumerate(offsets):
        end = offsets[i + 1] if i + 1 < count else len(blob)
        if end < start:
            raise ValueError(f"Record offsets are not monotonic at record {i + 1}")
        records.append(Record(i + 1, start, end, end - start, blob[start:end]))
    return records


def parse_palette_triplets(buf: bytes, offset: int, order: str = "RGB") -> Optional[List[Tuple[int, int, int]]]:
    if offset < 0 or offset + 768 > len(buf):
        return None
    out = []
    chunk = buf[offset:offset + 768]
    for i in range(0, 768, 3):
        a, b, c = chunk[i], chunk[i + 1], chunk[i + 2]
        if order == "RGB":
            out.append((a, b, c))
        elif order == "BGR":
            out.append((c, b, a))
        else:
            raise ValueError(order)
    return out


def parse_palette_quads(buf: bytes, offset: int, order: str = "RGBA") -> Optional[List[Tuple[int, int, int]]]:
    if offset < 0 or offset + 1024 > len(buf):
        return None
    out = []
    chunk = buf[offset:offset + 1024]
    for i in range(0, 1024, 4):
        a, b, c, d = chunk[i], chunk[i + 1], chunk[i + 2], chunk[i + 3]
        if order == "RGBA":
            out.append((a, b, c))
        elif order == "BGRA":
            out.append((c, b, a))
        else:
            raise ValueError(order)
    return out


def score_palette(colors: Sequence[Tuple[int, int, int]], kind: str, reason: str) -> Tuple[float, dict]:
    flat = [v for rgb in colors for v in rgb]
    max_ch = max(flat) if flat else 0
    min_ch = min(flat) if flat else 0
    unique = len(set(colors))
    zero_frac = sum(1 for v in flat if v == 0) / max(1, len(flat))
    grayish = sum(1 for r, g, b in colors if max(r, g, b) - min(r, g, b) <= 2) / max(1, len(colors))

    # Common old-game palette sources are 6-bit VGA DAC values, then shifted <<2 by runtime code.
    likely_vga6 = max_ch <= 63 and unique >= 16
    likely_8bit = max_ch > 63 and unique >= 16

    # Penalize data that is mostly zeros/repetition. UI palettes can have ramps, but not 95% zero.
    score = 0.0
    if likely_vga6:
        score += 45.0
    if likely_8bit:
        score += 25.0
    score += min(unique, 256) / 256.0 * 30.0
    score += (1.0 - min(zero_frac, 0.9)) * 15.0
    if grayish < 0.85:
        score += 8.0
    if kind in ("rgb768", "bgr768"):
        score += 10.0
    if "whole_record" in reason:
        score += 18.0
    if "near_header" in reason:
        score += 10.0
    if "riff_pal" in reason or "logpalette" in reason:
        score += 25.0

    # Very low-entropy windows are nearly always false positives.
    if unique < 8:
        score -= 50.0
    if zero_frac > 0.80:
        score -= 35.0

    # Cheap monotonic/ramp heuristic: many palettes include gradients but should not be pure binary noise.
    diffs = []
    for (r0, g0, b0), (r1, g1, b1) in zip(colors, colors[1:]):
        diffs.append(abs(r1 - r0) + abs(g1 - g0) + abs(b1 - b0))
    if diffs:
        medianish = sorted(diffs)[len(diffs) // 2]
        ramp_score = 1.0 / (1.0 + medianish / 32.0)
    else:
        ramp_score = 0.0
    score += ramp_score * 5.0

    return score, {
        "max_channel": max_ch,
        "min_channel": min_ch,
        "unique_colors": unique,
        "grayish_fraction": grayish,
        "zero_fraction": zero_frac,
        "monotonic_run_score": ramp_score,
    }


def make_candidate(record: Record, offset: int, kind: str, order: str, colors: Sequence[Tuple[int, int, int]], reason: str) -> Candidate:
    score, stats = score_palette(colors, kind, reason)
    return Candidate(
        record_id=record.record_id,
        offset=offset,
        kind=kind,
        byte_len=768 if "768" in kind else 1024,
        order=order,
        score=score,
        max_channel=stats["max_channel"],
        min_channel=stats["min_channel"],
        unique_colors=stats["unique_colors"],
        grayish_fraction=stats["grayish_fraction"],
        zero_fraction=stats["zero_fraction"],
        monotonic_run_score=stats["monotonic_run_score"],
        reason=reason,
    )


def candidate_offsets_for_record(size: int, embedded_stride: int, embedded_max_offsets: int) -> List[Tuple[int, str]]:
    offsets: List[Tuple[int, str]] = []
    fixed = [0, 4, 8, 12, 16, 24, 32, 64, 80, 96, 128]
    for off in fixed:
        if off < size:
            label = "whole_record" if off == 0 and size in (768, 1024) else "near_header"
            offsets.append((off, label))
    # Conservative embedded search. No byte-by-byte sliding. Capped per record.
    if embedded_stride > 0 and size >= 768:
        count = 0
        for off in range(0, size - 767, embedded_stride):
            if off in fixed:
                continue
            offsets.append((off, f"embedded_stride_{embedded_stride}"))
            count += 1
            if count >= embedded_max_offsets:
                break
    # Deduplicate preserving first reason.
    seen = set()
    out = []
    for off, why in offsets:
        if off not in seen:
            seen.add(off)
            out.append((off, why))
    return out


def find_riff_pal_candidates(record: Record) -> List[Candidate]:
    data = record.data
    out: List[Candidate] = []
    # RIFF....PAL data usually contains 'data' chunk with LOGPALETTE-ish entries.
    search_pos = 0
    while True:
        idx = data.find(b"RIFF", search_pos)
        if idx < 0:
            break
        if idx + 12 <= len(data) and data[idx + 8:idx + 12] == b"PAL ":
            data_idx = data.find(b"data", idx + 12)
            if data_idx >= 0 and data_idx + 8 <= len(data):
                chunk_size = read_u32le(data, data_idx + 4)
                payload = data_idx + 8
                # LOGPALETTE-ish: version u16, count u16, then PALETTEENTRY BGRA/RGBA? Usually RGB flags after.
                if payload + 4 + 256 * 4 <= len(data):
                    colors_rgba = parse_palette_quads(data, payload + 4, "RGBA")
                    colors_bgra = parse_palette_quads(data, payload + 4, "BGRA")
                    if colors_rgba:
                        out.append(make_candidate(record, payload + 4, "rgba1024", "RGBA", colors_rgba, "riff_pal_logpalette"))
                    if colors_bgra:
                        out.append(make_candidate(record, payload + 4, "bgra1024", "BGRA", colors_bgra, "riff_pal_logpalette"))
        search_pos = idx + 4
    return out


def collect_candidates(records: Sequence[Record], args: argparse.Namespace) -> List[Candidate]:
    candidates: List[Candidate] = []
    for rec in records:
        if args.records and rec.record_id not in args.records:
            continue
        candidates.extend(find_riff_pal_candidates(rec))
        for off, reason in candidate_offsets_for_record(rec.size, args.embedded_stride, args.embedded_max_offsets_per_record):
            if off + 768 <= rec.size:
                rgb = parse_palette_triplets(rec.data, off, "RGB")
                bgr = parse_palette_triplets(rec.data, off, "BGR")
                if rgb:
                    candidates.append(make_candidate(rec, off, "rgb768", "RGB", rgb, reason))
                if bgr:
                    candidates.append(make_candidate(rec, off, "bgr768", "BGR", bgr, reason))
            if off + 1024 <= rec.size:
                rgba = parse_palette_quads(rec.data, off, "RGBA")
                bgra = parse_palette_quads(rec.data, off, "BGRA")
                if rgba:
                    candidates.append(make_candidate(rec, off, "rgba1024", "RGBA", rgba, reason))
                if bgra:
                    candidates.append(make_candidate(rec, off, "bgra1024", "BGRA", bgra, reason))
    candidates.sort(key=lambda c: c.score, reverse=True)
    return candidates


def extract_colors(record: Record, c: Candidate) -> List[Tuple[int, int, int]]:
    if c.kind == "rgb768":
        return parse_palette_triplets(record.data, c.offset, "RGB") or []
    if c.kind == "bgr768":
        return parse_palette_triplets(record.data, c.offset, "BGR") or []
    if c.kind == "rgba1024":
        return parse_palette_quads(record.data, c.offset, "RGBA") or []
    if c.kind == "bgra1024":
        return parse_palette_quads(record.data, c.offset, "BGRA") or []
    return []


def write_rgb768(path: Path, colors: Sequence[Tuple[int, int, int]], scale_vga6: bool = False) -> None:
    out = bytearray()
    for r, g, b in colors[:256]:
        if scale_vga6:
            r = min(255, int(r) * 4)
            g = min(255, int(g) * 4)
            b = min(255, int(b) * 4)
        out.extend([r & 0xff, g & 0xff, b & 0xff])
    while len(out) < 768:
        out.extend([0, 0, 0])
    path.write_bytes(bytes(out[:768]))


def write_tsv(path: Path, rows: Iterable[Sequence[object]], header: Sequence[str]) -> None:
    with path.open("w", encoding="utf-8", newline="") as f:
        f.write("\t".join(header) + "\n")
        for row in rows:
            f.write("\t".join(str(x) for x in row) + "\n")


def parse_record_filter(spec: Optional[str]) -> Optional[set[int]]:
    if not spec:
        return None
    out: set[int] = set()
    for part in spec.split(','):
        part = part.strip()
        if not part:
            continue
        if '-' in part:
            a, b = part.split('-', 1)
            start = int(a, 0)
            end = int(b, 0)
            out.update(range(start, end + 1))
        else:
            out.add(int(part, 0))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description="Bounded DATABASE.MW2 palette scanner")
    ap.add_argument("database", type=Path)
    ap.add_argument("out_dir", type=Path)
    ap.add_argument("--records", help="Optional record filter, e.g. 1-83 or 0x24-0x40")
    ap.add_argument("--min-score", type=float, default=55.0)
    ap.add_argument("--max-emit", type=int, default=64, help="Maximum palette files to emit")
    ap.add_argument("--embedded-stride", type=int, default=256, help="Stride for conservative embedded scans; use 0 to disable")
    ap.add_argument("--embedded-max-offsets-per-record", type=int, default=64)
    args = ap.parse_args()
    args.records = parse_record_filter(args.records)

    records = load_database(args.database)
    args.out_dir.mkdir(parents=True, exist_ok=True)
    pal_dir = args.out_dir / "palettes"
    pal_dir.mkdir(exist_ok=True)

    candidates = collect_candidates(records, args)
    record_by_id = {r.record_id: r for r in records}

    # Emit only unique record/offset/kind/order candidates above score threshold, capped.
    emitted: List[Candidate] = []
    seen_keys = set()
    for c in candidates:
        key = (c.record_id, c.offset, c.kind, c.order)
        if key in seen_keys:
            continue
        seen_keys.add(key)
        if c.score < args.min_score:
            continue
        if len(emitted) >= args.max_emit:
            break
        rec = record_by_id[c.record_id]
        colors = extract_colors(rec, c)
        safe = f"rec{c.record_id:03d}_off{c.offset:06x}_{c.kind}_{c.order}_score{c.score:.1f}".replace('.', '_')
        c.emit_name = safe + ".pal"
        write_rgb768(pal_dir / c.emit_name, colors, scale_vga6=False)
        if c.max_channel <= 63:
            write_rgb768(pal_dir / (safe + "_vga6_scaled_rgb768.pal"), colors, scale_vga6=True)
        emitted.append(c)

    write_tsv(args.out_dir / "records.tsv",
              [(r.record_id, f"0x{r.start:x}", f"0x{r.end:x}", r.size, r.data[:8].hex()) for r in records],
              ["record_id", "start", "end", "size", "first8_hex"])

    cand_rows = []
    for c in candidates[:10000]:
        cand_rows.append((c.record_id, f"0x{c.offset:x}", c.kind, c.order, f"{c.score:.3f}", c.byte_len,
                          c.min_channel, c.max_channel, c.unique_colors,
                          f"{c.grayish_fraction:.4f}", f"{c.zero_fraction:.4f}",
                          f"{c.monotonic_run_score:.4f}", c.reason, c.emit_name))
    write_tsv(args.out_dir / "palette_candidates.tsv", cand_rows,
              ["record_id", "offset", "kind", "order", "score", "byte_len", "min_channel", "max_channel",
               "unique_colors", "grayish_fraction", "zero_fraction", "monotonic_run_score", "reason", "emit_name"])

    top_rows = []
    for c in emitted:
        top_rows.append((c.record_id, f"0x{c.offset:x}", c.kind, c.order, f"{c.score:.3f}",
                         c.max_channel <= 63, c.unique_colors, c.reason, c.emit_name))
    write_tsv(args.out_dir / "top_candidates.tsv", top_rows,
              ["record_id", "offset", "kind", "order", "score", "likely_vga6", "unique_colors", "reason", "emit_name"])

    summary = {
        "database": str(args.database),
        "record_count": len(records),
        "candidates_ranked_total": len(candidates),
        "candidates_written_to_tsv": min(len(candidates), 10000),
        "palette_files_emitted": len(emitted),
        "min_score": args.min_score,
        "max_emit": args.max_emit,
        "embedded_stride": args.embedded_stride,
        "embedded_max_offsets_per_record": args.embedded_max_offsets_per_record,
        "note": "This scanner is intentionally bounded; it never emits every sliding-window candidate.",
    }
    (args.out_dir / "summary.json").write_text(json.dumps(summary, indent=2), encoding="utf-8")
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
