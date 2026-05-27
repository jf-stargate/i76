# Interstate '76 Material and Texture Extraction Reference

This page documents the current material and texture extraction baseline for
vehicles, static scene objects, terrain candidates, and validation geometry.

The current state combines binary-backed resource tracing, the reusable GEO
export path, the embedded PIX/PAK/ZFS resource index, and repeated Blender
inspection.

## Scope

This document covers:

```text
+---------------------------+-------------------------------------------------------------+
| Area                      | Covered                                                     |
+---------------------------+-------------------------------------------------------------+
| GEO face materials        | texture_name, RGB, flags, UVs, per-face source evidence      |
| Static object materials   | SDF/SGEO/GEO material slots and texture export               |
| Vehicle materials         | VTF/TMT/MAP/M16/VQM/CBK chain and VQM-first baseline         |
| Terrain candidates        | direct MAP vs MAP->M16/VQM candidate handling                |
| Palettes                  | ACT selection, mission ACT, global selected palette          |
| Alpha                     | targeted color-key alpha for cutout textures                 |
| OBJ/MTL                   | map_Kd/map_d, Kd policy, material identity preservation      |
+---------------------------+-------------------------------------------------------------+
```

It does not yet fully cover runtime DirectDraw/Direct3D render-state behavior,
complete LUM/TBL/PCF remapping, or exact road material selection.

## Current Material Pipeline Summary

```text
+----------------------+-----------------------------+-----------------------------+
| Source               | Current export path         | Notes                       |
+----------------------+-----------------------------+-----------------------------+
| Vehicle GEO          | VTF/TMT/MAP -> VQM/M16      | VQM-first validated         |
| Static SDF GEO       | GEO texture_name -> VQM/M16 | VQM-first generally correct |
| Static I2D* family   | direct MAP override         | Road/junction family        |
| Static AT_* family   | VQM override                | Ground/pad/floor family     |
| Terrain miss8        | direct 128x128 MAP          | Example TT181SD_.MAP        |
| Terrain miss16       | MAP name -> M16/VQM         | Example TP051DR6.M16/VQM    |
| Sky/environment      | direct MAP or image sibling | Example NK_1CLD2.MAP        |
+----------------------+-----------------------------+-----------------------------+
```

## Practical Static-Material Baseline

For the current M06 `miss8` validation scene, the best static material baseline
is:

```text
--static-texture-map-mode prefer-vqm
--static-texture-override "I2D*=prefer-direct-map"
--static-texture-override "AT_*=prefer-vqm"
--static-uv-v-flip
--static-alpha-mode auto
```

The `--static-uv-v-flip` behavior is now considered required/default for static
GEO UVs.  Without it, material placement is visibly inverted.

## Texture Resource Selection

```text
+--------------------------+-----------------------------------------------------------+
| Mode                     | Behavior                                                  |
+--------------------------+-----------------------------------------------------------+
| prefer-vqm               | Use same-stem VQM first, then M16 fallback                |
| prefer-m16               | Use same-stem M16 first, preserving older behavior        |
| prefer-direct-map        | Use direct indexed MAP payload first, then siblings       |
| auto                     | Direct indexed MAP when present; otherwise M16/VQM path   |
+--------------------------+-----------------------------------------------------------+
```

Current validated family rules:

```text
+---------------------+----------------------+---------------------------------------------+
| Texture family      | Rule                 | Evidence / notes                            |
+---------------------+----------------------+---------------------------------------------+
| ordinary building   | prefer-vqm           | Corrected broad static-object appearance    |
| I2D*                | prefer-direct-map    | Road/junction-style material family         |
| AT_*                | prefer-vqm           | Ground/pad/floor under-building candidates  |
| terrain TT* miss8   | direct MAP           | 128x128 indexed payload in MAP itself       |
| sky NK_* miss8      | direct MAP           | 128x128 indexed environment texture         |
+---------------------+----------------------+---------------------------------------------+
```

## Direct Indexed MAP Payloads

Some MAP files are not merely references to a sibling M16/VQM resource.  The
`miss8` terrain/environment path demonstrated direct indexed MAP payloads:

```text
+------------+----------+----------+----------------------------------+
| Resource   | u32[0]   | u32[1]   | Interpretation                   |
+------------+----------+----------+----------------------------------+
| TT181SD_   | 128      | 128      | 128x128 indexed terrain texture  |
| NK_1CLD2   | 128      | 128      | 128x128 indexed sky/environment  |
+------------+----------+----------+----------------------------------+
```

Payload shape:

```c
struct direct_indexed_map {
    uint32_t width;
    uint32_t height;
    uint8_t  indexed_pixels[width * height];
};
```

## VQM / CBK Decoding

`VQM` is a 4x4 block-compressed indexed texture.  `CBK` is the tile codebook.

```text
+-----------------------------+---------------------------------------------------------+
| Component                   | Layout / rule                                           |
+-----------------------------+---------------------------------------------------------+
| VQM +0x00                   | uint32 width                                            |
| VQM +0x04                   | uint32 height_flags; height = height_flags & 0x1fffffff |
| VQM +0x08                   | char cbk_name[12]                                       |
| VQM +0x18                   | uint16 block_tokens[]                                   |
| CBK +0x00                   | uint32 tile_count                                       |
| CBK +0x04                   | tiles[tile_count][16]                                   |
| token no high bit           | copy tile at cbk + 4 + token * 16                       |
| token high bit set          | fill 4x4 block with token & 0xff                        |
| token count                 | ceil(width/4) * ceil(height/4)                          |
| validated intra-tile layout | yx: tile[sy * 4 + sx]                                   |
+-----------------------------+---------------------------------------------------------+
```

## Palette Handling

Current practical palette defaults:

```text
+--------------------------+------------------------------------------------------------+
| Context                  | Current baseline                                           |
+--------------------------+------------------------------------------------------------+
| Static objects           | mission ACT first; selected palette as fallback/probe      |
| Terrain candidates       | mission ACT first                                          |
| Vehicle baseline         | scratch_data/palettes/i76_vehicle_palette_selected.act     |
| Palette scaling          | auto                                                       |
+--------------------------+------------------------------------------------------------+
```

Current preferred command arguments:

```text
--palette-file "scratch_data/palettes/i76_vehicle_palette_selected.act"
--palette-scale auto
```

Known caveat: ACT selection alone did not solve every color mismatch.  The
mission `LUM` and `TBL` resources are 65536-byte tables and remain candidates
for runtime remap/translucency/luma behavior.

## Alpha / Transparency Policy

The current static-object alpha rule is targeted color-key alpha, not global
palette-index alpha.

```text
+------------------+-----------------------------------------------------------+
| Alpha mode       | Behavior                                                  |
+------------------+-----------------------------------------------------------+
| none             | No alpha post-process                                     |
| black-key        | Make near-black pixels transparent                        |
| magenta-key      | Make magenta-key pixels transparent                       |
| auto             | Apply black-key only when near-black fraction is high      |
+------------------+-----------------------------------------------------------+
```

Validated example:

```text
+-------------+--------------------------+-------------------------------------+
| Texture     | Object / part            | Behavior                            |
+-------------+--------------------------+-------------------------------------+
| AW_1BR_1    | awatert1 / aw1_bas1.geo  | Black area should be transparent    |
+-------------+--------------------------+-------------------------------------+
```

The exporter writes RGBA PNGs and emits MTL hints:

```text
d 0.999
Tr 0.001
illum 4
map_d textures/<texture>.png
```

Blender may still require material blend mode set to Alpha Clip or Alpha Blend
after OBJ import.

## Terrain Material Status

Terrain surface-class coloring is diagnostic, not final terrain art.

```text
+---------------+------------------------------+-------------------------------+
| TER class     | Current role candidate       | Visual diagnostic color        |
+---------------+------------------------------+-------------------------------+
| 0             | minor/default/boundary        | medium tan/brown              |
| 1             | dominant base ground          | darker brown                  |
| 3             | road surface candidate        | neutral gray                  |
| 5             | secondary ground/pad          | dark olive/green-brown        |
| 7             | roadbed/shoulder candidate    | light tan/beige               |
+---------------+------------------------------+-------------------------------+
```

Current validated terrain UV baseline:

```text
--terrain-uv-mode world-repeat
--terrain-uv-repeat 1.0
```

## RSEG Road Material Status

An experimental RSEG road-surface mesh exists and places road/corridor geometry
in approximately the correct area.  Its material/UV/type mapping is not yet
correct.

Current conclusion:

```text
+--------------------------+------------------------------------------------------------+
| Item                     | Status                                                     |
+--------------------------+------------------------------------------------------------+
| RSEG placement           | Useful / visually near road corridor                       |
| Road material family     | I2D* candidates are closer than terrain texture             |
| Road UVs                 | Still incorrect / stretched or rotated                     |
| Multiple road types      | Not resolved; likely game/editor binary tracing required   |
+--------------------------+------------------------------------------------------------+
```

## Recommended Debug Tables

```text
+------------------------------------+------------------------------------------------------------+
| Table                              | Purpose                                                    |
+------------------------------------+------------------------------------------------------------+
| static_material_slots.tsv          | Per-face material evidence                                 |
| static_texture_exports.tsv         | Texture asset selected and exported                        |
| static_texture_asset_probe.tsv     | Direct MAP / M16 / VQM / TMT / CBK availability            |
| static_texture_alpha.tsv           | Alpha decision and keyed pixel evidence                    |
| terrain_texture_candidates.tsv     | Mission terrain/environment texture candidates             |
| terrain_map_probe.tsv              | MAP direct payload vs sibling asset structure              |
| level_color_table_probe.tsv        | ACT/LUM/TBL/PCF color context candidates                   |
| rseg_road_texture_bindings.tsv     | Experimental road overlay material binding                 |
+------------------------------------+------------------------------------------------------------+
```

## Known Failure Modes

```text
+--------------------------------------+---------------------------------------------+-----------------------------+
| Problem                              | Likely cause                                 | Current mitigation           |
+--------------------------------------+---------------------------------------------+-----------------------------+
| Static UVs inverted                  | GEO V convention vs OBJ/Blender              | Static V flip required       |
| Static colors wrong under M16-first  | Wrong sibling choice for static path         | Prefer VQM                   |
| I2D road/junction bad under VQM      | Family-specific resource convention          | I2D*=prefer-direct-map       |
| Black cutout planes                  | Missing keyed alpha                          | static-alpha-mode auto       |
| Terrain texture not visible          | Terrain OBJ had no vt coordinates            | world-repeat UVs             |
| Road overlay texture wrong           | Unknown road type/material/UV runtime path   | Trace game/editor binaries   |
+--------------------------------------+---------------------------------------------+-----------------------------+
```

## Future Work

1. Trace `T01.LUM` and `T01.TBL` usage in the renderer/material path.
2. Trace road material selection in `i76.exe` and `I76EDIT.EXE`.
3. Determine how multiple road types choose material families and UVs.
4. Add a Blender post-import material helper for alpha clip and nearest filtering.
5. Preserve source evidence tables for every visual material decision.
