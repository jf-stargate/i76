# Interstate ’76 Material and Texture Extraction Reference

This page documents the current reverse-engineered material and texture extraction process for Interstate ’76 vehicle models. It is intended as a durable human-readable and machine-actionable reference for GitHub, future handoff, and regression testing.

Status: reverse-engineered from retail `i76.exe`, validated against the retail archive corpus, Open76 where useful, and repeated Blender visual inspection.

## Scope

This document covers:

- How GEO face texture slots resolve to vehicle materials.
- How VTF, TMT, MAP, M16, VQM, CBK, and ACT resources participate in material extraction.
- Current texture decoding rules.
- Palette handling.
- OBJ/MTL material export policy.
- Transparency/alpha handling.
- Debug artifacts that should be preserved for durable validation.

This document does not fully cover:

- Full runtime animation of TMT frames.
- All non-vehicle scene material conventions.
- Exact DirectDraw/Direct3D render-state behavior.
- Complete software rasterizer span behavior.
- Every alpha/translucency edge case across the full vehicle corpus.

## High-Level Material Extraction Chain

The material path begins with a per-face GEO texture slot, then resolves through vehicle texture tables and texture payloads:

```text
+-----------------+------------------------+----------------------------+----------------------------------------------------+
| Stage           | Input                  | Output                     | Purpose                                            |
+-----------------+------------------------+----------------------------+----------------------------------------------------+
| Vehicle config  | VCF / VCFC             | VDF + VTF refs             | Find vehicle definition and texture map set        |
| Geometry        | GEO face texture_name  | raw slot / normalized slot | Per-face material key source                       |
| Texture map set | VTF / VTFC             | TMT slots + MAP slots      | Resolve semantic vehicle material slots            |
| Texture set     | TMT                    | frame basenames            | Resolve animated/static texture frames             |
| Image resource  | M16 / VQM + CBK        | indexed pixels             | Decode texture image data                          |
| Palette         | ACT                    | RGB/RGBA image             | Convert indexed pixels to exportable PNG           |
| Material export | runtime material model | MTL + TSV/JSON             | Represent resolved materials for Blender/debugging |
+-----------------+------------------------+----------------------------+----------------------------------------------------+
```

Current practical flow:

```text
GEO face.texture_name
  -> normalize GEO material slot
  -> VTF TMT/MAP slot lookup or direct texture lookup
  -> TMT frame basename when applicable
  -> prefer VQM over M16 where source evidence supports it
  -> decode indexed pixels
  -> apply selected ACT palette
  -> export PNG + MTL material
  -> preserve TSV/JSON debug evidence
```

## Core Principle

The material exporter should separate source evidence from Blender display policy.

Source evidence includes:

```text
GEO face RGB
GEO surface flags
GEO texture_name
normalized material slot
resolved TMT/MAP/M16/VQM/CBK asset
raw indexed texture pixels
palette source
alpha/transparency flags
```

Blender display policy includes:

```text
MTL Kd value
PNG RGB/RGBA conversion
alpha clipping/blending settings
texture interpolation mode
material splitting policy
```

The current baseline intentionally preserves all source evidence in TSV/JSON while using conservative Blender display choices that match observed vehicles.

## GEO Face Material Fields

Each GEO face carries these material-relevant fields:

```c
struct geo_face_material_fields {
    uint8_t  rgb[3];                // raw GEO face color
    float    surface_plane[4];      // also used by geometry/runtime section
    uint32_t unk3;
    uint8_t  flags[3];             // surface/material/render flags
    char     texture_name[13];      // material slot or direct texture name
    uint32_t unk4;
    uint32_t unk5;
};
```

Important interpretation:

- `texture_name` is the primary material-resolution key.
- `rgb` is real source data, but should not be used as default diffuse tint for textured OBJ materials.
- `flags[1]` is relevant for transparency in Open76-style behavior, but global application is unsafe.
- All fields should be preserved in debug outputs.

## GEO Slot Resolution Rules

Current slot resolution behavior:

```text
+-------------------------------+-------------------------------------------------------------------------+-----------------------------------------------------+
| Case                          | Rule                                                                    | Confidence / notes                                  |
+-------------------------------+-------------------------------------------------------------------------+-----------------------------------------------------+
| Empty GEO texture_name        | Treat as color-only/untextured face                                     | High; binary leaves runtime texture slot empty      |
| GEO texture_name contains dot | Treat as direct resource-style texture reference                        | High; constructor copies direct dotted name         |
| GEO texture_name without dot  | Try basename + .tmt first                                               | High; binary tries TMT first                        |
| TMT missing                   | Fallback to basename + .map                                             | High; binary fallback behavior observed             |
| BODY slot                     | Resolve through VTF BODY/map path; prefer same-stem VQM when configured | Medium-high; fixed visible Piranha body/sill issues |
| LF vs LT                      | Normalize GEO LF to VTF/TMT LT where appropriate                        | Medium-high; observed asset naming convention       |
| Direct .MAP with VQM sibling  | Prefer VQM over M16 when --direct-map-prefer vqm                        | High for vehicles; fixed known Piranha bad bindings |
| Unresolved slot               | Emit unresolved material and preserve evidence                          | High; do not guess silently                         |
+-------------------------------+-------------------------------------------------------------------------+-----------------------------------------------------+
```

The resolver should emit both `raw_slot` and `normalized_slot` for every face. This allows later review of whether an apparent material problem is caused by original GEO data, normalization, or downstream texture selection.

## VTF / VTFC Texture Map Set

The `VTF`/`VTFC` resource provides vehicle-specific texture-slot mapping.

```text
+-------------------+------------------------------------------------------------------------------------+
| Field / concept   | Current understanding                                                              |
+-------------------+------------------------------------------------------------------------------------+
| TMT slot count    | 78                                                                                 |
| MAP slot count    | 13                                                                                 |
| Slot string size  | 13-byte fixed C-string-ish names                                                   |
| Six-face suffixes | FT.map, BK.map, RT.map, LF.map, TP.map, UN.map                                     |
| Paint/body map    | BODY path resolves through VTF map references                                      |
| Normalization     | GEO slot names may differ from VTF/TMT file stems; resolver normalizes known cases |
+-------------------+------------------------------------------------------------------------------------+
```

Known six-face suffixes:

```text
FT.map  front
BK.map  back
RT.map  right
LF.map  left
TP.map  top
UN.map  under / underside
```

The project currently normalizes some left-side conventions because GEO and VTF/TMT naming are not always identical. For example, GEO may refer to `LF` while VTF/TMT resources may use `LT`.

## TMT Texture Set / Animation Frame List

`TMT` resources map a material slot to one or more frame basenames.

```text
+--------+-----------------------+----------------------------------------+
| Offset | Field                 | Meaning                                |
+--------+-----------------------+----------------------------------------+
| +0x14  | dimension_count       | Number of dimension values             |
| +0x18  | dimension_values[]    | Texture-set dimension/control values   |
| +0x28  | animation period/rate | Runtime timer divisor/rate             |
| +0x2c  | flags                 | bit0 animation enabled; bit1 ping-pong |
| +0x40  | frame_names[][8]      | Packed 8-byte frame basenames          |
+--------+-----------------------+----------------------------------------+
```

Current static export behavior:

- Parse all frame names.
- Resolve the first usable frame for OBJ/MTL preview.
- Preserve animation-related fields in debug outputs where available.
- Do not yet attempt to reproduce runtime animated material timing in OBJ.

TMT flags currently interpreted:

```text
bit 0x01  animation enabled
bit 0x02  ping-pong animation
else      linear/default timer
```

## Texture Resource Selection

The current texture selector prefers source-truth and visual correctness over a naive extension order.

```text
+------------------------+---------------------------------------------------+-------------------------------------------------------------+
| Candidate              | Preferred when                                    | Notes                                                       |
+------------------------+---------------------------------------------------+-------------------------------------------------------------+
| VQM + CBK              | Same-stem VQM exists and VQM preference is active | Best vehicle baseline; 4x4 block-compressed indexed texture |
| M16                    | No VQM sibling or M16 explicitly preferred        | Simple indexed image payload                                |
| MAP                    | Intermediate/reference name                       | Often resolves onward to M16/VQM/TMT depending context      |
| TMT first frame        | GEO slot resolves to TMT                          | Current static OBJ export uses first resolved frame         |
| Raw unresolved payload | Decode fails or unsupported                       | Write raw/debug evidence instead of dropping record         |
+------------------------+---------------------------------------------------+-------------------------------------------------------------+
```

Important vehicle baseline rule:

```text
--direct-map-prefer vqm
```

This rule fixed known Piranha failures where literal `.MAP` slots resolved to small or incorrect M16 assets despite same-stem VQM textures being present.

Problematic examples from earlier validation:

```text
PP11BKU1.MAP -> pp11bku1.M16  # wrong for visual baseline
PP11FTU1.MAP -> pp11ftu1.M16  # wrong for visual baseline
PP11PIPE.MAP -> PP11PIPE.M16  # wrong for visual baseline

Same-stem VQM siblings exist:
pp11bku1.vqm
pp11ftu1.vqm
PP11PIPE.vqm
```

## BODY Slot Special Case

The BODY slot is especially important for vehicle paint/body panels. A regression showed that resolving BODY through M16 caused hood/door-sill/body color issues. The current baseline prefers same-stem VQM for BODY/VTF map paths when `--direct-map-prefer vqm` is active.

This rule restored the Piranha body color and door-sill behavior after alpha/material experiments caused regressions.

## M16 Decoding

Current `M16` layout:

```c
struct m16_header_like {
    uint32_t width;                 // +0x00
    uint32_t height_flags;          // +0x04
    uint8_t  pixels[width*height];  // +0x08
    uint8_t  trailing[];            // variable
};
```

Interpretation:

```text
width            = uint32 at +0x00
height           = height_flags & 0x1fffffff
pixel format     = 8-bit indexed color
palette required = yes
```

`M16` should not be considered inherently wrong. It is wrong only when a specific material path should have selected a better same-stem VQM sibling.

## VQM / CBK Decoding

`VQM` is a 4x4 block-compressed indexed texture. `CBK` is the tile codebook.

```text
+-----------------------------+---------------------------------------------------------+
| Component                   | Layout / rule                                           |
+-----------------------------+---------------------------------------------------------+
| VQM +0x00                   | uint32 width                                            |
| VQM +0x04                   | uint32 height_flags; height = height_flags & 0x1fffffff |
| VQM +0x08                   | char cbk_name[12]                                       |
| VQM +0x14                   | unknown/control field                                   |
| VQM +0x18                   | uint16 block_tokens[]                                   |
| CBK +0x00                   | uint32 tile_count                                       |
| CBK +0x04                   | tiles[tile_count][16]                                   |
| token no high bit           | copy tile at cbk + 4 + token * 16                       |
| token high bit set          | fill 4x4 block with token & 0xff                        |
| token count                 | ceil(width/4) * ceil(height/4)                          |
| validated intra-tile layout | yx: tile[sy * 4 + sx]                                   |
+-----------------------------+---------------------------------------------------------+
```

The validated intra-tile layout is:

```python
pixel = tile[sy * 4 + sx]
```

Current command-line baseline:

```text
--vqm-layout yx
```

Earlier `xy` layouts produced visibly aliased or incorrect textures.

## Palette Handling

Texture payloads are indexed color. Correct RGB preview/export depends on using the right palette.

```text
+----------------------------+---------------------------------------+----------------------------------------------------------------------+
| Palette source             | Status                                | Notes                                                                |
+----------------------------+---------------------------------------+----------------------------------------------------------------------+
| EXE 004fa170               | Do not use as default vehicle palette | Runtime active palette buffer, not necessarily final vehicle palette |
| p02.act                    | Current vehicle baseline              | Matches Open76 hardcoded baseline and visual probes                  |
| ACT raw scale              | Use --palette-scale raw               | Selected archive ACT appears already in 0..255 RGB range             |
| Palette-nearest face color | Use for untextured faces              | Approximates runtime nearest palette color path                      |
+----------------------------+---------------------------------------+----------------------------------------------------------------------+
```

Recommended palette selection command:

```bash
python3 scripts/i76_select_palette_candidate_v1.py \
  --probe-dir scratch_data/i76_vehicle_palette_candidates_v4_piranha \
  --key-contains p02.act \
  --out scratch_data/palettes/i76_vehicle_palette_selected.act
```

Recommended export options:

```text
--palette-file scratch_data/palettes/i76_vehicle_palette_selected.act
--palette-scale raw
```

## Kd / Polygon Color Policy

The current OBJ/MTL policy is:

```text
+-------------------------------+------------------------------------+------------------------------------------------------------+
| Face type                     | Default Kd policy                  | Reason                                                     |
+-------------------------------+------------------------------------+------------------------------------------------------------+
| Textured face                 | White Kd                           | Prevents Blender/MTL from tinting map_Kd with GEO face RGB |
| Untextured face               | GEO RGB / palette-nearest          | Color-only faces need face color as visible material       |
| Diagnostic textured tint      | --textured-kd-mode geo-direct      | Available for experiments only; not baseline               |
| Palette-nearest textured tint | --textured-kd-mode palette-nearest | Diagnostic only; can reveal runtime color evidence         |
+-------------------------------+------------------------------------+------------------------------------------------------------+
```

Why textured `Kd` defaults to white:

- OBJ/MTL importers usually multiply `map_Kd` by `Kd`.
- GEO face RGB values are not symmetric or paint-like for many textured faces.
- Applying GEO RGB to textured faces caused visible asymmetric and implausible color artifacts.
- Open76 uses color materials when texture names are absent; textured faces resolve to texture materials.

The exporter should still preserve source color evidence:

```text
geo_face_color
nearest_palette_index
diffuse_source
surface_flags
```

These fields belong in TSV/JSON even when they are not used as Blender material tint.

## Alpha / Transparency Policy

Alpha handling is the most sensitive material area. The current baseline avoids broad alpha rules.

```text
+-------------------+-------------------------------------------------------+----------------------------------------------------+
| Alpha mode        | Behavior                                              | Status                                             |
+-------------------+-------------------------------------------------------+----------------------------------------------------+
| opaque            | No PNG alpha; all textures opaque                     | Safe baseline for body/opaque materials            |
| index-ff          | Palette index 0xff transparent globally               | Rejected as default; creates hood/trunk/body holes |
| transparent-flags | Alpha for faces with surface flag byte 1 equal 5 or 7 | Too broad for OBJ/Blender baseline                 |
| light-flags       | Targeted alpha for flagged light overlay geometry     | Current practical baseline                         |
+-------------------+-------------------------------------------------------+----------------------------------------------------+
```

Rejected rule:

```text
palette index 0xff is always transparent
```

Reason: this created unwanted holes in body/hood/trunk areas, because some opaque materials use index `0xff` in pixels that can be sampled by opaque polygons.

Current practical rule:

```text
Apply alpha narrowly for transparent-flagged light overlay geometry.
```

Known Piranha light overlay objects:

```text
PP11HLGT.GEO
PP11BLGT.GEO
PP11TLGT.GEO
```

These used transparent-style flags and were visually corrected by targeted alpha without reintroducing body/hood/trunk holes.

## Material Splitting Policy

OBJ/MTL materials are not per-polygon unless explicitly split. Earlier experiments split textured materials by GEO face color, but that was not the correct baseline because textured face RGB should not drive `Kd`.

Current policy:

- Split materials by texture asset and transparency/display requirements.
- Do not split by GEO RGB for textured faces by default.
- Preserve per-face color in debug outputs.
- Split opaque and alpha variants when the same texture must be used with different alpha policies.
- Keep material names stable and traceable to resolved source assets.

Recommended material key contents:

```text
resolved texture stem
resolved asset type
alpha policy suffix when applicable
optional diagnostic suffix
```

## Blender Material Settings

After OBJ import, Blender may not respect all intended material behavior from MTL alone. The exporter may emit:

```text
blender_apply_i76_material_settings.py
```

The helper should:

- Set texture interpolation to closest/nearest for indexed-pixel authenticity.
- Enable alpha clipping only for materials known to require alpha.
- Avoid applying alpha settings globally.
- Avoid altering material diffuse color for textured materials unless explicitly requested.
- Keep body/paint materials opaque.

## Machine-Readable Debug Artifacts

Durable extraction should emit:

```text
+----------------------------------------+--------+------------------------------------------------------------+
| Artifact                               | Format | Purpose                                                    |
+----------------------------------------+--------+------------------------------------------------------------+
| materials.tsv                          | TSV    | Per-material debug inventory                               |
| material_binding.tsv                   | TSV    | Per-face material resolution evidence                      |
| face_mapping.tsv                       | TSV    | Face/slot/UV/material/flag details                         |
| render_records.json                    | JSON   | Runtime-equivalent render record structure                 |
| textures/*.png                         | PNG    | Decoded indexed texture images using selected palette      |
| *.mtl                                  | MTL    | OBJ material definitions                                   |
| *.obj                                  | OBJ    | Final view/export mesh using resolved materials            |
| blender_apply_i76_material_settings.py | Python | Blender material cleanup: alpha/nearest filtering settings |
+----------------------------------------+--------+------------------------------------------------------------+
```

Minimum recommended per-face TSV fields:

```text
vehicle
vdf
vtf
geo
part
parent
face_index
runtime_section_index
raw_slot
normalized_slot
resolved_kind
resolved_name
texture_asset
material_name
surface_flags
geo_face_color
nearest_palette_index
texture_transparency_enabled
texture_alpha_mode
raw_u_min
raw_u_max
raw_v_min
raw_v_max
```

Minimum recommended per-material TSV fields:

```text
vehicle
material_name
raw_slot
normalized_slot
resolved_kind
resolved_name
resolved_asset_id
texture_asset_name
texture_asset_id
texture_output_path
kd_policy
diffuse_color
geo_face_color_sample
alpha_policy
contains_alpha
source_evidence
```

## Current Baseline Command

Current Piranha material extraction baseline with the v13 modeller:

```bash
python3 scripts/i76_binary_geo_modeller_v13.py \
  --zfs orig/I76.ZFS \
  --zix orig/I76.ZIX \
  --resolver scripts/i76_vehicle_texture_slot_resolver_v5.py \
  --helper-exporter scripts/i76_vehicle_geo_obj_export_v20.py \
  --out scratch_data/i76_binary_geo_modeller_v13_piranha_light_alpha \
  --vehicle vppirna1 --vehicle vppirna2 --vehicle vppirna3 \
  --damage-state 0 \
  --export-textures \
  --palette-file scratch_data/palettes/i76_vehicle_palette_selected.act \
  --palette-scale raw \
  --flat-color-mode palette-nearest \
  --vdf-sobj-mode separate \
  --vqm-layout yx \
  --direct-map-prefer vqm \
  --overwrite \
  --tar \
  --tar-out-dir scratch_data/
```

For all vehicles:

```bash
python3 scripts/i76_binary_geo_modeller_v13.py \
  --zfs orig/I76.ZFS \
  --zix orig/I76.ZIX \
  --resolver scripts/i76_vehicle_texture_slot_resolver_v5.py \
  --helper-exporter scripts/i76_vehicle_geo_obj_export_v20.py \
  --out scratch_data/i76_binary_geo_modeller_v13_all_vehicles \
  --all \
  --damage-state 0 \
  --export-textures \
  --palette-file scratch_data/palettes/i76_vehicle_palette_selected.act \
  --palette-scale raw \
  --flat-color-mode palette-nearest \
  --vdf-sobj-mode separate \
  --vqm-layout yx \
  --direct-map-prefer vqm \
  --overwrite \
  --tar \
  --tar-out-dir scratch_data/
```

## Known Material Failure Modes and Fixes

```text
+-----------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| Problem                                       | Cause                                             | Fix / baseline rule                               |
+-----------------------------------------------+---------------------------------------------------+---------------------------------------------------+
| Bad underside/wheelwell/headlight-like colors | Direct .MAP resolved to M16 despite VQM sibling   | --direct-map-prefer vqm                           |
| Aliased VQM decode                            | Wrong CBK intra-tile order                        | --vqm-layout yx                                   |
| Body/hood/door-sill wrong colors              | BODY slot resolving to M16 or textured Kd tinting | BODY VQM preference + white textured Kd           |
| Asymmetric polygon colors                     | Using GEO RGB as Kd for textured materials        | Do not tint textured faces by default             |
| Hood/trunk holes                              | Global index 0xff alpha                           | Do not use global alpha; use targeted light alpha |
| Opaque light overlays                         | No alpha on flagged light geometry                | Use targeted light-flags alpha                    |
| Black auxiliary planes                        | VDF SOBJ/_SOR included in main mesh               | --vdf-sobj-mode separate or skip                  |
+-----------------------------------------------+---------------------------------------------------+---------------------------------------------------+
```

## Validation Checklist

For each vehicle material extraction run, verify:

```text
[ ] No decompression or resource-index failures.
[ ] All expected VDF/VTF refs resolved from VCF/VCFC.
[ ] BODY slot resolves to expected same-stem VQM when available.
[ ] Direct .MAP slots prefer VQM when same-stem VQM exists and preference is active.
[ ] VQM textures use yx layout.
[ ] Selected palette is p02.act/raw or another explicitly validated ACT.
[ ] Textured materials use white Kd by default.
[ ] Untextured materials use GEO face color / palette-nearest.
[ ] Global index-0xff alpha is not enabled.
[ ] Light overlay alpha is targeted and does not affect body textures.
[ ] SOBJ/_SOR auxiliary geometry is separated or skipped.
[ ] materials.tsv and material_binding.tsv preserve raw evidence.
```

## Confidence Levels

```text
+------------------------------------+-----------------------------------+--------------------------------------------------------------------------+
| Area                               | Confidence                        | Notes                                                                    |
+------------------------------------+-----------------------------------+--------------------------------------------------------------------------+
| GEO texture slot extraction        | High                              | Runtime constructor stores/copies texture slot strings                   |
| TMT-first then MAP fallback        | High                              | Observed in binary path                                                  |
| VTF slot counts                    | High                              | Consistent with Open76 and resolver corpus behavior                      |
| VQM/CBK decode                     | High                              | Validated visually and against corpus probes                             |
| yx tile layout                     | High for vehicles                 | xy family visibly wrong for known assets                                 |
| p02.act raw palette                | High for current vehicle baseline | Matches visual checks and Open76                                         |
| Textured Kd white default          | High for Blender/OBJ export       | Avoids incorrect texture tinting                                         |
| Untextured palette-nearest color   | Medium-high                       | Matches binary nearest-palette evidence                                  |
| BODY VQM preference                | Medium-high                       | Validated by Piranha visual correction                                   |
| Targeted light alpha               | Medium                            | Works for observed Piranha lights; needs broad vehicle corpus inspection |
| Full animated TMT runtime behavior | Medium                            | Frame list/flags known; exact runtime timing still not fully exported    |
| General non-vehicle materials      | Medium                            | Likely similar but less exhaustively validated                           |
+------------------------------------+-----------------------------------+--------------------------------------------------------------------------+
```

## Future Work

Recommended next steps:

1. Run the v13 material baseline across the full vehicle corpus.
2. Use the Blender grid import script to inspect all vehicles for:
   - opaque body holes,
   - missing light alpha,
   - incorrect BODY material resolution,
   - wrong VQM/M16 preference,
   - palette outliers.
3. Create a per-vehicle exception registry for alpha policy rather than broadening transparency globally.
4. Add regression tests for Piranha:
   - `PP11BDY1` BODY VQM preference,
   - hood/door-sill color,
   - `PP11HLGT` / `PP11BLGT` / `PP11TLGT` alpha,
   - VQM `yx` decode,
   - white textured Kd.
5. Trace the binary render-state path for `surface_flags` to distinguish alpha, additive, clamp, blend, and light-overlay behavior.
6. Extend material reference pages with representative rows from `material_binding.tsv` for known-good and known-bad cases.
