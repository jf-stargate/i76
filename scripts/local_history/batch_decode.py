#!/usr/bin/env python3

import subprocess
from pathlib import Path
import sys

db = Path("orig/DATABASE.MW2")
decoder = Path("../scripts/cgpt_i76_decode_database_mw2_110_images_palette.py")
pal_dir = Path("pal_candidates/palettes")
out_root = Path("db_110_images_palette_batch")

palettes = sorted(pal_dir.glob("*.pal"))

print(f"Found {len(palettes)} palette files")

if len(palettes) > 128:
    raise SystemExit(f"Refusing to run: expected <=128 palettes, found {len(palettes)}")

out_root.mkdir(parents=True, exist_ok=True)

for pal in palettes:
    out = out_root / pal.stem
    print(f"[+] Decoding with palette: {pal.name}")

    subprocess.run(
        [
            sys.executable,
            str(decoder),
            str(db),
            str(out),
            "--palette",
            str(pal),
        ],
        check=True,
    )

print(f"[+] Done: {out_root}")
