# Interstate '76 Object Resource Resolution Reference

This page records the current binary-backed object resource resolution model for mission
objects in Interstate '76. It is intended to prevent regressions back to the earlier
over-broad interpretations that either all `ODEF/OBJ` objects resolve as `.vcf`, or all
non-car-looking `ODEF/OBJ` objects resolve as `.sdf`.

The current source of truth is the retail `i76.exe` control flow, with Open76 used as a
sanity check only where it agrees with the binary.

## Current conclusion

`ODEF/OBJ` resource suffixing is class-specific. `LDEF/OBJ` uses `.sdf`. `SOBJ` children
inside SDF resources use `.geo`.

| Record owner | Class / condition         | Binary-backed resource behavior                             | Confidence |
|--------------|---------------------------|-------------------------------------------------------------|------------|
| ODEF/OBJ     | class 0x01 label == spawn | special spawn marker table                                  | high       |
| ODEF/OBJ     | class 0x01 label == regen | special regen marker table                                  | high       |
| ODEF/OBJ     | class 0x01 other label    | label.vcf                                                   | high       |
| ODEF/OBJ     | class 0x08                | label.vcf                                                   | high       |
| ODEF/OBJ     | class 0x09                | label.vcf                                                   | high       |
| ODEF/OBJ     | class 0x02                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x03                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x04                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x07                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x0a                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x0b                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x0c                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x50                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x52                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x53                | label.sdf                                                   | high       |
| ODEF/OBJ     | class 0x05 / 0x06         | fallback / null-ish path, not ordinary visible geometry yet | medium     |
| ODEF/OBJ     | class 0x0d..0x4f / 0x51   | fallback / null-ish path, not ordinary visible geometry yet | medium     |
| ODEF/OBJ     | class 0x00 / blank        | invalid or special diagnostic row                           | medium     |
| LDEF/OBJ     | all parsed labels         | label.sdf                                                   | high       |
| SDF/SOBJ     | child part label          | partName.geo                                                | high       |

## Key binary functions

| Address  | Working name                                  | Role                                                       |
|----------|-----------------------------------------------|------------------------------------------------------------|
| 004b7ac0 | load_odef_object_entity_record                | Handles ODEF/OBJ payloads and class dispatch               |
| 004b8230 | copy_odef_basis_position_to_runtime_transform | Copies 3x3 basis and position into runtime transform block |
| 00450f90 | register_spawn_or_regen_marker                | Stores spawn/regen transform entries                       |
| 004ad640 | format_8char_resource_basename_with_suffix    | Normalizes 8-byte labels and appends optional suffix       |
| 004ad6f0 | load_vehicle_config_for_world_object          | Loads/parses label.vcf for VCF-backed classes              |
| 004b41e0 | parse_bwd2_resource_with_descriptor_table     | Resource parse helper used by VCF/SDF paths                |
| 004b7ea0 | parse_scene_object_descriptor_resource        | Parses SDF child descriptor table                          |
| 004b8470 | load_sobj_scene_object_geometry_id            | Formats partName.geo and enters GEO load path              |
| 00446c90 | construct_geometry_from_geo_buffer            | Builds runtime GEO object from OEG. buffer                 |

## ODEF payload fields relevant to resource resolution

The payload is 0x64 bytes for ordinary `ODEF/OBJ` records.

| Payload offset | Current interpretation       | Notes                                                                   |
|----------------|------------------------------|-------------------------------------------------------------------------|
| +0x00..+0x07   | 8-byte label / resource stem | High bits may carry flags/ID information; visible label masks with 0x7f |
| +0x08..+0x28   | 3x3 basis matrix             | Copied directly by 004b8230                                             |
| +0x2c          | pos_x                        | Float, converted to double in runtime transform block                   |
| +0x30          | pos_y                        | Float, vertical axis in game coordinates                                |
| +0x34          | pos_z                        | Float                                                                   |
| +0x38..+0x58   | tail fields                  | Flags/team/linkage/class-adjacent values; not fully named               |
| +0x5c          | class discriminator          | Controls .vcf, .sdf, spawn/regen, or fallback behavior                  |
| +0x60          | tail field                   | Still unknown                                                           |

## Why this page exists

Earlier traces showed `.vcf` suffix formatting in the `ODEF/OBJ` handler, while Open76 displayed many
static objects by resolving `label.sdf`. A later class-body trace resolved the apparent conflict:
the retail binary has both `.vcf` and `.sdf` ODEF case bodies. Static town/building classes such as
`0x02`, `0x03`, `0x04`, `0x50`, and `0x52` are binary-backed `.sdf` placements.

## Practical reconstruction policy

Use this ordering for reconstruction:

1. Decode `ODEF/OBJ`.
2. If label is `spawn` or `regen` on the class-0x01 path, emit marker metadata rather than geometry.
3. Resolve class `0x01`, `0x08`, and `0x09` as `label.vcf`.
4. Resolve classes `0x02`, `0x03`, `0x04`, `0x07`, `0x0a`, `0x0b`, `0x0c`, `0x50`, `0x52`, and `0x53` as `label.sdf`.
5. Resolve `LDEF/OBJ` as `label.sdf`.
6. Parse SDF child descriptors and resolve `SOBJ` child geometry as `partName.geo`.
7. Treat class 0 and blank-label records as diagnostic until proven otherwise.

## Open76 comparison

Open76's broad “car versus non-car” behavior is no longer the preferred description for the retail
binary. It remains useful as a sanity check because its `.sdf` resolution agrees with the binary for
the static-object class families that dominate town/building placements. It is simplified relative to
the class-specific retail dispatch.
