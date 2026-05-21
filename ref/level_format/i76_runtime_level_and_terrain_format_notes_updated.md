# Interstate '76 Runtime Level, Terrain, and Object Format Notes

This document summarizes the current reverse-engineering findings for Interstate '76 level, terrain, and mission object handling. The emphasis is the runtime format used by the retail game, not the original editor workspace format. The long-term goal is to reconstruct shipped missions in Blender or a modern engine from the runtime mission resources and binary-backed loading behavior.

## Current high-level conclusion

A playable Interstate '76 mission is assembled from a BWD2 mission stream, a terrain sidecar, and many separately loaded object, vehicle, scene, texture, palette, route, and script resources.

```text
.MSN / .SPC / .LVL      BWD2 mission stream
.TER                    terrain page sidecar referenced by TDEF/ZONE
.HZD                    hazard/map metadata support resource
.NPT                    objective / mission text
.RTM                    route/road support resource for some missions
.VCF                    vehicle/object config used by selected ODEF classes
.VDF / VTF / WDF        vehicle geometry/texture/mount resources
.SDF                    scene-object descriptor used by selected ODEF classes and LDEF
.GEO                    geometry records referenced through SDF/SOBJ and vehicle paths
.TMT / MAP / M16        material and texture resources
.VQM / CBK              block-compressed indexed texture/frame resources
.ACT / TBL / LUM        palette and rendering support resources
```

Terrain geometry comes from the BWD2 mission stream plus the `.TER` sidecar. Standalone `.TAB`, `.LUM`, and `.TBL` resources are supporting render/data resources; they are not sufficient by themselves for terrain reconstruction.

The current reconstruction baseline is:

```text
terrain:
  dense welded full-heightfield OBJ for visual inspection

RSEG:
  route/road overlays using terrain-sampled height

ODEF:
  placement axes from binary-backed ODEF transform records

object geometry:
  class-specific ODEF resource policy:
    VCF for vehicle/turret-like classes
    SDF for static scene-object classes

adaptive terrain:
  diagnostic only until shared edge-record tessellation is faithfully implemented
```

## Runtime mission directories: `miss8` and `miss16`

The installed game contains two runtime mission directories:

```text
miss8/
miss16/
```

Both contain the shipped mission streams and terrain sidecars:

```text
miss8:
  40 .MSN
  40 .TER

miss16:
  40 .MSN
  40 .TER
  24 *_16.PCF preload/config files
```

Matching `.TER` files observed between `miss8` and `miss16` are byte-identical. Terrain height geometry is therefore effectively shared between the low-color and high-color mission sets.

Most `.MSN` files differ between `miss8` and `miss16`, but the differences are concentrated in fixed-width resource-name fields, especially `WDEF/WRLD`. The `miss16` missions substitute high-color or hardware-oriented visual resources such as `_16.ACT`, different cloud/sky textures, different surface textures, and different `.HZD` resources.

The game chooses between `miss8` and `miss16` through the high-color/resource-mode predicate at `00495060`:

```c
bool is_miss16_high_color_resource_mode(void)
{
    return g_runtime_high_color_resource_mode == 1;
}
```

Relevant symbols:

```text
00495060  is_miss16_high_color_resource_mode
005dd2a8  g_runtime_high_color_resource_mode
005a4618  g_terrain_cached_high_color_resource_mode
005dd340  g_selected_raster_plugin_dll_name
```

The function previously suspected to be heap-related is not a heap getter. It is the high-color / `miss16` selection predicate. When the predicate is false, mission paths are formatted through `miss8\%s`; when true, they are formatted through `miss16\%s`.

## Hardware/software terrain render split

The `miss8` versus `miss16` choice is separate from the terrain polygon callback choice.

Important flags:

```text
005dd2a8  g_runtime_high_color_resource_mode
00654b8b  g_player_options_terrain_alt_polygon_path
```

`g_runtime_high_color_resource_mode` controls high-color resource selection and `miss16` usage. `g_player_options_terrain_alt_polygon_path` controls which polygon emission callback is used after the adaptive terrain primitive list has been built.

The observed branch is:

```c
if (g_player_options_terrain_alt_polygon_path == 0) {
    walk_adaptive_terrain_primitives(..., i76_runtime_emit_terrain_polygon_software_path);
} else {
    walk_adaptive_terrain_primitives(..., i76_runtime_emit_terrain_polygon_alt_path);
}
```

Relevant functions:

```text
004922f0  i76_runtime_emit_terrain_polygon_software_path
004924b0  i76_runtime_emit_terrain_polygon_alt_path
```

The adaptive terrain topology appears to be shared. Hardware/high-color mode changes resource selection, optional per-vertex terrain lighting, polygon work-record contents, and downstream render submission, but it does not appear to use a different terrain height/tessellation source.

Known renderer/backend command-line options include:

```text
-gdi      software/GDI path
-glide    ZGLIDE.DLL
-redline  ZREDLINE.DLL
-d3d      ZDX5DRAW.DLL
-powervr  ZPOWERVR.DLL
-hal      hardware/HAL-related flag
```

## BWD2 mission stream

Runtime missions are BWD2 chunk streams. The mission loader validates and dispatches chunk records through descriptor tables.

Top-level mission flow:

```text
BWD2
  VER
  WDEF
  TDEF
  RDEF
  ODEF
  LDEF
  ADEF
  EXIT
```

Key loader functions:

```text
004b42b0  load_and_parse_selected_mission_resource
004b41e0  parse_bwd2_resource_with_descriptor_table
004b3db0  parse_tagged_chunk_descriptor_table
```

High-level section handlers:

```text
WDEF  world/resource metadata
TDEF  terrain definition
RDEF  route/road/corridor definitions
ODEF  object placement definitions
LDEF  static scene-object / world-entity definitions
ADEF  FSM / mission scripting definitions
EXIT  validation/finalization
```

## Descriptor tables

Known descriptor table anchors:

```text
WDEF table @ 00500ca0
  WREV -> 004b4610 validate_mission_revision_chunks
  WRLD -> 004b8a10 load_world_resource_config_from_wrld
  EXIT -> 004b4290 handle_bwd2_exit_chunk

TDEF table @ 004fae18
  TREV -> 004b4610 validate_mission_revision_chunks
  ZMAP -> 00493960 parse_zmap_chunk
  ZONE -> 004939d0 load_ter_sidecar_pages
  EXIT -> 00493bd0 terrain_tdef_exit_helper

RDEF table @ 00500cd0
  RREV -> 004b4610 validate_mission_revision_chunks
  RSEG -> 004b8780 load_rseg_route_corridor_records
  ISEG -> 004b8960 load_iseg_tseg_record_table_context_helper
  TSEG -> 004b8960 load_iseg_tseg_record_table_context_helper
  EXIT -> 004b4290 handle_bwd2_exit_chunk

ODEF table @ 00500ae8
  OREV -> 004b4610 validate_mission_revision_chunks
  OBJ  -> 004b7ac0 load_odef_object_placement_record
  EXIT -> 004b4290 handle_bwd2_exit_chunk

SDF / ODEF child descriptor table @ 00500b18
  SDFC -> 004b7f70 parse_sdfc_scene_object_descriptor_header
  SOBJ -> 004b8470 load_sobj_scene_object_geometry_id
  SGEO -> 004b7ff0 parse_sgeo_scene_object_geometry_part
  SCHK -> 004b8050 add_sdf_child_chunk_to_parent_object
  LOBJ -> 004b8ed0 create_lobj_light_object
  EXIT -> 004b4290 handle_bwd2_exit_chunk

ADEF table @ 00500d20
  AREV -> 004b4610 validate_mission_revision_chunks
  FSM  -> 00409740 initialize_fsm_runtime_heap_and_tables
  EXIT -> 004b4290 handle_bwd2_exit_chunk

Extended/X resource table @ 00500d50
  XDFC -> 004b8e00 parse_xdfc_world_record
  XGEO -> 004b8e20 null_xgeo_world_record_handler
  EXIT -> 004b4290 handle_bwd2_exit_chunk

LDEF table @ 00500d80
  LREV -> 004b4610 validate_mission_revision_chunks
  OBJ  -> 004b8f70 load_ldef_static_scene_object_record
  EXIT -> 004b4290 handle_bwd2_exit_chunk
```

## `WDEF/WRLD`

`WDEF/WRLD` carries fixed-width resource filenames and world metadata.

Observed fixed-width resource fields include:

```text
palette / ACT
luma table / LUM
translucency table / TBL
objective/notepad text / NPT
sky/cloud texture
scrounge texture / SDF-like support resource
surface texture
level map texture
hazard/map data / HZD
```

This explains why `miss8` and `miss16` mission streams often differ while their `.TER` sidecars remain identical. `miss16` frequently substitutes different palettes, sky/cloud textures, surface textures, and HZD resources.

The `WRLD` handler calls palette/luma/translucency loaders, initializes scrounge state, installs terrain texture defaults, and prepares sky/horizon texture state.

## `TDEF/ZMAP/ZONE`

Terrain loading is well understood.

The `TDEF` handler clears terrain runtime tables and parses nested terrain chunks:

```text
00493910  parse_tdef_terrain_chunks
00493960  parse_zmap_chunk
004939d0  load_ter_sidecar_pages
00493bd0  terrain_tdef_exit_helper
```

`ZMAP` payload:

```c
struct i76_zmap_payload {
    uint8_t active_patch_count;
    uint8_t page_index_map[80 * 80];
};
```

Each `ZMAP` cell is a direct page index into the `.TER` sidecar. Empty cells are `0xff`. Non-empty values are validated against `active_patch_count`.

`ZONE` provides the sidecar terrain filename. The runtime opens this sidecar from the mission/add-on resource path and maps it as a sequence of terrain pages.

The `.TER` sidecar layout:

```text
active_patch_count pages
page size: 0x8000 bytes
page shape: 128 * 128 uint16 little-endian samples
```

Each terrain sample word:

```text
bits  0..11   height low12
bit      12   surface/special flag
bits 13..15   surface class
```

## Runtime terrain page indirection

The game does not sample terrain directly from the `80 x 80` ZMAP. It first builds a `128 x 128` runtime page-pointer grid:

```text
00493080  build_runtime_terrain_page_pointer_grid
00644380  g_runtime_terrain_page_ptr_grid_128x128
```

The builder initializes the page-pointer grid to a default page, then copies each active `ZMAP` cell into the larger page-pointer table with a `+24, +24` offset:

```c
page_ptr_grid[(zmap_z + 24) * 128 + (zmap_x + 24)] =
    active_zone_page_ptrs[zmap_value];
```

The `+24` offset explains constants such as:

```text
0xc00 = 24 * 128
```

Height lookup uses the page-pointer grid and local `x/z & 0x7f` sample coordinates:

```c
uint16_t lookup_terrain_height_low12(int x, int z)
{
    int table_index =
        ((z + 0xc00) & 0xffffff80) +
        ((x + 0xc00) >> 7);

    int local_index =
        ((z + 0xc00) & 0x7f) * 0x80 +
        ((x + 0xc00) & 0x7f);

    return *(uint16_t *)(page_ptr_grid[table_index] + local_index * 2) & 0x0fff;
}
```

Related functions:

```text
00493160  lookup_terrain_height_low12
004927b0  lookup_terrain_surface_class
004931c0  compute_terrain_normal_from_height_samples
```

The terrain should be treated as one continuous integer sample domain backed by indirection. The runtime does not simply synthesize a `129 x 129` mesh per page.

## Dense terrain export baseline

For Blender inspection, the current stable baseline is a dense welded heightfield mesh. It is not runtime-faithful topology, but it is the most useful visual baseline.

Baseline exporter behavior:

```text
one welded vertex per global terrain sample coordinate
shared seam vertices across adjacent active pages
terrain origin centered from active ZMAP bounds
Blender coordinate order: OBJ v = x, z, height
terrain height sampled through the runtime page-grid model
```

For M06, the active ZMAP block is:

```text
bounds:      x=2..5, z=74..77
center cell: x=4.0, z=76.0
origin:      world x=2560, world z=48640
```

RSEG and ODEF overlays must subtract the same origin as the terrain, or they will appear tens of thousands of units away from the centered terrain.

## Adaptive terrain mesh pipeline

The runtime renderer builds adaptive terrain primitives.

Core functions:

```text
004929b0  compute_visible_terrain_bounds
00490a00  build_visible_adaptive_terrain_mesh
004911e0  subdivide_terrain_quad_for_render
00491810  alloc_terrain_primitive_node
004918b0  alloc_terrain_edge_record
004918f0  split_terrain_edge_insert_midpoint_vertex
00491a30  walk_adaptive_terrain_primitives_and_emit_polygons
00492270  flatten_edge_forward_emit_vertex_a_leaves
004922b0  flatten_edge_reverse_emit_vertex_b_leaves
004937c0  transform_generated_terrain_vertices
```

The builder seeds root vertices and edges, recursively subdivides quads, emits primitive nodes, then walks those nodes to produce polygon work records.

`004911e0` is the exact recursive subdivision predicate. Known block structure:

```text
entry / edge extent / reject test
half-scale + distance/error gate
center height-error test
quarter height-error tests
minimum-scale + raw surface-word scan setup
special-surface forced-split scan
split four edges, create center edges, recurse
leaf primitive-node emission
```

The hard split floor is confirmed:

```c
half_scale = scale >> 1;
if (half_scale >= 0x20) {
    split;
}
```

This was the main reason early adaptive-exporter attempts were too sparse.

The special terrain-word forced-split condition is:

```c
word >= 0x4000 && (word & 0xe000) != 0xa000
```

That scan uses the same runtime page-grid addressing model as height lookup. High terrain-word bits influence tessellation behavior, not only material assignment.

Adaptive overlay caveat: a correct runtime-faithful adaptive exporter must reproduce the shared edge-record graph. Independent per-quad subdivision creates T-junctions and edge discontinuities. Until shared edge splitting and `00491a30` flattening are reproduced, adaptive overlay exports are diagnostic only.

## Adaptive terrain structures

Generated terrain vertex:

```c
struct i76_runtime_terrain_vertex_xyz {
    float x;
    float y_or_height;
    float z_or_depth;
}; // 0x0c
```

Terrain edge record:

```c
struct i76_runtime_terrain_edge_record {
    int16_t vertex_a;        // +0x00
    int16_t vertex_b;        // +0x02
    edge_t *child_edge_a;    // +0x04
    edge_t *child_edge_b;    // +0x08
}; // 0x0c
```

Terrain primitive node:

```c
struct i76_runtime_terrain_primitive_node {
    int16_t screen_or_bucket_start; // +0x00
    int16_t screen_or_bucket_end;   // +0x02
    int32_t range_delta;            // +0x04
    primitive_t *next;              // +0x08
    edge_t *edge_ref_0;             // +0x0c
    edge_t *edge_ref_1;             // +0x10
    edge_t *edge_ref_2;             // +0x14
    edge_t *edge_ref_3;             // +0x18
}; // 0x1c
```

The `next` field at `+0x08` links generated terrain primitive nodes. It is not unused padding.

Terrain globals:

```text
005dd320  g_runtime_terrain_vertex_xyz_buffer
005dd2ec  g_runtime_terrain_vertex_projected_or_lighting_buffer
0059c560  g_runtime_terrain_primitive_list_head
0059c574  g_runtime_terrain_primitive_list_tail
0059c568  g_runtime_terrain_edge_record_count
0059c56c  g_runtime_terrain_primitive_node_count
006442ec  g_runtime_terrain_vertex_count
00654380  g_runtime_terrain_arena_cursor
```

## Edge flattening

Adaptive primitives reference four edge records. Before rendering, split edge trees are flattened into a polygon vertex-index loop.

Forward flatten:

```c
int *flatten_forward(int *out, edge_t *e)
{
    if (e->child_edge_a) {
        out = flatten_forward(out, e->child_edge_a);
        out = flatten_forward(out, e->child_edge_b);
        return out;
    }

    *out++ = e->vertex_a;
    return out;
}
```

Reverse flatten:

```c
int *flatten_reverse(int *out, edge_t *e)
{
    if (e->child_edge_a) {
        out = flatten_reverse(out, e->child_edge_b);
        out = flatten_reverse(out, e->child_edge_a);
        return out;
    }

    *out++ = e->vertex_b;
    return out;
}
```

`00491a30` uses this asymmetric order over the primitive’s four edge refs:

```text
edge_ref_2 (+0x14): forward traversal
edge_ref_1 (+0x10): forward traversal
edge_ref_3 (+0x18): reverse traversal
edge_ref_0 (+0x0c): reverse traversal
```

A terrain primitive may therefore render as a polygon with more than three or four vertices after edge-tree flattening.

`00491a30` also calls `00494a90` several times, likely to compute polygon/plane normal data for generated terrain polygons. A faithful exporter should eventually preserve this calculation rather than relying only on OBJ face normals.

## Terrain polygon work records and scan buckets

After flattening, terrain callbacks create variable-length polygon work records.

Polygon work header:

```c
struct i76_runtime_terrain_polygon_work_header {
    uint32_t vertex_count;        // +0x00
    uint32_t material_or_type;    // +0x04
    uint32_t flags;              // +0x08
    uint32_t record_type;        // +0x0c
    float max_or_sort_depth;     // +0x10
    polygon_t *next;             // +0x14
    polygon_t *prev;             // +0x18
}; // 0x1c
```

Variable vertex record:

```c
struct i76_runtime_terrain_polygon_work_vertex {
    float x;                     // +0x00
    float y;                     // +0x04
    float z;                     // +0x08
    float screen_or_projected_x; // +0x0c
    float screen_or_projected_y; // +0x10
    float shade_or_depth;        // +0x14
}; // 0x18
```

Scan bucket header:

```c
struct i76_runtime_terrain_scan_bucket_header {
    void *head; // +0x00
    void *tail; // +0x04
    int count;  // +0x08
}; // 0x0c
```

Relevant functions:

```text
00490590  alloc_prepare_terrain_polygon_work_record
0048fe10  bin_terrain_polygon_work_record
00490470  add_terrain_scan_bucket_span_entry
```

## Terrain lighting

In high-color / `miss16` mode, the terrain builder performs additional per-generated-vertex lighting.

Relevant helper:

```text
00490fb0  compute_terrain_lighting_from_neighbor_heights
```

This samples the center and four neighboring terrain heights, computes slope terms, applies a light vector, clamps against constants, and returns a shade/intensity value.

The result is stored in the companion terrain buffer:

```text
005dd2ec  g_runtime_terrain_vertex_projected_or_lighting_buffer
```

Specifically, high-color mode writes lighting data into the companion record’s `+8` field.

## `RDEF/RSEG`: route/road/corridor records

`RDEF/RSEG` is now understood as a route/road/corridor-style geometry/control table.

Serialized RSEG layout:

```c
struct i76_rseg_serialized {
    uint32_t kind;
    uint32_t count;
    struct i76_rseg_point points[count];
};

struct i76_rseg_point {
    float left_x;       // +0x00
    float left_z;       // +0x04
    float aux_z_or_mid; // +0x08, often tracks z
    float right_x;      // +0x0c
    float unknown_10;   // +0x10, not reliable height
    float right_z;      // +0x14
}; // 0x18
```

The `0x18` records look like paired left/right edge samples for a road/corridor, not single points. Width statistics are road-like, commonly around 5–10 world units.

Important correction: `unknown_10` is not a reliable vertical height. Some segment endpoints contain large values in this field. For visualization, RSEG overlays should sample terrain height at the road point and optionally add a small height offset. This is the current baseline.

Runtime loader:

```text
004b8780  load_rseg_route_corridor_records
```

The runtime chunks large serialized RSEG records into linked runtime nodes. Each runtime node allocation is:

```c
size = 0x2c + point_count * 0x18;
```

with `point_count <= 0x18`.

RSEG globals:

```text
005db988  g_runtime_rseg_node_list_head
005db98c  g_runtime_rseg_node_count
```

Kind `3072` appears as a rare count-zero record and is best treated as a sentinel/control entry until proven otherwise.

## `ODEF/OBJ`: object placement records

`ODEF/OBJ` payloads are 100-byte placement/entity records.

Current structure:

```c
struct i76_odef_obj_record {
    char  label_raw[8];          // +0x00, high bits may carry ID flags
    float basis_3x3[9];          // +0x08..+0x28
    float pos_x;                 // +0x2c
    float pos_y;                 // +0x30
    float pos_z;                 // +0x34
    uint32_t tail_00;            // +0x38
    uint32_t tail_04;            // +0x3c
    uint32_t tail_08;            // +0x40
    uint32_t tail_0c;            // +0x44
    uint32_t tail_10;            // +0x48
    uint32_t tail_14;            // +0x4c
    uint32_t tail_18;            // +0x50
    uint32_t tail_1c;            // +0x54
    uint32_t tail_20;            // +0x58
    uint32_t class_id;           // +0x5c
    uint32_t tail_28;            // +0x60
}; // payload 0x64
```

The runtime normalizes the 8-byte label by masking high bits with `0x7f`. The high-bit pattern appears to carry an ID/flag field. A blank normalized label is not ordinary visible geometry.

The transform interpretation is confirmed by `004b8230`:

```text
source +0x08..+0x28 -> destination +0x04..+0x24 as dwords
source +0x2c        -> destination +0x28 as double
source +0x30        -> destination +0x30 as double
source +0x34        -> destination +0x38 as double
```

So the 3x3 basis and position are consumed directly by the runtime transform path.

For Blender debug output, `ODEF` axes objects are a scaffold: they draw the local basis vectors at each valid placement transform. They are not final game geometry.

## Corrected ODEF class-specific resource policy

The major correction from the v42 binary trace is that `ODEF` resource resolution is class-specific.

The handler at `004b7ac0` dispatches using `class_id` at payload `+0x5c`:

```asm
mov eax, [record + 0x5c]
dec eax
cmp eax, 0x52
ja  fallback
mov cl, byte ptr [eax + 0x004b7e44]
jmp dword ptr [ecx * 4 + 0x004b7e24]
```

The class-to-resource policy is:

```text
ODEF class 0x01:
  if label == "spawn" -> spawn table
  if label == "regen" -> regen table
  otherwise label.vcf

ODEF class 0x08:
  label.vcf

ODEF class 0x09:
  label.vcf

ODEF class 0x02:
  label.sdf

ODEF class 0x03:
  label.sdf

ODEF class 0x04:
  label.sdf

ODEF class 0x07:
  label.sdf

ODEF class 0x0a:
  label.sdf

ODEF class 0x0b:
  label.sdf

ODEF class 0x0c:
  label.sdf

ODEF class 0x50:
  label.sdf

ODEF class 0x52:
  label.sdf

ODEF class 0x53:
  label.sdf

ODEF class 0x05, 0x06, 0x0d..0x4f, 0x51:
  fallback/null-ish path, not ordinary visible geometry yet

ODEF class 0 or blank label:
  invalid/special diagnostic rows for now
```

This reconciles Open76 with the binary for static scene objects. Open76’s `label.sdf` behavior is not merely a visual workaround for the static classes that dominate maps such as M06; it is consistent with the retail binary for those classes. The earlier broad assumption that all dispatch-valid ODEF classes go to `.vcf` was wrong.

Known case bodies:

```text
004b7b96  ODEF .vcf case body
  calls 004b8230
  formats label + ".vcf"
  calls 004ad6f0 load_vehicle_config_for_world_object

004b7be9  ODEF .sdf case body
  calls 004b8230
  formats label + ".sdf"
  calls 004b41e0 parse_bwd2_resource_with_descriptor_table
  uses SDF child descriptor table 00500b18
```

## Spawn and regen records

`spawn` and `regen` are special ODEF class-1 markers, not ordinary resources.

Handler:

```text
00450f90  register_spawn_or_regen_transform
```

Tables:

```text
spawn:
  table base   0053fd88
  count global 00540d98

regen:
  table base   0053ecb0
  count global 00540d9c
```

Each table has capacity `0x40`, with entry size `0x40`.

The copied transform payload is:

```text
source +0x08..+0x28 copied as dwords to entry +0x00..+0x20
source +0x2c copied as float and stored as double at entry +0x28
source +0x30 copied as float and stored as double at entry +0x30
source +0x34 copied as float and stored as double at entry +0x38
```

## `LDEF/OBJ`: static scene-object path

`LDEF/OBJ` is distinct from `ODEF/OBJ`. It is a static/world scene-entity construction path.

Handler:

```text
004b8f70  load_ldef_static_scene_object_record
```

This path formats `label.sdf`, parses the scene-object descriptor resource, allocates/registers a world object, applies transforms/bounds, and supports child part creation.

`LDEF` object records are variable size and are not the same 100-byte placement structure as `ODEF/OBJ`.

## SDF child descriptor path

Both ODEF `.sdf` class bodies and LDEF `.sdf` objects use the SDF child descriptor table at `00500b18`.

Relevant child handlers:

```text
004b7f70  SDFC / scene object descriptor header
004b8470  SOBJ / scene object geometry id
004b7ff0  SGEO / scene object geometry part transform
004b8050  SCHK / add chunk to parent object
004b8ed0  LOBJ / light object child
```

`SOBJ` formats `partName.geo` and calls the GEO loader path. The static-object pipeline is therefore:

```text
ODEF static class or LDEF object
  -> label.sdf
    -> SDF child descriptor table
      -> SOBJ / SGEO / SCHK / LOBJ
        -> partName.geo
          -> GEO constructor/render-record path
```

Open76’s SDF parser shape is a useful sanity check here:

```text
SDFC
SGEO
  numParts
  part records:
    8-byte part name
    right/up/forward vectors
    position
    parent name
    56 skipped/extra bytes
```

The binary remains the source of truth, but Open76’s SDF/SOBJ/GEO structure is now broadly aligned with the traced binary path.

## VCF / vehicle-object path

Selected ODEF classes use `.vcf`:

```text
class 0x01, except spawn/regen
class 0x08
class 0x09
```

Key functions:

```text
004ad640  format_8char_resource_basename_with_suffix
004ad6f0  load_vehicle_config_for_world_object
004adb90  parse_vcfc_vehicle_config_root
004ad950  parse_vcfc_vdf_vtf_wdf_resource_refs
004b3650  parse_vdf_vehicle_definition_resource
004b7800  instantiate_vdf_vehicle_geometry_part_sets
```

`004ad6f0` is a real VCFC/VCF loader. It calls `004b41e0` with the VCFC descriptor table. There is no `.sdf` fallback inside the `.vcf` path.

Optional `.vsf` state loading exists under a separate mode predicate and appears to be vehicle state/config, not a scene-object fallback.

## GEO construction and render-record path

Main GEO constructor:

```text
00446c90  construct_geometry_from_geo_buffer
```

This validates `OEG.` magic (`0x2e47454f`), reads vertex/section/face counts, computes runtime allocation size, and constructs a runtime geometry object.

Lit render-record builder:

```text
0045cbe0  build_lit_geo_render_records_from_sections
```

This path composes transforms, transforms vertex data, computes lighting from normals, and emits lit render records from sections.

Higher-level render paths:

```text
0045d100  render_or_prepare_world_object_geo_branch_a
0045d530  render_or_prepare_world_object_geo_branch_b
00471fd0  submit_lit_textured_polygon_to_renderer
00478430  compute_geo_vertex_lighting_from_normals
00493550  transform_world_object_bounds_or_geometry
00494e20  compose_world_object_transform
004925f0  link_or_update_world_object_bounds
```

PIX/PAK indexes contain many embedded `.geo`, `.tmt`, `.m16`, `.vqm`, and `.map` resources. Current observed PIX inventory:

```text
.geo
.vqm
.m16
.tmt
.map
```

`.vcf` and `.sdf` are not PIX-indexed in the observed resource set; they are loose/ZFS-extracted resources under `resources/`.

## Resource acquisition path

Resource acquisition below high-level suffix formatting is centered on `004b41e0` and `0046ffc0`.

Key flow:

```text
004ad6f0 load_vehicle_config_for_world_object
  -> 004b41e0 parse_bwd2_resource_with_descriptor_table
    -> 0046ffc0 open_resource_file_into_memory
      -> 00470b20 load_indexed_resource_record_payload
      -> 00470070 load_resource_stream_into_loaded_cache
        -> 004b3310 get_registered_resource_payload_size
        -> 004b3000 / 004b3030 load_registered_resource_payload
```

`0046ffc0` lowercases the requested name, checks indexed PIX/PAK resources, checks the registered/cache/ZFS/loose-file path, and can retry in an alternate order depending on a global mode flag.

`00470660` loads PIX/PAK resource indexes. It scans `*.pix`, derives sibling `.pak`, parses rows with a `%s %d %d`-style format, lowercases resource keys, and sorts the resource index.

Important distinction: evidence from resource probes must separate real binary/container hits from hits inside generated reports, manifests, and tar files under scratch directories.

## ADEF / FSM scripting

`ADEF/FSM` is the mission behavior scripting system.

Top-level bootstrap:

```text
00409740  initialize_fsm_runtime_heap_and_tables
```

Serialized table loader:

```text
00410720  load_serialized_fsm_runtime_tables
004105a0  load_serialized_fsm_record_array_with_bitfields
004102d0  load_serialized_fsm_record_array_with_vec3_lists
00410490  load_serialized_fsm_linked_state_blocks
```

Finalizer:

```text
004125c0  finalize_loaded_fsm_runtime_tables
00410a10  initialize_or_match_fsm_command_name_table
00412400  register_fsm_instance_ids_from_mission
004122d0  validate_project_wav_smk_resource_list
00412500  relocate_fsm_command_table_internal_pointers
```

The command matcher contains mission scripting verbs/predicates such as:

```text
behave
attack
sit
goto
guard
do
set
inc
dec
rand
whoRammed
whoShot
startTimer
success
fail
playScene
isWithin
isDead
setId
follow
teleport
destroy
playMovie
camera commands
triggerGate
setSkill
reveal
setAgg
salvage
setSiren
setArtillery
stopCB
```

The string matcher order is not always equal to command ID order; durable documentation should use the extracted return-ID table, not simple sequence order.

## Current reconstruction baseline

The current practical reconstruction baseline is:

```text
terrain:
  dense welded heightfield from TDEF/ZMAP/ZONE + TER sidecar

RSEG:
  route/road overlays using terrain-sampled height
  unknown_10 is preserved in TSV but not used as vertical height by default

ODEF:
  axes scaffold from binary-confirmed basis + position transforms

ODEF resource resolution:
  class-specific .vcf or .sdf according to binary case bodies

LDEF:
  label.sdf static scene-object path

SDF:
  decode child SOBJ/SGEO/SCHK/LOBJ
  resolve SOBJ to partName.geo

GEO:
  next implementation target for actual mesh instancing
```

Do not enable adaptive terrain overlay by default yet. The dense welded terrain is the visual baseline; adaptive overlay remains diagnostic until shared edge-record subdivision and edge flattening are implemented.

## Immediate next implementation targets

The next implementation tasks are:

```text
1. Update reconstruction exporter resource policy:
     ODEF 0x01/0x08/0x09 -> VCF
     ODEF static classes -> SDF
     LDEF -> SDF
     SOBJ -> GEO

2. Add SDF decoding:
     SDFC / SGEO / SOBJ / SCHK / LOBJ
     extract child part names, transforms, and parent relationships

3. Index and load GEO resources:
     loose resources and PIX/PAK-indexed resources
     route through construct_geometry_from_geo_buffer semantics

4. Instantiate SDF-backed ODEF objects:
     apply ODEF basis/position transform
     apply SDF child transforms
     then attach decoded GEO meshes

5. Continue VCF/VDF path separately:
     parse VCF/VCFC
     resolve VDF/VTF/WDF
     instantiate vehicle/object geometry where classes require VCF

6. Implement faithful adaptive terrain:
     shared edge records
     hard half-scale split floor
     center/quarter error tests
     special-surface scan
     edge flattening order
```

## Known limitations

Known unresolved or partially resolved areas:

```text
Exact adaptive terrain projection/error constants beyond confirmed hard split and surface scan
Exact terrain polygon work-record material binding
RSEG unknown_10 field semantics
RSEG kind-specific behavior
Class 0 / blank ODEF diagnostic records
Fallback/null-ish ODEF class cases 0x05, 0x06, 0x0d..0x4f, 0x51
Full SDF child transform semantics
Full GEO face/winding/UV/material parity
Exact VDF/VTF/WDF object instancing
FSM bytecode/table execution semantics beyond command matching
```

## Useful trace / rename scripts from this investigation

Not exhaustive, but useful anchors:

```text
cgpt_i76exe_export_level_config_unknowns_trace_v14_fixed.java
cgpt_i76exe_export_level_descriptor_tables_v15_fixed.java
cgpt_i76exe_export_level_record_handlers_v16_fixed.java
cgpt_i76exe_export_level_record_handler_deeptrace_v17_fixed.java
cgpt_i76exe_export_level_record_handler_deeptrace_v18_fixed.java
cgpt_i76exe_export_level_record_handler_deeptrace_v19.java
cgpt_i76exe_export_level_semantic_tables_v20.java
cgpt_i76exe_export_level_semantic_tables_v21.java
cgpt_i76exe_export_level_semantic_tables_v22.java
cgpt_i76exe_export_geometry_reconstruction_deeptrace_v23.java
cgpt_i76exe_export_geometry_reconstruction_deeptrace_v24.java
cgpt_i76exe_export_geometry_reconstruction_deeptrace_v25.java
cgpt_i76exe_export_geometry_reconstruction_deeptrace_v26.java
cgpt_i76exe_export_object_geometry_resolution_trace_v27.java
cgpt_i76exe_export_object_geometry_resolution_trace_v28.java
cgpt_i76exe_export_object_geometry_resolution_trace_v29.java
cgpt_i76exe_export_sdf_geo_resolution_trace_v30.java
cgpt_i76exe_validate_open76_object_lookup_v31.java
cgpt_i76exe_export_binary_object_resource_path_v32.java
cgpt_i76exe_export_binary_object_resource_path_v33.java
cgpt_i76exe_export_binary_object_lookup_case_bodies_v34.java
cgpt_i76exe_export_vcf_loader_deeptrace_v35.java
cgpt_i76exe_apply_level_geometry_resource_renames_v36.java
cgpt_i76exe_export_resource_acquisition_trace_v37_fixed.java
cgpt_i76exe_export_resource_acquisition_deeptrace_v38.java
cgpt_i76exe_export_resource_acquisition_chokepoints_v39.java
cgpt_i76exe_export_pix_pak_index_trace_v40.java
cgpt_i76exe_export_resource_lookup_failure_paths_v41.java
cgpt_i76exe_export_odef_class_case_truth_v42_fixed2.java
cgpt_i76exe_apply_level_object_resource_renames_v43.java
```

Related Python probes/exporters:

```text
i76_runtime_dense_terrain_export_v5.py
i76_level_reconstruction_export_v4.py
i76_geometry_reconstruction_corpus_probe_v7.py
i76_object_geometry_resolution_probe_v4_binary_truth.py
i76_resource_acquisition_index_probe_v13_vcf_inventory.py
i76_object_class_resource_policy_probe_v14.py
```
