# Interstate '76 Vehicle, GEO, and Static Model Extraction Reference

This page documents the current reverse-engineered understanding of Interstate
'76 model extraction.  It covers both vehicle models and the reusable GEO/SDF
static-object path now used by mission reconstruction.

## Scope

```text
+-------------------------+------------------------------------------------------------+
| Covered area            | Notes                                                      |
+-------------------------+------------------------------------------------------------+
| Vehicle chain           | VCF -> VDF/VTF/WDF -> VGEO/SOBJ/GEO                        |
| Static scene chain      | ODEF/LDEF -> SDF -> SGEO/SOBJ -> GEO                       |
| GEO mesh layout         | vertices, normal table, faces, texture slots, UV refs       |
| Hierarchy composition   | VGEO/SDF parented part transforms                          |
| Embedded GEO lookup     | PIX/PAK/ZFS resource index                                 |
| OBJ validation output   | terrain/static/road/sky combined scene export              |
+-------------------------+------------------------------------------------------------+
```

## High-Level Asset Chains

Vehicle chain:

```text
VCF
  -> VDF + VTF + optional WDF
  -> VDF/VGEO visible part hierarchy
  -> partName.geo
  -> embedded PIX/PAK/ZFS GEO payload
  -> GEO parser
  -> material resolver
  -> OBJ/MTL/PNG validation asset
```

Static mission-object chain:

```text
MSN BWD2
  -> ODEF/LDEF OBJ records
  -> class-specific SDF/VCF root policy
  -> SDF SGEO declared parts
  -> partName.geo
  -> embedded PIX/PAK/ZFS GEO payload
  -> hierarchy-composed static_objects.obj
```

## Important Runtime Functions

```text
+----------+---------------------------------------------------+---------------------------------------------+
| Address  | Current name                                      | Role                                        |
+----------+---------------------------------------------------+---------------------------------------------+
| 00446c90 | construct_geometry_from_geo_buffer                | Convert GEO file buffer to runtime object   |
| 0045cbe0 | build_lit_geo_render_records_from_sections        | Build render records from runtime GEO       |
| 0045d100 | render_world_object_geometry_tree_pass_primary    | Primary geometry-tree render pass           |
| 0045d530 | render_world_object_geometry_tree_pass_secondary  | Secondary geometry-tree render pass         |
| 00471fd0 | submit_lit_textured_polygon_to_renderer           | Submit lit textured n-gon                   |
| 00478430 | compute_geo_vertex_lighting_from_normals          | Lighting from normal/secondary table        |
| 004b8470 | load_sobj_scene_object_geometry_id                | SDF/SOBJ child geometry loader              |
| 004b8f70 | LDEF/OBJ static scene-object handler              | Formats .sdf for LDEF records               |
+----------+---------------------------------------------------+---------------------------------------------+
```

## GEO File Layout

Current parsed GEO layout:

```c
struct geo_file {
    char     magic[4];       // "OEG." / little-endian 0x2e47454f
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

Face interpretation:

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

struct geo_face_ref {
    uint32_t vertex_index;
    uint32_t normal_index;
    float    u;
    float    v;
};
```

Important behavior:

```text
+--------------------+-------------------------------------------------------------+
| Field              | Current interpretation                                      |
+--------------------+-------------------------------------------------------------+
| vertex_index        | Indexes GEO vertex table                                    |
| normal_index        | Indexes normal/secondary table; used by lighting            |
| u, v                | Raw floats copied into render vertices                      |
| texture_name        | Primary material/resource key                               |
| rgb                 | Source color evidence; not default tint for textured faces  |
+--------------------+-------------------------------------------------------------+
```

## Static SDF / SGEO Model Layout

The static mission-object path uses SDF roots.  The useful visual geometry is in
the `SGEO` part list.

Observed `SGEO` layout:

```text
+-------------+--------------------------------------------------------------+
| Offset      | Field                                                        |
+-------------+--------------------------------------------------------------+
| +0x00       | uint32 part_count                                             |
| +0x04       | SdfPart records, 0x78 bytes each                              |
+-------------+--------------------------------------------------------------+
```

SDF part record:

```text
+----------------------+---------------------------------------------------------+
| Field                | Meaning                                                 |
+----------------------+---------------------------------------------------------+
| name[8]              | Part/GEO basename                                       |
| right/up/forward     | Local basis vectors                                     |
| position             | Local part translation                                  |
| parent_name[8]       | Parent part name or WORLD                               |
| trailing fields      | Not fully interpreted                                   |
+----------------------+---------------------------------------------------------+
```

The exporter composes parent hierarchy before writing static OBJ geometry.

## Current Static Reconstruction Status

```text
+-------------------------------+----------------------------------------------------------+
| Stage                         | Status                                                   |
+-------------------------------+----------------------------------------------------------+
| ODEF/LDEF record parsing      | Working via BWD2 mission parsing                         |
| Root resource policy          | Class-specific SDF/VCF resolution working                |
| SDF SGEO part parsing         | Working; declared parts only used for reconstruction     |
| GEO embedded lookup           | Working via resolver/ZFS/PIX/PAK index                   |
| Static OBJ emission           | Working for M06/full miss8/miss16 validation             |
| Static material assignment    | Working with VQM-first and family overrides              |
| Static UVs                    | V flip required/default                                  |
| Static alpha                  | Black-key cutouts working for observed water-tower base  |
+-------------------------------+----------------------------------------------------------+
```

## ODEF / LDEF Object Resource Policy

```text
+---------------------------+-----------------------------+--------------------------------------+
| Record/source             | Classes / condition          | Resource behavior                    |
+---------------------------+-----------------------------+--------------------------------------+
| ODEF/OBJ                  | class 0x01 + "spawn"         | special spawn marker table           |
| ODEF/OBJ                  | class 0x01 + "regen"         | special regen marker table           |
| ODEF/OBJ                  | class 0x01                   | label.vcf                            |
| ODEF/OBJ                  | class 0x08 / 0x09            | label.vcf                            |
| ODEF/OBJ                  | 0x02/0x03/0x04               | label.sdf                            |
| ODEF/OBJ                  | 0x07/0x0a/0x0b/0x0c          | label.sdf                            |
| ODEF/OBJ                  | 0x50/0x52/0x53               | label.sdf                            |
| ODEF/OBJ                  | 0x05/0x06/0x0d..0x4f/0x51    | fallback/null-ish diagnostic         |
| LDEF/OBJ                  | all normal records           | label.sdf                            |
| SDF child SOBJ/SGEO       | child part name              | partName.geo                         |
+---------------------------+-----------------------------+--------------------------------------+
```

Do not revert to either incorrect simplification:

```text
all ODEF -> .vcf    // wrong
all ODEF -> .sdf    // also wrong
```

## OBJ Export Baselines

```text
+------------------------+-----------------------------------------------------------+
| Output                 | Baseline                                                  |
+------------------------+-----------------------------------------------------------+
| Terrain                | dense welded OBJ with world-repeat UV repeat 1.0          |
| Static objects         | hierarchy-composed static_objects.obj                     |
| Static UVs             | write UVs with V flip                                     |
| RSEG road mesh         | experimental overlay only                                 |
| Sky                    | hemisphere validation object from mission sky MAP         |
| Combined scene         | terrain + static + RSEG + markers + optional sky          |
+------------------------+-----------------------------------------------------------+
```

## Road Mesh Caveat

The experimental `rseg_road_surface.obj` places road/corridor geometry close to
the correct visual route, but material/UV mapping remains unresolved.  Each
level appears likely to support multiple road material types, so road material
selection should be traced in both game and editor binaries.

```text
+------------------+-------------------------------------------------------------+
| RSEG item        | Current state                                                |
+------------------+-------------------------------------------------------------+
| left/right edges | Useful for corridor mesh generation                          |
| height           | use terrain-sampled height plus small offset                 |
| material         | I2D* family is closer than terrain texture, but incomplete    |
| UVs              | world/strip variants tested; still not runtime-faithful       |
| next step        | trace road type/material path in i76.exe and I76EDIT.EXE      |
+------------------+-------------------------------------------------------------+
```

## Validation Checklist

```text
[ ] Static object count matches ODEF/LDEF/SDF SGEO declared parts.
[ ] No static_mesh_errors rows.
[ ] Static UVs are emitted and V-flipped.
[ ] Static materials use VQM-first with I2D*/AT_* overrides.
[ ] Black-key alpha is applied only where validated.
[ ] Terrain UV uses world-repeat repeat 1.0.
[ ] Sky hemisphere appears in combined scene when requested.
[ ] RSEG road overlay is treated as diagnostic until road tracing is complete.
```
