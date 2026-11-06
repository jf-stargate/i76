# Original shared edges and compatibility

## Executed layouts

The following widths/offsets are original runtime facts, verified against original writes and every byte in the reconstructed source arena. Pointer values belong only to the bounded emulator allocation.

| Record | Offset | Original role |
|---|---|---|
| edge, 0x0C bytes | +00,+02 | signed int16 source vertex_a, vertex_b |
| edge | +04,+08 | child A and child B pointers; both zero for terminal edge |
| leaf, 0x1C bytes | +00,+02 | signed int16 lattice X,Z of e0.vertex_a, rounded through original ftol(x+0.5) |
| leaf | +04 | int32 lattice side length, derived from e1.vertex_b.x minus stored X |
| leaf | +08 | next leaf; zero at allocation, then linked by subdivision caller |
| leaf | +0C,+10,+14,+18 | original arguments e0,e1,e2,e3 |

The old screen/bucket/range field names are too vague: the selected executed cases identify +00/+02 as X/Z and +04 as side length. The public full graph fixtures and exact arena comparison support this narrowing; no canonical document is edited here.

004918B0 allocates 12 bytes from 00654380, fills endpoints, clears children and increments 0059C568. Some equivalent allocations are inlined in 00490A00 and 004911E0; watching allocator entry alone would miss them. 00491810 allocates 28 bytes from the SAME cursor and increments 0059C56C. Neither record owns a separately allocated vertex buffer. Indices address the current frame source XYZ arena 005DD320; source count is 006442EC. The linked list head/tail are 0059C560/0059C574.

## In-place splitting and chronological identity

004918F0 tests edge+04 at 004918FD. If nonzero, it returns without creating a vertex or child edges. Otherwise it computes midpoint lattice X/Z as trunc(endpointSum+0.5)>>1, allocates exactly one source index, samples its low12 height with original 00493160, writes XYZ (last source height store 0049199D), and creates A=(old_a,midpoint), B=(midpoint,old_b). It stores children into the existing parent at 004919F9 and 00491A26. The original parent endpoint pair remains unchanged. Primary: 167 actual midpoint creations, 43 no-op repeated calls. Contrast: 89 creations, 16 no-op calls. Observers pair every original split entry/return and independently check both paths.

For subdivision arguments (a,b,c,d), split all four in that order. Create a cross-edge from midpoint(c) to midpoint(d), then split that cross-edge to obtain the center source vertex. Create L=(midpoint(a),center), R=(center,midpoint(b)). Child regions execute in exactly this order:

```
(a.A, cross.A, c.A, L)
(cross.A, b.A, c.B, R)
(cross.B, b.B, R, d.B)
(a.B, cross.B, L, d.A)  // tail iteration in retail code
```

These references, rather than coordinate hash guesses, cause sibling regions to share the same objects. Allocation order and tail iteration are part of deterministic source index identity. The independent graph constructs its own pointers/indices and matches the original interleaved arena byte-for-byte, not merely its counts.

## Unequal neighboring depths and T-junction prevention

There is no demonstrated rule forcing a coarser neighboring LEAF to subdivide to the finer leaf's depth. Refinement propagates through the shared EDGE tree: a coarser leaf continues pointing at a parent whose children have become deeper. Its later flattening incorporates those children. Existing leaves are never independently triangulated as four-corner quads.

Primary has 20 boundary loops longer than four vertices (maximum eight), 147 shared terminal boundary segments, 48 segments between unequal-size leaves. Example leaf 44000778 has boundary indices [8,26,63,59,90,58,98,55]; its size-8 edge segment 63→59 is shared with a size-2 neighbor in reverse, 59→63. Public edge_graph.json retains both complete primary/contrast graphs and bounded unequal-size examples. The verifier checks ALL positive-length geometric boundary overlaps between distinct leaves; every one has identical reversed endpoint indices. Partial overlaps that would form T-junctions are rejected. Candidate leaves bordering a culled region need not have a surviving neighbor.

All primary source lattice X/Z pairs are unique (171 vertices); contrast also has 93 unique pairs. Both include six vertices on source seam Z=9600. The camera-seam pair z47996.4/z47996.6 has 19 vertices on that seam and identical complete source graph hashes. This proves shared geometry for these executed, mapped M06 boundaries. It is not a universal coordinate-cache or default-page ownership theorem. Reuse follows the graph, regardless of the page from which a midpoint's height is sampled. Pointer-grid and world mapping assumptions remain the accepted #76 mapping, not a new coordinate result.

Allocation capacity, signed-index overflow, asynchronous ownership and graph persistence across retail frames are unresolved. The proposed C++ representation should use checked IDs, frame ownership and stable storage rather than 32-bit pointers or packed signed indices.
