# M-RND-07 — original software draw and raster boundary

**Complete under the assignment's bounded command/span criterion.** Original `0047CE40` executes twice from authenticated stock-bus GEO, returns to `004721B3`, and produces two 96-byte native commands, four 32-byte native edges and native shade planes. Original finalization `00473640 → 00474380` additionally produces 14 packed scanline records and naturally dispatches the first command to `0047CB00`. Execution stops at that callback's entry, before its first instruction. There are no framebuffer writes or source-backed images in this result.

Run `i76exe-20261031T011731Z-307babbf`, track i76exe, advisory RND/GEO. Exact authenticated base is `4de0c902628535fd91c3a5bd7b15b3af622d7ee8`, protocol 1.0.4, schema 1.2.0. The supplied reference `abd69273611721dceaab88005d750f1930c2713a` is historical. PR #73 had merged at bootstrap; its accepted implementation is read from this new checkout's main-derived tree, never its workspace or branch. No #71–#74 workspace is reused or modified. Accepted research and canonical documentation are unchanged.

## Original source and chronology

The unchanged full PR #70 driver first reproduces five camera/visibility/queue cases and passes its 1,402 source checks. The accepted PR #73 driver then reproduces original projection, natural secondary BF00 fallback, negative visibility and a fresh import; its source checks pass before this extension. Every EXE/ZFS/GZF identity is measured, not inherited as an assertion. See manifest and provenance.

The primary case retains a single emulator from original vehicle constructors, actual `nobus1.vcf`/`vxbus.vdf`/`xb11bdym.geo` loading and original registration through two `00406AB0` camera callbacks, `00457FF0` production and `0048FAC0` consumption. It uses the accepted selected camera owner and separate unselected stock bus, controlled target basis and Z=+50. The source polygon path is `00406AB0 → 00457FF0 → 0048FAC0 → 0045CBE0 → 00471FD0`. The actual child is `27006800`, GEO is `36003CD0`, and source vertex excerpt SHA-256 is `31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468`. The original kind-6 queue record remains `38015540`, owner `26100000`, registry `005428A8`, persistent view `004C2730`.

Before projection, an independent comparison requires the accepted camera/scene/queue event prefix through original production to agree exactly. No fabricated face, work record, queue link or camera matrix enters the primary case. Original dispatch is still index `0x101 → C8D0`, secondary index `1 → BF00`, draw index `1 → CE40`. The latter receives four 24-byte vertices from the actual original fallback output. BF00 retains projected XYZ here; this does not establish an actual clipping-plane intersection. The standalone verifier independently follows the authenticated source vertices through world/view matrices and original projection, using the accepted upstream oracle only for that upstream boundary.

## Draw dependencies removed one at a time

1. Remove the CE40 draw substitution. Original execution reaches `00472DF0`, then `004BA2FE` (`JMP [004BC154]`), then fails decoding the unmapped imported `operator new` target `000C0DD2`. Return site is `00472E17`, requested allocation is 12 bytes. Exact register/stack/context events are published in `blockers.json`.
2. Supply only guarded, deterministic CRT heap backing. Original arena initialization and command constructor execute. Original workspace growth reaches `00473788` with capacity `[0058DA9C]=0`, requested height 316. Doubling zero cannot reach 316. The final probe stops at this documented prerequisite, rather than spinning through the original zero-capacity loop. The first exploratory run was manually interrupted in that same loop.
3. Execute the original startup thunk `00473620`, which supplies original constant 128 to original constructor `004736B0` at `ECX=0058DA68`. No host constructs the workspace arrays or command. Original growth later requires imported delete at `004BA2F8 → [004BC150] → 000C0DC2`, return `0047390A`; without the next narrow service, instruction decode fails there.
4. Acknowledge that CRT delete without reusing backing. Original `0047CE40` now returns normally twice. No function inside CE40, its command constructor, scanline builder, edge constructor, barycentric inverse or finalizer is replaced. The kind-10 D110 draw and its initial clip service remain explicitly substituted.

Added backing is exactly four allocations: 5,120 bytes at `3E000000`, 12 at `3E001440`, 65,536 at `3E0014A0`, and 20,480 at `3E0114E0` (91,148 bytes total, plus 128 bytes of allocation guards). Original growth releases the first allocation; this service keeps its backing without reuse for observation. Every retired original step checks each 16-byte guard. All host scalar/bulk writes are forbidden from overwriting an existing draw allocation, and inherited view/queue seals remain active. Zero-backed storage is a supplied allocation property; unchanged zero bytes are never claimed as original stores. `DRAW_STORE_BYTE` captures changed bytes after original steps, including PC and prior value; unchanged writes are established separately by original opcode/register chronology and constructor-field checks.

The initializer is explicitly called by the research driver before queue production. It is original code, but this is not proof of full retail startup chronology or OS execution. Existing OS/CRT/resource/math/texture and scene-pose services remain as documented in SERVICE_LEDGER.

## Native command, edge and span ownership

Original command arena is `[3E0014A0,3E0114A0)`, allocated by original `00472DF0`. `0047CE78/0047CE8E` reserve 0x60 downward; the two commands are `3E011440` and `3E0113A0`. Original edges descend further, in 0x20 increments. Their inputs are actual projected polygon vertices; there is no host edge builder.

| Command offset | Native meaning and evidence |
| --- | --- |
| +00 | 32-bit supplied-through-original-call color/control argument, zero here; constructor store `00472EEA` |
| +04 | Deferred list link, written on next append at `00474234`; tail terminated by finalizer before callback |
| +08 | Original callback `0047CB00`, store `00472EEE` |
| +18 | float32 shade-plane constant, store `0047CF68` |
| +1C | Constructor zero/control, `00472EF5` |
| +20 / +24 | Original left/right edge-chain pointers, `00473FAB` / `00473D8F` |
| +28 | Current/last packed span, initialized -1 at `00472EF8`; native finalizer updates `0047324F` |
| +2C | Span-list base; zero until finalization |
| +30 | Pre-finalizer Y extent (2,12), store `00473FFF`; subsequently last span-slot pointer |
| +34 | Original serial 4,8, store `00472F13` |
| +38 | Deferred scanline/bucket link; lifetime belongs to original builder/finalizer |
| +58 / +5C | float32 X/Y shade gradients, stores `0047CF9D` / `0047CFA0` |

Other words are unproven/unused for this path; 96 bytes is the measured allocation size, not a complete inferred C++ type. Command +04 is not treated as a valid link before the next append or finalizer terminator. The commands survive draw return and queue consumption; their lifetime ends when original finalization finishes/reset reuses the arena. This experiment stops before that completion.

Each edge has native fixed-point X at +00, links at +04/+08, owning command at +0C, starting Y at +10, copied reciprocal depth at +14, fixed-point delta-X at +18 and exclusive ending Y at +1C. Original `00472F20` fills the numeric state; the original builder inserts these records into the ten scanline workspace arrays. Capacity grows 128→512; host supplies only backing for original growth/copy/initialization instructions.

Commands have Y intervals `[313,315)` and `[315,327)`. Finalization uses original incremental helper `00472FD0`; the observed packed-buffer writer is **`00473236`**, with span accumulator store `0047324F`. `00474270` is a statically audited alternate emitter, not the observed span writer in this positive case.

The native packed layout is `x<<21 | length<<10 | y`, using 11-bit X, 11-bit length and 10-bit Y. All 14 spans here are X=233, length=15, Y=313..326. Lists begin at `3E011354` and `3E011320`. Each begins with `FFFFFFFF`. The final pending span is stored in command +28; +30 points to its reserved slot, which still contains zero. Original callback `0047CB00` first copies +28 to that slot before walking the list. The verifier checks this split representation exactly; it does not pretend the callback's completing store has executed. Native buffer content plus native command state, together, define the 14 spans.

## Independent arithmetic and controls

`verify_draw.py` does not execute Ghidra or invoke a drawing service. It replays original changed-byte effects, checks allocation bounds and output snapshots, verifies exact command/edge metadata and original writer order, and calculates edge fixed-point values independently from authenticated projected vertices. Integer fields, sizes, pointers, serials, scanline bounds and every packed span compare exactly.

For matrix/plane arithmetic, it independently evaluates the triangle inverse algebra while respecting measured float32 spill boundaries: two coordinate products remain in x87, four are spilled; the reciprocal is spilled before eight of nine coefficient stores. All 18 matrix float32 words and all six shade-plane float32 words compare **bit-for-bit** for this corpus. This resolved an initially over-strict comparison to an ideal real-number inverse. The ideal constant is 8064, whereas native constants are 8063.3154296875 and 8063.84619140625; those measurable rounding effects are retained, not corrected by the host. Source/world/view/projection arithmetic retains the accepted float tolerance (relative 2e-6, absolute 2e-5). No hardware-x87 parity or general error bound for other polygons is claimed.

Positive visible, behind-camera negative, command/edge fresh-GZF repeat, finalizer/span positive and a second finalizer fresh-GZF repeat are all recorded. The negative changes only the controlled target Z to -50 and produces no draw command or edge. Both complete private positive trace pairs compare byte-for-byte, and the public selections compare exactly. Six corruptions (callback, edge delta, plane, packed span, writer chronology, source polygon) must fail. `corrupted_sample.json` is intentionally invalid and the ordinary verifier rejects it with nonzero exit status. Sparse opcode evidence is independently checked against retail PE bytes, not trusted merely because the GZF contains an instruction/symbol.

## Furthest boundary and image prerequisite

The finalizer naturally calls the original pointer in command +08. At `0047CB00`, args are `(3E011440,005DCEC0)`. This is a deliberate **pre-instruction boundary stop**, recorded as BOUNDARY_STOP, not a return or substituted successful raster call. The callback body remains original and statically audited.

Its first actual pixel destination would be `pitch*(y + descriptor[8]) + x + descriptor[5] + descriptor[7]`. Measured descriptor DWORDs 0 (pitch), 5 and 7 (base contribution) are zero. For the first span that formula yields address `000000E9`, not an owned framebuffer. Original initialized viewport extent values 479/639 exist elsewhere in this descriptor; they do not establish a usable raster surface, pitch, dimensions or color-depth ownership. The callback's byte stores and palette-table indexing establish an 8-bit indexed output path **statically**, not executed pixels.

The minimal next prerequisite is a coherently initialized original raster-surface descriptor with owned framebuffer address and positive pitch, plus authenticated original palette/shade-table initialization (the inherited palette/device service is still supplied). Original `0047CB00` and its writes can then be attempted with guarded surface backing and source-backed colors. No additional synthetic polygon is needed. Producing these commands does not close RND-v1, a maintained renderer, terrain/material/image gates or full gameplay integration. Human review and separate documentation promotion remain required; this PR stays unmerged.

## Final validation

The complete source driver passes 1,402 accepted integration assertions, 2,769 accepted polygon assertions and 11,350 new native assertions plus 292 delegated upstream assertions. Trusted base unit tests pass 38/38 (aggregate 15,851 checks, excluding deliberate expected failures). Six new corruptions reject; the published corrupted sample exits nonzero. Public-only native verification passes 9,810 checks plus 292 upstream checks. Trusted protocol/hash/schema and exact-commit pr_integrity validation are publication gates; the exact published-head GitHub result is reported in the PR/final handoff.
