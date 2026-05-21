#!/usr/bin/env python3
"""
Generate Windows 9x/Win32 256-color system/halftone palette candidates
for testing Interstate '76 DATABASE.MW2 1.10 shell/menu image colorization.

This intentionally emits a small candidate set, not a broad scan.
Outputs raw RGB768 .pal files plus JASC-PAL text copies.

Optional: batch-run an existing 1.10 decoder against every generated palette.
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path
from typing import Iterable, List, Sequence, Tuple

RGB = Tuple[int, int, int]

# Standard Win32 20 static system colors as commonly used in 256-color palette mode.
# These are placed at entries 0-9 and 246-255 in the system palette.
WIN_STATIC_FIRST_10: List[RGB] = [
    (0x00, 0x00, 0x00),  # black
    (0x80, 0x00, 0x00),  # dark red
    (0x00, 0x80, 0x00),  # dark green
    (0x80, 0x80, 0x00),  # dark yellow/olive
    (0x00, 0x00, 0x80),  # dark blue
    (0x80, 0x00, 0x80),  # dark magenta
    (0x00, 0x80, 0x80),  # dark cyan
    (0xC0, 0xC0, 0xC0),  # light gray
    (0xC0, 0xDC, 0xC0),  # money green
    (0xA6, 0xCA, 0xF0),  # sky blue
]

WIN_STATIC_LAST_10: List[RGB] = [
    (0xFF, 0xFB, 0xF0),  # cream
    (0xA0, 0xA0, 0xA4),  # medium gray
    (0x80, 0x80, 0x80),  # dark gray
    (0xFF, 0x00, 0x00),  # red
    (0x00, 0xFF, 0x00),  # green
    (0xFF, 0xFF, 0x00),  # yellow
    (0x00, 0x00, 0xFF),  # blue
    (0xFF, 0x00, 0xFF),  # magenta
    (0x00, 0xFF, 0xFF),  # cyan
    (0xFF, 0xFF, 0xFF),  # white
]

LEVELS_6 = [0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF]


def clamp_byte(v: int) -> int:
    return max(0, min(255, int(v)))


def grayscale_fill(n: int, include_endpoints: bool = True) -> List[RGB]:
    if n <= 0:
        return []
    if n == 1:
        vals = [0]
    elif include_endpoints:
        vals = [round(i * 255 / (n - 1)) for i in range(n)]
    else:
        vals = [round((i + 1) * 255 / (n + 1)) for i in range(n)]
    return [(v, v, v) for v in vals]


def color_cube(order: str = "rgb") -> List[RGB]:
    """Generate a 6x6x6 cube. order controls which channel varies fastest."""
    order = order.lower()
    if sorted(order) != ["b", "g", "r"]:
        raise ValueError(f"Invalid cube order: {order!r}")

    out: List[RGB] = []
    for a in LEVELS_6:
        for b in LEVELS_6:
            for c in LEVELS_6:
                vals = {order[0]: a, order[1]: b, order[2]: c}
                out.append((vals["r"], vals["g"], vals["b"]))
    assert len(out) == 216
    return out


def make_system20_gray_middle() -> List[RGB]:
    # Exact middle contents are not guaranteed; this is a diagnostic baseline.
    return WIN_STATIC_FIRST_10 + grayscale_fill(236) + WIN_STATIC_LAST_10


def make_halftone_candidate(order: str, gray_after_cube: bool = True) -> List[RGB]:
    # 10 system + 216 cube + 20 grays + 10 system = 256.
    # This is a common practical approximation of a Win32 halftone/system palette shape.
    cube = color_cube(order)
    grays = grayscale_fill(20, include_endpoints=False)
    middle = cube + grays if gray_after_cube else grays + cube
    pal = WIN_STATIC_FIRST_10 + middle + WIN_STATIC_LAST_10
    assert len(pal) == 256
    return pal


def make_system20_cube_only_reserved_tail(order: str) -> List[RGB]:
    # 20 static + 216 cube leaves 20 spare entries. Fill spares with a smooth gray ramp.
    return make_halftone_candidate(order, gray_after_cube=True)


def write_raw_rgb768(path: Path, pal: Sequence[RGB]) -> None:
    if len(pal) != 256:
        raise ValueError(f"Palette must contain 256 entries, got {len(pal)}")
    data = bytearray()
    for r, g, b in pal:
        data.extend((clamp_byte(r), clamp_byte(g), clamp_byte(b)))
    path.write_bytes(bytes(data))


def write_jasc(path: Path, pal: Sequence[RGB]) -> None:
    lines = ["JASC-PAL", "0100", "256"]
    for r, g, b in pal:
        lines.append(f"{clamp_byte(r)} {clamp_byte(g)} {clamp_byte(b)}")
    path.write_text("\n".join(lines) + "\n", encoding="ascii")


def write_palette_pair(out_dir: Path, stem: str, pal: Sequence[RGB]) -> Path:
    raw = out_dir / f"{stem}.pal"
    jasc = out_dir / f"{stem}.jasc.pal"
    write_raw_rgb768(raw, pal)
    write_jasc(jasc, pal)
    return raw


def maybe_run_decoder(decoder: Path, database: Path, out_root: Path, palette_files: Sequence[Path]) -> None:
    out_root.mkdir(parents=True, exist_ok=True)
    for pal in palette_files:
        out = out_root / pal.stem
        print(f"[+] Decode test: {pal.name} -> {out}")
        subprocess.run(
            [sys.executable, str(decoder), str(database), str(out), "--palette", str(pal)],
            check=True,
        )


def main() -> int:
    ap = argparse.ArgumentParser(description="Generate small Windows system/halftone palette candidate set.")
    ap.add_argument("out_dir", help="Output directory for generated palette candidates")
    ap.add_argument("--decoder", help="Optional path to cgpt_i76_decode_database_mw2_110_images_palette.py")
    ap.add_argument("--database", help="Optional path to DATABASE.MW2; requires --decoder")
    ap.add_argument("--decode-out", default="win_palette_decode_tests", help="Output root for optional decode runs")
    args = ap.parse_args()

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    candidates: List[Tuple[str, List[RGB], str]] = []
    candidates.append((
        "win_system20_static_positions_gray_middle_rgb768",
        make_system20_gray_middle(),
        "Win32 20 static system colors at 0-9/246-255; middle entries are diagnostic grayscale ramp",
    ))

    for order in ["rgb", "rbg", "grb", "gbr", "brg", "bgr"]:
        candidates.append((
            f"win_system20_halftone_cube_{order}_gray_after_rgb768",
            make_halftone_candidate(order, gray_after_cube=True),
            f"Win32 static colors plus 6x6x6 cube order={order}, then 20 middle gray entries",
        ))
        candidates.append((
            f"win_system20_halftone_gray_before_cube_{order}_rgb768",
            make_halftone_candidate(order, gray_after_cube=False),
            f"Win32 static colors plus 20 middle gray entries, then 6x6x6 cube order={order}",
        ))

    emitted: List[Path] = []
    manifest_lines = ["file\tdescription"]
    for stem, pal, desc in candidates:
        raw = write_palette_pair(out_dir, stem, pal)
        emitted.append(raw)
        manifest_lines.append(f"{raw.name}\t{desc}")

    (out_dir / "manifest.tsv").write_text("\n".join(manifest_lines) + "\n", encoding="utf-8")

    print(f"[+] Wrote {len(emitted)} raw RGB768 palette candidates to {out_dir}")
    print(f"[+] Wrote JASC copies and manifest.tsv")

    if args.decoder or args.database:
        if not args.decoder or not args.database:
            raise SystemExit("--decoder and --database must be supplied together")
        maybe_run_decoder(Path(args.decoder), Path(args.database), Path(args.decode_out), emitted)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
