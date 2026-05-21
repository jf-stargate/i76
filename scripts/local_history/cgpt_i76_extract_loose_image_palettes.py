#!/usr/bin/env python3
"""
Extract palette candidates from loose Interstate '76 image files.

Targets the practical next step from the I76 reverse-engineering thread:
find frontend/menu palettes that may be carried by loose PCX/BMP resources
rather than DATABASE.MW2 itself.

Supported inputs:
  - 8-bit PCX with VGA palette trailer: 0x0c + 768 RGB bytes
  - BMP/DIB with indexed color table: BI_RGB-style palette entries BGRA

Outputs:
  palettes/*.pal              raw RGB768 palettes
  palettes/*.jasc.pal         JASC-PAL text copies
  palette_index.tsv           source file, format, palette size, hashes
  unique_palette_index.tsv    unique palettes by SHA-256

Usage:
  python3 cgpt_i76_extract_loose_image_palettes.py orig out_loose_palettes

Then test candidates:
  python3 cgpt_i76_decode_database_mw2_110_images_palette.py \
      orig/DATABASE.MW2 db_110_images_loosepal_test \
      --palette out_loose_palettes/palettes/<candidate>.pal
"""

from __future__ import annotations

import argparse
import hashlib
import os
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, List, Optional, Tuple


IMAGE_EXTS = {".pcx", ".bmp"}


@dataclass
class PaletteHit:
    source: Path
    rel_source: str
    fmt: str
    colors: int
    rgb: bytes
    note: str

    @property
    def sha256(self) -> str:
        return hashlib.sha256(self.rgb).hexdigest()

    @property
    def short_hash(self) -> str:
        return self.sha256[:16]


def safe_name(s: str) -> str:
    out = []
    for ch in s:
        if ch.isalnum() or ch in "._-":
            out.append(ch)
        else:
            out.append("_")
    return "".join(out)


def read_pcx_palette(path: Path, rel: str) -> Optional[PaletteHit]:
    data = path.read_bytes()
    if len(data) < 128 + 769:
        return None
    # PCX header byte 0 should be manufacturer 0x0a; version/encoding are not enough alone,
    # but this avoids treating arbitrary files as PCX.
    if data[0] != 0x0A:
        return None
    # VGA palette marker is last 769 bytes: 0x0c + 256 RGB triples.
    if data[-769] != 0x0C:
        return None
    rgb = data[-768:]
    return PaletteHit(path, rel, "pcx_vga_trailer_rgb768", 256, rgb, "PCX trailing 256-color VGA palette")


def read_bmp_palette(path: Path, rel: str) -> Optional[PaletteHit]:
    data = path.read_bytes()
    if len(data) < 54 or data[0:2] != b"BM":
        return None
    try:
        bf_off_bits = struct.unpack_from("<I", data, 10)[0]
        dib_size = struct.unpack_from("<I", data, 14)[0]
    except struct.error:
        return None
    if dib_size < 40 or len(data) < 14 + dib_size:
        return None

    try:
        width = struct.unpack_from("<i", data, 18)[0]
        height = struct.unpack_from("<i", data, 22)[0]
        planes = struct.unpack_from("<H", data, 26)[0]
        bpp = struct.unpack_from("<H", data, 28)[0]
        compression = struct.unpack_from("<I", data, 30)[0]
        clr_used = struct.unpack_from("<I", data, 46)[0] if dib_size >= 40 else 0
    except struct.error:
        return None

    if planes != 1 or bpp > 8:
        return None

    # Indexed BMP color table follows BITMAPFILEHEADER + DIB header.
    palette_start = 14 + dib_size
    if clr_used:
        colors = min(int(clr_used), 1 << bpp)
    else:
        colors = 1 << bpp
    if colors <= 0 or colors > 256:
        return None
    palette_bytes = colors * 4
    if palette_start + palette_bytes > len(data) or palette_start >= bf_off_bits:
        # Some BITMAPCOREHEADER-style BMPs differ, but I76 frontend BMPs are likely Windows DIBs.
        return None

    bgra = data[palette_start:palette_start + palette_bytes]
    rgb = bytearray()
    for i in range(colors):
        b, g, r, _a = bgra[i*4:i*4+4]
        rgb += bytes((r, g, b))
    # Pad to 256 colors so the main decoder can consume it as raw RGB768.
    if colors < 256:
        rgb += bytes((0, 0, 0)) * (256 - colors)

    note = f"BMP indexed color table; width={width}; height={height}; bpp={bpp}; compression={compression}; colors={colors}"
    return PaletteHit(path, rel, f"bmp_bgra_colortable_{colors}_to_rgb768", 256, bytes(rgb), note)


def write_jasc(path: Path, rgb: bytes) -> None:
    with path.open("w", encoding="ascii", newline="\n") as f:
        f.write("JASC-PAL\n0100\n256\n")
        for i in range(256):
            r, g, b = rgb[i*3:i*3+3]
            f.write(f"{r} {g} {b}\n")


def iter_image_files(root: Path) -> Iterable[Path]:
    for dirpath, _dirnames, filenames in os.walk(root):
        for name in filenames:
            p = Path(dirpath) / name
            if p.suffix.lower() in IMAGE_EXTS:
                yield p


def main() -> int:
    ap = argparse.ArgumentParser(description="Extract unique palette candidates from loose PCX/BMP files.")
    ap.add_argument("input_root", type=Path, help="Base game directory, e.g. orig/")
    ap.add_argument("output_dir", type=Path, help="Output directory")
    args = ap.parse_args()

    root = args.input_root
    out = args.output_dir
    pal_dir = out / "palettes"
    pal_dir.mkdir(parents=True, exist_ok=True)

    hits: List[PaletteHit] = []
    for p in sorted(iter_image_files(root)):
        rel = str(p.relative_to(root)) if p.is_relative_to(root) else str(p)
        try:
            hit = None
            if p.suffix.lower() == ".pcx":
                hit = read_pcx_palette(p, rel)
            elif p.suffix.lower() == ".bmp":
                hit = read_bmp_palette(p, rel)
            if hit is not None:
                hits.append(hit)
        except Exception as e:
            # Keep the extractor robust against odd BMP/PCX variants.
            print(f"[WARN] failed to inspect {p}: {e}")

    unique = {}
    for h in hits:
        unique.setdefault(h.sha256, h)

    with (out / "palette_index.tsv").open("w", encoding="utf-8", newline="\n") as f:
        f.write("source\tformat\tcolors\tsha256\tnote\n")
        for h in hits:
            f.write(f"{h.rel_source}\t{h.fmt}\t{h.colors}\t{h.sha256}\t{h.note}\n")

    with (out / "unique_palette_index.tsv").open("w", encoding="utf-8", newline="\n") as f:
        f.write("palette_file\tjasc_file\tfirst_source\tformat\tsha256\tnote\n")
        for idx, (sha, h) in enumerate(sorted(unique.items(), key=lambda kv: kv[1].rel_source)):
            stem = f"pal{idx:03d}_{safe_name(Path(h.rel_source).stem)}_{h.short_hash}"
            raw_path = pal_dir / f"{stem}.pal"
            jasc_path = pal_dir / f"{stem}.jasc.pal"
            raw_path.write_bytes(h.rgb)
            write_jasc(jasc_path, h.rgb)
            f.write(f"{raw_path.name}\t{jasc_path.name}\t{h.rel_source}\t{h.fmt}\t{sha}\t{h.note}\n")

    with (out / "summary.txt").open("w", encoding="utf-8", newline="\n") as f:
        f.write(f"Input root: {root}\n")
        f.write(f"Palette hits: {len(hits)}\n")
        f.write(f"Unique palettes: {len(unique)}\n")
        f.write(f"Output palettes: {pal_dir}\n")

    print(f"[+] Palette hits: {len(hits)}")
    print(f"[+] Unique palettes: {len(unique)}")
    print(f"[+] Wrote: {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
