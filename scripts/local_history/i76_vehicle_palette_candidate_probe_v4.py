#!/usr/bin/env python3
"""
i76_vehicle_palette_candidate_probe_v4.py

Generate candidate-palette contact sheets for Interstate '76 indexed vehicle
textures.

Purpose:
  The vehicle texture index/UV pipeline appears structurally correct, but the
  palette is wrong. This script decodes selected vehicle texture assets once,
  then renders them through every candidate ACT/trailing palette found in the
  archive, producing contact sheets for visual comparison against known game
  screenshots.

Inputs:
  --zfs I76.ZFS
  --resolver i76_vehicle_texture_slot_resolver_v5.py
  --vehicle vppirna1.vcf / vppirna2.vcf / etc.
  --texture pp11mdl1 / pp11bdy1 / etc.
  --out scratch_data/i76_vehicle_palette_candidates_v2

It uses the resolver module for ZFS decompression, PIX/PAK indexing, VQM/CBK
and M16 asset lookup. It includes a local copy of M16/VQM pixel decode logic.

Outputs:
  palettes/*.act
  palette_manifest.csv
  decoded_indexed/*.pgm
  contact_sheets/*.png or *.ppm
  candidate_scores.csv
  README.md

Notes:
  - Contact sheets are the main product; scores are only rough diagnostics.
  - The script writes both raw and x4-scaled variants for low-range palettes.
  - For visual comparison, prefer x4 variants unless a palette is already 0..255.
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import math
import re
import struct
import sys
from collections import Counter
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple


@dataclass
class PaletteCandidate:
    key: str
    source: str
    asset_name: str
    asset_id: str
    offset: int
    variant: str
    path: str
    max_value: int
    entries: List[Tuple[int, int, int]]


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


def scale_x4(v: int) -> int:
    return max(0, min(255, v * 4))


def maybe_x4_palette(entries: List[Tuple[int, int, int]]) -> List[Tuple[int, int, int]]:
    mx = max(max(c) for c in entries) if entries else 0
    if mx <= 63:
        return [(scale_x4(r), scale_x4(g), scale_x4(b)) for r, g, b in entries]
    return entries


def write_act(path: Path, entries: List[Tuple[int, int, int]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("wb") as f:
        for r, g, b in entries[:256]:
            f.write(bytes([r & 0xff, g & 0xff, b & 0xff]))


def write_pgm(path: Path, w: int, h: int, pixels: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("wb") as f:
        f.write(f"P5\n{w} {h}\n255\n".encode("ascii"))
        f.write(pixels)


def write_rgb_image(path_no_ext: Path, w: int, h: int, pixels: List[Tuple[int, int, int]]) -> str:
    path_no_ext.parent.mkdir(parents=True, exist_ok=True)
    try:
        from PIL import Image  # type: ignore
        img = Image.new("RGB", (w, h))
        img.putdata(pixels)
        out = path_no_ext.with_suffix(".png")
        img.save(out)
        return str(out)
    except Exception:
        out = path_no_ext.with_suffix(".ppm")
        with out.open("wb") as f:
            f.write(f"P6\n{w} {h}\n255\n".encode("ascii"))
            for r, g, b in pixels:
                f.write(bytes([r & 0xff, g & 0xff, b & 0xff]))
        return str(out)


def render_indexed(w: int, h: int, pixels: bytes, pal: List[Tuple[int, int, int]]) -> List[Tuple[int, int, int]]:
    out = []
    for px in pixels:
        out.append(pal[px] if px < len(pal) else (255, 0, 255))
    return out


def parse_m16_pixels(data: bytes) -> Optional[Tuple[int, int, bytes]]:
    if len(data) < 8:
        return None
    w, hf = struct.unpack_from("<II", data, 0)
    h = hf & 0x1FFFFFFF
    if not (0 < w <= 4096 and 0 < h <= 4096):
        return None
    need = 8 + w * h
    if len(data) < need:
        return None
    return w, h, data[8:need]


def decode_vqm_pixels(data: bytes, cbk_data: bytes) -> Optional[Tuple[int, int, bytes]]:
    if len(data) < 0x18 or len(cbk_data) < 4:
        return None
    w, hf = struct.unpack_from("<II", data, 0)
    h = hf & 0x1FFFFFFF
    if not (0 < w <= 4096 and 0 < h <= 4096):
        return None
    tiles_x = (w + 3) // 4
    tiles_y = (h + 3) // 4
    token_count = tiles_x * tiles_y
    if len(data) < 0x18 + 2 * token_count:
        return None
    pixels = bytearray(w * h)
    pos = 0x18
    for by in range(tiles_y):
        for bx in range(tiles_x):
            tok = struct.unpack_from("<H", data, pos)[0]
            pos += 2
            if tok & 0x8000:
                tile = bytes([tok & 0xff]) * 16
            else:
                tile_off = 4 + tok * 16
                if tile_off + 16 > len(cbk_data):
                    tile = bytes([0]) * 16
                else:
                    tile = cbk_data[tile_off:tile_off + 16]
            for sy in range(4):
                py = by * 4 + sy
                if py >= h:
                    continue
                for sx in range(4):
                    px = bx * 4 + sx
                    if px >= w:
                        continue
                    pixels[py * w + px] = tile[sx * 4 + sy]
    return w, h, bytes(pixels)


def decode_texture_asset(resolver, idx, asset) -> Optional[Tuple[int, int, bytes, str]]:
    data = idx.payloads.get(asset.asset_id, b"")
    if asset.ext == "m16":
        parsed = parse_m16_pixels(data)
        if parsed:
            return parsed[0], parsed[1], parsed[2], "m16"
    if asset.ext == "vqm":
        cbk_ref = cstring(data[0x08:0x14]).upper() if len(data) >= 0x14 else ""
        if cbk_ref and "." not in cbk_ref:
            cbk_ref += ".CBK"
        cbk = idx.resolve(cbk_ref, "cbk", source=asset) if cbk_ref else None
        if cbk:
            parsed = decode_vqm_pixels(data, idx.payloads.get(cbk.asset_id, b""))
            if parsed:
                return parsed[0], parsed[1], parsed[2], "vqm_cbk:" + cbk.name
    return None


def find_texture_assets(resolver, idx, names: Sequence[str]) -> List[object]:
    out = []
    seen = set()
    for name in names:
        n = name.strip()
        if not n:
            continue
        stem = n.rsplit(".", 1)[0] if "." in n else n
        for ext in ["m16", "vqm"]:
            refs = [n] if "." in n else [stem + "." + ext.upper(), stem + "." + ext.lower(), stem]
            for ref in refs:
                a = idx.resolve(ref, ext, source=None)
                if a and a.asset_id not in seen:
                    out.append(a)
                    seen.add(a.asset_id)
                    break
    return out


def extract_act_candidates(idx, out_dir: Path) -> List[PaletteCandidate]:
    candidates: List[PaletteCandidate] = []
    pal_dir = out_dir / "palettes"
    seen_bytes = set()

    for asset in idx.assets:
        data = idx.payloads.get(asset.asset_id, b"")
        ext = getattr(asset, "ext", "").lower()
        if not data:
            continue

        candidates_offsets: List[Tuple[str, int, bytes]] = []

        if ext == "act" and len(data) >= 768:
            candidates_offsets.append(("act_full", 0, data[:768]))

        # trailing PCX-style palette marker 0x0c + 768 RGB bytes
        if len(data) >= 769 and data[-769] == 0x0c:
            candidates_offsets.append(("pcx_trailing_marker", len(data) - 768, data[-768:]))

        # generic trailing 768 bytes for known image-ish records only
        if ext in {"pcx", "p", "pix", "m16", "vqm"} and len(data) >= 768:
            tail = data[-768:]
            if len(set(tail)) > 16:
                candidates_offsets.append(("generic_trailing_768", len(data) - 768, tail))

        for kind, off, raw768 in candidates_offsets:
            if raw768 in seen_bytes:
                continue
            seen_bytes.add(raw768)
            entries_raw = [(raw768[i * 3], raw768[i * 3 + 1], raw768[i * 3 + 2]) for i in range(256)]
            maxv = max(max(c) for c in entries_raw)
            variants = [("raw", entries_raw)]
            if maxv <= 63:
                variants.append(("x4", [(scale_x4(r), scale_x4(g), scale_x4(b)) for r, g, b in entries_raw]))
            for variant, entries in variants:
                key = f"{safe_name(asset.name)}_{asset.asset_id}_{kind}_{off}_{variant}"
                path = pal_dir / (key + ".act")
                write_act(path, entries)
                candidates.append(PaletteCandidate(
                    key=key,
                    source=kind,
                    asset_name=asset.name,
                    asset_id=asset.asset_id,
                    offset=off,
                    variant=variant,
                    path=str(path),
                    max_value=max(max(c) for c in entries),
                    entries=entries,
                ))

    return candidates


def load_extra_palettes(paths: Sequence[Path], out_dir: Path) -> List[PaletteCandidate]:
    out = []
    pal_dir = out_dir / "palettes"
    for p in paths:
        data = p.read_bytes()
        if len(data) < 768:
            continue
        raw = data[:768]
        entries = [(raw[i * 3], raw[i * 3 + 1], raw[i * 3 + 2]) for i in range(256)]
        key = "extra_" + safe_name(p.stem)
        path = pal_dir / (key + ".act")
        write_act(path, entries)
        out.append(PaletteCandidate(
            key=key,
            source="extra",
            asset_name=p.name,
            asset_id="",
            offset=0,
            variant="as_is",
            path=str(path),
            max_value=max(max(c) for c in entries),
            entries=entries,
        ))
    return out


def contact_sheet_for_texture(
    out_dir: Path,
    tex_name: str,
    w: int,
    h: int,
    pixels: bytes,
    palettes: List[PaletteCandidate],
    max_palettes: int,
    write_individual: bool,
    contact_scale: int,
    contact_page_size: int,
) -> List[dict]:
    rows = []
    sheets_dir = out_dir / "contact_sheets"
    samples_dir = out_dir / "sample_renders"
    indexed_dir = out_dir / "decoded_indexed"
    write_pgm(indexed_dir / (safe_name(tex_name) + ".pgm"), w, h, pixels)

    use = palettes[:max_palettes] if max_palettes > 0 else palettes

    # Write individual renders and collect rough diagnostic stats.
    for pal in use:
        rgb = render_indexed(w, h, pixels, pal.entries)
        out_path = ""
        if write_individual:
            out_path = write_rgb_image(samples_dir / f"{safe_name(tex_name)}__{safe_name(pal.key)}", w, h, rgb)
        avg = tuple(sum(c[i] for c in rgb) / max(1, len(rgb)) for i in range(3))
        unique_indices = len(set(pixels))
        blueish = sum(1 for r, g, b in rgb if b > r + 15 and b > g + 5)
        green_orange = sum(1 for r, g, b in rgb if (g > b + 20 and g > r - 10) or (r > b + 30 and g > b + 10))
        rows.append({
            "candidate_id": len(rows),
            "texture": tex_name,
            "width": w,
            "height": h,
            "palette_key": pal.key,
            "palette_source": pal.source,
            "palette_asset": pal.asset_name,
            "palette_variant": pal.variant,
            "palette_path": pal.path,
            "render_path": out_path,
            "unique_indices": unique_indices,
            "avg_r": round(avg[0], 2),
            "avg_g": round(avg[1], 2),
            "avg_b": round(avg[2], 2),
            "blueish_pixels": blueish,
            "green_orange_pixels": green_orange,
            "blue_minus_green_orange": blueish - green_orange,
        })

    # Contact sheets: paginated, larger labels, fixed nearest-neighbor scale.
    try:
        from PIL import Image, ImageDraw  # type: ignore
        scale = max(1, int(contact_scale))
        page_size = max(1, int(contact_page_size))
        thumb_w, thumb_h = w * scale, h * scale
        label_h = 48
        cols = 4
        sheets_dir.mkdir(parents=True, exist_ok=True)
        for page_start in range(0, len(use), page_size):
            page = use[page_start:page_start + page_size]
            total_rows = (len(page) + cols - 1) // cols
            cell_w, cell_h = thumb_w, thumb_h + label_h
            sheet = Image.new("RGB", (cols * cell_w, max(1, total_rows) * cell_h), (30, 30, 30))
            draw = ImageDraw.Draw(sheet)
            for j, pal in enumerate(page):
                i = page_start + j
                rgb = render_indexed(w, h, pixels, pal.entries)
                img = Image.new("RGB", (w, h))
                img.putdata(rgb)
                img = img.resize((thumb_w, thumb_h), Image.Resampling.NEAREST)
                x = (j % cols) * cell_w
                y = (j // cols) * cell_h
                sheet.paste(img, (x, y))
                label1 = f"#{i:03d} {pal.asset_name[:28]}"
                label2 = f"{pal.source}/{pal.variant}"
                draw.text((x + 2, y + thumb_h + 2), label1, fill=(240, 240, 240))
                draw.text((x + 2, y + thumb_h + 20), label2, fill=(210, 210, 210))
            sheet_path = sheets_dir / (safe_name(tex_name) + f"_palette_contact_sheet_page_{page_start // page_size + 1:03d}.png")
            sheet.save(sheet_path, compress_level=1)
    except Exception:
        # Individual renders still exist if enabled.
        pass

    return rows


def write_csv(path: Path, rows: List[dict], fields: Optional[List[str]] = None) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if not rows:
        path.write_text("", encoding="utf-8")
        return
    if fields is None:
        fields = list(rows[0].keys())
    with path.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for row in rows:
            w.writerow({k: row.get(k, "") for k in fields})


def write_palette_manifest(path: Path, pals: List[PaletteCandidate]) -> None:
    rows = []
    for p in pals:
        d = asdict(p)
        d.pop("entries", None)
        rows.append(d)
    write_csv(path, rows)


def write_readme(path: Path, rows: List[dict], textures: List[str]) -> None:
    lines = []
    lines.append("# I76 vehicle palette candidate probe")
    lines.append("")
    lines.append("This pass renders selected indexed vehicle textures through every candidate palette.")
    lines.append("The goal is visual identification of the palette that matches known screenshots.")
    lines.append("")
    lines.append("## Textures")
    for t in textures:
        lines.append(f"- {t}")
    lines.append("")
    lines.append("## Top blue-favoring candidates")
    lines.append("")
    lines.append("| texture | palette | source | variant | blue-green score | avg RGB |")
    lines.append("|---|---|---|---|---:|---|")
    for r in sorted(rows, key=lambda x: int(x.get("blue_minus_green_orange", 0)), reverse=True)[:40]:
        lines.append(f"| {r['texture']} | {r['palette_key']} | {r['palette_source']} | {r['palette_variant']} | {r['blue_minus_green_orange']} | {r['avg_r']},{r['avg_g']},{r['avg_b']} |")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")



def filter_palettes_by_sources(palettes: List[PaletteCandidate], source_text: str) -> List[PaletteCandidate]:
    wanted = {s.strip().lower() for s in source_text.split(",") if s.strip()}
    if "all" in wanted:
        return palettes
    out = []
    for p in palettes:
        src = p.source.lower()
        if "extra" in wanted and src == "extra":
            out.append(p)
        elif "act" in wanted and src == "act_full":
            out.append(p)
        elif "pcx" in wanted and src == "pcx_trailing_marker":
            out.append(p)
        elif "generic" in wanted and src == "generic_trailing_768":
            out.append(p)
    return out

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--zfs", required=True, type=Path)
    ap.add_argument("--resolver", required=True, type=Path)
    ap.add_argument("--out", required=True, type=Path)
    ap.add_argument("--texture", action="append", default=[], help="Texture basename/name to render. Repeatable.")
    ap.add_argument("--vehicle", action="append", default=[], help="Optional vehicle name for README context only.")
    ap.add_argument("--extra-palette", action="append", default=[], type=Path)
    ap.add_argument("--max-palettes", type=int, default=80, help="Maximum palettes per contact sheet. Default 80. Use 0 for all.")
    ap.add_argument("--palette-sources", default="act,extra", help="Comma list: act,pcx,generic,extra,all. Default act,extra.")
    ap.add_argument("--write-individual-renders", action="store_true", help="Also write one image per texture/palette candidate. Default is contact sheets only.")
    ap.add_argument("--contact-scale", type=int, default=4, help="Nearest-neighbor upscale factor for contact-sheet thumbnails. Default 4.")
    ap.add_argument("--contact-page-size", type=int, default=40, help="Number of palette candidates per contact-sheet page. Default 40.")
    args = ap.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)
    resolver = load_resolver(args.resolver)

    wanted_exts = {"vcf", "vdf", "vtf", "pix", "pak", "tmt", "map", "m16", "vqm", "cbk", "act", "pcx", "p"}
    header, records = resolver.parse_zfs_records(args.zfs)
    payloads, errors = resolver.decompress_records(args.zfs, records, wanted_exts)
    idx, warnings = resolver.build_asset_index(records, payloads, None)

    print("[palette] extracting candidates", flush=True)
    palettes_all = extract_act_candidates(idx, args.out)
    palettes_all.extend(load_extra_palettes(args.extra_palette, args.out))
    palettes_all.sort(key=lambda p: (p.source, p.asset_name.lower(), p.variant, p.key))
    write_palette_manifest(args.out / "palette_manifest_all.csv", palettes_all)
    palettes = filter_palettes_by_sources(palettes_all, args.palette_sources)
    palettes.sort(key=lambda p: (p.source, p.asset_name.lower(), p.variant, p.key))
    write_palette_manifest(args.out / "palette_manifest.csv", palettes)
    print(f"[palette] using {len(palettes)} / {len(palettes_all)} candidates from sources={args.palette_sources}", flush=True)

    tex_names = args.texture or [
        "pp11mdl1", "pp11bdy1", "pp11ftf1", "pp11ftl1", "pp11ftt1", "pp11bkb1",
        "pp12mdl1", "pp13mdl1", "pp14mdl1",
    ]
    assets = find_texture_assets(resolver, idx, tex_names)

    all_rows: List[dict] = []
    decoded_rows = []
    for asset in assets:
        decoded = decode_texture_asset(resolver, idx, asset)
        if not decoded:
            decoded_rows.append({"texture": asset.name, "asset_id": asset.asset_id, "status": "decode_failed"})
            continue
        w, h, pix, mode = decoded
        decoded_rows.append({
            "texture": asset.name,
            "asset_id": asset.asset_id,
            "status": "ok",
            "width": w,
            "height": h,
            "mode": mode,
            "unique_indices": len(set(pix)),
            "top_indices": ";".join(f"{k}:{v}" for k, v in Counter(pix).most_common(20)),
        })
        print(f"[render] {asset.name} {w}x{h} palettes={len(palettes)} max={args.max_palettes}", flush=True)
        rows = contact_sheet_for_texture(args.out, asset.name, w, h, pix, palettes, args.max_palettes, args.write_individual_renders, args.contact_scale, args.contact_page_size)
        all_rows.extend(rows)

    write_csv(args.out / "decoded_textures.csv", decoded_rows)
    write_csv(args.out / "candidate_scores.csv", all_rows)
    write_readme(args.out / "README.md", all_rows, [a.name for a in assets])
    (args.out / "summary.json").write_text(json.dumps({
        "zfs": str(args.zfs),
        "palette_candidates": len(palettes),
        "palette_sources": args.palette_sources,
        "contact_scale": args.contact_scale,
        "contact_page_size": args.contact_page_size,
        "decoded_textures": len([r for r in decoded_rows if r["status"] == "ok"]),
        "zfs_errors": len(errors),
        "pix_pak_warnings": len(warnings),
    }, indent=2, sort_keys=True), encoding="utf-8")

    print(json.dumps({
        "out": str(args.out),
        "palette_candidates": len(palettes),
        "palette_sources": args.palette_sources,
        "contact_scale": args.contact_scale,
        "contact_page_size": args.contact_page_size,
        "decoded_textures": len([r for r in decoded_rows if r["status"] == "ok"]),
        "contact_sheets": str(args.out / "contact_sheets"),
    }, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
