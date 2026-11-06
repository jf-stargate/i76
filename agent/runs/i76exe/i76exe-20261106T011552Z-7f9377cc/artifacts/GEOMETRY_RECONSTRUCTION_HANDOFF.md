# C++ geometry reconstruction handoff

## Implementation disposition

A renderer-neutral, bounded adaptive SOURCE mesh builder can now be implemented faithfully for the verified M06 inputs once original root/visibility-plane inputs are supplied. Shared topology is no longer the reason to retain independently triangulated diagnostic quads. The independent source builder reproduces indices and all arena bytes across nine valid cameras, including unequal-depth and page-seam cases. This is research evidence pending human review, not canonical promotion or authorization to alter maintained C++ in this PR.

Keep the temporary dense/chunked builder as the general scene fallback until camera-to-root hull calculation, walker added-center/facing/shading behavior and numeric edge cases have their own oracle coverage. Do not label a new full camera-to-visible-emission adaptive path retail-faithful based only on these source-graph results. Successful alternate texture/material emission and rendering are separate blockers; they need not block an explicitly bounded source-geometry feature.

## Proposed independently authored types

The following are safer reconstruction representations, NOT recovered retail C++ layouts or symbols:

```cpp
using VertexId = uint32_t;
using EdgeId = uint32_t;
struct SourceVertex {
  int32_t lattice_x, lattice_z;
  uint16_t packed_sample;
  Float3 source_xyz;       // float(lattice_x), float(low12), float(lattice_z)
  Float2 source_aux;       // observed producer: x*float32(0.125), z*float32(0.125)
};
struct SharedEdge {
  VertexId a, b;
  std::optional<std::array<EdgeId, 2>> children;
};
struct AdaptiveLeaf {
  int32_t x, z, size;
  std::array<EdgeId, 4> edges;  // retail +0C,+10,+14,+18 order
};
struct PolygonLoop { uint32_t leaf; std::vector<VertexId> boundary; };
struct AdaptiveInputs {
  int32_t root_x, root_z; uint32_t root_exponent;
  float camera_lattice_x, camera_lattice_z;
  float distance_threshold, height_threshold;
  std::vector<VerticalPlane> original_visible_planes;
};
struct EmittedGeometry {
  std::vector<SourceVertex> source;
  std::vector<Float3> view_vertices;  // keep source intact
  std::vector<PolygonLoop> loops;
  std::vector<Triangle> selected_triangles;
};
```

Float3/Float2/VerticalPlane/Triangle above stand for project-owned typed values. Explicitly define plane nx/nz as float and offset as double, and preserve operation/store points. IDs replace retail pointers; optional children replace a zero child-pointer sentinel. Vectors, optionals, uint32 IDs, separate source/view buffers, packed-sample retention, provenance tags, error returns and storage bounds are reconstruction decisions. Original records use int16 endpoints and interleaved 12/28-byte allocations; their observed fields are documented separately in SHARED_EDGE_TOPOLOGY.md. Original XYZ is overwritten in place by 004937C0; preserving both spaces is an intentional safety improvement.

No coordinate-keyed vertex cache is required for parity: source IDs are created in original root/split order. Avoid independently splitting neighboring quads or deduplicating vertices after assembly; either changes midpoint chronology and may hide incompatible boundaries. Edges need stable IDs while their child arrays mutate. Reserve/check capacity explicitly. Do not carry source TER classes into renderer tokens or infer a singular material per mixed-class polygon.

## Exact next geometry PR scope

1. Add a frame-owned shared-edge/source-leaf builder behind an explicit diagnostic adaptive mode. Its inputs should be an authenticated sample provider plus bounded root/LOD/visible-plane inputs; general camera-to-hull support should remain clearly unverified until separately closed. Preserve float32 source and threshold bits and the original exponent mask. Add the recovered size/height/boundary-surface rules, not an invented geometric-error metric.
2. Implement four root vertices, original edge seed order, idempotent edge split, cross-edge center creation and ordered four-child recursion. Use the independent script as a specification/checking aid; do not embed proprietary fixture samples. Generate small independently authored fixtures for maintained tests and keep licensed M06 replay optional/private.
3. Export boundary loops with exact +14/+10/+18/+0C flattening and explicit winding. If converting into renderer-oriented work order, reverse each loop exactly once. Keep fan triangulation separate from source topology; geometric fan membership is now demonstrated, while original visibility/shade-dependent choice still needs a dedicated parity stage.
4. Require index/graph/loop equivalence, manifold boundary-overlap checks, unequal-depth compatibility, repeated split no-op, stable camera threshold behavior and source-vs-clipped attribute separation. Count source leaves, loop candidates, emitted attempts and accepted outputs independently. A public midpoint/flatten checker is provided.

## Outstanding fidelity work

Original hull ordering and ground-intersection cases; invalid-to-valid repeated frames/counter lifecycle; unmapped/default and out-of-domain samples; page-crossing raw boundary scan; exact hardware x87 parity; overflow/allocation failure; post-transform added-center; independent full facing/shade/fallback selection; successful alternate descriptor initialization and high-color lighting. Plane/sample layout assumptions should be reconciled with the independent coordinate/page-continuity run before widening supported domains. No maintained C++ or renderer changes accompany this handoff.
