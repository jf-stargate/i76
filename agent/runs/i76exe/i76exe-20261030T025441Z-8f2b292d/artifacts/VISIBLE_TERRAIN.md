# Original M06 terrain selection and adaptive primitive production

Run `i76exe-20261030T025441Z-8f2b292d`, base `b219f0f2edea9da7f6ea9f44b80de90d4ddecb49`. **Bounded positive original adaptive-leaf production; partial renderer material/output boundary.** This is an original-instruction experiment with explicit numerical and peripheral services, not Windows execution. It does not close G-RND-05, RND-R2, RND-I1 or SC-RND-04/05.

## Observed result

Original `00490A00 → 004929B0 → 004911E0 → 00491810` creates **267 vertices, 743 shared edge records and 172 linked leaf primitive nodes** from authenticated M06. Execution deliberately stops at original `004937C0` entry, return address **00490EF2**, after the original CALL at `00490EED`. The buffer is still in source grid coordinates and packed-height units. No triangle list, renderer work record or pixels are claimed. These are the original adaptive quad/edge primitives destined for the visual path, not physics contact records.

Fresh read-only Ghidra import reproduces the complete trace, pointer grid, vertex buffer and arena byte-for-byte. A view shifted +200 in X produces **97 vertices / 256 edges / 41 leaves**. A below-height view returns bounds result zero at `00490B23`, takes the original empty-fill branch, returns from `00490A00`, and produces zero vertices/edges/leaves. The fill body is replaced and writes no framebuffer. An `A5`-filled output-storage control produces byte-identical positive vertex/arena bytes. An output-write guard rejects any harness/service write to the output storage after producer entry; zero such writes occur. Independent verification also requires original writer events for every vertex and leaf, compares final bytes, and independently traverses the edge graph.

The final raw control actually attempts the unsupported original `FPATAN` at `00492EAF` without its service, fails there, and yields no primitives. This is an emulator instruction prerequisite, not a retail defect. The positive run supplies exactly that x87 instruction and the two sampler FISTP sites; it does not replace visible-bounds selection or the subdivision predicate. See [service ledger](SERVICE_LEDGER.md).

## Controlled view, not a recovered live camera

All tested views are explicitly authored 118-dword records at `45000000`, logged in full privately. No original player camera callback, view scheduling, world object registration or vehicle queue work runs here. Only fields read before the chosen boundary are supplied:

| Offset | Controlled value and original use |
| --- | --- |
| `+08` float | 320; LOD threshold computation |
| `+2C` float | 1; LOD threshold computation |
| `+3C` pointer | `46000000`, first dword 640; width-dependent LOD threshold |
| `+160,+168,+170` doubles | `(2952.5,200,48152.5)`; source position for visible bounds and distance-dependent subdivision |
| `+178..+1D7` | Four double XYZ points: X=position±80, Z=position±80, Y=1; order near-left, near-right, far-right, far-left |
| `+40..+7F` | Zero; deliberately not a valid downstream affine view; not consumed before the stop |

The position is a controlled value near accepted M06 source samples, not an original camera-produced pose. Contrast uses X=3152.5, with its four points shifted equally. Rejection uses camera Y=-100; source terrain is unchanged. Original bounds produces grid origin `(512,9568)`, exponent 7 and four planes for primary, versus `(576,9568)`, exponent 7 and four planes for contrast. This is a controlled visibility/LOD volume, not a claim of a ratified 640×480 perspective fixture. Source rejection does call the real height sampler as a guard; that sampler alone is not visual proof. The subsequent original leaf writes are the new visual-path evidence.

## One identifiable original primitive

The primary first leaf is **440002A0**, written by original `00491810` (last field/next-zero store `00491892`) and linked by the original caller. Its four source edge references flatten in the original walker's static order to vertex indices **23,20,15,22**. Each vertex was written by original FSTP **0049199D**, not the harness.

| Index | Grid X, low12 height, grid Z | TER page / row / col | TER byte offset | Packed word | Material class |
| --- | --- | --- | --- | --- | --- |
| 23 | 568,300,9608 | 0 / 8 / 56 | `0870` | `012C` | 0 |
| 20 | 576,309,9608 | 0 / 8 / 64 | `0880` | `6135` | 3 |
| 15 | 576,278,9616 | 0 / 16 / 64 | `1080` | `2116` | 1 |
| 22 | 568,252,9616 | 0 / 16 / 56 | `1070` | `20FC` | 1 |

These samples belong to ZMAP cell **(4,75)**, page index 0, installed in runtime grid cell **(28,99)**. Independent XZ signed area×2 is +128 grid units² in that loop order. This checks ordering/nondegeneracy of the leaf boundary; original `00491A30` is not executed and its eventual triangle/fan choice is not claimed.

The source-world sample X/Z values are **(2840,48040), (2880,48040), (2880,48080), (2840,48080)** using the original step 5. Nominal source heights are **30,30.9,27.8,25.2** using low12×0.1. `results.json` retains the independently calculated values using the exact float32 multiplier `3DCCCCCD`, without pretending these are executed transformed vertices. Fresh retail instructions in `004937C0` install X/Z scale 5 and Y scale 0.1 before composing with `view+40`; that downstream transform is unexecuted. Constants 1000/1000/16000 in its stack frame initialize bounds/extrema outside the copied transform; they are not source-world translation offsets.

Every generated vertex, including vertices later unused by accepted leaves, is independently checked against its active source page. Primary vertices use pages 0,9,10,11 and classes 0,1,3,5,7. Source height/coordinate identity is exact in pre-transform units. Material bit 12 is preserved in the source ledger without assigning meaning. The primitive spans different source classes: it has no single proven texture or material descriptor field.

## Original retail path and ownership map

Addresses below are retail VAs; descriptive roles are findings, not reliance on historical names. The audit first compares all **765,952 executable-section bytes** in the annotated program against the private PE (SHA-256 `e58a54c0e39b55c2d0110cf8a6d22bedf8c53896a85b10dc7d1e8775cfe1318a`). The independent verifier rechecks sparse published instruction bytes directly from that PE. Full decompilation stays private.

| Anchor | Verified instruction/dataflow and execution tier |
| --- | --- |
| `00401DE1` | Original software-frame CALL to `00490A00`; static, not executed as a full frame |
| `00490B1E / 004929B0` | Builder calls original visible-bounds routine; height guard, point hull, aligned root extent and plane globals; executed |
| `00490A00` | Resets original counts/list/cursor; writes four root vertices, four shared edges, calls recursion, then transform/walker; executed through transform entry |
| `004911E0` | Culls against original bound planes; computes scale/distance/height error; scans source material words; subdivides shared edges or creates a leaf; executed |
| `004915F7,0049160F,00491627,0049163F` | Original uint16 material-predicate reads; compare word≥4000 and `(word & E000) != A000`; recorded and checked against TER. Classes 3 and 7 satisfy the static predicate; only observed reads establish actual dynamic use |
| `00491810` | Allocates 1C-byte node from `00654380`; original coordinate/range fields, next=0 and four edge refs; executed |
| `004918B0 / 004918F0` | Original 0C-byte edge allocation/shared midpoint splitting; source heights from `00493160`; executed |
| `00493160 / 004931A4` | Runtime pointer-grid lookup, original word read, low12 mask; executed for visual vertex production |
| `004937C0` | Original transform successor, never substituted with a fake result: stop before its first instruction |
| `00491A30` | Static primitive-list reader, flatten edges +14 forward,+10 forward,+18 reverse,+0C reverse, optional center/fan and polygon callbacks; unexecuted |
| `00490F6F..00490F9B` | Static byte `00654B8B` selects callbacks `(0048E190,004922F0)` or `(004923F0,004924B0)`; unexecuted |
| `004922F0` | Static polygon allocator `00490590`, record +0C=0 and **+04=B4**, copied vertices, clip callback and binning; unexecuted |
| `004923F0 / 004924B0` | Static alternate path derives flags by leaf range and material state via `00471F00` / `005A4588` descriptor selection, stores `0059C558`, then record +04 from that global; unexecuted |

Runtime source/primitive ownership:

| Global | Original writer / reader and observed role |
| --- | --- |
| `006442C0/C4` | Original `00493080` installs step 5 / reciprocal float 0.2 |
| `00644380` | Original loader/initializer writes all 16,384 page pointers; `00493160` and LOD material scan read them |
| `005DD320` | Controlled allocation pointer; original builder/midpoint code writes 0C-byte XYZ source vertices; allocator/recursion/transform/walker read it |
| `005DD2EC` | Controlled companion allocation pointer; original builder/splitter writes aux XZ data; later lighting/UV path remains unexecuted |
| `005DD324 / 00654380` | Controlled arena base; original builder resets cursor, allocators advance it by 0C/1C |
| `0059C560/574` | Original first/last leaf pointers; caller links original leaf +08; later walker reads |
| `0059C568/56C / 006442EC` | Original edge/leaf/vertex counts; independently agree with final arena sizes and recorded writers |
| `006442E0/E4/E8/F0`, `00644308...` | Original aligned root origin, root exponent and hull planes consumed by recursion |

## Material boundary and exact downstream prerequisites

The source material ledger establishes packed TER class provenance and original LOD predicate consumption. **It does not establish rendered texture identity, UVs, or a class→texture mapping.** In particular, observed class 3 is not proof of a road texture. Fresh retail static instructions show path A writes fixed record +04=B4, while path B obtains +04 through separate descriptor/global state. Neither instruction path simply copies `TER >> 13` into the polygon material field. Historical diagnostic texture/color hypotheses remain hypotheses.

Primitive production is no longer blocked in this bounded service environment. Untreated Ghidra execution remains blocked at `00492EAF` FPATAN. The next unexecuted boundary is exactly original `00490EED → 004937C0`, with original source-owned leaf and vertex memory retained. To advance without manufacturing output requires a valid source-backed **affine view at record+40** (ours is zero), original transform and walker, owned polygon scratch/allocation (`00490590`) and raster/clip context. For the alternate textured path, the deliberately omitted WRLD `004908F0` texture initialization and descriptor selection `004923F0 → 00471F00 → 0059C558` must also be measured against authenticated resource bytes. Palette ACT/LUM/TBL acquisition is explicitly absent here and reports three errors per WRLD call; no palette/material-render success is inferred. This is a minimal interface prerequisite list, not evidence that further execution will succeed.

## Independent checks and acceptance handoff

The standalone Python verifier knows no emulator code and authors no primitive. It checks all page pointers against ZMAP, all generated heights against source uint16, original write events against final typed buffers, all leaf allocator arguments and record fields, arena allocation accounting, shared-edge ownership/acyclicity and loop order/area. It verifies every logged visual height/material read, the numeric instruction services via exact host replay and independent Python rounding/atan2, source identities, sparse original calls, WRLD physical-property copying, negative/contrast/poison controls and fresh-project equality. WRLD properties are physics metadata, not promoted as visual materials. See [reproduction](REPRODUCE.md), [results](../evidence/results.json) and [selected original events](../evidence/selected_events.tsv).

M-RND-05 has positive original visual-LOD leaf production and source height/material-class provenance. Its final polygon/material and image boundaries remain partial. No vehicle visibility queue, collision list, M-RND-03 integration, full RND fixture or maintained renderer is implemented. This run proposes evidence only; human review and separate documentation promotion remain required.
