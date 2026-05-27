# Interstate '76 Reverse-Engineering Reference Index

This directory is the durable human-readable reference set for the current
Interstate '76 reconstruction work.  It is intentionally organized by runtime
system rather than by individual exporter revision.

## Current reference folders

```text
+------------------------------+--------------------------------------------------------------+
| Folder                       | Contents                                                     |
+------------------------------+--------------------------------------------------------------+
| ref/level_format/            | Mission/terrain/RSEG/ODEF/SDF/static-object reconstruction   |
| ref/material_format/         | Indexed texture, MAP/M16/VQM/CBK, palette, alpha policy      |
| ref/model_format/            | VCF/VDF/VTF/VGEO/GEO vehicle and reusable GEO model details  |
| ref/zfs/                     | ZFSF archive structure, LZO decode, PIX/PAK resource index   |
| ref/object_resource_resolution/ | ODEF/LDEF class policy and SDF/SGEO static resolution     |
| ref/mission_reconstruction/  | End-to-end current exporter pipeline and validation state    |
+------------------------------+--------------------------------------------------------------+
```

## Current visual/exporter baselines

```text
+--------------------------+--------------------------------------------------------------+
| Area                     | Current baseline                                             |
+--------------------------+--------------------------------------------------------------+
| Terrain mesh             | Dense welded terrain OBJ from TER/ZMAP/TDEF                  |
| Terrain UV               | --terrain-uv-mode world-repeat; --terrain-uv-repeat 1.0      |
| Terrain material style   | natural diagnostic surface-class colors                      |
| Terrain texture, miss8   | direct indexed MAP payloads, e.g. TT181SD_.MAP               |
| Static object roots      | ODEF/LDEF class policy -> SDF/VCF                            |
| Static SDF geometry      | SDF SGEO declared parts -> partName.geo                      |
| Static GEO lookup        | embedded PIX/PAK/ZFS resource index                          |
| Static texture selection | default VQM-first, with per-family overrides                 |
| Static UVs               | GEO UVs with V flip required                                 |
| Static alpha             | targeted black-key alpha for cutout textures                 |
| Sky                      | hemisphere validation object from mission sky/environment MAP|
| RSEG road geometry       | placement useful; material/type mapping unresolved           |
+--------------------------+--------------------------------------------------------------+
```

## Important unresolved items

```text
+--------------------------+--------------------------------------------------------------+
| Topic                    | Next evidence needed                                         |
+--------------------------+--------------------------------------------------------------+
| RSEG road materials      | Trace game/editor road material/type selection               |
| Multiple road types      | Determine how road kind/table chooses I2D* or other textures |
| Road UVs                 | Trace runtime/editor road mesh UV generation                 |
| LUM/TBL/PCF color tables | Determine whether static/terrain palettes are remapped       |
| Runtime render states    | Trace blend/clamp/filter/alpha flags beyond OBJ approximation|
+--------------------------+--------------------------------------------------------------+
```
