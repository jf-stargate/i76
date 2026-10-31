# M-RND-08: coherent original camera to M06 terrain clipping and binning

Run `i76exe-20261031T011728Z-b887fccd`, i76exe / RND, TER, VEH. Base `4de0c902628535fd91c3a5bd7b15b3af622d7ee8`, protocol 1.0.4/schema 1.2.0. This current protected main is a descendant of the user's reference `abd69273611721dceaab88005d750f1930c2713a`. Only the new run is proposed. No canonical, governance, accepted-run or other checkout changes.

**Bounded positive:** the same original-updated 472-byte camera at `004C2730` drives original authenticated M06 selection, adaptive generation, affine transformation, polygon emission, depth/screen clipping and actual bin insertion. The primary produces **171 vertices, 79 leaves, 181 attempted polygons and 30 accepted records in 10 buckets / 3,792 bytes**. A controlled X shift of 200 produces **93 vertices, 30 leaves, 45 attempts and 13 accepted records in 10 buckets / 1,732 bytes**. The below-terrain control produces zero primitives. A separately imported project reproduces the entire primary trace and nine output files exactly.

This satisfies the assignment's coherent camera-to-bin research experiment within original-instruction emulation and declared services. It is **not a complete original frame**, mission spawn, selected-player scheduler event, physics result, drawing experiment, texture/UV/color result, image, RND-v1 completion or reconstruction authorization. Original frame/consumer reset evidence below is static; neither the frame dispatcher nor the queue consumer executes in this experiment.

## Accepted baseline reproduced first

Read accepted #67 camera continuity, #70 integrated vehicle camera/queue, #69 adaptive M06 terrain and #74 transform/clip/bin evidence. Every listed artifact hash and standalone/manifest validation equality of all four runs was checked (13, 13, 14 and 16 artifacts respectively). Their immutable manifests and lineage are recorded in `evidence/reproduction.json`.

The unchanged #74 driver ran in a new private project, including its unchanged #69 source/graph/numerical controls and second imports. It reproduced **105,139 #69 checks**, then **209,140 #74 checks**, including **182 records / 21 bins / 23,144 bytes**, the null allocator baseline, arena-only rejection, controlled projection, differential/negative and corruptions. These counts are separate from this run's checks. `evidence/reproduction.json` records actual regenerated hashes/results.

#74's visibility origin `(2952.5,200,48152.5)`, separately authored affine origin `(2952.5,200,47800)`, identity basis, projection scales `(320,-320)`, center `(320,240)`, screen `(0,0,640,480)`, near 1/far 4095 and supplied heap remain **controlled baseline inputs**. They are not relabeled as recovered native camera fields. Its 182 records cannot be compared as a fidelity score against our different coherent camera and native far=150 scene.

## Actual original ownership, independently of old labels

`00403E64` is a PUSH inside the containing WinMain FSM, not an initializer function entry. It pushes literal `004C2730`; `00403E69` calls `00401C90`. Actual instructions at `00401C90` call the flow-state getter, compare with 5 and select `00401FA0` versus `00401CC0` using `00495060`. Thus its old “AI/frame-update” label does **not** identify the actual work. In software frame `00401CC0`, `00401DE1` calls `00490A00`; subsequent source calls include roads, world-object production and consumption. These frame functions are audited, not executed as a retail frame.

`00472220` is likewise more specific than its historical “raster command context” label: it builds and returns a 118-dword view from viewport, FOV, aspect, distance and zoom inputs. `00405970(0)` calls it with original FOV constant `3FC90FDA`, mode-derived aspect and far=150, then copies the record by original `REP MOVSD` at `00405A2D`. Zero argument deliberately avoids camera-mode/player activation. Original `00406AB0` later calls original `00472400` and `00472990`; no output view is copied from an earlier experiment.

The private audit compares all **765,952 executable-section bytes** to authenticated retail PE, and records instructions, xrefs and decompilation. Published sparse anchors authenticate original field writer/consumer instructions against that PE. Ghidra's absent function boundary at `00406AB0` and interior address `00403E64` are annotation facts, not absent original instructions. Full private source dumps are not published.

## Field-by-field provenance

Offsets below are relative to **this exact** view, not assumed interchangeable with every historical structure. O = original instructions; C = controlled scene/service input. All final camera fields remain sealed after the callbacks and byte-identical through terrain return.

| Field | Actual origin and value / dependency |
|---|---|
| Root basis +18..+38 and doubles +40/+48/+50 | C pose on O-constructed registered stock bus: identity and `(2952.5,60,48152.5)`; contrast X=3152.5; negative Y=-100. These world-unit positions are selected near authenticated M06 pages; **not derived mission spawn coordinates**. |
| Root/runtime/VLOC/world entry | O `0045EBD0`, spawn-policy basic blocks, `004AD6F0` from authenticated stock VCF/VDF/GEO/TMT, O `004572B0`; root `26000000`, entry `00542830`, VLOC `27000800`, actual runtime from root+70. Class staging/resource/heap services explicit. |
| Viewport descriptor `005DCEC0` | C width=640, height=480; clip min X/Y=0 at +1C/+20, max X/Y=639/479 at +24/+28; color-mode input 2. No OS surface creation. |
| View +00/+04 projection center | O `00472220`, `00472311/0047231F`: half inclusive viewport extent, `(320,240)`. |
| +2C tangent / +30 aspect / +34 zoom | O builder/math boundary and `00472441`; tangent `3F7FFFFF`, aspect=1 from original mode-2 branch, zoom=1 through original callback. Sine/cosine service disclosed. |
| +08/+0C scales | O `004724E6/004724E9`: `(320.0000305175781,-320.0000305175781)`. No host projection writes. |
| +1C/+20/+24/+28 float clip rectangle | O `00472599/59E/5AD/5B6` after original descriptor clip setter; `(0,0,639,479)`. Descriptor extent remains C. |
| +3C viewport pointer | O builder installs `005DCEC0`; points to C descriptor. Terrain's width read therefore resolves to 640. |
| +108 near | O `004725A1`, literal `3DCCCCCD` = 0.1f; not old report's “near 1”. It is also the Z component of first local near corner. |
| +138 far | O `0047270F`, far-distance×zoom clamp; 150, also first local far corner Z. |
| +100..+12F, +130..+15F local corners | O `00472530`, including near/far offsets above. Four far local corners, no independently supplied visibility rectangle. |
| +40..+60 inverse basis; +68/+70/+78 doubles | O `00406AB0 → 00472990 → 00494F70`, final matrix copy `00472C05`; transpose and negative rotated camera translation. Padding +64 is copied, not given invented semantics. |
| +160/+168/+170 camera position | O `00472990` source-transform translation copy. Primary `(2952.0923249721527,62.02251482009888,48155.97027873993)` from C root and O stock attachment/callback. Contrast adds exactly 200 to X. |
| +178..+1D7 four world corners | O `00472A40/00472A62/00472A85`: local corners transformed with the **same source camera**. |
| +80/+88/+90 center, +98 radius | O `00472B6F/80/86`, `00472BF0`: five-point camera/corners bounding volume, independently recomputed. |
| +A0..+FF frustum planes | O `00472530`; stored alongside local corners; source linked classifier `00472C10` audited. Terrain uses original position/corner bounds algorithm, not an invented classifier. |
| `00654398/39C/3C0` polygon base/active/cursor | O `0048F9B0` from external backing; O `00490590` active installation and scratch clears, O bin advancement. Actual base `48000000`. |
| `006543B0/384`, `00654388/3A8` bucket bases/cursors | O `0048F9B0` from external backing `48200000/48300000`; 4096 entries each. Original table-one initialization stores independently checked at every dword. |
| `00654390/3B8/3BC`, `006543A0/3B4/38C` | O span/effect buffer pointers/limits from external backing `48100000/48400000`; no claim every consumer was exercised. |
| `006543AC` bin minimum / `006543A4` bin maximum | O terrain transform `004938DF/004938FF`: -300 and source-dependent maximum; independently checked. **Distinct from** view +108/+138 camera clip depths. No supplied scan bound 4095. |
| `005DD320/005DD2EC/005DD324` source scratch bases | C backing at `42000000/43000000/44000000`; O terrain initializes cursor and writes all source/edge/leaf geometry. Native allocation ownership for these three bases is not recovered here. |
| Timer/velocity/active entry/angle inputs | C delta .016, runtime velocity `(2,0,1)`, active entry from O registration, angle integers 1; retail mapped smoothing constant retained. Direct callbacks, no original clock/physics/scheduler claim. |

The inherited #67 descriptor initializer had max X=479/max Y=639, despite its verbal 640×480 description; its first descriptor width dword was zero. Original `00472444..4A` establishes X ownership, and `00472530` consumes descriptor +24/+28 as X/Y maxima. This run corrects only its **own** input fixture to actual width=640/height=480 and inclusive rectangle 639/479. Accepted evidence is unchanged. The previous claimed viewport and near labels must not be propagated without checking the instructions.

## One retained original camera and terrain state

Each case builds, attaches and registers the bus in one emulator, performs original math startup and projection initialization, supplies its root pose and bounded camera inputs, and invokes original `00406AB0` twice. The second call begins with the first call's entire record and smoothing history. Original root reads and original source matrices are retained; callback stores never modify the controlled root pose. No camera reset, synthetic projection or separate visibility-position substitution follows.

Authenticated M06 WRLD/TDEF loading then runs in that same emulator, with declared file/peripheral services. Geometry scratch bases and software backend are supplied. Original `0048F9B0` installs renderer arena state. The full original camera is sealed and passed directly to `00490A00`, which produces original source geometry, calls `004937C0`, walks leaves through `00491A30/004922F0`, clips through `0047BF00/0047B8C0` and bins through `0048FE10`. No work record, index array, bucket link or accepted count is manufactured. Attempts rejected by original clipping reuse the same original cursor; attempted polygons include fallback triangles.

The original affine uses row-vector convention: a source row point multiplies the 3×3 matrix, then adds the three doubles. Original source scales are 5 for lattice X/Z and float32 `3DCCCCCD` for packed low12 height. The original composed coefficients are rounded float32; the verifier checks those coefficients first, then **exact rounded float32 equality for every transformed coordinate**. It does not substitute an unrounded world-space transform.

The camera source rotation has positive determinant `1.000026841538967` and measured maximum Gram defect `6.014088080711841e-5` after the second callback. Original `00494F70` implements a transpose-based inverse, not a general matrix inversion/orthonormalization. The verifier checks that exact implementation, camera-origin-to-zero identity, corners and conditioning without repairing the basis. This bounded emulator result does not establish ideal hardware orthogonality or full x87 parity.

## Independent verification

`verify_context.py` is standalone Python; it imports neither Java producer nor Ghidra. It authenticates PE/GZF/ZFS/MSN/TER and all 64 fixture digests against accepted evidence; verifies sparse PE anchors; replays original callback changes from actual before samples; checks source matrix transpose/translation, origin, six plane/corner incidence checks, local/world corners, bounding center/radius, projection/depth offsets, coordinate scales, all 16,384 page pointers, every source height/material read and original source/transform/leaf writer.

For each attempted polygon it independently resolves leaf shared edges and source indices, requires exact original emitter source bytes and same camera/polygon pointers, applies near/far depth clipping followed by projection and four screen planes, checks original projection store chronology and values, exact external copy bytes, then reconciles all original bucket mutations with every final record/chain. All 43 accepted records are in exactly one bucket. No bin-entry count is used as a substitute for membership.

Numerical rules are local to these operations. Ownership, addresses, integer fields, bytes, counts and links are exact. Transform outputs require exact rounded float32 equality using the checked composed coefficients; these fixtures exhibited no intermediate-double/x87 ambiguity. Projection permits one float32 ULP after reciprocal/product/add. Clip interpolation permits eight per-coordinate float32 ULPs for two depth and four screen stages, extending #74's four-screen-plane budget to six planes; counts/order/bounds and copy bytes remain exact. This is a bounded arithmetic test, not a universal x87/image tolerance. Camera double sum checks use an operation/magnitude-derived bound `8*2^-52*sum(abs(terms))`. Radius uses coordinate-magnitude error, because original extended midpoint retention can differ from recomputing distances from a rounded, far-from-origin center; a radius-only ULP limit was inappropriate. Basis conditioning is reported separately, not confused with arithmetic rounding.

The negative case uses the original height/region rejection branch, not a forced clip failure. Repeat requires byte equality of trace, view, page grid, source, transformed/final vertices, source arena, polygon arena and bucket table. Corrupting source height, inverse view or emitter XYZ must produce a verifier failure at its named check in separate processes. Final standalone result: **89,114 executed checks**, distinct from predecessor/unit/protocol checks.

## Arena/frame lifecycle and next integration prerequisite

Original `0048F9B0` requests 370000, 128000, 49152, 49152 and 2880 bytes through `00498940/00499CE0`. Their actual bodies are audited; this experiment supplies only deterministic zero-backed memory at those entry boundaries. Original pointer installation, primary bucket zeroing, allocation cursor use and binning run unchanged. The second bucket table is initialized by original code but its initializer clears +0/+8, whereas the first clears all three dwords; this is not silently described as identical initialization.

Source instructions in `0048FAC0` show shared terrain/vehicle kind queues: a type dispatch selects consumer routines; after consumption original code clears table one (`0048FD6D`), resets polygon cursor from base (`0048FD7B`) and writes depth sentinels +1,000,000 / -1,000,000 (`0048FDE2/DEC`). Optional second-table/effect resets are branch-dependent. Arena bases/backing persist; contents/cursors/depth range are frame work state. Resetting between terrain production and vehicle production would discard shared queued work. #70 dynamically demonstrated kind-6/10 use and clearing; this run verifies the source ownership but does **not execute consumer/reset/drawing** or assert unified terrain-and-vehicle queue coexistence was tested.

The camera/terrain coordinate contradiction in #74 is removed for this bounded scene. A unified M06 camera-to-image experiment still needs original-compatible common-frame scratch ownership and queue lifecycle for terrain plus vehicle, authenticated WRLD/palette/texture/material initialization, and the separately assigned draw/output work. Source scratch pointers, viewport/surface and external services remain supplied; mission spawn/physics/selected scheduling remain separate. No negative initialization prerequisite prevents this camera-to-bin result. The next unexecuted output boundary is downstream queue consumption with a valid material/output context, not another invented camera position. No draw-command investigation is included here.
