# Interstate '76 Runtime Level, Terrain, Object, and Reconstruction Format Notes

This document summarizes the current reverse-engineering baseline for Interstate '76 runtime level loading, terrain reconstruction, mission object placement, static object geometry, materials, and current exporter behavior.

The scope is the shipped runtime resources used by the retail game, not the original editor workspace format. The current practical goal is to reconstruct shipped missions in Blender or a modern engine using the runtime mission streams, sidecar terrain pages, ZFS/PIX/PAK resources, and binary-backed dispatch behavior.

## Current high-level conclusion

A playable mission is assembled from a BWD2 mission stream, a `.TER` terrain sidecar, and many separately loaded object, vehicle, scene, texture, palette, road, sky, script, and support resources.

```text
Runtime component     Current interpretation
------------------    ------------------------------------------------------------
.MSN / .SPC / .LVL    BWD2 mission stream
.TER                  terrain page sidecar referenced by TDEF/ZONE
.ACT                  palette resource, selected by WDEF/WRLD / mission context
.LUM                  luma / lighting lookup support table
.TBL                  lookup / translucency / remap support table
.PCF                  high-color / preload / render-side support sidecar
.HZD                  hazard/map metadata support resource
.NPT                  objective / notepad / mission text sidecar
.RTM                  route/road support resource for some missions
.VCF                  vehicle/object config used by selected ODEF classes
.VDF / VTF / WDF      vehicle geometry, texture, and mount resources
.SDF                  scene-object descriptor used by static ODEF classes and LDEF
.GEO                  geometry records referenced by SDF/SOBJ and vehicle paths
.TMT / MAP / M16      material and texture resources
.VQM / CBK            block-compressed indexed texture/frame resources
```

The current reconstruction baseline is:

```text
Subsystem             Current reconstruction baseline
------------------    ------------------------------------------------------------
Terrain               dense welded heightfield from TDEF/ZMAP/ZONE + TER
Terrain UVs           world-repeat, repeat 1.0; visually validated baseline
Terrain materials     diagnostic TER high-bit classes plus candidate texture binding
RSEG                  road/corridor overlays using terrain-sampled height
RSEG road mesh        diagnostic overlay only; road material mapping still unresolved
ODEF                  placement axes from binary-confirmed basis + position
ODEF resources        class-specific .vcf or .sdf according to retail binary
LDEF                  label.sdf static scene-object path
SDF                   SDFC / SGEO / SOBJ / SCHK / LOBJ child descriptor path
Static GEO            SDF child parts resolved to embedded GEO and instanced
Static materials      VQM-first generally works; family overrides required
Sky                   mission sky/environment MAP exported to validation hemisphere
Adaptive terrain      diagnostic only until shared edge graph is reproduced
```

## Runtime mission directories: `miss8` and `miss16`

The installed game contains two runtime mission directories:

```text
miss8/
miss16/
```

Both contain shipped mission streams and terrain sidecars. In the observed retail install:

```text
Directory    Mission streams             Terrain sidecars             Extra sidecars
---------    -------------------------   -------------------------    -----------------------
miss8        A/M/S/T mission .MSN files   matching .TER files          some .PCF resources
miss16       A/M/S/T mission .MSN files   matching .TER files          *_16.PCF resources
```

The `.TER` files observed between `miss8` and `miss16` are byte-identical for matching missions. Terrain height geometry is therefore shared between low-color and high-color mission sets.

Most `.MSN` files differ between `miss8` and `miss16`. The differences are concentrated in resource-name fields, especially `WDEF/WRLD`, where the two mission sets may select different palettes, sky/cloud textures, surface textures, HZD resources, and high-color support resources.

For M06, the currently observed mission-level visual references include:

```text
Mission tree    Palette     Luma       Table      Terrain texture candidate    Sky/env candidate
------------    --------    -------    -------    --------------------------   -----------------
miss8/M06       t01.act     t01.lum    t01.tbl    tt181sd_.map                 nk_1cld2.map
miss16/M06      t09_16.act  t01.lum    t01.tbl    tp051dr6.map                 nk_6clde.map
```

Important distinction:

```text
miss8 terrain MAP       often direct indexed MAP payload, e.g. 128 x 128
miss16 terrain MAP      often same-stem MAP -> M16/VQM image resource
```

## High-color resource-mode predicate

The game chooses between `miss8` and `miss16` through the high-color/resource-mode predicate at `00495060`.

```c
bool is_miss16_high_color_resource_mode(void) {
    return g_runtime_high_color_resource_mode == 1;
}
```

Relevant symbols:

```text
Address     Symbol
--------    ------------------------------------------------
00495060    is_miss16_high_color_resource_mode
005dd2a8    g_runtime_high_color_resource_mode
005a4618    g_terrain_cached_high_color_resource_mode
005dd340    g_selected_raster_plugin_dll_name
```

The function previously suspected to be heap-related is not a heap getter. It is the high-color / `miss16` selection predicate. When false, mission paths are formatted through `miss8\%s`; when true, they are formatted through `miss16\%s`.

## Hardware/software terrain render split

The `miss8` versus `miss16` resource choice is separate from the terrain polygon callback choice.

```text
Global                                      Role
----------------------------------------    -----------------------------------------------
005dd2a8 g_runtime_high_color_resource_mode  high-color resource selection / miss16 usage
00654b8b g_player_options_terrain_alt_polygon_path  terrain polygon callback selection
```

Observed branch:

```c
if (g_player_options_terrain_alt_polygon_path == 0) {
    walk_adaptive_terrain_primitives(..., i76_runtime_emit_terrain_polygon_software_path);
} else {
    walk_adaptive_terrain_primitives(..., i76_runtime_emit_terrain_polygon_alt_path);
}
```

Relevant functions:

```text
Address     Symbol
--------    ------------------------------------------------
004922f0    i76_runtime_emit_terrain_polygon_software_path
004924b0    i76_runtime_emit_terrain_polygon_alt_path
```

Hardware/high-color mode changes resource selection, optional per-vertex terrain lighting, polygon work-record contents, and downstream render submission. It does not appear to use a different terrain height or tessellation source.

Known renderer/backend options include:

```text
Option      Renderer/backend implication
-------     ------------------------------------------------
-gdi        software/GDI path
-glide      ZGLIDE.DLL
-redline    ZREDLINE.DLL
-d3d        ZDX5DRAW.DLL
-powervr    ZPOWERVR.DLL
-hal        hardware/HAL-related flag
```

## BWD2 mission stream

Runtime missions are BWD2 chunk streams.

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
Address     Symbol
--------    ------------------------------------------------
004b42b0    load_and_parse_selected_mission_resource
004b41e0    parse_bwd2_resource_with_descriptor_table
004b3db0    parse_tagged_chunk_descriptor_table
```

High-level sections:

```text
Section     Role
-------     ------------------------------------------------------------
WDEF        world/resource metadata
TDEF        terrain definition
RDEF        route/road/corridor definitions
ODEF        object placement definitions
LDEF        static scene-object / world-entity definitions
ADEF        FSM / mission scripting definitions
EXIT        validation/finalization
```

## Descriptor tables

Known descriptor table anchors:

```text
Table / tag                          Address / handler      Current interpretation
----------------------------------   ------------------     ---------------------------------------------
WDEF table                           00500ca0               world/resource definition table
  WREV                               004b4610               validate mission revision chunks
  WRLD                               004b8a10               load world resource config from WRLD
  EXIT                               004b4290               handle BWD2 EXIT

TDEF table                           004fae18               terrain definition table
  TREV                               004b4610               validate mission revision chunks
  ZMAP                               00493960               parse ZMAP chunk
  ZONE                               004939d0               load TER sidecar pages
  EXIT                               00493bd0               TDEF terrain exit helper

RDEF table                           00500cd0               route/road/corridor table
  RREV                               004b4610               validate mission revision chunks
  RSEG                               004b8780               load RSEG route/corridor records
  ISEG                               004b8960               ISEG/TSEG table context helper
  TSEG                               004b8960               ISEG/TSEG table context helper
  EXIT                               004b4290               handle BWD2 EXIT

ODEF table                           00500ae8               object placement table
  OREV                               004b4610               validate mission revision chunks
  OBJ                                004b7ac0               load ODEF object placement record
  EXIT                               004b4290               handle BWD2 EXIT

SDF / ODEF child table               00500b18               scene-object child descriptor table
  SDFC                               004b7f70               parse SDFC scene-object descriptor header
  SOBJ                               004b8470               load SOBJ scene-object geometry id
  SGEO                               004b7ff0               parse SGEO scene-object geometry part
  SCHK                               004b8050               add SDF child chunk to parent object
  LOBJ                               004b8ed0               create LOBJ light object
  EXIT                               004b4290               handle BWD2 EXIT

ADEF table                           00500d20               mission FSM table
  AREV                               004b4610               validate mission revision chunks
  FSM                                00409740               initialize FSM runtime heap and tables
  EXIT                               004b4290               handle BWD2 EXIT

Extended/X resource table            00500d50               extended world record table
  XDFC                               004b8e00               parse XDFC world record
  XGEO                               004b8e20               null XGEO world record handler
  EXIT                               004b4290               handle BWD2 EXIT

LDEF table                           00500d80               static scene-object table
  LREV                               004b4610               validate mission revision chunks
  OBJ                                004b8f70               load LDEF static scene-object record
  EXIT                               004b4290               handle BWD2 EXIT
```

## `WDEF/WRLD`

`WDEF/WRLD` carries fixed-width resource filenames and world metadata.

Observed resource fields include:

```text
WRLD field family       Examples / role
-------------------     ------------------------------------------------------------
palette / ACT           t01.act, t09_16.act
luma / LUM              t01.lum
translucency / TBL      t01.tbl
objective text / NPT    m06.npt
sky/cloud texture       nk_1cld2.map, nk_6clde.map
scrounge/SDF support    ngscrng1.sdf
surface texture         tt181sd_.map, tp051dr6.map
level/minimap texture   zmap6m00.map
hazard/map data         HZD references vary by mission/resource mode
terrain sidecar         m06.ter
```

The WRLD handler calls palette/luma/translucency loaders, initializes scrounge state, installs terrain texture defaults, and prepares sky/horizon texture state. This is the correct target for future tracing of terrain/road material semantics.

## `TDEF/ZMAP/ZONE`

Terrain loading is well understood.

```text
Address     Symbol
--------    --------------------------------------
00493910    parse_tdef_terrain_chunks
00493960    parse_zmap_chunk
004939d0    load_ter_sidecar_pages
00493bd0    terrain_tdef_exit_helper
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

`.TER` sidecar layout:

```text
Field / concept        Value
-------------------    -----------------------------------------
page count             active_patch_count
page size              0x8000 bytes
page shape             128 * 128 uint16 little-endian samples
```

Each terrain sample word:

```text
Bits        Meaning
-------     -----------------------------------------
0..11       height low12
12          surface/special flag
13..15      surface class
```

## Runtime terrain page indirection

The game does not sample terrain directly from the `80 x 80` ZMAP.

It first builds a `128 x 128` runtime page-pointer grid:

```text
Address     Symbol
--------    ------------------------------------------------
00493080    build_runtime_terrain_page_pointer_grid
00644380    g_runtime_terrain_page_ptr_grid_128x128
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
uint16_t lookup_terrain_height_low12(int x, int z) {
    int table_index = ((z + 0xc00) & 0xffffff80) + ((x + 0xc00) >> 7);
    int local_index = ((z + 0xc00) & 0x7f) * 0x80 + ((x + 0xc00) & 0x7f);
    return *(uint16_t *)(page_ptr_grid[table_index] + local_index * 2) & 0x0fff;
}
```

Related functions:

```text
Address     Symbol
--------    ------------------------------------------------
00493160    lookup_terrain_height_low12
004927b0    lookup_terrain_surface_class
004931c0    compute_terrain_normal_from_height_samples
```

## Dense terrain export baseline

For Blender inspection, the stable baseline is a dense welded heightfield mesh. It is not runtime-faithful adaptive topology, but it is the most useful visual baseline.

```text
Behavior                         Current baseline
-----------------------------    ------------------------------------------------------------
vertex grid                      one welded vertex per global terrain sample coordinate
seams                            shared seam vertices across adjacent active pages
origin                           centered from active ZMAP bounds
Blender coordinate order         OBJ v = x, z, height
height sampling                  runtime page-grid model
texture UVs                      world-repeat, repeat 1.0
```

For M06, the active ZMAP block is:

```text
Metric         Value
----------     ----------------
bounds         x=2..5, z=74..77
center cell    x=4.0, z=76.0
origin         world x=2560, world z=48640
```

RSEG, ODEF, static objects, and resource markers must subtract the same origin as the terrain.

The visually validated terrain UV baseline is:

```text
--terrain-uv-mode world-repeat
--terrain-uv-repeat 1.0
```

`whole-terrain` UV mapping stretches the 128 x 128 terrain texture over the entire dense export and is not the current visual baseline.

## Terrain surface classes and diagnostic materials

Runtime terrain surface class is:

```text
surface_class = terrain_word >> 13
height        = terrain_word & 0x0fff
```

M06 currently observes these classes:

```text
Surface class    High bits    Runtime forced split    Current evidence-backed role
-------------    ---------    --------------------    -----------------------------------------
0                0x0000       no                      minor/default/boundary candidate
1                0x2000       no                      dominant base ground candidate
3                0x6000       yes                     road surface candidate
5                0xa000       no                      secondary ground/pad candidate
7                0xe000       yes                     roadbed/shoulder/adjacent candidate
```

Natural diagnostic material colors currently used in the exporter:

```text
Surface class    Material name         Kd RGB                Approximate visual color
-------------    ------------------    ------------------    ---------------------------
0                terrain_surface_0     0.48 0.42 0.30       medium tan / brown
1                terrain_surface_1     0.36 0.31 0.22       darker brown / base ground
3                terrain_surface_3     0.30 0.30 0.30       neutral gray / road
5                terrain_surface_5     0.22 0.28 0.18       dark olive / green-brown
7                terrain_surface_7     0.70 0.66 0.50       light tan / beige
```

M06 RSEG overlap strongly supports the class 3 road interpretation:

```text
Surface class    RSEG centerline overlap    RSEG left-edge overlap    RSEG right-edge overlap
-------------    -----------------------    ----------------------    -----------------------
3                about 95.66%               about 95.59%             about 95.79%
7                about 4.21%                about 4.14%              about 3.54%
```

Current interpretation:

```text
Class    Current role hypothesis
-----    -----------------------------------------------------------------------
3        primary road/corridor surface
7        roadbed, shoulder, road-edge transition, or adjacent special road area
1        dominant base terrain
5        distinct non-forced-split ground / pad / local surface bucket
0        minor default / boundary / filler bucket
```

## Terrain texture candidates

The exporter now distinguishes terrain texture candidates from static-object textures.

For `miss8/M06`:

```text
Resource       Observed structure                         Current role
----------     ----------------------------------------    ------------------------------
TT181SD_.MAP   uint32 width=128, uint32 height=128,        terrain surface texture candidate
               then 128*128 indexed pixels

NK_1CLD2.MAP   uint32 width=128, uint32 height=128,        sky / environment texture
               then 128*128 indexed pixels
```

For `miss16/M06`:

```text
Resource       Observed structure                         Current role
----------     ----------------------------------------    ------------------------------
TP051DR6.MAP   same-stem MAP -> M16/VQM image assets       terrain surface texture candidate
NK_6CLDE.MAP   same-stem MAP -> M16/VQM image assets       sky / environment texture
```

Current terrain binding behavior:

```text
Component       Current baseline
------------    ------------------------------------------------------------
texture decode  mission ACT where available
terrain MTL     diagnostic surface materials plus optional map_Kd candidate
UVs             world-repeat repeat 1.0
```

The terrain texture association is visually usable for M06, but the exact runtime mapping from terrain classes to road/ground textures is not fully solved.

## Adaptive terrain mesh pipeline

The runtime renderer builds adaptive terrain primitives.

```text
Address     Symbol
--------    ------------------------------------------------------------
004929b0    compute_visible_terrain_bounds
00490a00    build_visible_adaptive_terrain_mesh
004911e0    subdivide_terrain_quad_for_render
00491810    alloc_terrain_primitive_node
004918b0    alloc_terrain_edge_record
004918f0    split_terrain_edge_insert_midpoint_vertex
00491a30    walk_adaptive_terrain_primitives_and_emit_polygons
00492270    flatten_edge_forward_emit_vertex_a_leaves
004922b0    flatten_edge_reverse_emit_vertex_b_leaves
004937c0    transform_generated_terrain_vertices
```

`004911e0` is the exact recursive subdivision predicate. Known structure:

```text
Step family
------------------------------------------------------------
entry / edge extent / reject test
half-scale + distance/error gate
center height-error test
quarter height-error tests
minimum-scale + raw surface-word scan setup
special-surface forced-split scan
split four edges, create center edges, recurse
leaf primitive-node emission
```

Hard split floor:

```c
half_scale = scale >> 1;
if (half_scale >= 0x20) {
    split;
}
```

Special terrain-word forced-split condition:

```c
word >= 0x4000 && (word & 0xe000) != 0xa000
```

Therefore, surface classes 2, 3, 4, 6, and 7 can force subdivision under this predicate, while class 5 (`0xa000`) is explicitly excluded.

Adaptive overlay caveat: a correct runtime-faithful adaptive exporter must reproduce the shared edge-record graph. Independent per-quad subdivision creates T-junctions and edge discontinuities.

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
    int16_t vertex_a;       // +0x00
    int16_t vertex_b;       // +0x02
    edge_t *child_edge_a;   // +0x04
    edge_t *child_edge_b;   // +0x08
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

Terrain globals:

```text
Address     Symbol
--------    ------------------------------------------------
005dd320    g_runtime_terrain_vertex_xyz_buffer
005dd2ec    g_runtime_terrain_vertex_projected_or_lighting_buffer
0059c560    g_runtime_terrain_primitive_list_head
0059c574    g_runtime_terrain_primitive_list_tail
0059c568    g_runtime_terrain_edge_record_count
0059c56c    g_runtime_terrain_primitive_node_count
006442ec    g_runtime_terrain_vertex_count
00654380    g_runtime_terrain_arena_cursor
```

## Edge flattening

Adaptive primitives reference four edge records. Before rendering, split edge trees are flattened into a polygon vertex-index loop.

Forward flatten:

```c
int *flatten_forward(int *out, edge_t *e) {
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
int *flatten_reverse(int *out, edge_t *e) {
    if (e->child_edge_a) {
        out = flatten_reverse(out, e->child_edge_b);
        out = flatten_reverse(out, e->child_edge_a);
        return out;
    }
    *out++ = e->vertex_b;
    return out;
}
```

`00491a30` uses this order:

```text
Primitive edge ref        Traversal
------------------        -----------------
edge_ref_2 (+0x14)        forward
edge_ref_1 (+0x10)        forward
edge_ref_3 (+0x18)        reverse
edge_ref_0 (+0x0c)        reverse
```

A terrain primitive may render as a polygon with more than three or four vertices.

## Terrain polygon work records and scan buckets

Polygon work header:

```c
struct i76_runtime_terrain_polygon_work_header {
    uint32_t vertex_count;       // +0x00
    uint32_t material_or_type;   // +0x04
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
    void *head;                  // +0x00
    void *tail;                  // +0x04
    int count;                   // +0x08
}; // 0x0c
```

Relevant functions:

```text
Address     Symbol
--------    ------------------------------------------------
00490590    alloc_prepare_terrain_polygon_work_record
0048fe10    bin_terrain_polygon_work_record
00490470    add_terrain_scan_bucket_span_entry
```

## Terrain lighting

In high-color / `miss16` mode, the terrain builder performs additional per-generated-vertex lighting.

```text
Address     Symbol
--------    ------------------------------------------------
00490fb0    compute_terrain_lighting_from_neighbor_heights
```

This samples the center and four neighboring terrain heights, computes slope terms, applies a light vector, clamps against constants, and returns a shade/intensity value. The result is stored in the companion terrain buffer:

```text
005dd2ec g_runtime_terrain_vertex_projected_or_lighting_buffer
```

In high-color mode, lighting data is written into the companion record’s `+8` field.

## `RDEF/RSEG`: route/road/corridor records

`RDEF/RSEG` is a route/road/corridor-style geometry/control table.

Serialized layout:

```c
struct i76_rseg_serialized {
    uint32_t kind;
    uint32_t count;
    struct i76_rseg_point points[count];
};

struct i76_rseg_point {
    float left_x;       // +0x00
    float left_z;       // +0x04
    float aux_z_or_mid; // +0x08, often tracks z or center/mid value
    float right_x;      // +0x0c
    float unknown_10;   // +0x10, not reliable vertical height
    float right_z;      // +0x14
}; // 0x18
```

The `0x18` records look like paired left/right edge samples for a road/corridor, not single points. Width statistics are road-like, commonly around 5–10 world units.

Important correction:

```text
point +0x10 is not reliable vertical height
```

Some endpoints contain large values in this field. For visualization, RSEG overlays should sample terrain height and optionally add a small height offset.

Runtime loader:

```text
Address     Symbol
--------    ------------------------------------------------
004b8780    load_rseg_route_corridor_records
```

The runtime chunks large serialized RSEG records into linked runtime nodes. Each runtime node allocation is:

```text
size = 0x2c + point_count * 0x18
point_count <= 0x18
```

RSEG globals:

```text
Address     Symbol
--------    -----------------------------------------
005db988    g_runtime_rseg_node_list_head
005db98c    g_runtime_rseg_node_count
```

Kind `3072` appears as a rare count-zero record and is best treated as a sentinel/control entry until proven otherwise.

## RSEG road mesh status

The current exporter can generate an experimental road/corridor surface mesh from RSEG left/right edge samples. This is useful for validating alignment, but it is not yet a faithful runtime road renderer.

Current status:

```text
Aspect                  Current status
--------------------    ------------------------------------------------------------
Placement               appears correct; RSEG aligns with terrain road surface
Height                  sampled from terrain, not serialized +0x10
Texture binding         experimental
UV mapping              not solved
Multiple road types     not yet decoded
```

Current road material issue:

```text
Observation
----------------------------------------------------------------------------------
Road overlay lands in the correct place, but material mapping is rotated/stretched
or otherwise inconsistent with road junction/static road meshes. Each level appears
to support multiple road types, so road material assignment likely requires deeper
tracing of game/editor RSEG or road-material handling.
```

Known/likely road and junction texture families in M06 static objects:

```text
Family pattern    Current interpretation
--------------    ------------------------------------------------------------
I2DNG*            road/intersection/junction candidate family
I2DNT*            road/intersection/junction candidate family
I2DNX*            road/intersection/junction candidate family
```

Do not treat the RSEG road overlay material mapping as solved. Future work should trace road material selection in both the game binary and editor binary.

## `ODEF/OBJ`: object placement records

`ODEF/OBJ` payloads are 100-byte placement/entity records.

```c
struct i76_odef_obj_record {
    char label_raw[8];       // +0x00, high bits may carry ID flags
    float basis_3x3[9];      // +0x08..+0x28
    float pos_x;             // +0x2c
    float pos_y;             // +0x30
    float pos_z;             // +0x34
    uint32_t tail_00;        // +0x38
    uint32_t tail_04;        // +0x3c
    uint32_t tail_08;        // +0x40
    uint32_t tail_0c;        // +0x44
    uint32_t tail_10;        // +0x48
    uint32_t tail_14;        // +0x4c
    uint32_t tail_18;        // +0x50
    uint32_t tail_1c;        // +0x54
    uint32_t tail_20;        // +0x58
    uint32_t class_id;       // +0x5c
    uint32_t tail_28;        // +0x60
}; // payload 0x64
```

The runtime normalizes the 8-byte label by masking high bits with `0x7f`. The high-bit pattern appears to carry an ID/flag field. A blank normalized label is not ordinary visible geometry.

Transform interpretation is confirmed by `004b8230`:

```text
Source record range      Runtime transform use
-------------------      -----------------------------------------------------
+0x08..+0x28             copied as dwords to destination +0x04..+0x24
+0x2c                    converted/stored as double at destination +0x28
+0x30                    converted/stored as double at destination +0x30
+0x34                    converted/stored as double at destination +0x38
```

For Blender debug output, ODEF axes are a scaffold only.

## Corrected ODEF class-specific resource policy

The major correction from the v42 binary trace is that `ODEF` resource resolution is class-specific. The handler at `004b7ac0` dispatches using `class_id` at payload `+0x5c`.

```text
ODEF class / condition                 Resource behavior
-----------------------------------    --------------------------------------------
class 0x01 + label "spawn"             special spawn table
class 0x01 + label "regen"             special regen table
class 0x01 ordinary                    label.vcf
class 0x08                             label.vcf
class 0x09                             label.vcf
class 0x02                             label.sdf
class 0x03                             label.sdf
class 0x04                             label.sdf
class 0x07                             label.sdf
class 0x0a                             label.sdf
class 0x0b                             label.sdf
class 0x0c                             label.sdf
class 0x50                             label.sdf
class 0x52                             label.sdf
class 0x53                             label.sdf
class 0x05,0x06,0x0d..0x4f,0x51        fallback/null-ish path, not ordinary geometry yet
class 0 or blank label                 invalid/special diagnostic row for now
```

Known case bodies:

```text
Address     Case body
--------    ----------------------------------------------------------------------
004b7b96    ODEF .vcf case; calls 004b8230; formats .vcf; calls VCF loader
004b7be9    ODEF .sdf case; calls 004b8230; formats .sdf; parses SDF child table
00450f90    spawn/regen table writer
```

This reconciles Open76-style `label.sdf` static object behavior with the retail binary. The earlier broad assumption that all dispatch-valid ODEF classes go to `.vcf` was wrong, and the opposite assumption that all ODEF goes to `.sdf` is also wrong.

## Spawn and regen records

`spawn` and `regen` are special ODEF class-1 markers, not ordinary resources.

```text
Symbol / table       Address / value
----------------     -------------------------------------------
handler              00450f90 register_spawn_or_regen_transform
spawn table base     0053fd88
spawn count global   00540d98
regen table base     0053ecb0
regen count global   00540d9c
entry capacity       0x40
entry size           0x40
```

Copied transform payload:

```text
Source ODEF record range    Destination entry range
------------------------    --------------------------------
+0x08..+0x28                +0x00..+0x20 as dwords
+0x2c                       +0x28 as double
+0x30                       +0x30 as double
+0x34                       +0x38 as double
```

## `LDEF/OBJ`: static scene-object path

`LDEF/OBJ` is distinct from `ODEF/OBJ`. It is a static/world scene-entity construction path.

```text
Address     Symbol
--------    ------------------------------------------------
004b8f70    load_ldef_static_scene_object_record
```

This path formats `label.sdf`, parses the scene-object descriptor resource, allocates/registers a world object, applies transforms/bounds, and supports child part creation. `LDEF` object records are variable size and are not the same 100-byte placement structure as `ODEF/OBJ`.

## SDF child descriptor path

Both ODEF `.sdf` class bodies and LDEF `.sdf` objects use the SDF child descriptor table at `00500b18`.

```text
Handler     Tag       Current interpretation
--------    ----      ------------------------------------------------------------
004b7f70    SDFC      scene-object descriptor header
004b8470    SOBJ      scene-object geometry id; formats partName.geo
004b7ff0    SGEO      scene-object geometry part transform
004b8050    SCHK      add chunk to parent object
004b8ed0    LOBJ      light object child
```

Static-object pipeline:

```text
ODEF static class or LDEF object
  -> label.sdf
  -> SDF child descriptor table
  -> SOBJ / SGEO / SCHK / LOBJ
  -> partName.geo
  -> GEO constructor/render-record path
```

Open76’s SDF parser shape remains a useful sanity check:

```text
SDFC
SGEO
  uint32 numParts
  part records:
    8-byte part name
    right/up/forward vectors
    position
    8-byte parent name
    56 skipped/extra bytes
```

## Static object geometry reconstruction

The exporter now reconstructs static SDF-backed objects through embedded GEO assets.

Current validated chain:

```text
MSN BWD2
  -> ODEF/LDEF OBJ records
  -> class-specific SDF/VCF root policy
  -> SDF SGEO declared parts
  -> partName.geo
  -> embedded PIX/PAK/ZFS asset hit
  -> GEO parser
  -> hierarchy-composed static_objects.obj
```

For M06, current observed static labels include:

```text
Label       Current role family
--------    ------------------------------------------------
bchotel1    building / town object
aleanto1    lean-to / small structure
igd27_1     static road/intersection or ground object family
ahut1       hut / building
bdsaloo1    saloon / building
ild27_1     static road/intersection or ground object family
awatert1    water tower
itd27_1     static road/intersection or ground object family
ixd27_1     static road/intersection or ground object family
anbunkr1    bunker / structure
```

For M06, static reconstruction currently yields:

```text
Metric                         Approximate M06 value
----------------------------   ---------------------
static part instances          42
unique object labels           10
unique GEO names               22
mesh errors                    0 in current baseline
```

## Static object UV and material baseline

Static GEO UVs require V flip for visual correctness.

```text
--static-uv-v-flip
```

This is now the baseline/default behavior. Without V flip, textures appear inverted.

The current static material decode baseline is:

```text
Family / behavior               Baseline
----------------------------    ---------------------------------------------------------
ordinary static textures         prefer VQM over M16
I2D* road/intersection family    prefer direct MAP path where available
AT_* ground/pad family           prefer VQM
alpha/cutout textures            black-key alpha auto-detection
```

Current exporter options used for M06 material baseline:

```text
--static-texture-map-mode prefer-vqm
--static-texture-override "I2D*=prefer-direct-map"
--static-texture-override "AT_*=prefer-vqm"
--static-alpha-mode auto
```

Black-key alpha is required for textures such as:

```text
Texture       Example geometry / object                         Current alpha behavior
----------    -----------------------------------------------    ----------------------
AW_1BR_1      awatert1 / AW1_BAS1 / aw1_bas1.geo                black-key transparent
```

OBJ/MTL transparency caveat: the PNG alpha and `map_d` are emitted, but Blender may still require material blend mode to be set to Alpha Clip or Alpha Blend after import.

## Static texture asset findings

For M06 building/static textures, direct indexed `.MAP` payloads comparable to `TT181SD_.MAP` are generally not present. Static texture references such as `AH_1BDL1.MAP` resolve to same-stem embedded `M16` and `VQM` siblings.

Example:

```text
Texture reference    Direct MAP payload    M16 sibling    VQM sibling    Current baseline
-----------------    ------------------    -----------    -----------    ----------------
AH_1BDL1.MAP         missing               present        present        prefer VQM
RUSTMET1.MAP         missing               present        present        prefer VQM
BURNWOOD.MAP         missing               present        present        prefer VQM
I2DNG_17.MAP         family-specific        varies         varies         override/probe
AT_1PL_1.MAP         family-specific        varies         varies         prefer VQM
```

The 65,536-byte `T01.LUM` and `T01.TBL` remain important future tracing targets. They may participate in color/luma/remap behavior not yet fully reproduced.

## Sky object baseline

The sky/environment texture for `miss8/M06` is currently:

```text
NK_1CLD2.MAP -> NK_1CLD2.png
```

The skybox validation object was useful, but the current preferred shape is a hemisphere:

```text
--write-sky-object
--sky-shape hemisphere
```

Current sky output:

```text
sky_obj/m06.skyhemisphere.obj
sky_obj/m06.skyhemisphere.mtl
```

The hemisphere is a validation export, not yet a proven runtime sky renderer. It confirms the environment texture association and provides a useful Blender context.

## VCF / vehicle-object path

Selected ODEF classes use `.vcf`:

```text
Class / condition    Resource path
-----------------    ---------------------------
0x01 ordinary        label.vcf
0x08                 label.vcf
0x09                 label.vcf
```

Key functions:

```text
Address     Symbol
--------    ------------------------------------------------
004ad640    format_8char_resource_basename_with_suffix
004ad6f0    load_vehicle_config_for_world_object
004adb90    parse_vcfc_vehicle_config_root
004ad950    parse_vcfc_vdf_vtf_wdf_resource_refs
004b3650    parse_vdf_vehicle_definition_resource
004b7800    instantiate_vdf_vehicle_geometry_part_sets
```

`004ad6f0` is a real VCFC/VCF loader. It calls `004b41e0` with the VCFC descriptor table. There is no `.sdf` fallback inside the `.vcf` path. Optional `.vsf` state loading exists under a separate mode predicate and appears to be vehicle state/config, not a scene-object fallback.

## GEO construction and render-record path

Main GEO constructor:

```text
Address     Symbol
--------    ------------------------------------------------
00446c90    construct_geometry_from_geo_buffer
```

This validates `OEG.` magic (`0x2e47454f`), reads vertex/section/face counts, computes runtime allocation size, and constructs a runtime geometry object.

Lit render-record builder:

```text
Address     Symbol
--------    ------------------------------------------------
0045cbe0    build_lit_geo_render_records_from_sections
```

Higher-level render paths:

```text
Address     Symbol
--------    ------------------------------------------------
0045d100    render_or_prepare_world_object_geo_branch_a
0045d530    render_or_prepare_world_object_geo_branch_b
00471fd0    submit_lit_textured_polygon_to_renderer
00478430    compute_geo_vertex_lighting_from_normals
00493550    transform_world_object_bounds_or_geometry
00494e20    compose_world_object_transform
004925f0    link_or_update_world_object_bounds
```

PIX/PAK indexes contain many embedded `.geo`, `.tmt`, `.m16`, `.vqm`, and `.map` resources. `.vcf` and `.sdf` are not PIX-indexed in the observed resource set; they are loose/ZFS-extracted resources under `resources/`.

## Resource acquisition path

Resource acquisition below high-level suffix formatting is centered on `004b41e0` and `0046ffc0`.

```text
Function                                        Role
--------------------------------------------    ------------------------------------------------
004ad6f0 load_vehicle_config_for_world_object   VCF loader entry
004b41e0 parse_bwd2_resource_with_descriptor_table  BWD2 resource parser
0046ffc0 open_resource_file_into_memory         resource open path
00470b20 load_indexed_resource_record_payload   indexed resource payload
00470070 load_resource_stream_into_loaded_cache loaded resource cache path
004b3310 get_registered_resource_payload_size   registered resource size
004b3000 / 004b3030                             registered payload load
```

`0046ffc0` lowercases requested names, checks indexed PIX/PAK resources, checks registered/cache/ZFS/loose-file paths, and can retry in an alternate order depending on a global mode flag.

`00470660` loads PIX/PAK indexes. It scans `*.pix`, derives sibling `.pak`, parses rows with a `%s %d %d`-style format, lowercases resource keys, and sorts the resource index.

Important distinction: evidence from probes must separate real binary/container hits from hits inside generated reports, manifests, and tar files under scratch directories.

## ADEF / FSM scripting

`ADEF/FSM` is the mission behavior scripting system.

```text
Address     Symbol
--------    ------------------------------------------------
00409740    initialize_fsm_runtime_heap_and_tables
00410720    load_serialized_fsm_runtime_tables
004105a0    load_serialized_fsm_record_array_with_bitfields
004102d0    load_serialized_fsm_record_array_with_vec3_lists
00410490    load_serialized_fsm_linked_state_blocks
004125c0    finalize_loaded_fsm_runtime_tables
00410a10    initialize_or_match_fsm_command_name_table
00412400    register_fsm_instance_ids_from_mission
004122d0    validate_project_wav_smk_resource_list
00412500    relocate_fsm_command_table_internal_pointers
```

The command matcher contains mission scripting verbs/predicates such as:

```text
behave attack sit goto guard do set inc dec rand whoRammed whoShot
startTimer success fail playScene isWithin isDead setId follow teleport
destroy playMovie camera triggerGate setSkill reveal setAgg salvage
setSiren setArtillery stopCB
```

The string matcher order is not always equal to command ID order; durable documentation should use the extracted return-ID table, not simple sequence order.

## Current exporter baseline

The current exporter family has reached a practical visual baseline for M06:

```text
Area                        Current state
------------------------    ------------------------------------------------------------
Terrain geometry            dense welded heightfield, correct origin and heightfield
Terrain UVs                 world-repeat repeat 1.0, visually validated
Terrain class colors        diagnostic natural palette for surface classes
Terrain texture             direct MAP for miss8, M16/VQM path for miss16 candidates
Static SDF objects          instanced with hierarchy-composed transforms
Static UVs                  V-flip required and default
Static materials            VQM-first plus family overrides, generally correct
Static alpha                black-key alpha works for water-tower/cutout texture
Sky                         hemisphere validation object from mission sky MAP
RSEG road mesh              placement good, material/UV/type mapping unresolved
Combined scene              terrain + static + RSEG + sky validation exports
```

Important current command-line defaults / required options:

```text
Option family                   Baseline
----------------------------    -----------------------------------------------------------
terrain UVs                     --terrain-uv-mode world-repeat --terrain-uv-repeat 1.0
terrain material style          --terrain-material-style natural
palette                         --palette-file scratch_data/palettes/i76_vehicle_palette_selected.act
palette scale                   --palette-scale auto
static UVs                      V flip enabled by default
static texture map mode         prefer VQM
static I2D override             I2D*=prefer-direct-map
static AT override              AT_*=prefer-vqm
static alpha                    auto black-key
sky shape                       hemisphere
```

## Known unresolved items

```text
Topic                         Status / next action
--------------------------    ------------------------------------------------------------
RSEG road material mapping     unresolved; trace game/editor road material selection
RSEG road UV mapping           unresolved; current overlay texture can rotate/stretch
Multiple road types            likely supported; need binary/editor tracing
T01.LUM / T01.TBL              present; likely color/remap/luma support, not fully modeled
PCF semantics                  high-color/preload support, not fully decoded
Adaptive terrain topology      diagnostic only until shared edge graph reproduced
Terrain class -> texture rule  partially inferred, not fully proven
VCF vehicle instancing         separate future pass from static SDF objects
```

## Immediate next tracing targets

```text
Priority    Target                                  Reason
--------    ------------------------------------    ----------------------------------------------
1           game/editor RSEG road material path      each level appears to support multiple road types
2           WRLD terrain/surface texture handlers    connect terrain classes to actual texture resources
3           T01.LUM / T01.TBL users                  resolve luma/remap/color behavior
4           PCF loader / high-color sidecar users     explain miss16 preload/config resources
5           adaptive terrain shared-edge graph        runtime-faithful terrain topology
6           VCF/VDF object instancing                 vehicle/turret/object classes
```
