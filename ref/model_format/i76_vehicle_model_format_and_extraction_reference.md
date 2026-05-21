# Interstate ’76 Vehicle / Scene Model Format and Extraction Reference

This page documents the current reverse-engineered understanding of Interstate ’76 visual model extraction and reconstruction. It covers the vehicle chain from `VCF` through `VDF`/`VTF`/`GEO`, the scene-object chain from `SDF` through `SOBJ`/`GEO`, texture decoding, material binding, and the current binary-faithful OBJ export conventions.

Status: reverse-engineered from retail `i76.exe`, validated against the retail archive/resource corpus, checked against Open76 where useful, and repeatedly sanity-checked in Blender.

## Scope

This document covers:

- Vehicle model resource relationships.
- Scene-object geometry resource relationships where they share the same `GEO` runtime path.
- Binary-backed object resource selection from mission `ODEF`/`LDEF` records.
- The known layouts of `VCF`, `VDF`, `VGEO`, `SDF`, `SOBJ`, `GEO`, `VTF`, `TMT`, `M16`, `VQM`, and `CBK`.
- Runtime GEO reconstruction as observed in the binary.
- Texture/material resolution rules.
- Current OBJ/MTL export conventions.
- Practical extraction pipeline steps.
- Known pitfalls and confidence levels.

This document does not fully cover:

- Full mission/world behavior scripting.
- Complete terrain LOD rendering.
- Complete weapon/equipment behavior.
- Audio, cockpit UI, FMV, or gameplay simulation.
- A complete specification of all chunk types not needed for visual model extraction.

For mission terrain, `TDEF/ZMAP/ZONE`, `RSEG`, `ODEF` placement records, and runtime terrain reconstruction, see `ref/level_format/i76_runtime_level_and_terrain_format_notes.md`.

## Current Binary-Backed Resource Policy

The most important correction since the previous revision is that mission `ODEF/OBJ` resource resolution is class-specific. It is not simply “all ODEF records use `.vcf`,” and it is not simply “all non-car ODEF records use `.sdf`.”

The retail binary uses the class byte at ODEF payload `+0x5c` to dispatch to different case bodies.

```text
ODEF/OBJ class policy:

  class 0x01:
    if label == "spawn" or "regen":
      special spawn/regen transform table marker
    else:
      label + ".vcf"

  class 0x08 / 0x09:
      label + ".vcf"

  class 0x02 / 0x03 / 0x04 / 0x07 /
        0x0a / 0x0b / 0x0c /
        0x50 / 0x52 / 0x53:
      label + ".sdf"

  class 0x05 / 0x06 / 0x0d..0x4f / 0x51:
      fallback/null-ish path; not ordinary visible geometry yet

  class 0 or blank:
      invalid/special diagnostic rows for now
```

`LDEF/OBJ` records resolve through:

```text
label + ".sdf"
```

SDF child `SOBJ` records resolve through:

```text
partName + ".geo"
```

This reconciles the binary and Open76 for static mission objects such as the M06 town/building placements: those records use ODEF static classes that take the `.sdf` case body. Open76 is still simplified at the high level, but its `.sdf` behavior for these static object classes is now binary-supported.

## High-Level Asset Chains

A visible vehicle or scene object is not a single-file decode. The current reconstruction model has three related chains.

### Vehicle Chain

```text
VCF / VCFC
  -> VDF + VTF + optional WDF/CDF/component references

VDF / VDFC
  -> VGEO part names and transforms
  -> WLOC wheel transforms
  -> HLOC hardpoint/mount transforms
  -> collision and display metadata

VGEO part basename + ".geo"
  -> usually embedded in PIX/PAK and indexed by sibling PIX records

VTF / VTFC
  -> TMT/MAP material slots

TMT
  -> MAP/M16/VQM frame basenames

VQM + CBK
  -> decoded indexed texture pixels

ACT / runtime palette
  -> RGB preview/export of indexed texture pixels
```

### Scene-Object Chain

```text
ODEF class taking the SDF case
  -> label + ".sdf"

LDEF object
  -> label + ".sdf"

SDF
  -> SDFC
  -> SGEO/SOBJ/SCHK/LOBJ child descriptors

SOBJ part name + ".geo"
  -> GEO constructor path
  -> same runtime GEO/render-record path as vehicle parts
```

### Shared Runtime GEO Chain

```text
GEO
  -> construct_geometry_from_geo_buffer
  -> runtime GEO object
  -> build_lit_geo_render_records_from_sections
  -> render_world_object_geometry_tree_pass_primary / secondary
  -> submit_lit_textured_polygon_to_renderer
```

## Relevant Binary Functions

Current project names for the most important model/resource functions:

```text
+----------+---------------------------------------------------------+--------------------------------------------------------------+
| Address  | Current name                                            | Role                                                         |
+----------+---------------------------------------------------------+--------------------------------------------------------------+
| 004ad640 | format_8char_resource_basename_with_suffix              | Build fixed-width basename + optional suffix resource names  |
| 004ad6f0 | load_vehicle_config_for_world_object                    | Top-level VCF/VCFC vehicle-object loader                    |
| 004ad950 | parse_vcfc_vdf_vtf_wdf_resource_refs                    | Parse VCFC VDF/VTF/WDF references                           |
| 004adb90 | parse_vcfc_vehicle_config_root                          | Parse VCFC root chunk                                       |
| 004ae3a0 | parse_vgeo_vehicle_geometry_part_set_chunk              | Parse VGEO part sets                                        |
| 004ae5a0 | copy_wloc_six_wheel_transform_table                     | Copy six wheel-location records                             |
| 004aea90 | append_hloc_hardpoint_location_record                   | Append hardpoint/mount records                              |
| 004af8f0 | load_vtfc_vehicle_texture_map_sets                      | Load VTF material map sets                                  |
| 004b0150 | bind_optional_vtfc_texture_map_slot                     | Bind optional VTF texture slot                              |
| 004b0190 | bind_vtfc_six_face_map_slots                            | Bind FT/BK/RT/LF/TP/UN map slots                            |
| 004b3650 | parse_vdf_vehicle_definition_resource                   | Parse VDF resource                                          |
| 004b7800 | instantiate_vdf_vehicle_geometry_part_sets              | Instantiate vehicle visible geometry hierarchy              |
| 004b7ac0 | load_odef_object_or_vehicle_entity_record               | Mission ODEF object/entity placement loader                 |
| 004b8230 | copy_odef_basis_position_to_runtime_transform_block      | Copy ODEF 3x3 basis and position to runtime transform block |
| 004b8f70 | load_ldef_static_world_entity_from_sdf                  | LDEF object loader; formats `.sdf`                          |
| 004b7ea0 | parse_scene_object_descriptor_resource                  | Parse SDF child descriptor table                            |
| 004b8470 | load_sobj_scene_object_geometry_id                      | SOBJ child loader; formats `.geo`                           |
| 004b7f70 | parse_sdf_sdfc_child_context                            | SDFC child descriptor handler                               |
| 004b7ff0 | parse_sdf_sgeo_child_context                            | SGEO child descriptor handler                               |
| 004b8050 | add_sdf_schk_chunk_to_parent_object                     | SCHK child descriptor handler                               |
| 004b8ed0 | create_lobj_light_object                                | LOBJ/light-object handler                                   |
| 00446c90 | construct_geometry_from_geo_buffer                      | Convert GEO file buffer to runtime GEO structure            |
| 0045cbe0 | build_lit_geo_render_records_from_sections              | Build lit render records from runtime GEO sections          |
| 0045d100 | render_world_object_geometry_tree_pass_primary          | Primary geometry-tree render pass                           |
| 0045d530 | render_world_object_geometry_tree_pass_secondary        | Secondary geometry-tree render pass                         |
| 00471fd0 | submit_lit_textured_polygon_to_renderer                 | Submit lit textured n-gon to renderer                       |
| 00478430 | compute_geo_vertex_lighting_from_normals                | Compute lighting from normal/secondary table                |
| 00494e20 | compose_or_apply_world_object_transform                 | Transform composition/application helper                    |
| 00493550 | apply_world_object_transform_to_bounds_or_geometry      | Transform/bounds/geometry helper                            |
| 0044b430 | decode_vqm_cbk_4x4_blocks_to_indexed_pixels             | Decode VQM + CBK 4x4 block texture                          |
| 004474b0 | load_texture_resource_resolving_vqm_cbk_to_cache        | Load texture resource into cache                            |
| 004478b0 | load_texture_resource_resolving_vqm_cbk_to_buffer       | Load texture resource to caller buffer                      |
| 00470660 | load_pix_pak_resource_index                             | Load PIX/PAK embedded resource index                        |
+----------+---------------------------------------------------------+--------------------------------------------------------------+
```

## Mission Placement Records and Model Resource Selection

Although this page focuses on model formats, model reconstruction now depends on mission placement records because static scene objects and vehicles are placed through `ODEF`/`LDEF`.

### ODEF/OBJ Placement Record

`ODEF/OBJ` payload size is consistently `0x64` for ordinary placement records.

```c
struct i76_odef_obj_record {
    char  label[8];        // +0x00, high bits masked off by runtime formatter
    float basis_3x3[9];    // +0x08..+0x28
    float pos_x;           // +0x2c
    float pos_y;           // +0x30
    float pos_z;           // +0x34
    uint32_t tail[11];     // +0x38..+0x63
    // tail[9] / payload +0x5c is the class discriminator
}; // 0x64
```

The runtime copies the 3x3 basis and position through `004b8230`. The position floats are converted into double fields in the destination transform block. The current Blender/debug exporter treats the ODEF axes OBJ as a transform scaffold only; it is not final geometry.

### Spawn/Regen Markers

Class `0x01` records with labels `spawn` or `regen` are special. They are copied into fixed-capacity transform tables rather than treated as ordinary geometry resources.

Known table behavior:

```text
spawn:
  table base   0053fd88
  count global 00540d98

regen:
  table base   0053ecb0
  count global 00540d9c

entry size: 0x40
capacity:   0x40
```

### LDEF/OBJ Static Objects

`LDEF/OBJ` records are SDF-backed static/world-entity objects. They use `label + ".sdf"` and then call the SDF child descriptor parser.

## SDF Scene-Object Format

`SDF` is a BWD2-style scene-object descriptor resource. It is used by LDEF objects and by static ODEF classes.

The important child descriptor table is at `00500b18`:

```text
+------+----------+------------------------------------------+
| Tag  | Handler  | Meaning                                  |
+------+----------+------------------------------------------+
| SDFC | 004b7f70 | Scene descriptor/config child            |
| SOBJ | 004b8470 | Scene object geometry child; loads .geo  |
| SGEO | 004b7ff0 | Scene geometry child/context             |
| SCHK | 004b8050 | Chunk/check data attached to parent      |
| LOBJ | 004b8ed0 | Linked/light object                      |
| EXIT | 004b4290 | End table                                |
+------+----------+------------------------------------------+
```

Open76's SDF parser is useful for the broad `SGEO` part-record model:

```text
numParts
for each part:
    name[8]
    right vector
    up vector
    forward vector
    position vector
    parent name[8]
    trailing/skipped fields
```

The retail binary confirms that SOBJ child records format `partName + ".geo"` and call the GEO loader path. For mission reconstruction, this means static ODEF/LDEF placements should resolve to SDF, then to SOBJ/SGEO children, and finally to GEO resources.

## VCF / VCFC Root Vehicle Config

`VCF` is the root vehicle configuration. It contains a `VCFC` chunk whose fixed fields reference the vehicle definition, texture map set, weapon definitions, and component selectors.

Binary evidence distinguishes offsets in the full chunk pointer used by Ghidra from offsets in the Python BWD2 payload helper. The Python helper returns the chunk payload after the 8-byte tag/size header, so Python offsets are 8 bytes earlier.

```text
+----------------------+--------------------------+----------------------------+----------------------------------+
| Field                | Ghidra full chunk offset | Python BWD2 payload offset | Meaning                          |
+----------------------+--------------------------+----------------------------+----------------------------------+
| VDF reference        | param_1 + 0x18           | payload + 0x10             | Vehicle definition resource      |
| VTF reference        | param_1 + 0x25           | payload + 0x1d             | Vehicle texture map-set resource |
| Component selector 0 | param_1 + 0x32           | payload + 0x2a             | CDF/component selector           |
| Component selector 1 | param_1 + 0x36           | payload + 0x2e             | CDF/component selector           |
| Component selector 2 | param_1 + 0x3a           | payload + 0x32             | CDF/component selector           |
| WDF slot 0           | param_1 + 0x3e           | payload + 0x36             | Weapon definition reference      |
| WDF slot 1           | param_1 + 0x4b           | payload + 0x43             | Weapon definition reference      |
| WDF slot 2           | param_1 + 0x58           | payload + 0x50             | Weapon definition reference      |
+----------------------+--------------------------+----------------------------+----------------------------------+
```

A robust extractor should parse the `VCFC` chunk directly instead of relying only on regex-style filename scans. Regex fallback remains useful for damaged or variant files, but the binary uses fixed offsets.

## VDF Vehicle Definition

`VDF` is a BWD2-style chunked vehicle definition. Important known chunks:

```text
+-------+------------------------------------------------------------------------------------------------------------+
| Chunk | Meaning                                                                                                    |
+-------+------------------------------------------------------------------------------------------------------------+
| VDFC  | Core vehicle definition/runtime fields                                                                     |
| SOBJ  | Base object or auxiliary scene/object reference; should not be blindly included in main vehicle visual OBJ |
| VSHL  | Shell/display metadata                                                                                     |
| VLOC  | Vehicle-local attachment objects                                                                           |
| VGEO  | Visible part hierarchy; four third-person damage-state part sets                                           |
| VCHK  | Geometry/check data                                                                                        |
| LOBJ  | Linked objects                                                                                             |
| COLP  | Collision bounds                                                                                           |
| WLOC  | Six wheel transforms, six records of 0x38 bytes                                                            |
| HLOC  | Hardpoint records; runtime table at vehicle +0x378, stride 0xfc, up to seven entries                       |
| SPCS  | Special sprite/reference/display metadata                                                                  |
| ETBL  | Display/equipment/special table metadata                                                                   |
+-------+------------------------------------------------------------------------------------------------------------+
```

### WLOC

`WLOC` contains six wheel-location records. Each record is `0x38` bytes. The runtime copies these from chunk payload `+0x08` into the vehicle wheel-location table at runtime vehicle context `+0x168`.

### HLOC

`HLOC` appends up to seven hardpoint records into a runtime table at vehicle context `+0x378`, stride `0xfc`.

Current field interpretation:

```text
chunk +0x08  hardpoint name
chunk +0x18  position-like field x
chunk +0x1c  position-like field y
chunk +0x20  position-like field z
chunk +0x54  extra field copied by runtime
```

### SOBJ Handling

Do not blindly include `VDF` `SOBJ` geometry in the main visible vehicle mesh.

Binary evidence shows distinct SOBJ concepts:

```text
Vehicle VDF descriptor table: SOBJ callback is not the scene SOBJ loader.
Scene/SDF descriptor table at 00500b18: SOBJ callback = 004b8470.
```

The function at `004b8470` is a scene-object SOBJ geometry loader that formats `partName + ".geo"`. It is not automatically the vehicle VDF SOBJ path.

In current tools:

```text
--vdf-sobj-mode separate  # source-truth-safe default
--vdf-sobj-mode skip      # clean visual export
--vdf-sobj-mode include   # legacy/debug only
```

## VGEO Visible Part Hierarchy

`VGEO` contains four third-person damage-state part sets. Each part record includes:

```text
name[8]
right vector
up vector
forward vector
position vector
parent name[8]
trailing per-part fields
```

Current model:

- State 0 provides the stable hierarchy and transform parentage.
- Damage states 1–3 provide alternate part/GEO names by slot index.
- Current exporter binds alternate damage-state GEO names by VGEO slot index while preserving state-0 hierarchy.
- This avoids false parent failures where alternate-state parent strings reference alternate names not present in the selected partial set.

Open76 and the binary agree on the broad four-state VGEO structure.

## GEO File Layout

The current parsed GEO file layout is:

```c
struct geo_file {
    char     magic[4];          // raw bytes OEG. / little-endian 0x2e47454f
    uint32_t unk1;
    char     name[16];
    uint32_t vertex_count;
    uint32_t face_count;
    uint32_t unk2;
    vec3     vertices[vertex_count];
    vec3     normals[vertex_count];
    face     faces[face_count];
};
```

Each face is currently interpreted as:

```c
struct geo_face {
    uint32_t face_index;
    uint32_t vertex_ref_count;
    uint8_t  rgb[3];
    float    surface_normal_or_plane[4];
    uint32_t unk3;
    uint8_t  flags[3];
    char     texture_name[13];
    uint32_t unk4;
    uint32_t unk5;
    geo_face_ref refs[vertex_ref_count];
};
```

Each face reference is:

```c
struct geo_face_ref {
    uint32_t vertex_index;
    uint32_t normal_index;
    float    u;
    float    v;
};
```

Important interpretation:

- `vertex_index` indexes the GEO vertex table.
- `normal_index` indexes the normal/secondary-vector table and is used by the runtime lighting path.
- `u` and `v` are copied as raw floats into render vertices.
- Face RGB is real source data, but should not be used as default diffuse tint for textured faces in OBJ/Blender.

## Runtime GEO Object Produced by the Binary

The binary does not render the GEO file structure directly. `construct_geometry_from_geo_buffer` converts it into a compact runtime GEO object.

Observed runtime GEO header:

```text
+-------------------+-----------------------------------------------+
| Runtime offset    | Field                                         |
+-------------------+-----------------------------------------------+
| runtime_geo +0x00 | refcount / live marker                        |
| runtime_geo +0x04 | vertex_count                                  |
| runtime_geo +0x08 | normal_count                                  |
| runtime_geo +0x0c | runtime vertex array pointer                  |
| runtime_geo +0x10 | runtime normal/secondary-vector array pointer |
| runtime_geo +0x14 | first runtime section pointer                 |
+-------------------+-----------------------------------------------+
```

Observed runtime section layout:

```text
+----------------+----------------------------------------+
| Section offset | Field                                  |
+----------------+----------------------------------------+
| +0x04          | corner_count                           |
| +0x08          | nearest palette index for GEO face RGB |
| +0x09          | raw face R                             |
| +0x0a          | raw face G                             |
| +0x0b          | raw face B                             |
| +0x0c          | plane/surface normal field 0           |
| +0x10          | plane/surface normal field 1           |
| +0x14          | plane/surface normal field 2           |
| +0x18          | plane/surface normal field 3           |
| +0x1c          | face flag byte 0                       |
| +0x1d          | face flag byte 1                       |
| +0x1e          | face flag byte 2                       |
| +0x20          | texture/resource slot string           |
| +0x30          | next section pointer                   |
| +0x34          | centroid x                             |
| +0x38          | centroid y                             |
| +0x3c          | centroid z                             |
| +0x40          | first corner record                    |
+----------------+----------------------------------------+
```

Observed runtime corner layout:

```text
+---------------+-------------------------------+
| Corner offset | Field                         |
+---------------+-------------------------------+
| +0x00         | vertex_index                  |
| +0x04         | normal_index / lighting index |
| +0x08         | raw GEO u                     |
| +0x0c         | raw GEO v                     |
+---------------+-------------------------------+
```

## Binary Render-Record Rules

Deeptrace evidence from `build_lit_geo_render_records_from_sections` indicates:

- The runtime walks section corners in reverse order when building render vertices.
- The game copies raw `u` and raw `v` into render vertex fields.
- The lighting path uses `corner.normal_index`, not `corner.vertex_index`.
- The game submits the full n-gon vertex list to `submit_lit_textured_polygon_to_renderer`.
- The game does not pre-triangulate GEO faces in this construction/build path.

This is the basis for the current binary-faithful modeller.

## Resource Acquisition and PIX/PAK

Visual assets are split across several storage layers:

```text
ZFSF/ZIX
  top-level archive and registered-resource lookup

resources/*.vcf / *.sdf / etc.
  loose extracted resource payloads from the archive

PIX/PAK
  embedded indexed resource containers
```

The runtime `load_pix_pak_resource_index` path scans `*.pix`, derives/uses the sibling `.pak`, parses rows resembling:

```text
name offset size
```

and lowercases the resource keys. Current corpus parsing found PIX records for:

```text
.geo
.tmt
.m16
.vqm
.map
```

This is why many `GEO/TMT/MAP/VQM/CBK` resources are not top-level loose files. They must be resolved through PIX/PAK indexes for faithful extraction.

## VTF Vehicle Texture Map Set

`VTF` / `VTFC` provides material slot mapping for vehicle textures.

```text
+-------------------------+-------------------------------------------------------------------------------------------------+
| VTF concept             | Current understanding                                                                           |
+-------------------------+-------------------------------------------------------------------------------------------------+
| TMT slots               | 78 fixed 13-byte names                                                                          |
| MAP slots               | 13 fixed 13-byte names                                                                          |
| Six-face suffixes       | FT.map, BK.map, RT.map, LF.map, TP.map, UN.map                                                  |
| Left-side normalization | GEO may use LF; VTF/TMT names may use LT; resolver maps LF -> LT where appropriate              |
| BODY slot               | Resolved through VTF map/body path; prefer same-stem VQM when --direct-map-prefer vqm is active |
+-------------------------+-------------------------------------------------------------------------------------------------+
```

Important rule: direct literal `.MAP` slots and BODY/VTF map slots should prefer same-stem VQM over M16 when both are available and `--direct-map-prefer vqm` is active. This corrected visible Piranha body/hood/door-sill texture issues.

## TMT Texture Animation / Frame List

`TMT` describes a texture set or animation frame list.

```text
+--------+-------------------------------------+
| Offset | Field                               |
+--------+-------------------------------------+
| +0x14  | dimension_count                     |
| +0x18  | dimension_values[]                  |
| +0x28  | animation period/rate divisor       |
| +0x2c  | flags: bit0 animate, bit1 ping-pong |
| +0x40  | packed 8-byte frame basenames       |
+--------+-------------------------------------+
```

Current interpretation of flags:

```text
bit 0x01  animation enabled
bit 0x02  ping-pong animation
else      linear/default timer
```

The frame names at `+0x40` are packed 8-byte C strings. They usually resolve to `MAP`, `M16`, or `VQM` basenames.

## M16 Texture Payload

Current `M16` interpretation:

```c
struct m16_header_like {
    uint32_t width;        // +0x00
    uint32_t height_flags; // +0x04, high bit usually set
    uint8_t  pixels[width * height]; // +0x08
    uint8_t  trailing[];   // variable
};
```

`M16` pixels are indexed-color bytes. Correct visual export requires a palette.

## VQM / CBK Texture Payload

`VQM` is a 4x4 block-compressed indexed texture. `CBK` is the codebook.

```text
+-----------------------+------------------------------------------------------------+
| Offset / rule         | Meaning                                                    |
+-----------------------+------------------------------------------------------------+
| VQM +0x00             | width                                                      |
| VQM +0x04             | height_flags; effective height = height_flags & 0x1fffffff |
| VQM +0x08             | 12-byte CBK name                                           |
| VQM +0x14             | unknown/control field                                      |
| VQM +0x18             | uint16 block_tokens[]                                      |
| CBK +0x00             | tile_count, often 4096                                     |
| CBK +0x04             | 4x4 indexed-color tiles, 16 bytes each                     |
| token & 0x8000 == 0   | copy CBK tile at cbk + 4 + token * 16                      |
| token & 0x8000 != 0   | fill 4x4 block with token & 0xff                           |
| token count           | ceil(width / 4) * ceil(height / 4)                         |
| validated tile layout | tile[sy * 4 + sx], named yx in current tools               |
+-----------------------+------------------------------------------------------------+
```

The current default layout is `yx`, meaning each 4x4 tile is read as:

```python
tile[sy * 4 + sx]
```

Earlier `xy` decoding produced visibly aliased/wrong vehicle textures.

## Palette Handling

Do not use the static EXE bytes at `004fa170` as the default vehicle palette. That address is a runtime active palette buffer, not necessarily the final vehicle palette.

Open76 hardcodes `p02.act`. Current vehicle extraction uses an archive ACT palette selected through palette-candidate probing. For Piranha/contact-sheet tests, `p02.act` in raw form matched expected vehicle colors.

Recommended selected-palette workflow:

```bash
python3 scripts/i76_select_palette_candidate_v1.py \
  --probe-dir scratch_data/i76_vehicle_palette_candidates_v4_piranha \
  --key-contains p02.act \
  --out scratch_data/palettes/i76_vehicle_palette_selected.act
```

Use with:

```text
--palette-file scratch_data/palettes/i76_vehicle_palette_selected.act
--palette-scale raw
```

## Material and Color Rules

Current interpretation:

- GEO face RGB is real source data and should be preserved in debug outputs.
- For untextured/color-only faces, GEO face RGB should be used, preferably quantized through the selected palette when `--flat-color-mode palette-nearest` is active.
- For textured faces, do not use GEO face RGB as default Blender/MTL `Kd` tint.
- Use white `Kd` for textured faces by default to avoid Blender multiplying/tinting `map_Kd`.
- Preserve `geo_face_color`, `surface_flags`, and palette-index evidence in `face_mapping.tsv`, `material_binding.tsv`, and JSON outputs.

This matches the practical reading of Open76: textured faces resolve texture materials, while color materials are used when texture names are absent.

## Transparency / Alpha Rules

Global palette-index `0xff` alpha is not safe. Some opaque body textures use `0xff` in regions that are sampled by opaque polygons; global alpha produced holes in hood/trunk/body areas.

Current targeted baseline:

- Default body/opaque materials remain opaque.
- Transparent light overlay geometry may apply alpha when flagged appropriately.
- Piranha light overlay objects such as `PP11HLGT.GEO`, `PP11BLGT.GEO`, and `PP11TLGT.GEO` use transparent-style flags and benefit from targeted alpha.

Current alpha rule in the vehicle exporter is intentionally narrow and should be expanded only after per-model validation.

## Current OBJ/MTL Export Baseline

Current binary-faithful vehicle export rules:

```text
+-----------------------+-----------------------------------------------------------------------------------------+
| Aspect                | Current baseline rule                                                                   |
+-----------------------+-----------------------------------------------------------------------------------------+
| Runtime corner order  | Reverse GEO corner order when building render vertices                                  |
| UV fields             | Copy raw U and raw V from GEO corner records into render records                        |
| OBJ V convention      | Use Blender OBJ view convention, vt.v = 1.0 - raw_v                                     |
| Normals/lighting      | Use corner normal_index, not vertex_index, for lighting/normal lookup                   |
| Geometry handedness   | Apply final negative-determinant OBJ view transform; current baseline mirror-x          |
| Textured Kd           | White by default; preserve GEO face RGB in TSV/JSON                                     |
| Untextured Kd         | Use GEO face RGB, usually palette-nearest when palette is supplied                      |
| Direct MAP preference | Prefer VQM over M16 when same-stem siblings exist and --direct-map-prefer vqm is active |
| VQM tile layout       | yx                                                                                      |
| Palette               | Use archive ACT p02.act/raw selected palette workflow, not static EXE bytes at 004fa170 |
| Light overlay alpha   | Apply targeted alpha for transparent-flagged light overlay geometry                     |
| VDF SOBJ              | Separate or skip, not included in main vehicle visual OBJ by default                    |
+-----------------------+-----------------------------------------------------------------------------------------+
```

The final negative-determinant `mirror-x` view transform is important. Before this was discovered, text on the Piranha rear, bumper, and license-like areas appeared mirrored even when UVs and textures were otherwise correct. Both `mirror-x` and `mirror-z` fixed text, differing by 180-degree yaw; `mirror-x` was selected as the current baseline orientation.

## Practical Extraction Commands

Current Piranha baseline command using the v13 modeller:

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

For all vehicles, use `--all` instead of individual `--vehicle` filters:

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

For mission object reconstruction, the current staged baseline is:

```text
1. Export dense welded terrain.
2. Export RSEG overlays using terrain-sampled height.
3. Export ODEF placement axes.
4. Resolve ODEF class policy:
   - 0x01/0x08/0x09 -> VCF/vehicle chain.
   - 0x02/0x03/0x04/0x07/0x0a/0x0b/0x0c/0x50/0x52/0x53 -> SDF scene-object chain.
5. Resolve SDF SOBJ children to GEO.
6. Instantiate GEO at the ODEF/LDEF transform.
```

## Recommended Output Artifacts

A durable vehicle or scene-object extraction should emit both visual and machine-readable artifacts:

```text
<vehicle-or-object>/
  <name>.obj
  <name>.mtl
  textures/
    *.png
  vehicle_model_runtime.json
  scene_object_runtime.json
  geo_runtime_sections.json
  render_records.json
  face_mapping.tsv
  corner_mapping.tsv
  material_binding.tsv
  placement_transform.tsv
  blender_apply_i76_material_settings.py
```

Important debug fields:

```text
mission
source_record
odef_class
resource_policy
vcf
sdf
vdf
vtf
geo
part
parent
face_index
runtime_section_index
source_corner_index
render_corner_index
vertex_index
normal_index
raw_u
raw_v
obj_u
obj_v
raw_slot
normalized_slot
resolved_name
texture_asset
surface_flags
geo_face_color
texture_transparency_enabled
material_name
```

## Common Failure Modes

### Mirrored text on vehicle surfaces

Likely cause: missing final negative-determinant OBJ view transform.

Do not fix this with broad UV flips. The validated baseline uses binary runtime corner order and a final `mirror-x` OBJ view transform.

### Incorrect underside, wheelwell, or pipe textures

Likely cause: direct literal `.MAP` slot resolving to M16 when a same-stem VQM exists.

Use:

```text
--direct-map-prefer vqm
```

### Aliased or blocky VQM textures

Likely cause: wrong CBK intra-tile layout.

Use:

```text
--vqm-layout yx
```

### Body/hood/door-sill color mismatches

Likely cause: BODY/VTF map slot resolving to M16 instead of same-stem VQM, or textured material incorrectly using GEO face RGB as `Kd`.

Use same-stem VQM preference and white textured `Kd`.

### Hood/trunk holes after enabling alpha

Likely cause: global `0xff` alpha applied to opaque body textures.

Do not use global index-`0xff` alpha as a default.

### Black planes around vehicles

Likely cause: VDF SOBJ / `_SOR` auxiliary geometry included in the main visible OBJ.

Use:

```text
--vdf-sobj-mode separate
```

or:

```text
--vdf-sobj-mode skip
```

### Static mission objects appear missing

Likely cause: treating all dispatch-valid ODEF records as `.vcf`.

Use the class-specific ODEF policy. Static classes such as `0x02`, `0x03`, `0x04`, `0x50`, and `0x52` use the `.sdf` case body, then the SDF child descriptor table, then SOBJ/GEO.

### SDF resolves but no geometry appears

Likely cause: failing to decode SDF child descriptors or failing to resolve `SOBJ` part names to `.geo` through the PIX/PAK resource index.

The GEO may not be loose under `resources/`; it may be indexed in `.pix/.pak`.

## Relationship to Open76

Open76 is a useful independent reference for broad structure:

- GEO header, vertex table, normal table, face layout, and face refs.
- VDF/VGEO concept and four damage-state part sets.
- VTF slot interpretation.
- `p02.act` as a practical vehicle palette baseline.
- SDF/SGEO broad part-record structure.
- Color material usage only when a texture is absent.

Open76 should not be adopted wholesale for Blender OBJ output. A broad Open76 parity rewrite with raw V, inverted normals, and Open76 triangle fan order produced incorrect texture orientation in the Blender OBJ path. Use Open76 as corroborating evidence, not as the final export convention.

For ODEF resource selection, Open76’s broad car/non-car rule is simplified. The retail binary class-specific rule is the durable baseline.

## Current Confidence

```text
+--------------------------------------------+-------------------------+-----------------------------------------------------------------------+
| Area                                       | Confidence              | Notes                                                                 |
+--------------------------------------------+-------------------------+-----------------------------------------------------------------------+
| VCF/VCFC root refs                         | High                    | Fixed offsets validated against binary evidence                       |
| VDF VGEO four damage-state part sets       | High                    | Binary and Open76 agree on general structure                          |
| ODEF class-specific VCF/SDF policy         | High                    | Validated by ODEF class case-body trace                               |
| LDEF -> SDF                                | High                    | Binary formats .sdf in LDEF handler                                   |
| SDF child table SOBJ -> GEO                | High                    | Binary formats .geo in SOBJ handler                                   |
| GEO file layout                            | High                    | Matches runtime constructor and Open76 parser                         |
| Runtime GEO section/corner layout          | High                    | Validated by deeptrace of construct/build path                        |
| Reverse render corner walk                 | High                    | Observed in build_lit_geo_render_records_from_sections                |
| Raw U/V copy into render vertices          | High                    | Observed in binary trace                                              |
| VQM + CBK yx tile layout                   | High for current corpus | Validated visually and by decode-variant probes                       |
| Palette p02.act/raw baseline               | High for vehicles       | Matches Open76 baseline and visual probes                             |
| BODY same-stem VQM preference              | Medium-high             | Matches corrected visual output and Open76-style texture preference   |
| Light overlay alpha rule                   | Medium                  | Works for observed Piranha lights; keep as targeted rule              |
| VDF SOBJ auxiliary handling                | Medium-high             | Binary distinguishes vehicle VDF SOBJ vs scene SOBJ callback          |
| Exact SDF child trailing fields            | Medium                  | Broad layout known; some trailing fields still need binary naming     |
| Exact non-vehicle material exceptions      | Medium                  | Likely same GEO path, but scene-object material validation is ongoing |
+--------------------------------------------+-------------------------+-----------------------------------------------------------------------+
```

## Future Work

Recommended next work items:

1. Update the reconstruction exporter to instantiate class-specific ODEF resources:
   - `0x01/0x08/0x09` through VCF/VDF/VGEO.
   - `0x02/0x03/0x04/0x07/0x0a/0x0b/0x0c/0x50/0x52/0x53` through SDF/SOBJ/GEO.
2. Decode SDF child descriptors into a durable machine-readable intermediate format.
3. Resolve SOBJ part names to GEO through PIX/PAK indexes, not only loose files.
4. Validate static scene-object GEOs against the same runtime GEO rules used for vehicle GEOs.
5. Run the current v13 vehicle baseline across all vehicles and inspect in Blender grid view.
6. Record per-vehicle exceptions for alpha/light overlays rather than broadening alpha rules prematurely.
7. Add regression tests for:
   - Piranha rear text orientation.
   - BODY VQM preference.
   - VQM yx decoding.
   - SOBJ separation.
   - Light overlay alpha.
   - Untextured palette-nearest face colors.
   - M06 static ODEF `.sdf` object placement.
8. Build a standalone extraction pipeline that does not depend on the older OBJ exporter helper except for validated reusable decoding code.
