# Validation and unresolved cases

Original execution is bounded Ghidra instruction emulation with the services listed in SERVICE_LEDGER.md. Camera-to-root/hull is retained original code, not independently modeled. No maintained reconstruction is changed.

| Controlled root case | Vertices | Edges | Leaves | Emitter attempts | Triangles | Clip accepted | Bin accepted |
|---|---:|---:|---:|---:|---:|---:|---:|
| below | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| contrast | 93 | 245 | 30 | 45 | 25 | 13 | 13 |
| primary | 171 | 464 | 79 | 181 | 112 | 30 | 30 |
| x2952.6 | 171 | 464 | 79 | 181 | 112 | 30 | 30 |
| x2953.5 | 171 | 464 | 80 | 181 | 112 | 30 | 30 |
| x2957.5 | 187 | 511 | 81 | 177 | 109 | 32 | 32 |
| z47996.4 | 148 | 400 | 59 | 96 | 49 | 32 | 32 |
| z47996.6 | 148 | 400 | 59 | 96 | 49 | 32 | 32 |
| z47999.9 | 158 | 429 | 61 | 84 | 39 | 33 | 33 |
| z48000.1 | 158 | 429 | 61 | 84 | 39 | 33 | 33 |

Nine valid cases match independent source graph construction, vertex identities/XYZ, numerical decision outcomes, full interleaved source arena, every flattened boundary loop, reverse work-vertex XYZ and emitted fan membership. Zero predicate mismatches. 45255 independent topology checks pass. These include all geometric overlaps between leaf boundaries, not only matching index pairs. The public fixture verifier separately checks midpoints/flattening/source attributes without assets. Counts are check invocations, not independent scientific claims.

The 0.1 root-X move has identical source graph hashes. At root X+1 one previously culled leaf survives without changing source vertices. At X+5 the size-2 region (588,9632) changes from height-test split (004913F9→00491674) to a retained leaf after the height test passes and the size<=4 guard (00491550→004917B4). This is an executed LOD threshold change, not just a count difference. Other regions also enter/leave visibility; the decision table separates these causes.

The actual camera source Z values for controlled root z47996.4 and z47996.6 are 47999.87027873993 and 48000.07027873993, crossing lattice seam Z=9600. Source graph hashes remain equal; both contain 19 seam vertices. Earlier z47999.9/z48000.1 controls cross the root-pose seam but their original cameras are both above the seam; they are retained transparently and are not the camera-seam proof.

Material-class refinement: primary quad165, packed0x6011, load0049160F, branch00491623→0049166C. Four original load/threshold/mask branches are audited and actual samples are authenticated. Class bits are never used as emitted material IDs. Near and distant selected leaves, differing height-test outcomes and unequal neighbor sizes are covered. There is no separately controlled constant-height TER modification or exhaustive surface-class synthetic corpus; that remains a scope limit.

Primary/contrast/below also pass 89159 inherited independent source/camera/transform/near-far/screen-clip/bin checks and three deliberate corruptions. Accepted tolerances: float32 source/index/arena and source-to-work copies exact; inherited transform/projection up to one ULP per stage, clipped coordinate up to eight ULP across six planes, operation-magnitude bounds for camera double arithmetic. No general floating-point tolerance or hardware-wide x87 parity is inferred.

Fresh v100 import: full primary trace and ten sidecars exactly equal. Unchanged accepted #76 observer: all eight common sidecars equal. v100 GZF identity differs from accepted v97 and is explicitly measured; full 765952-byte executable section equality establishes opcode provenance, not equality of annotations.

Alternate mode executes original selector and header setup, with descriptor0, flags0xF4, stop004924E0. Missing original texture initialization is the blocker. This case is not counted as a complete emission oracle. Added-center walker branch, high-color lighting, exhaustive independent whole-polygon/facing/shade selection, source-to-root hull parity, default pages/raw scan crossings, allocation failure/signed-index overflow and repeated rejected-frame lifetime remain open.

The source graph algorithm is implementable for these bounded original inputs. A general retail adaptive visible-output implementation is not yet certified; retain the dense/chunked fallback while widening camera/root and walker coverage. Research findings require human review and separate documentation promotion.

The packaged reproduce.py driver was also executed into another new private project for primary/contrast/below; regenerated scenario summaries match publication. Trusted local protocol tests:12/12, CI integrity tests:40/40. Three additional owned corruptions (edge arena, threshold input and emitter index) are independently rejected at their intended semantic checks; evidence/corruption_results.json records diagnostics.
