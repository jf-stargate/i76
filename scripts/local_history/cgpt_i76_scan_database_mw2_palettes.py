#!/usr/bin/env python3
"""
cgpt_i76_scan_database_mw2_palettes.py

Scan Interstate '76 / MW2-style DATABASE.MW2 indexed pack records for palette-like
payloads and emit candidate palette files for testing with the 1.10 image decoder.

This is intentionally heuristic. It does not assume the shell/menu palette is stored
as a standalone .PAL resource; it also searches for embedded 256-color tables inside
larger records.

Usage:
  python3 cgpt_i76_scan_database_mw2_palettes.py DATABASE.MW2 out_palette_scan

Then test a candidate:
  python3 cgpt_i76_decode_database_mw2_110_images_palette.py DATABASE.MW2 out_test \
      --palette out_palette_scan/palettes/record_XX_off_0xYYYY_rgb768.pal

@author ChatGPT
"""

from __future__ import annotations

import argparse
import json
import math
import os
import struct
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Iterable, List, Optional, Tuple


@dataclass
class RecordInfo:
    record_id: int
    offset: int
    size: int
    magic4: str
    entropy: float


@dataclass
class PaletteCandidate:
    record_id: int
    record_offset: int
    offset_in_record: int
    file_offset: int
    fmt: str
    size: int
    score: float
    reason: str
    unique_colors: int
    min_channel: int
    max_channel: int
    zero_entries: int
    grayscale_entries: int
    monotonic_gray_prefix: int
    out_file: str


def shannon_entropy(buf: bytes) -> float:
    if not buf:
        return 0.0
    counts = [0] * 256
    for b in buf:
        counts[b] += 1
    total = len(buf)
    ent = 0.0
    for c in counts:
        if c:
            p = c / total
            ent -= p * math.log2(p)
    return ent


def safe_magic4(buf: bytes) -> str:
    if len(buf) < 4:
        return ""
    out = []
    for b in buf[:4]:
        if 32 <= b <= 126:
            out.append(chr(b))
        else:
            out.append(f"\\x{b:02x}")
    return ''.join(out)


def read_database(path: Path) -> Tuple[bytes, List[RecordInfo]]:
    data = path.read_bytes()
    if len(data) < 8:
        raise ValueError("file too small")
    count = struct.unpack_from('<I', data, 0)[0]
    if count <= 0 or count > 100000:
        raise ValueError(f"implausible record count: {count}")
    table_end = 4 + count * 4
    if table_end > len(data):
        raise ValueError("offset table extends past EOF")
    offsets = list(struct.unpack_from('<' + 'I' * count, data, 4))
    infos: List[RecordInfo] = []
    for i, off in enumerate(offsets):
        next_off = offsets[i + 1] if i + 1 < len(offsets) else len(data)
        if off < table_end or off > len(data) or next_off < off or next_off > len(data):
            size = max(0, min(len(data), next_off) - min(len(data), off)) if off < len(data) else 0
        else:
            size = next_off - off
        rec = data[off:off + size] if off < len(data) else b''
        infos.append(RecordInfo(i + 1, off, size, safe_magic4(rec), shannon_entropy(rec[:min(len(rec), 4096)])))
    return data, infos


def colors_from_rgb(buf: bytes, order: str) -> List[Tuple[int, int, int]]:
    if len(buf) < 768:
        return []
    colors = []
    for i in range(256):
        a, b, c = buf[i * 3:i * 3 + 3]
        if order == 'rgb':
            colors.append((a, b, c))
        else:
            colors.append((c, b, a))
    return colors


def colors_from_rgba(buf: bytes, order: str) -> List[Tuple[int, int, int]]:
    if len(buf) < 1024:
        return []
    colors = []
    for i in range(256):
        a, b, c, d = buf[i * 4:i * 4 + 4]
        if order == 'rgba':
            colors.append((a, b, c))
        else:
            colors.append((c, b, a))
    return colors


def palette_metrics(colors: List[Tuple[int, int, int]]) -> dict:
    vals = [v for rgb in colors for v in rgb]
    unique = len(set(colors))
    zero = sum(1 for c in colors if c == (0, 0, 0))
    gray = sum(1 for r, g, b in colors if r == g == b)
    prefix = 0
    last = -1
    for r, g, b in colors:
        if r == g == b and r >= last:
            prefix += 1
            last = r
        else:
            break
    max_delta = 0
    for r, g, b in colors:
        max_delta = max(max_delta, abs(r - g), abs(r - b), abs(g - b))
    return {
        'unique_colors': unique,
        'min_channel': min(vals) if vals else 0,
        'max_channel': max(vals) if vals else 0,
        'zero_entries': zero,
        'grayscale_entries': gray,
        'monotonic_gray_prefix': prefix,
        'max_rgb_delta': max_delta,
    }


def score_palette(colors: List[Tuple[int, int, int]], fmt: str, alignment_bonus: float = 0.0) -> Tuple[float, str]:
    if len(colors) != 256:
        return 0.0, "wrong_color_count"
    m = palette_metrics(colors)
    score = 0.0
    reasons = []

    unique = m['unique_colors']
    maxc = m['max_channel']
    minc = m['min_channel']
    zeros = m['zero_entries']
    gray = m['grayscale_entries']
    gray_prefix = m['monotonic_gray_prefix']

    # Real game palettes usually have variety, but not necessarily 256 unique colors.
    if unique >= 128:
        score += 3.0; reasons.append("many_unique_colors")
    elif unique >= 64:
        score += 1.5; reasons.append("some_unique_colors")
    else:
        score -= 3.0; reasons.append("low_unique_colors")

    if maxc <= 63:
        score += 1.5; reasons.append("vga_6bit_range")
    elif maxc >= 180:
        score += 1.0; reasons.append("8bit_channel_range")
    else:
        score -= 0.5; reasons.append("limited_channel_range")

    if zeros <= 32:
        score += 1.0; reasons.append("not_mostly_zero")
    else:
        score -= 2.0; reasons.append("many_black_entries")

    if gray >= 240:
        score -= 4.0; reasons.append("mostly_grayscale")
    elif gray_prefix >= 16:
        score += 0.5; reasons.append("gray_ramp_prefix")

    # Penalize monotonically trivial ramps masquerading as palettes.
    if gray_prefix >= 128:
        score -= 3.0; reasons.append("large_gray_ramp")

    score += alignment_bonus
    if alignment_bonus:
        reasons.append("aligned_or_whole_record")

    return score, ",".join(reasons)


def write_rgb768(path: Path, colors: List[Tuple[int, int, int]], scale_6bit_to_8bit: bool = False) -> None:
    out = bytearray()
    for r, g, b in colors:
        if scale_6bit_to_8bit:
            r = min(255, int(round(r * 255 / 63)))
            g = min(255, int(round(g * 255 / 63)))
            b = min(255, int(round(b * 255 / 63)))
        out.extend([r, g, b])
    path.write_bytes(bytes(out))


def consider_candidate(
    candidates: List[PaletteCandidate],
    rec: RecordInfo,
    rec_data: bytes,
    base_out: Path,
    offset: int,
    fmt: str,
    colors: List[Tuple[int, int, int]],
    size: int,
    whole_record: bool = False,
) -> None:
    if len(colors) != 256:
        return
    align_bonus = 0.75 if (offset == 0 or offset % 16 == 0 or whole_record) else 0.0
    score, reason = score_palette(colors, fmt, align_bonus)
    if score < 1.5:
        return
    m = palette_metrics(colors)

    stem = f"record_{rec.record_id:02d}_off_0x{offset:06x}_{fmt}"
    raw_path = base_out / f"{stem}.pal"
    write_rgb768(raw_path, colors, scale_6bit_to_8bit=False)

    out_file = str(raw_path.relative_to(base_out.parent))
    candidates.append(PaletteCandidate(
        record_id=rec.record_id,
        record_offset=rec.offset,
        offset_in_record=offset,
        file_offset=rec.offset + offset,
        fmt=fmt,
        size=size,
        score=score,
        reason=reason,
        unique_colors=m['unique_colors'],
        min_channel=m['min_channel'],
        max_channel=m['max_channel'],
        zero_entries=m['zero_entries'],
        grayscale_entries=m['grayscale_entries'],
        monotonic_gray_prefix=m['monotonic_gray_prefix'],
        out_file=out_file,
    ))

    # If it looks like VGA DAC 6-bit, also emit a scaled 8-bit version for convenient testing.
    if m['max_channel'] <= 63 and m['unique_colors'] >= 32:
        scaled = base_out / f"{stem}_vga6_scaled_rgb768.pal"
        write_rgb768(scaled, colors, scale_6bit_to_8bit=True)


def scan_records_for_palettes(data: bytes, records: List[RecordInfo], out_dir: Path) -> List[PaletteCandidate]:
    pal_dir = out_dir / 'palettes'
    pal_dir.mkdir(parents=True, exist_ok=True)
    candidates: List[PaletteCandidate] = []

    for rec in records:
        rec_data = data[rec.offset:rec.offset + rec.size]
        if rec.size < 48:
            continue

        # Whole-record common cases.
        if rec.size in (768, 769, 1024, 1032):
            if rec.size >= 768:
                for order in ('rgb', 'bgr'):
                    colors = colors_from_rgb(rec_data[:768], order)
                    consider_candidate(candidates, rec, rec_data, pal_dir, 0, order + '768_whole', colors, 768, True)
            if rec.size >= 1024:
                for order in ('rgba', 'bgra'):
                    colors = colors_from_rgba(rec_data[:1024], order)
                    consider_candidate(candidates, rec, rec_data, pal_dir, 0, order + '1024_whole', colors, 1024, True)

        # RIFF PAL simple parse.
        if rec_data[:4] == b'RIFF' and b'PAL ' in rec_data[:32]:
            # Search for data chunk. Windows LOGPALETTE starts with version/count then PALETTEENTRY RGBA.
            idx = rec_data.find(b'data')
            if idx >= 0 and idx + 8 < len(rec_data):
                sz = struct.unpack_from('<I', rec_data, idx + 4)[0]
                payload = rec_data[idx + 8:idx + 8 + sz]
                if len(payload) >= 4 + 256 * 4:
                    count = struct.unpack_from('<H', payload, 2)[0]
                    if count >= 256:
                        colors = []
                        p = 4
                        for i in range(256):
                            r, g, b, flags = payload[p:p+4]
                            colors.append((r, g, b))
                            p += 4
                        consider_candidate(candidates, rec, rec_data, pal_dir, idx + 8 + 4, 'riff_pal', colors, 1024, False)

        # Embedded scan. Step by 1 for small records, by 4 for large records to keep output manageable.
        step = 1 if rec.size <= 4096 else 4
        max_scan = rec.size - 768
        if max_scan >= 0:
            for off in range(0, max_scan + 1, step):
                # Prioritize likely alignments, but still allow unaligned for smaller records.
                if step != 1 and off % 16 != 0 and off not in (0, 4, 8, 12, 16, 32, 64, 128):
                    continue
                chunk = rec_data[off:off + 768]
                for order in ('rgb', 'bgr'):
                    colors = colors_from_rgb(chunk, order)
                    consider_candidate(candidates, rec, rec_data, pal_dir, off, order + '768_embedded', colors, 768, False)

        max_scan4 = rec.size - 1024
        if max_scan4 >= 0:
            step4 = 4 if rec.size <= 8192 else 16
            for off in range(0, max_scan4 + 1, step4):
                if off % 16 != 0 and off not in (0, 4, 8, 12, 16, 32, 64, 128):
                    continue
                chunk = rec_data[off:off + 1024]
                for order in ('rgba', 'bgra'):
                    colors = colors_from_rgba(chunk, order)
                    consider_candidate(candidates, rec, rec_data, pal_dir, off, order + '1024_embedded', colors, 1024, False)

    # De-duplicate exact same record/offset/fmt paths and keep best scores.
    candidates.sort(key=lambda c: (-c.score, c.record_id, c.offset_in_record, c.fmt))
    return candidates


def write_tsv(path: Path, rows: Iterable[dict], fields: List[str]) -> None:
    with path.open('w', encoding='utf-8', newline='') as f:
        f.write('\t'.join(fields) + '\n')
        for row in rows:
            f.write('\t'.join(str(row.get(k, '')) for k in fields) + '\n')


def main() -> int:
    ap = argparse.ArgumentParser(description='Scan DATABASE.MW2 for palette-like records/tables')
    ap.add_argument('database_mw2', type=Path)
    ap.add_argument('out_dir', type=Path)
    ap.add_argument('--top', type=int, default=100, help='number of candidates to list in top_candidates.tsv')
    args = ap.parse_args()

    out = args.out_dir
    out.mkdir(parents=True, exist_ok=True)

    data, records = read_database(args.database_mw2)
    candidates = scan_records_for_palettes(data, records, out)

    write_tsv(out / 'records.tsv', (asdict(r) for r in records),
              ['record_id', 'offset', 'size', 'magic4', 'entropy'])

    cand_fields = [
        'record_id', 'record_offset', 'offset_in_record', 'file_offset', 'fmt', 'size', 'score', 'reason',
        'unique_colors', 'min_channel', 'max_channel', 'zero_entries', 'grayscale_entries',
        'monotonic_gray_prefix', 'out_file'
    ]
    write_tsv(out / 'palette_candidates.tsv', (asdict(c) for c in candidates), cand_fields)
    write_tsv(out / 'top_candidates.tsv', (asdict(c) for c in candidates[:args.top]), cand_fields)

    summary = {
        'database': str(args.database_mw2),
        'file_size': len(data),
        'record_count': len(records),
        'palette_candidates': len(candidates),
        'top_candidates': [asdict(c) for c in candidates[:10]],
        'notes': [
            'Candidates are heuristic; test the emitted .pal files with the palette-capable 1.10 decoder.',
            'If max_channel <= 63, a *_vga6_scaled_rgb768.pal companion file is emitted for convenient testing.',
            'The shell/menu palette may also be initialized by DirectDraw or engine callbacks, not necessarily stored in DATABASE.MW2.'
        ],
    }
    (out / 'summary.json').write_text(json.dumps(summary, indent=2), encoding='utf-8')

    print(f"[+] records: {len(records)}")
    print(f"[+] palette candidates: {len(candidates)}")
    print(f"[+] wrote: {out}")
    if candidates:
        print("[+] top candidates:")
        for c in candidates[:10]:
            print(f"    rec={c.record_id:02d} off=0x{c.offset_in_record:x} fmt={c.fmt} score={c.score:.2f} file={c.out_file}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
