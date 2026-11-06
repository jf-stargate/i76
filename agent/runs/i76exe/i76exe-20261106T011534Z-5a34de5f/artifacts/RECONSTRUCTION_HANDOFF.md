# Proposed next reconstruction PR

Implement only a checked terrain coordinate resolver and neighboring-page sampler, with corpus-derived tests from this run. Keep lifecycle/resource loading in the existing owned terrain scene. No maintained C++ implementation is included here. F1/F2/F3 establish addressing; F4/F5 separate exact numerical behavior from an approximate bilinear implementation.

## Proposed API and exact semantics

Use int32 for global lattice inputs, uint16 for packed words/height12, uint8 for class/page ordinal, and at least uint32/size_t for checked offsets. Perform additions/range checks in int64 before indexing, avoiding C++ signed-overflow and negative-shift assumptions. Suggested return states: `ok`, `default_page`, `invalid_coordinate`, `invalid_scene`. Both `ok` and `default_page` contain a value; failures leave caller output unchanged.

| Proposed operation | Contract |
|---|---|
| `terrain_sample(int32 global_x, int32 global_z)` | Checked domain **[-3072,13311] in each axis**, the rectangular 128×128 runtime grid. Compute page/local by nonnegative translated coordinates, or explicit floor division/modulo. Resolve serialized cell if runtime page is in [24,103]²; `0xff` or outside the embedded region yields an explicit zero default-page value. Return raw word, low12, class, unknown bit12, page/default provenance and source indices. |
| `terrain_position(int32 global_x, int32 global_z)` | Same checked resolution; return conceptual world **double** XYZ `(5*x, double(height12)*double(0.1f), 5*z)`. These products are exactly representable as double over this domain. If storing float mesh vertices, document the subsequent binary32 rounding. Do not claim the original has an intermediate world-position buffer; its source vertices remain in lattice/low12 units before the view transform. |
| `terrain_height(double world_x, double world_z)` | Require finite ordinary inputs within an explicit supported query envelope, proposed [-5,51205] per axis. Outside that envelope return `invalid_coordinate`; this is a checked API policy, not a claim about original extremes. Within it apply original bias admission and the independent four-corner resolver. Return value zero with a separate `rejected_by_original_admission` status on original rejection. Admitted corners may use default pages. For numerical parity follow F4's staged rounding and convert final ST0-equivalent value explicitly to double. |
| `terrain_surface_class(int32 global_x, int32 global_z)` | Same checked lattice resolver; extract raw class bits with no world rounding/interpolation. Optionally expose a separately named world-material query with original bias rounding, class5 on admission rejection and class0 for valid default backing. Do not silently give the lattice API the original world-query rounding policy. |

This rectangular safe domain deliberately rejects original flattened-row spill and negative-slot accesses. It is a **proposed safety boundary**: not emulation of original unchecked int32 behavior. Tests in this run explicitly identify those original quirks so the distinction stays visible. Validate scene page counts and array lengths before any active-page read; invalid active IDs return `invalid_scene`, never silently default to page0. A default page is a distinct zero source, not TER ordinal zero. The current serialized-ordinal sampling function may retain its `0xff` failure behavior; the new runtime resolver must expose the different original default semantics explicitly.

## Geometry and seam rules

A page's local sample 127 is five world units before its neighbor's local sample0. A cell beginning at local127 needs the next page for its +X/+Z corners. Resolve all four corners by global lattice keys; never clamp them to the current page or duplicate an artificial 129th sample. When two cells reference one TER ordinal, reuse sample data while deriving positions from their **different serialized cells**, not from page ordinal. Shared global vertex identity prevents cracks caused by separate rounding/placement of page boundaries. It does not promise flat slopes or zero height differences across a cell.

Keep the original packed word and unresolved bit12 as source metadata. Do not apply bit12 to Y, spacing or discontinuity without new evidence. Do not use surface class as a texture ID. Do not substitute query normals for rendering lighting or infer UVs/materials from this run.

## Numerical acceptance options

The next PR should state whether it implements exact sampled geometry only or also the original height-query arithmetic. Geometry at integer lattice points needs only exact addressing, masks and scales. A conventional double bilinear query with nearest-rounded float stores is an **approximation**, and must not claim exact retail parity. Exact query tests should consume the published native outputs and their deliberate float32/downward storage stages; avoid relying on default compiler excess precision, FMA contraction or a process-wide changed rounding mode. The rational model is a test oracle, not a recommended production implementation.

Required tests: row/column orientation, lattice/world scale, bytes/strides, four independent seam corners including diagonal and active/default boundaries, repeated source pages at distinct origins, valid default vs invalid scene, safe negative coordinates, source and runtime-grid edges, original admission/class differences, and the published CPU-vs-emulator mismatch example. Validate both M06 and CD M02 derived cases without committing proprietary assets. Use a tiny independently authored synthetic page pattern for maintained unit fixtures, keeping reference original outputs as bounded evidence.

Separate future work: complete native normal parity, rendering-normal/material/UV provenance, original adaptive shared-edge topology and rasterization, bit12 purpose and more missions. No changes to PR #139's scene binding are required by this research.
