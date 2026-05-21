# Interstate '76 Runtime Terrain LOD Reference

This page captures the current understanding of the retail terrain LOD renderer. It complements the
general level-format page and focuses specifically on adaptive subdivision.

## Key functions

| Address  | Working name                              | Role                                                                |
|----------|-------------------------------------------|---------------------------------------------------------------------|
| 00493080 | build_runtime_terrain_page_grid_from_zmap | Build 128x128 runtime page-pointer grid using ZMAP +24/+24          |
| 00493160 | sample_runtime_terrain_height             | Height lookup through runtime page-grid and +0x0c00 sample bias     |
| 004927b0 | sample_runtime_terrain_surface_class      | Surface/material-class lookup                                       |
| 00490a00 | seed_adaptive_terrain_root_edges          | Create root vertices/edges for adaptive terrain pass                |
| 004911e0 | subdivide_or_emit_adaptive_terrain_quad   | Core adaptive split predicate and recursion                         |
| 00491810 | allocate_terrain_leaf_primitive_node      | Allocate/link primitive node for a leaf quad                        |
| 004918b0 | create_terrain_edge_record                | Create split edge record                                            |
| 004918f0 | split_or_lookup_terrain_edge_midpoint     | Split boundary edge and generate midpoint                           |
| 00491a30 | flatten_terrain_primitive_edges           | Flatten edge refs in asymmetric order and compute plane/normal data |
| 00494a90 | compute_plane_or_triangle_normal          | Called from terrain primitive flattening                            |

## Terrain data model

| Concept               | Value                                 |
|-----------------------|---------------------------------------|
| TER page              | 128 x 128 uint16 samples              |
| Runtime page grid     | 128 x 128 page-pointer slots          |
| ZMAP source grid      | 80 x 80 page index grid               |
| ZMAP placement offset | +24 x, +24 z                          |
| Height extraction     | word & 0x0fff                         |
| Surface extraction    | word >> 13                            |
| Sample bias           | +0x0c00 in height/surface lookup path |

## `004911e0` split structure

| Block                | Behavior                                                         |
|----------------------|------------------------------------------------------------------|
| entry / edge extent  | Compute quad bounds and initial reject/extent tests              |
| hard split floor     | Compute half_scale = scale >> 1; split if half_scale >= 0x20     |
| camera/error gate    | Compare projected/camera-space terms against terrain globals     |
| center test          | Sample center height and compare to interpolated estimate        |
| quarter tests        | Sample quarter points and compare height error                   |
| surface scan setup   | Prepare raw terrain-word scan for candidate region               |
| special-surface scan | Force split on selected packed-word conditions                   |
| split path           | Split boundary edges, create center edges, recurse four children |
| leaf path            | Allocate primitive node and link into primitive list             |

## Hard split floor

The current important correction is that large quads are not controlled only by camera distance or
height error. `004911e0` performs a hard subdivision rule:

```c
half_scale = scale >> 1;
if (half_scale >= 0x20) {{
    split();
}}
```

Any adaptive exporter that omits this rule will be far too sparse.

## Special-surface forced split

The raw packed-word scan forces subdivision when:

```c
word >= 0x4000 && (word & 0xe000) != 0xa000
```

This must be evaluated through the runtime page-grid addressing model, not by directly indexing the
TER file as one stitched dense array.

## Current exporter caveat

The current adaptive overlay is diagnostic. It includes the hard split floor and special-surface
predicate, but it does not yet reproduce the retail shared edge-record graph. Neighboring quads can
therefore disagree about split depth, producing T-junctions or visible discontinuities.

The dense welded terrain remains the visual baseline until shared-edge adaptive tessellation is
implemented.
