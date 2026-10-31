# Independent M-RND-06 — original terrain transform and polygon handoff

This run independently extends merged #69 from accepted main `3e10251444a117c8d9da053b6887245a2bc4dbcf`. PRs #71/#72, their branches, scripts and outputs were not consulted. All new research belongs to this run. No canonical reference, milestone, schema or governance changes are proposed. M-RND-06 is a bounded assignment, not a new ratified RND-v1 gate; G-RND-05 remains open.

## Scientific result and scope

Original `00490A00`, its adaptive producer and original `004937C0` transform authentic M06 source geometry. Original `00491A30` passes actual leaf-owned indices to polygon emitters. The untouched allocator baseline returns null. A separate experiment invokes original `0048F9B0` with supplied heap backing; its original arena/bucket initialization enables candidate allocation. With the inherited zero clip interval, original `0047BF00` rejects every candidate. A further controlled projection fixture enables original clipping and actual original `0048FE10` insertion. These are **controlled original-instruction results**, not a retail frame, genuine OS allocation lifecycle, texture proof or rendering/framebuffer output.

The furthest demonstrated boundary is original polygon insertion and original return from `00490A00`, with independently checked source vertices, clip outputs, record sizes and bucket membership. The projected diagnostic has 182 clipped/binned records in 21 bins (23,144 bytes); the arena-only diagnostic rejects 538 attempts. The final standalone verifier executes 209,140 assertions. The exact hashes and selected candidate are in `evidence/results.json`. Trusted publication validation is separate from scientific acceptance.

## Checkpoint A — accepted experiment first

The unchanged #69 producer, original-code audit, host instruction service and standalone verifier were read and executed before extending its probe. A private fresh GZF import and second fresh repeat reproduced **105,139 executed standalone checks**, primary **267 source vertices / 743 shared edges / 172 leaves**, contrast **97 / 256 / 41**, and rejected-region zero output. The accepted verifier checks every source height, full initialized page grid, original source/leaf writers, shared-edge graph, material predicate, poisoned output storage and raw unsupported FPATAN. Its entire regenerated public result equals the accepted result. This complete accepted verification is repeated by our reproduction driver; its count is reported separately and is not added to this run's assertion count.

The accepted producer stops at `004937C0` entry, via the CALL at `00490EED`, stack return `00490EF2`. These pre-transform leaf records are not render polygons. Accepted #70 was read for camera/geometry/interface context only. Its origin near zero and vehicle coordinate experiment do not establish compatibility with this distant M06 source region; no camera record from it is reused.

## Checkpoints B/C — affine contract and independent source transform

`view=45000000`, 118 dwords; private traces retain every dword. Source buffers are XYZ `42000000`, auxiliary `43000000`, shared edge/leaf arena `44000000`. As in accepted #69, only their base pointers/backing are supplied; original instructions create all geometry. A write guard rejects harness writes to geometry after producer entry.

The controlled volume uses +08 float 320; +2C float 1; +3C pointer `46000000` with width 640. Position doubles at +160/+168/+170 are `(2952.5,200,48152.5)`; contrast X is 3152.5. Four point triples at +178, +190, +1A8, +1C0 use X±80/Z±80, Y=1, ordered near-left, near-right, far-right, far-left. Below control changes position Y to -100. These are an explicit visibility fixture, not a live camera or a ratified complete RND-v1 frustum.

The newly valid affine record occupies +40..+7F: nine float32 values at +40..+60 are row-major identity, +64 is zero alignment, and float64 translations at +68/+70/+78 are `(-2952.5,-200,-47800)` (contrast X translation -3152.5). Basis determinant is +1 and translations are exactly representable. The render-space origin Z=47800 deliberately differs from the visibility-volume position Z=48152.5; these independently declared controls do not establish a coherent original camera record. This proper affine transform does not claim original camera production. There is no replacement transform body.

Original `004937C0` installs X/Z grid scale **5** from original terrain initialization and float32 Y scale **0x3DCCCCCD**, composes them with the view through original `00494E20`, then writes X, Z, Y via `004938A8`, `004938AA`, `004938BC`. The composed matrix and every retired coordinate store are logged. Pre and post buffers are captured separately before the walker may use or extend them.

For each source-grid `(x,h,z)`, the independent verifier resolves ZMAP page, row `z mod 128`, column `x mod 128`, TER byte offset, packed uint16, low12 height and material class. It calculates:

```
X = float32(5*x - cameraX)
Y = float32(float32(0.1)*(TERword & 4095) - 200)
Z = float32(5*z - 47800)
```

For this identity-basis fixture, products and translations are exact dyadic values in binary64 and x87 extended precision before the final float32 store. Therefore the acceptance threshold is **exact rounded float32 equality**, not a broad distance bound. All 801 primary coordinates pass. Maximum primary rounding error versus the exact dyadic expression is about `7.16e-6`. Source buffers equal the accepted source result; pre-transform inputs are not manufactured.

Original bounds use near `C3960000` (-300), far `44750000` (980), and minimum source height state `3F333333` (~0.7), checked from actual original stores and independent computation. The far calculation retains stack sentinel 1000, takes the greatest `(transformed Z+1000)`, subtracts -300 and 1000. Minimum height uses the **pre-transform packed-height component**, scaled by original 0.1. These are not translations of 1000/16000. Original `004937C0` returns to `00490EF2` with XYZ pointer end `42000C84`.

## Checkpoint D — retail walker, arguments and allocator baseline

Backend byte `00654B8B=0` selects original `(0048E190,004922F0)` callbacks. `0048E190` is a retail RET, not an omitted harness callback. Original `00491A30` walks the linked leaves, recursively flattens +14/+10 forward then +18/+0C reverse, performs plane/facing/lighting work, and calls the emitter with a pointer to its own stack index list, count and shade. It may try a polygon, then fall back to triangles if the emitter returns zero; thus rejected attempts are not unique source polygons or successful submissions.

The first leaf is `440002A0`; original callback returns to `00491DF9`. Original emitter `004922F0` receives index list at `3001C7F0`, count 4, shade bits zero and source indices **23,20,15,22**, from call return `00492091`. The emitter calls allocator `00490590`, return `004922F9`. Allocator takes **no size argument**: it reads cursor `006543C0`, installs active `0065439C`, clears +14 link and +00 count, and returns that same pointer. The untouched cursor/active values are zero. Original writes at `0049059A/004905A6` target `0x14/0`; Ghidra permits these null-address writes. The harness captures return zero and stops before the emitter stores. This is an **omitted original runtime prerequisite**, not a retail null-allocation failure or an unsupported Ghidra instruction. The baseline is never repaired in place.

## Checkpoint E — separated allocation and projection diagnostics

Each diagnostic starts a new emulator, reloads authentic terrain and reruns original geometry. Original `0048F9B0` executes, using supplied zero-backed heap services at `00498940/00499CE0`. Its five requests are 370000, 128000, 49152, 49152, 2880 bytes, mapped at `48000000`, `48100000`, `48200000`, `48300000`, `48400000`. Original initializer writes all polygon cursor/active/base globals and all 12,288 dwords of the spatial bucket table; these original stores are captured and independently checked. Host-provided backing is diagnostic memory. This does not prove real VirtualAlloc/heap behavior, frame reset, allocation capacity enforcement or original scheduler ownership.

**Arena-only diagnostic:** affine and visibility are valid, but +108 and +138 clip depths remain inherited zeros. Original `0047BF00` computes a nonzero common depth outcode for every positive-Z candidate, returns zero, and original bin insertion does not run. It reuses one scratch record. Rejection may trigger the walker's triangle fallback. Counted attempts must not be presented as accepted polygons.

**Projected diagnostic:** retains the same source visibility/affine fixture and adds center `(320,240)` at +00/+04, X/Y scales `(320,-320)` at +08/+0C, screen min/max `(0,0,640,480)` at +1C/+20/+24/+28, near=1 at +108 and far=4095 at +138. All fields are explicitly supplied, not recovered camera outputs. Original `0047BF00` executes depth classification, projection and original compact screen clip `0047B8C0`; it is never replaced with a pass-through count. Its four original projection stores per source corner are observed at `0047C29D/0047C2AB/0047C2AF/0047C2B6`.

The original screen clip's final call at `0047BED9` uses imported CRT memcpy (return `0047BEDF`). This external service is supplied. The guard permits it only for that exact caller, original clip-stack source, `currentRecord+28` destination and 1..32 vertex records. It logs all copied bytes. Copying original-produced clip output is explicitly separate from original arithmetic/store execution; it is not a replacement clip routine or test-authored geometry. The initial guard rejection is recorded in execution notes.

The independent verifier checks perspective X/Y and reciprocal Z against transformed source with a one-float32-ULP budget for reciprocal/product/add and final storage; it independently applies four screen clipping planes. Screen results permit four float32 ULPs for stored interpolation stages (at 640, about 0.000244), preserving vertex count and cyclic polygon order. It also requires exact original projection-write chronology and exact CRT source/output bytes. These tolerances concern this bounded positive-depth fixture, not hardware x87 parity in general.

For every accepted record, original `0048FE10` receives the **unprojected maximum source depth** stored at +10. It computes the depth-relative integer bucket, checks range/count/type, mutates original bucket head/tail/count and +14 links, and advances the original cursor by `28+24*clippedCount`. The verifier reconciles retired bucket changes against final table bytes and traverses every final chain. Merely entering binning is not counted as acceptance. The final projected run accepts **182** original records; all are independently present in bins. No draw/consumer or framebuffer routine is run.

## Record fields and source material boundary

The ordinary emitter writes +00 count, +04 literal **B4**, +0C record kind **0**, +10 maximum unprojected Z, +14 next, +18 link state, with 24-byte vertices starting at +1C. Each vertex copies transformed XYZ in **reverse emitter index order**, retains attribute slots and writes shade at vertex +14. In this zero-backed, missing-palette context the other attribute slots are zero; no UV meaning is assigned. Header B4 is a retail literal, not `TERword >> 13`, and is not claimed to identify a texture. Allocation size becomes concrete only after successful clipping/bin cursor advancement; rejected candidates reuse the cursor.

A separate alternate-backend diagnostic sets only the declared selector byte to 1, runs original `004923F0`, original `00471F00`, and original `004924B0` through header stores, then deliberately stops before vertex copies. `004923F0` aligns leaf coordinate ranges and selects one of seven eight-byte descriptor pairs at `005A4588` from width/depth-related state. `00471F00` selects pair+4 only if nonnull and view descriptor mode is 1, otherwise pair+0. `004924B0` writes +04 from `0059C558` and +08 from `0059C548`; its subsequent static code derives U/V-like attributes from auxiliary X/Z minus the aligned origin and indexes the clip table by flags. Texture initialization `004908F0` is omitted as in #69: the measured pair and returned descriptor are **null**. This does not authenticate any texture, UV chart, material load success or alternate accepted render polygon.

Every tested source vertex has authenticated material class provenance. The first ordinary candidate spans classes 0,3,1,1; this cannot be turned into a single rendered texture identity. Bit 12 remains uninterpreted. Source TER metadata, renderer B4 literal, alternate descriptor state and texture bytes are distinct evidence boundaries.

## Checkpoint F — controls, repeat and publication

The driver reruns accepted A before B/C, source-verifies primary before entering D, captures the null baseline before E, and retains separate diagnostic contexts. Contrast shifts the valid view and affine X translation by 200 and changes source/output. Below-height region produces no valid source primitives. The full projected positive is repeated in another fresh GZF project with byte-identical trace, page grid, pre/post/final vertices, leaf arena, polygon arena and bucket table. Three deliberately corrupted source height, transformed coordinate and emitted-record inputs must be rejected by the standalone verifier. The reported assertion count increments on actually executed `check()` calls; inherited baseline and unit-test counts are separately labeled.

All proprietary inputs, full decompilation, projects, source grids/meshes, full traces and record arenas remain private. Published evidence is bounded derived data, selected instructions/events and complete versioned scripts. Manifest validation equals standalone validation exactly; every artifact has measured length/SHA-256. Trusted protocol, unit and PR-integrity checks precede publication; required GitHub integrity must pass on the exact published head. This run remains a review proposal and is not merged or promoted.

## Next prerequisites and claims excluded

The controlled source→transform→ordinary polygon→clip→bin chain is demonstrated. A complete original frame still requires authentic runtime allocation/reset/capacity lifecycle, original-compatible camera/frustum scheduling, source-backed lighting/palette and WRLD texture/descriptor initialization, consumption/draw/raster output and source-to-image verification. The explicit projected diagnostic does not replace those provenance obligations. No original retail Windows execution, material/texture success, UV authentication, rendered pixels, completed RND gate or maintained reconstruction is claimed.
