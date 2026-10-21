# Original editor: road and terrain serialization

**Evidence baseline:** v16–v20 editor/game static investigations; original retail bytes, original BUILDER documentation, and 40 paired mission layouts. Annotated Ghidra function names are research labels, not original developer symbols.

## Editable road workspace versus runtime road strips

The public builder maintains a road graph of straight and **cubic Bézier** segments with control handles and neighboring links. The editor's `.I76` `ROAD` section stores an array of 0x50-byte road descriptors (0x54-byte live payload). Shape 0 is straight, shape 1 is curve; link indices are stored at offsets `+0x40/+0x44`. Workspace saving: `00415CA0`; loading: `00415AE0`; outer `ROAD` chunk writer: `0041A7E0`. The loader decompilation is incomplete; index restoration still requires native-instruction or genuine workspace verification.

Curves use four Bézier points `P0,P1,P2,P3`: `(1-t)^3 P0 + 3(1-t)^2 t P1 + 3(1-t)t^2 P2 + t^3 P3`. The coefficient routine is `00402E70`. Edge sampling uses an additional distance/parameter search, so ordinary analytic Bézier evaluation alone may not duplicate original sample placement.

Export writes `RDEF` containing `RSEG` records (`004022B0`). Each `RSEG` has an 8-byte tag/length header, then a 4-byte road-kind field, 4-byte cross-section count, and **24 bytes per paired left/right edge sample**. The two serialized Y fields are not authoritative: runtime loader `0048E1A0` replaces them with terrain-sampled heights; `0048E900` renders the resulting polygon strips. Do not treat each 24-byte section as six reliable XYZ floats.

The 80 shipped alternative-render mission files contain **1,302 RSEG chunks**, **179,190 cross-sections**; the 40 actual layouts have identical road geometry in `miss8` and `miss16`. All populated retail road strips have nominal **10-world-unit width**. Two T05 chunks have zero samples and unusual kind `3072`. The builder has a wider-road subtype but the historical documentation says four-lane roads were cut; 20-unit compatibility is **not verified**.

## Terrain data and material semantics

Each active `.TER` zone has 128×128 packed 16-bit samples; bits 15–13 index eight surface materials, bit 12 has an unresolved special purpose, and the lower 12 bits contain packed height. The game uses a **5-world-unit grid** and **0.1 height multiplier**. Historic exporter factor `409.5/4096` differs slightly and should not be substituted for predicting retail runtime height.

The editor writes an eight-entry material property table (20 bytes per entry) into `WRLD`. It grades each road kind into a separate terrain-material plane: kind **0 paved → index 2**, kind **1 unpaved → index 3**, kind **2 riverbed/wash → index 4**. In the examined shipped WRLD tables, indices 6/7 use parameter records equivalent to paved 2/unpaved 3; equal physical parameters do not imply equal index or visible texture.

In the `miss8` corpus, sampled road centerline materials agree with their expected index at **87,551/89,595 (97.72%)**; counting the two known equivalent records yields **88,856/89,595 (99.18%)**. The remaining differences require junction/authoring-context checks, not automatic repainting.

## Original render / grading sequence

The public editor's explicit render command `0040E3C0` rasterizes height zones, merges painted terrain, applies grading lines and object grading, traverses road chains (`00420EE0 → 00421070`), updates objects, and then applies **four road-height smoothing passes** (`00422870`) before packing/merging generated terrain. Separate setters `0041F3A0` (height) and `0041F4A0` (surface) are used. Smoothing is gated on road material classes 2–4, with a missing-height sentinel. A changed road graph without rerendering the underlying terrain can produce mismatched visible roads and driving physics.

**Version boundary:** original public editor writes **WREV 8**; shipped missions use **WREV 9**, with a **13-byte longer WRLD prefix** ahead of the surface records. Compatible tools must dispatch layouts by version.

## Still unresolved

Exactly reproducing the editor's rasterization arithmetic/FPU rounding, all road UV coordinates, **rendered road texture selection**, object-specific intersection leveling, the wider-road mode, and live contact physics remain open. The established **road-kind-to-TER material mapping** must not be misrepresented as proof of the road texture/UV selection.
