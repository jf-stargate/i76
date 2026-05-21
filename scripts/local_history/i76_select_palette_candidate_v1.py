#!/usr/bin/env python3
"""
i76_select_palette_candidate_v1.py

Select one palette from an i76_vehicle_palette_candidate_probe_v4 output folder
and copy it to a stable exporter path.

Typical workflow:
  1. Run i76_vehicle_palette_candidate_probe_v4.py.
  2. Inspect contact_sheets/*.png.
  3. Choose the candidate number shown in the contact sheet cell, e.g. #012.
  4. Run this selector.

Example:
  python3 scripts/i76_select_palette_candidate_v1.py \
    --probe-dir scratch_data/i76_vehicle_palette_candidates_v4_piranha \
    --candidate-id 12 \
    --out scratch_data/palettes/i76_vehicle_palette_selected.act

Then export vehicles with:
  --exporter-arg=--palette-file
  --exporter-arg=scratch_data/palettes/i76_vehicle_palette_selected.act
  --exporter-arg=--palette-scale
  --exporter-arg=raw

Selection modes:
  --candidate-id N
      Select row N from palette_manifest.csv. This matches the #NNN labels on
      v4 contact sheets.

  --key-contains TEXT
      Select first manifest row whose key or asset_name contains TEXT.

  --first-third
      Pick the middle row of the first third of palette_manifest.csv. This is a
      rough convenience mode only; candidate-id is preferred.
"""

from __future__ import annotations

import argparse
import csv
import json
import shutil
from pathlib import Path
from typing import List, Dict, Optional


def read_manifest(path: Path) -> List[dict]:
    if not path.exists():
        raise FileNotFoundError(f"palette manifest not found: {path}")
    with path.open("r", encoding="utf-8", errors="replace", newline="") as f:
        return list(csv.DictReader(f))


def choose_row(rows: List[dict], args: argparse.Namespace) -> tuple[int, dict]:
    if not rows:
        raise ValueError("palette manifest is empty")

    if args.candidate_id is not None:
        idx = args.candidate_id
        if idx < 0 or idx >= len(rows):
            raise IndexError(f"--candidate-id {idx} outside manifest range 0..{len(rows)-1}")
        return idx, rows[idx]

    if args.key_contains:
        needle = args.key_contains.lower()
        for i, row in enumerate(rows):
            hay = " ".join([
                row.get("key", ""),
                row.get("asset_name", ""),
                row.get("source", ""),
                row.get("variant", ""),
                row.get("path", ""),
            ]).lower()
            if needle in hay:
                return i, row
        raise ValueError(f"no palette candidate contained: {args.key_contains!r}")

    if args.first_third:
        # "First third" on a contact sheet is visual shorthand. Pick the midpoint
        # of the first third so the result is stable, but ask users to switch to
        # --candidate-id once they identify the exact good cell.
        end = max(1, len(rows) // 3)
        idx = max(0, end // 2)
        return idx, rows[idx]

    raise ValueError("choose one of --candidate-id, --key-contains, or --first-third")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--probe-dir", required=True, type=Path, help="Output folder from i76_vehicle_palette_candidate_probe_v4.py")
    ap.add_argument("--candidate-id", type=int, default=None, help="Candidate number from v4 contact sheet label, e.g. #012 -> 12")
    ap.add_argument("--key-contains", default="", help="Select first candidate whose key/asset/source contains this text")
    ap.add_argument("--first-third", action="store_true", help="Convenience fallback: select midpoint of first third of manifest")
    ap.add_argument("--out", required=True, type=Path, help="Stable output ACT path")
    ap.add_argument("--manifest", default="palette_manifest.csv", help="Manifest filename inside --probe-dir")
    args = ap.parse_args()

    manifest_path = args.probe_dir / args.manifest
    rows = read_manifest(manifest_path)
    idx, row = choose_row(rows, args)

    src_path = Path(row.get("path", ""))
    if not src_path.is_absolute():
        # Manifest paths are usually written as relative-to-current-run paths,
        # but may also be relative to the probe directory in copied bundles.
        if src_path.exists():
            pass
        elif (args.probe_dir / src_path).exists():
            src_path = args.probe_dir / src_path

    if not src_path.exists():
        raise FileNotFoundError(f"selected palette file does not exist: {src_path}")

    args.out.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(src_path, args.out)

    summary = {
        "probe_dir": str(args.probe_dir),
        "manifest": str(manifest_path),
        "selected_candidate_id": idx,
        "selected_key": row.get("key", ""),
        "selected_source": row.get("source", ""),
        "selected_asset_name": row.get("asset_name", ""),
        "selected_variant": row.get("variant", ""),
        "selected_original_path": str(src_path),
        "out": str(args.out),
        "note": "Use exporter --palette-scale raw for this copied ACT file.",
    }

    sidecar = args.out.with_suffix(args.out.suffix + ".json")
    sidecar.write_text(json.dumps(summary, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
