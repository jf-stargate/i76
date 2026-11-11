# Geometry/sampler handoff

This is a research recommendation, not a maintained C++ change. Findings F-SCAN/F-CROSS/F-CLASS/F-GEOMETRY; original identities and evidence hashes are in the manifest.

| Operation | Original behavior | Recommended bounded reconstruction behavior |
|---|---|---|
| Adaptive class scan, 004911E0 | One page pointer; four descending boundaries over side×side samples; side8/16/32 in normal flow | Preserve half-open footprint, iteration/short-circuit order, class predicate and normal phase; assert/validate alignment and backing ownership |
| Ordinary integer height, 00493160 | Resolve a coordinate independently; read low12 | Checked global lattice resolver, explicit active/default provenance and bounds |
| Bilinear world height, 00493550 | Resolve all four corners independently, including neighbors | Retain #141 coordinate and numerical contract; do not use adaptive scan's retained pointer |
| Rounded discrete class, 004927B0 | Resolve one rounded sample; high3 bits, separate rejection behavior | Keep separate from height interpolation and adaptive range scanning |
| Shared-edge geometry | Ordinary global sample identity at endpoints/midpoints; mutable shared parent edge; late flattening | Share vertices by global lattice position and edges by graph identity; use global neighbor resolution at the far geometric edge |
| Default pointer | Shared zero backing in measured initialized setup; no class-trigger refinement | Represent initialized default explicitly; apply all other LOD/height rules |
| Repeated page ID | Aliased borrowed pointer; same content with each slot's independent local origin | Preserve alias content/lookup semantics; do not merge geographic vertex identities based on backing pointer |
| Unsupported unaligned scan | Linear row/ordinal spill, possible out-of-object read | Reject before access, or provide an explicitly documented coordinate-resolved extension |

The fast single-page class scan is safe for the ordinary recovered aligned caller. A checked coordinate-resolved implementation can be equivalent **within that invariant**, as demonstrated by complete address/word sequence equality in six geometry runs. It is not general original parity for arbitrary rectangles: native synthetic counterexamples explicitly disagree. Never silently repair unaligned pointer semantics and describe the result as original behavior.

The class footprint's last local sample127 belongs to this region; the far geometry vertex128 belongs to its neighbor. Preserve this distinction. Do not clamp far geometry vertices, duplicate127, use a127 page period, or scan the inclusive side+1 vertex perimeter. Default class0 is distinct from world-admission rejection class5.

The existing dense/chunked fallback remains an implementation choice outside this PR. A future adaptive builder should gate the fast path on side/phase/backing bounds and retain a tested fallback or explicit error for unsupported states. This run resolves the normal default/repeat scan blocker in #140, while retaining its other hull/walker/emission limitations and #141's native-versus-emulator numerical qualifications.
