# M-RND-03 — continuous original producer-to-consumer integration

**Positive bounded result.** In one retained Ghidra emulator, original stock vehicle construction and registration, original `00406AB0` camera callbacks and persistent `004C2730`, original `00457FF0` production, and original `0048FAC0` consumption reach original GEO traversal and polygon wrappers. No queue nodes, record owners, links, bucket heads or indices are supplied by the harness. Original clip/draw targets are intercepted; there is no pixel, M06, live scheduler, hardware x87 parity or RND-v1 completion claim.

Run `i76exe-20261030T025421Z-351de3fe`, track i76exe, advisory RND/OBJ/VEH/GEO. Original authenticated main/base `b219f0f2edea9da7f6ea9f44b80de90d4ddecb49`; protocol 1.0.4/schema 1.2.0. Only this new run is proposed; accepted runs and canonical documentation remain unchanged.

## Reconciling the predecessor experiments

Read merged [#66](https://github.com/jf-stargate/i76/pull/66) / run `i76exe-20261030T020552Z-41acec02`, merged [#67](https://github.com/jf-stargate/i76/pull/67) / run `i76exe-20261030T020546Z-e1909f11`, and synthetic consumer run `i76exe-20261023T062154Z-62e3a718`: manifests, findings, reports and source. Their listed artifact hashes were independently checked. The camera public verifier passed 9,220 assertions. Their evidence is context, never concatenated into this run's integrated trace.

#66 used one **unselected** stock bus at controlled Z=+50, original projection's initial identity view, and original depth globals zero. #67 used a **selected** native-root bus/GTSi with original VLOC attachment, supplied active entry, two or more explicit camera callbacks and retained smoothing. The earlier consumer used a synthetic leaf kind-6 envelope, body owner, +0x38=1 and synthetic view; its primary-pass result does not describe a producer-authored root record.

A selected camera owner alone is insufficient here: original producer camera-owner exclusion prevents its ordinary kind-6 record. This experiment therefore constructs **two separate original bus roots** in the same memory, preserving the selected camera owner and adding an unselected visibility target. It never changes the selected vehicle's status into an unselected status. Both statuses come from original spawn-status instructions; both VCF graphs and registry entries come from original routines. The geometry resource cache may share the original parsed GEO pointer across vehicles; their root and body nodes remain distinct.

An exploratory selected-only test and target identity/180-degree orientations did not establish the desired kind-6 polygon path. The final predeclared replay uses a controlled 90-degree target orientation; the accepted synthetic consumer is an **external baseline only**, not a synthetic case inserted into this integrated run. Its primary leaf selector is not copied into the real secondary root record.

## Single-state fixture and chronology

Each case starts a fresh `EmulatorHelper`. Original math seed `00493C50` executes before construction. The selected bus root `26000000` is constructed by `0045EBD0`, given documented class-1 staging bindings, selected through original `00451452..0045148B`, loaded from original `nobus1.vcf`/`vxbus.vdf` by `004AD6F0`, and registered by `004572B0` at `00542830`. Root translation is zero; original identity basis is retained. Original VLOC `27000800` survives; active entry `004C2908`, frame delta 0.016, velocity-like inputs (2,0,1), and integer angle inputs (1,1,1) are supplied as in #67. No selected-player pending init/post or physics step is claimed.

Original `00405970(0)` initializes a controlled 640×480/color-mode-2 viewport once. Two complete direct `00406AB0` callbacks update the same full 472-byte view and smoothing state. The second callback's complete view bytes are retained unchanged through target construction, visibility and consumption. Original camera origin is approximately (-0.407675, 2.022515, 3.470279); basis/history evolves between calls. No initial projection view is substituted after the callback.

Before visibility, original `004466C0` prebinds the selected camera headlight variant 4 using authenticated additional `hdlv_msk.geo`. This removes an otherwise missing optional resource from the producer phase. The target is separately constructed at root `26100000` using original **unselected** spawn policy and the same stock VCF/VDF. Controlled basis rows are `(0,0,-1); (0,1,0); (1,0,0)`, translation `(0,0,+50)`; behind control changes only target Z to -50. Original registration returns `005428A8`, count 2. These are supplied scene poses, not physics-produced movement.

Original `0048F9B0` initializes all arenas and bucket tables using explicit allocator services. Original five allocation sizes are 370000, 128000, 49152, 49152 and 2880. A supplied **frame depth scan bound** sets `006543A4` to float32 4095 before visibility; near remains zero. #66's far=0 sufficed for production but would make the consumer scan only the first bucket. The 4095 bound scans all valid buckets; it is not a bucket index, inserted node or original terrain-derived range. Original consumer later resets near/far to its sentinel extrema. Renderer support scratch pointers `005DD320/24` receive separate buffers; no synthetic camera is installed there.

After these inputs, host writes to the full allocated arena range and queue globals `00654380..006543C7` are forbidden. Host writes to the camera record are forbidden after callbacks. Every scalar and bulk harness memory write goes through the guard. Original instruction steps remain free to write and are observed separately. A host stack setup between explicitly called routines is not a memory checkpoint reload. No other emulator or trace supplies this case's queue.

## Exact ownership and original execution evidence

| Boundary | Measured original state |
| --- | --- |
| World visits `00458086` | Selected owner `26000000` at `00542830`; unselected target `26100000` at `005428A8` |
| Target classifier `00472C10`, return `0045829B` | Finite registered sphere transformed through the retained camera; result 0 |
| Stores `00458677/88/90` | Kind 6 / root owner / registry entry written to `38015540+0x0C/+0x1C/+0x40` |
| Original insertion `0048FE10` | Kind-6 record `38015540`, bucket 44, bucket address `3808F0A0`, table base `3808EE90` |
| Record link | Original insertion links +0x14 to following kind-10 `38015584`; original cursor ends `380155F8` |
| Consumer dispatch `0048F4C0` | **Same** `38015540`, owner `26100000`, entry `005428A8`, view `004C2730`; +0x38 remains 0 |
| Traversal `0045D530` | Receives original record substructure `3801555C`, not a fabricated primary envelope |
| GEO builder `0045CBE0` | Actual target child `27006800` in target's original +0x64/+0x60 child chain; GEO `36003CD0`, retail `xb11bdym.geo` |
| Original wrappers `00471FD0` | Two kind-6 four-vertex polygons, in original depth-tree order; separate kind-10 eight-vertex polygon |
| Original clearing `0048FCFE/0048FD07/0048FD10` | Bucket count, tail and head become zero; original cursor returns to `38015540` |

Kind-6 stride is 0x44; kind-10 stride is 0x74. The public event file records **changed dwords after original instructions retire**, not every write of identical bits. The verifier replays these changes from the allocator's zero bytes to reconstruct both produced and consumed 0xB8 bytes. The first record's +0x14 link is checked after all production, not incorrectly compared to the first insertion's earlier unlinked snapshot.

Source GEO has 16 vertices and five parsed four-corner sections. The native vertex-array hash exactly equals source bytes `xb11bdym.geo+0x24..+0xE3`: `31d85d852950cc079175612da560b3aa0054ac187d1cf8a3fd435e19fff55468`. Independent Python transforms all 16 source vertices through the measured original body/world matrix and persistent view, then checks emitted quad positions are actual transformed source vertices. Two original nonempty scratch records reach wrappers unchanged, in reversed depth-tree order. Original material lookup is `V1 MD RT.MAP`; VQM/M16 acquisition returns null, so original fallback produces untextured wrapper flags `0x101` from source scratch flags `0x115`. This is an explicit output boundary, not texture decoding.

## Kind-10 lifecycle, including the rejected attempt

The selected camera owner's original headlight path first prepares kind 10 at current cursor `38015540`, owner `27000E00`, and calls insertion with depth **-5**. Original insertion rejects it: no bucket membership, count or cursor advance. Original kind-6 production subsequently reuses that address. This short-lived kind-10 scratch record must not be confused with the later accepted kind 6 merely because addresses agree.

The target's original headlight then creates **accepted kind 10** at `38015584`, owner `27006600`, same bucket 44, linked after kind 6. Its +0x40 is matrix data, **not** the kind-6 registry-entry field. Original `0048FAC0` clears its +0x3C at `0048FCCD` before dispatching `00490640`; the changed bytes are accounted for, not treated as ownership corruption. Original `HEADLT.MAP` lookup and one eight-vertex `00471FD0` wrapper follow. Its supplied clip/draw targets `0047BF00/0047D110` differ from the kind-6 pair `0047C8D0/0047CE40`. Neither path executes a native rasterizer here.

## Controls, verification and limits

| Independent fresh process | Registered roots | Accepted records | Downstream wrappers |
| --- | ---: | --- | --- |
| visible | 2 | kind 6 + kind 10, bucket 44 | two quads + one kind-10 octagon |
| repeat, separately imported project | 2 | identical original records/addresses | full private trace byte-identical |
| behind, only target Z=-50 | 2 | none; target classifier rejects | none |
| empty | 0 | none | none |
| camera_only | 1 selected | none; ordinary camera owner excluded | none |

Behind and camera-only still execute the **rejected -5 kind-10 scratch attempt**. Their cursor and bucket tables remain unchanged; “no accepted records” does not mean “no producer stores.” Empty has no camera callback and is a zero-world baseline, not a fake initialized camera case.

Full independent verification passes **1,402 assertions**: private identities, 65 source fixture checks, original PE instruction/dispatch anchors, callback byte chronology, view transforms/frustum, exact queue record and bucket ownership/lifecycle, source GEO positions, output handoff, negative cases and full repeat. Public-only verification is also provided. Verifier mutations to consumed owner, retired queue store and camera bytes are each rejected. Trusted-base unit tests pass 38/38. Assertions are not completion percentages.

Private input identities, fixture hashes, sparse opcode anchors and measured probe hash are in `evidence/provenance.json`. All three accepted PE/ZFS/GZF hashes match. Final reproduction uses fresh read-only imports in owned scratch, Ghidra 12.1.4/OpenJDK 27-ea. One inherited optional geometry-name null read at `004461E0` remains in each nonempty process. An explicitly supplied emulated Windows SEH segment avoids an uninitialized FS read at the polygon wrapper; it is not a native OS environment. Construction still supplies optional resource/material/weapon services and incomplete stock geometry dependencies; this is a bounded stock-bus shell/body path, not a complete vehicle render or M06 scene.

This supplies the bounded M-RND-03 / G-RND-03 integration evidence for review. It does not close RND-R2, full RND-I1, RND-RESEARCH/INTEGRATED/PRODUCT-v1, M-RND-04, terrain/material/image gates or selected-player gameplay integration. Human scientific acceptance and separate documentation promotion remain required. No merge is performed.
