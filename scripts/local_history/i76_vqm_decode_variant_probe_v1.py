#!/usr/bin/env python3
"""
i76_vqm_decode_variant_probe_v1.py

Render one Interstate '76 VQM texture through several plausible CBK tile
orientation variants. This isolates VQM/CBK decode correctness from palette
selection.

Why:
  If the palette is wrong, colors are wrong but structure should remain coherent.
  If the VQM tile orientation is wrong, all palettes show the same combing,
  hatching, transpose, or block artifacts.

Example:
  python3 scripts/i76_vqm_decode_variant_probe_v1.py \
    --zfs orig/I76.ZFS \
    --resolver scripts/i76_vehicle_texture_slot_resolver_v5.py \
    --texture pp11mdl1 \
    --palette scratch_data/palettes/i76_game_palette_004fa170_x4.act \
    --out scratch_data/i76_vqm_decode_variant_pp11mdl1

If you have identified a better ACT palette candidate, pass that palette instead.
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import re
import struct
import sys
from pathlib import Path
from typing import Callable, Dict, List, Optional, Tuple


def load_resolver(path: Path):
    spec = importlib.util.spec_from_file_location("i76_resolver_v5", str(path))
    if spec is None or spec.loader is None:
        raise RuntimeError(f"could not import resolver script: {path}")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["i76_resolver_v5"] = mod
    spec.loader.exec_module(mod)
    return mod


def cstring(data: bytes) -> str:
    return data.split(b"\x00", 1)[0].decode("ascii", "replace").strip()


def safe_name(name: str) -> str:
    return re.sub(r"[^A-Za-z0-9._+\-]+", "_", name) or "unnamed"


def load_palette(path: Path) -> List[Tuple[int, int, int]]:
    data = path.read_bytes()
    if len(data) < 768:
        raise ValueError(f"palette too small: {path}")
    return [(data[i*3], data[i*3+1], data[i*3+2]) for i in range(256)]


def resolve_vqm(resolver, idx, texture_name: str):
    stem = texture_name.rsplit(".", 1)[0] if "." in texture_name else texture_name
    for ref in [texture_name, stem + ".VQM", stem + ".vqm", stem]:
        a = idx.resolve(ref, "vqm", source=None)
        if a:
            return a
    raise ValueError(f"could not resolve VQM texture: {texture_name}")


def get_cbk_for_vqm(idx, vqm_asset, vqm_data: bytes):
    cbk_ref = cstring(vqm_data[0x08:0x14]).upper() if len(vqm_data) >= 0x14 else ""
    if cbk_ref and "." not in cbk_ref:
        cbk_ref += ".CBK"
    cbk = idx.resolve(cbk_ref, "cbk", source=vqm_asset) if cbk_ref else None
    if not cbk:
        raise ValueError(f"could not resolve CBK {cbk_ref!r} for {vqm_asset.name}")
    return cbk, idx.payloads.get(cbk.asset_id, b"")


def tile_index(variant: str, sx: int, sy: int) -> int:
    # tile is 4x4. Variants test row/column-major and simple flips.
    x = sx
    y = sy
    if "flipx" in variant:
        x = 3 - x
    if "flipy" in variant:
        y = 3 - y
    if variant.startswith("xy"):
        return x * 4 + y   # current exporter/Open76-inspired interpretation
    if variant.startswith("yx"):
        return y * 4 + x   # conventional row-major interpretation
    raise ValueError(variant)


def decode_vqm_variant(vqm: bytes, cbk: bytes, variant: str, token_endian: str = "little") -> Tuple[int, int, bytes]:
    if len(vqm) < 0x18:
        raise ValueError("VQM too small")
    w, hf = struct.unpack_from("<II", vqm, 0)
    h = hf & 0x1FFFFFFF
    tiles_x = (w + 3) // 4
    tiles_y = (h + 3) // 4
    token_count = tiles_x * tiles_y
    if len(vqm) < 0x18 + token_count * 2:
        raise ValueError("VQM token data too short")

    pixels = bytearray(w * h)
    pos = 0x18
    for by in range(tiles_y):
        for bx in range(tiles_x):
            if token_endian == "little":
                tok = struct.unpack_from("<H", vqm, pos)[0]
            else:
                tok = struct.unpack_from(">H", vqm, pos)[0]
            pos += 2

            if tok & 0x8000:
                tile = bytes([tok & 0xff]) * 16
            else:
                tile_off = 4 + tok * 16
                if tile_off + 16 <= len(cbk):
                    tile = cbk[tile_off:tile_off + 16]
                else:
                    tile = bytes([0]) * 16

            for sy in range(4):
                py = by * 4 + sy
                if py >= h:
                    continue
                for sx in range(4):
                    px = bx * 4 + sx
                    if px >= w:
                        continue
                    pixels[py * w + px] = tile[tile_index(variant, sx, sy)]
    return w, h, bytes(pixels)


def render_indexed(w: int, h: int, pix: bytes, pal: List[Tuple[int, int, int]]) -> List[Tuple[int, int, int]]:
    return [pal[b] for b in pix]


def save_rgb(path: Path, w: int, h: int, rgb: List[Tuple[int, int, int]], scale: int) -> str:
    path.parent.mkdir(parents=True, exist_ok=True)
    try:
        from PIL import Image  # type: ignore
        img = Image.new("RGB", (w, h))
        img.putdata(rgb)
        if scale > 1:
            img = img.resize((w * scale, h * scale), Image.Resampling.NEAREST)
        img.save(path.with_suffix(".png"), compress_level=1)
        return str(path.with_suffix(".png"))
    except Exception:
        out = path.with_suffix(".ppm")
        with out.open("wb") as f:
            f.write(f"P6\n{w} {h}\n255\n".encode("ascii"))
            for r, g, b in rgb:
                f.write(bytes([r, g, b]))
        return str(out)


def save_sheet(path: Path, images: List[Tuple[str, int, int, List[Tuple[int, int, int]]]], scale: int) -> str:
    try:
        from PIL import Image, ImageDraw  # type: ignore
        cols = 2
        label_h = 28
        max_w = max(w for _, w, _, _ in images) * scale
        max_h = max(h for _, _, h, _ in images) * scale
        rows = (len(images) + cols - 1) // cols
        sheet = Image.new("RGB", (cols * max_w, rows * (max_h + label_h)), (30, 30, 30))
        draw = ImageDraw.Draw(sheet)
        for i, (label, w, h, rgb) in enumerate(images):
            img = Image.new("RGB", (w, h))
            img.putdata(rgb)
            img = img.resize((w * scale, h * scale), Image.Resampling.NEAREST)
            x = (i % cols) * max_w
            y = (i // cols) * (max_h + label_h)
            sheet.paste(img, (x, y))
            draw.text((x + 4, y + max_h + 4), label, fill=(240, 240, 240))
        path.parent.mkdir(parents=True, exist_ok=True)
        sheet.save(path.with_suffix(".png"), compress_level=1)
        return str(path.with_suffix(".png"))
    except Exception:
        return ""


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--resolver", required=True, type=Path)
    ap.add_argument("--texture", required=True)
    ap.add_argument("--palette", required=True, type=Path)
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--scale", type=int, default=8)
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)
    resolver = load_resolver(args.resolver)

    wanted_exts = {"pix", "pak", "vqm", "cbk"}
    header, records = resolver.parse_zfs_records(args.zfs)
    payloads, errors = resolver.decompress_records(args.zfs, records, wanted_exts)
    idx, warnings = resolver.build_asset_index(records, payloads, None)

    asset = resolve_vqm(resolver, idx, args.texture)
    vqm = idx.payloads.get(asset.asset_id, b"")
    cbk_asset, cbk = get_cbk_for_vqm(idx, asset, vqm)
    pal = load_palette(args.palette)

    variants = [
        ("xy", "little"),
        ("yx", "little"),
        ("xy_flipx", "little"),
        ("xy_flipy", "little"),
        ("xy_flipx_flipy", "little"),
        ("yx_flipx", "little"),
        ("yx_flipy", "little"),
        ("yx_flipx_flipy", "little"),
    ]

    images = []
    rows = []
    for variant, endian in variants:
        w, h, pix = decode_vqm_variant(vqm, cbk, variant, endian)
        rgb = render_indexed(w, h, pix, pal)
        label = f"{variant}_{endian}"
        out_path = save_rgb(args.out / "variants" / label, w, h, rgb, args.scale)
        images.append((label, w, h, rgb))
        rows.append({
            "variant": variant,
            "token_endian": endian,
            "width": w,
            "height": h,
            "render_path": out_path,
        })

    sheet_path = save_sheet(args.out / f"{safe_name(asset.name)}_vqm_decode_variants", images, args.scale)

    import csv
    with (args.out / "variant_manifest.csv").open("w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)

    summary = {
        "texture": asset.name,
        "asset_id": asset.asset_id,
        "cbk": cbk_asset.name,
        "palette": str(args.palette),
        "sheet": sheet_path,
        "variants": rows,
        "zfs_errors": len(errors),
        "pix_pak_warnings": len(warnings),
    }
    (args.out / "summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
