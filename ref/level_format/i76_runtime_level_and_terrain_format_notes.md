# Interstate '76 Runtime Level and Terrain Format Notes

This document summarizes the current reverse-engineering findings for Interstate '76 level and terrain handling, based on `i76.exe`, `i76edit.exe`, Open76 behavior, extracted game assets, and the Ghidra traces generated during the investigation.

The emphasis here is the **runtime format used by the game**, not the original editor workspace format. The long-term goal is to reconstruct stages in Blender or a modern engine from the shipped mission/terrain resources.

## Current high-level conclusion

Interstate '76 runtime levels are not a single monolithic mesh file. A playable mission is assembled from:

```text
.MSN / .SPC / .LVL     BWD2 mission stream
.TER                  terrain page sidecar referenced by TDEF/ZONE
.HZD                  map tile / hazard / level metadata support resource
.NPT                  objective / mission text
.RTM                  road / route metadata for some missions
.VCF/.VDF/.VTf/...    vehicle resources
.MAP/.M16/.VQM/.CBK   textures and texture frames
.GEO/.SDF/.WDF/...    geometry/object resources
.ACT/.TBL/.LUM/...    palette/render-support resources
```

The terrain geometry comes from the BWD2 mission stream plus the `.TER` sidecar. Standalone `.TAB`, `.LUM`, and `.TBL` records in `I76.ZFS` are supporting resources; they are not sufficient by themselves for game-faithful terrain reconstruction.

## Runtime mission directories: `miss8` and `miss16`

The installed game contains two runtime mission directories:

```text
miss8/
miss16/
```

Both directories contain mission streams and terrain sidecars:

```text
miss8:
  40 .MSN
  40 .TER

miss16:
  40 .MSN
  40 .TER
  24 *_16.PCF preload/config files
```

The `.TER` files observed between `miss8` and `miss16` are byte-identical for matching missions, so terrain height geometry is effectively shared.

Most `.MSN` files differ between `miss8` and `miss16`, but usually at fixed-width resource-name fields, especially in `WDEF/WRLD`. The `miss16` missions reference high-color or hardware-oriented visual resources such as `_16.ACT`, different sky textures, different surface textures, and different `.HZD` resources. The additional `*_16.PCF` files in `miss16` appear to be preload/config lists for 16-bit or hardware resource staging.

The game chooses between `miss8` and `miss16` through a high-color/resource-mode predicate:

```c
bool is_miss16_high_color_resource_mode(void)
{
    return g_runtime_high_color_resource_mode == 1;
}
```

The function previously misnamed `get_global_heap_handle` at `00495060` is not heap-related. It is this `miss16` / high-color predicate.

Relevant names:

```text
00495060  is_miss16_high_color_resource_mode

005dd2a8  g_runtime_high_color_resource_mode
005a4618  g_terrain_cached_high_color_resource_mode
005dd340  g_selected_raster_plugin_dll_name
```

When the predicate is false, the game formats mission paths using `miss8\%s`. When true, it uses `miss16\%s`.

## Hardware/software render mode split

The `miss8` versus `miss16` choice is separate from the terrain polygon callback choice.

There are two important flags:

```text
005dd2a8  g_runtime_high_color_resource_mode
00654b8b  g_player_options_terrain_alt_polygon_path
```

`g_runtime_high_color_resource_mode` controls high-color resource selection and `miss16` usage.

`g_player_options_terrain_alt_polygon_path` controls which terrain polygon emission callback is used after the adaptive terrain primitive list has been built.

The terrain callback branch is:

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

The adaptive terrain topology appears to be shared. `miss16` and hardware mode affect resource selection, optional terrain lighting, polygon work-record contents, and downstream render submission, but they do not appear to use a different terrain height/tessellation source.

Command-line backend options include:

```text
-gdi      software/GDI path
-glide    ZGLIDE.DLL
-redline  ZREDLINE.DLL
-d3d      ZDX5DRAW.DLL
-powervr  ZPOWERVR.DLL
-hal      hardware/HAL-related flag
```

When high-color or hardware mode is active, the player/display options loader forces several option bytes on, including the terrain alternate polygon path flag.

## BWD2 mission stream

Runtime missions are BWD2 chunk streams. The mission loader validates and dispatches chunk records through descriptor tables.

Known high-level runtime descriptor flow:

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

The game-side mission load path includes:

```text
004b42b0  load_and_parse_selected_mission_resource
004b41e0  parse_bwd2_resource_with_descriptor_table
004b3db0  parse_tagged_chunk_descriptor_table
```

The relevant mission section table includes:

```text
WDEF  world/resource metadata
TDEF  terrain definition
RDEF  road/route definition
ODEF  object definition
LDEF  lighting or related level data
ADEF  actor/AI/auxiliary definition
EXIT  validation/finalization
```

The nested terrain section table is:

```text
TDEF
  TREV
  ZMAP
  ZONE
  EXIT
```

## `WDEF/WRLD`

Open76 and the runtime traces indicate that `WDEF/WRLD` carries fixed-width resource filenames and world metadata.

Observed fields include resource references for:

```text
palette
luma table
translucency table
objective text
sky texture
scrounge texture
surface texture
level map
HZD
```

This explains why `miss8` and `miss16` mission streams often differ while their terrain sidecars remain identical: `miss16` frequently substitutes different palette, sky, surface, and HZD resources.

## `TDEF/ZMAP/ZONE`

Terrain loading is now well understood.

The `TDEF` handler clears terrain runtime tables and parses nested terrain chunks:

```text
00493910  i76_runtime_parse_tdef_terrain_chunks
00493960  i76_runtime_parse_zmap_chunk
004939d0  i76_runtime_load_ter_sidecar_pages
00493bd0  i76_runtime_tdef_exit_helper
```

`ZMAP` payload:

```c
struct i76_zmap_payload {
    uint8_t active_patch_count;
    uint8_t page_index_map[80 * 80];
};
```

Each `ZMAP` cell is a direct page index into the terrain sidecar. Empty cells are `0xff`. The game validates that non-empty values are less than `active_patch_count`.

`ZONE` provides the sidecar terrain filename. The runtime opens the sidecar from the add-on / mission resource path and maps it as a sequence of terrain pages.

The `.TER` sidecar is:

```text
active_patch_count pages
page size: 0x8000 bytes
page shape: 128 * 128 uint16 little-endian samples
```

Each terrain sample word is:

```text
bits  0..11   height low12
bit      12   surface flag / special bit
bits 13..15   surface class
```

## Runtime terrain page indirection

The game does not sample terrain directly from the `80 x 80` `ZMAP`.

It first builds a `128 x 128` terrain page-pointer grid:

```text
00493080  i76_runtime_build_terrain_page_pointer_grid
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

The height lookup uses the page-pointer grid and local `x/z & 0x7f` sample coordinates:

```c
uint16_t i76_runtime_lookup_terrain_height_low12(int x, int z)
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

Related runtime functions:

```text
00493160  i76_runtime_lookup_terrain_height_low12
004927b0  i76_runtime_lookup_terrain_surface_class
004931c0  i76_runtime_compute_terrain_normal_from_height_samples
```

The terrain should be considered one continuous integer sample domain backed by an indirection grid. The game does not explicitly synthesize a `129 x 129` page mesh and does not average seams.

## Why regular-grid OBJ exports showed artifacts

Several prototype OBJ exporters treated each terrain page as a simple regular heightfield patch. This led to problems:

```text
128x128 pages emitted as 128x128 vertices:
  Produced gaps because 127 sample intervals * 5 = 635, not 640.

129x129 page expansion:
  Removed gaps, but introduced visible ridges from duplicate seam vertices,
  per-patch normal splitting, or neighbor-edge mismatch.

Welded full-grid mesh:
  Removed duplicate seam topology, but still showed grid artifacts because
  the game does not render terrain as a dense regular full-grid mesh.
```

The original game renders an adaptive terrain primitive list. A full-resolution heightfield OBJ is useful for inspection, but it is not runtime-faithful.

## Adaptive terrain mesh pipeline

The terrain renderer builds adaptive primitives at runtime.

Core functions:

```text
004929b0  i76_runtime_compute_visible_terrain_bounds
00490a00  i76_runtime_build_visible_adaptive_terrain_mesh
004911e0  i76_runtime_subdivide_terrain_quad_for_render
00491810  i76_runtime_alloc_terrain_primitive_node
004918b0  i76_runtime_alloc_terrain_edge_record
004918f0  i76_runtime_split_terrain_edge_insert_midpoint_vertex
00491a30  i76_runtime_walk_adaptive_terrain_primitives_and_emit_polygons
00492270  i76_runtime_flatten_edge_forward_emit_vertex_a_leaves
004922b0  i76_runtime_flatten_edge_reverse_emit_vertex_b_leaves
004937c0  i76_runtime_transform_generated_terrain_vertices
```

The builder seeds root vertices and edges, recursively subdivides terrain quads, emits primitive nodes, then walks those nodes to produce polygon work records.

The recursive subdivision function tests:

```text
camera distance
projected error / screen-space size
quad scale / half-scale
sampled midpoint and quarter-point heights
packed surface bits
special high terrain-word cases
```

A surface-bit condition seen in the small-quad path:

```c
(word > 0x3fff) && ((word & 0xe000) != 0xa000)
```

This means terrain-word high bits can influence tessellation behavior, not only material assignment.

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

The `next` field at `+0x08` was an important correction. It is not unused padding; it links generated terrain primitive nodes.

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

`00491a30` uses an asymmetric order over the primitive’s four edge refs:

```text
edge_ref_2 (+0x14): forward traversal
edge_ref_1 (+0x10): forward traversal
edge_ref_3 (+0x18): reverse traversal
edge_ref_0 (+0x0c): reverse traversal
```

This means a terrain primitive may render as a polygon with more than three or four vertices after edge-tree flattening.

## Polygon work records and scan buckets

After flattening, terrain callbacks create variable-length polygon work records.

Polygon work header:

```c
struct i76_runtime_terrain_polygon_work_header {
    uint32_t vertex_count;       // +0x00
    uint32_t material_or_type;   // +0x04
    uint32_t flags;              // +0x08
    uint32_t record_type;        // +0x0c
    float    max_or_sort_depth;  // +0x10
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
    void *head;   // +0x00
    void *tail;   // +0x04
    int   count;  // +0x08
}; // 0x0c
```

Scan bucket span entry:

```c
struct i76_runtime_terrain_scan_bucket_span_entry {
    float left_or_min;     // +0x00
    float right_or_max;    // +0x04
    int   depth_bucket;    // +0x08
    void *next;            // +0x0c
}; // 0x10
```

Relevant functions:

```text
00490590  i76_runtime_alloc_prepare_terrain_polygon_work_record
0048fe10  i76_runtime_bin_terrain_polygon_work_record
00490470  i76_runtime_add_terrain_scan_bucket_span_entry
```

## Terrain lighting

In high-color / `miss16` mode, the terrain builder performs additional per-generated-vertex lighting work.

Relevant helper:

```text
00490fb0  i76_runtime_compute_terrain_lighting_from_neighbor_heights
```

This samples the center and four neighboring heights using the same terrain height lookup path, computes slope terms, applies a light vector, clamps against constants, and returns a shade/intensity value.

The result is stored in the terrain companion buffer:

```text
005dd2ec  g_runtime_terrain_vertex_projected_or_lighting_buffer
```

Specifically, high-color mode writes lighting data into the companion record’s `+8` field.

## Runtime-faithful Blender exporter direction

A faithful Blender terrain exporter should not export a full regular page grid as the final answer.

The correct implementation target is:

```text
1. Parse .MSN / .SPC / .LVL BWD2 stream.
2. Decode TDEF/ZMAP/ZONE.
3. Load matching .TER sidecar pages.
4. Build the same 128x128 page-pointer grid as 00493080.
5. Implement height/material lookup matching 00493160 / 004927b0.
6. Reproduce the adaptive subdivision path from 00490a00 / 004911e0.
7. Allocate edge records and primitive nodes logically.
8. Flatten edge trees in the same order as 00491a30.
9. Emit the resulting adaptive polygons to OBJ or Blender mesh.
10. Optionally compute terrain lighting using 00490fb0 semantics for miss16/high-color visual approximation.
```

Two exporter modes are worth keeping:

```text
heightfield-preview mode:
  Welded regular mesh from height samples.
  Useful for inspection/debugging.
  Not runtime-faithful.

runtime-adaptive mode:
  Reproduces adaptive primitive list and flattened polygons.
  Intended to match original game terrain topology.
```

## Mission prefixes

Observed mission prefixes:

```text
Axx  training / tutorial
Mxx  standalone arena or melee maps
Sxx  scenario missions
Txx  main story / trip progression missions
```

This interpretation is supported by objective text and naming patterns:

```text
Mxx  arena/combat challenge style blurbs
Sxx  self-contained scenarios
Txx  narrative progression involving Taurus, Skeeter, Fort Davis, Malocchio, etc.
```

## Current known limitations

The following areas are not yet fully resolved:

```text
RDEF road/route structure
ODEF object placement structure
LDEF lighting structure
ADEF actor/AI/auxiliary structure
Exact polygon callback differences beyond the work-record level
Exact hardware plugin behavior after terrain polygons are submitted
Exact material/texture binding for terrain surfaces
```

The immediate next practical implementation target is the adaptive terrain exporter. Road and object reconstruction should follow once `RDEF`, `ODEF`, and `LDEF` are decoded to the same level of confidence.

## Useful trace / rename scripts generated during this pass

Not exhaustive, but the key terrain-related scripts include:

```text
cgpt_i76exe_export_bwd2_descriptor_tables_v2.java
cgpt_i76exe_apply_runtime_level_loader_names_v1_safe.java
cgpt_i76exe_export_runtime_section_handler_trace_v3.java
cgpt_i76exe_scan_bwd2_descriptor_tables_v4.java

cgpt_i76exe_export_terrain_edge_runtime_trace_v8.java
cgpt_i76exe_export_terrain_tessellator_trace_v9.java
cgpt_i76exe_apply_terrain_runtime_names_v9_safe.java
cgpt_i76exe_apply_terrain_runtime_structs_v10_safe.java
cgpt_i76exe_export_terrain_primitive_render_trace_v10.java
cgpt_i76exe_apply_terrain_runtime_structs_v11_safe.java
cgpt_i76exe_export_terrain_callbacks_trace_v11.java
cgpt_i76exe_apply_terrain_runtime_structs_v12_safe.java

cgpt_i76exe_export_miss8_miss16_render_mode_trace_v12.java
cgpt_i76exe_export_render_mode_flag_writes_v13.java
cgpt_i76exe_apply_render_mode_names_v13_safe.java
```

