# Interstate '76 Runtime Terrain LOD / Adaptive Mesh Reference

This document focuses on the runtime adaptive terrain renderer. It complements the broader level-format notes.

## Current conclusion

The dense welded terrain exporter is the visual reconstruction baseline. The adaptive terrain exporter remains diagnostic because the runtime uses a shared edge-record graph and asymmetric edge flattening that has not yet been fully reproduced.

```text
Exporter target        Status
-------------------    ------------------------------------------------------------
dense heightfield      stable visual baseline
adaptive overlay       diagnostic only
faithful adaptive mesh requires shared edge records + runtime flattening order
```

## Core functions

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

## Terrain page and sample model

Adaptive terrain uses the same runtime page-grid model as dense terrain sampling.

```text
Source              Meaning
----------------    ------------------------------------------------------------
ZMAP                80 x 80 page-index grid
runtime grid        128 x 128 page-pointer grid
ZMAP offset         copied into runtime grid at +24,+24
height              terrain_word & 0x0fff
surface class       terrain_word >> 13
```

The runtime page-grid offset:

```text
0xc00 = 24 * 128
```

Known lookup helpers:

```text
Address     Symbol
--------    ------------------------------------------------
00493160    lookup_terrain_height_low12
004927b0    lookup_terrain_surface_class
004931c0    compute_terrain_normal_from_height_samples
```

## Subdivision predicate

`004911e0` is the exact recursive subdivision predicate.

Confirmed hard split floor:

```c
half_scale = scale >> 1;
if (half_scale >= 0x20) {
    split;
}
```

Special surface forced-split condition:

```c
word >= 0x4000 && (word & 0xe000) != 0xa000
```

This implies:

```text
Surface class    High bits    Forced by special-surface predicate?
-------------    ---------    -------------------------------------
0                0x0000       no
1                0x2000       no
2                0x4000       yes
3                0x6000       yes
4                0x8000       yes
5                0xa000       no
6                0xc000       yes
7                0xe000       yes
```

For M06, observed classes are 0, 1, 3, 5, and 7. Classes 3 and 7 are runtime forced-split special surfaces.

## Terrain surface class roles

Current M06 evidence:

```text
Surface class    Runtime split    Current role hypothesis
-------------    -------------    ------------------------------------------------
0                no               minor/default/boundary candidate
1                no               dominant base ground candidate
3                yes              primary road/corridor surface candidate
5                no               secondary ground/pad candidate
7                yes              roadbed/shoulder/adjacent road area candidate
```

RSEG overlap:

```text
Surface class    Centerline overlap        Current implication
-------------    ----------------------    ---------------------------------------
3                about 95.66%              strong road-surface candidate
7                about 4.21%               secondary road-adjacent candidate
```

## Runtime structures

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

Runtime globals:

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

Adaptive primitives reference four edge records. The runtime flattens edge trees into variable-length polygon loops.

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

Traversal order in `00491a30`:

```text
Primitive edge ref        Traversal
------------------        -----------------
edge_ref_2 (+0x14)        forward
edge_ref_1 (+0x10)        forward
edge_ref_3 (+0x18)        reverse
edge_ref_0 (+0x0c)        reverse
```

A faithful adaptive exporter must reproduce this shared edge graph and flattening order.

## Polygon work records

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

Vertex work record:

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

## Lighting

High-color mode computes additional terrain vertex lighting.

```text
Address     Symbol
--------    ------------------------------------------------
00490fb0    compute_terrain_lighting_from_neighbor_heights
```

This samples neighboring heights, computes slope terms, applies a light vector, clamps against constants, and stores lighting data in the companion terrain buffer at `005dd2ec`.

## Exporter guidance

Current exporter guidance:

```text
Task                         Recommendation
-------------------------    ------------------------------------------------------------
Blender visual baseline      use dense welded terrain
Terrain UVs                  world-repeat, repeat 1.0
Terrain materials            use diagnostic surface classes plus candidate texture
Adaptive overlay             keep diagnostic only
Runtime-faithful topology    wait for shared edge graph implementation
```

Do not treat independent adaptive subdivision as faithful. It will create T-junctions and mismatch runtime edge flattening.
