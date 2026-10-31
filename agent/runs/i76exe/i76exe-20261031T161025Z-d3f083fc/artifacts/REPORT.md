# M-RND-11 — unified original M06 terrain and stock-vehicle submission

**Bounded positive:** one retained original-instruction emulator and persistent original camera produce identifiable terrain and vehicle records in the same original arena. Their distinct original consumer paths execute, and original cleanup resets the arena. This completes the assignment's contribution-ownership/submission question under declared services. It does not establish a full retail frame, native drawing, pixels or RND-v1 completion.

Run i76exe-20261031T161025Z-d3f083fc; protected base6d151459f92b75aaadd5221dc8edd8e4776651ff; protocol1.0.4/schema1.2.0. One owned run, no canonical/governance/shared/accepted-run changes. No M-RND-10 dependency. Exact runtime model/thinking/token identifiers are not exposed.

## Baselines and corrected common ownership

Complete unchanged #76 reproduces89,114 checks, including #74/#69; unchanged #70 complete driver and standalone source-backed verifier reproduce1,402 checks. Full accepted #67/#70/#74/#76/#75/#77 reports, probes and service interfaces provide lineage; no records or images are transplanted from them.

#70 supplied near0/far4095 and separate GEO scratch. #76 supplied distinct terrain XYZ/aux/leaf buffers and derived depth bounds. Retail startup instructions resolve actual source backing:00402F98 requests108000 bytes,00402FAC installs XYZ,00402FC5 adds0xD2F0,00402FD4 installs auxiliary alias;00402FD9 requests524288 bytes and00402FE3 installs leaf/GEO backing. The final unified probe executes this exact block to00402FF7 with pointer-only allocation services. This corrects the exploratory independent auxiliary backing in the unpublished checkpoint. No live geometry is moved or zeroed to resolve it.

See MEMORY_OWNERSHIP.md for every range/classification and SERVICE_LEDGER.md for services. Original constructors and registry own two stock-bus graphs over supplied heap backing. Camera root is selected, target is separately unselected; original spawn-status blocks set those statuses. Controlled primary roots are camera(2952.5,60,48152.5), target(2952.5,60,48202.5), target basis(0,0,-1;0,1,0;1,0,0). These are not mission spawns or physics-produced poses.

## Exact retained lifecycle

Original math startup and construction/registration precede original projection00405970 and two00406AB0 callbacks. Supplied viewport640x480/max639,479 and bounded time/velocity/angles drive original camera writers. The full472-byte004C2730 record remains byte-identical thereafter. M06 WRLD/TDEF/TER mapping executes on authenticated licensed resources in the same emulator; no second terrain view is authored.

Original scratch installation precedes one0048F9B0 arena initialization. Original00490A00 terrain runs, followed by00457FF0 vehicle visibility and0048FAC0(view,1) consumption. This follows software-frame callsites00401DE1/00401E2C/00401E8D. The frame itself and intervening roads/skids/flamer/dust/tracer/HUD/particles/sky/device/timing passes are omitted explicitly. There is no live arena reset between producers.

Primary terrain produces171 source vertices,79 adaptive leaves,181 polygon attempts and30 accepted records in10 bins/3792 bytes, cursor48000ED0. Source page/row/column/packed-height/material, shared-edge leaf indices, original emitter XYZ and independent near/far/screen clipping identify every accepted polygon. Original terrain initializes min=-300 and source-derived max, rather than installing #70's4095 bound.

Visibility adds camera-owner kind10 at48000ED0, target kind6 at48000F44 and target kind10 at48000F88; cursor48000FFC. The camera-owner depth-5 record is now accepted because min=-300; #70's near0 rejected it. This is original insertion behavior, not an ownership anomaly. Original kind6 owner26100000/registry005428A8 reaches0048F4C0, secondary0045D530, original0045CBE0 body27006800 and authenticated xb11bdym.geo, then two original polygon wrappers. GEO source16 vertices are independently transformed through the actual body/world matrix and persistent view; nonempty GEO scratch positions are source-owned.

Terrain records have positive vertex count and take the consumer's direct polygon submission branch to00471FD0. Zero-count kind6/10 take retail dispatch-table targets0048F4C0/00490640. All30 terrain records reach original submission, all three work records reach original typed dispatch, in exactly reconstructed descending-bucket/link order. Terrain copies its clipped vertices into polygon storage before vehicle consumption reuses source XYZ/leaf scratch; no queued terrain bytes depend on surviving leaf scratch. Kind10 +3C clearing is original. Original0048FD6D clears primary buckets,0048FD7B resets cursor to48000000,0048FDE2/DEC reset depth sentinels. Original cleanup argument1 also clears its effect-list state.

## Independent controls and verification

| Case | Terrain | Kind6 | Kind10 | Outcome |
|---|---:|---:|---:|---|
| primary |30|1|2|Original submission/dispatch and cleanup|
| target absent |30|0|1|Terrain remains; camera-owner light remains|
| target behind |30|0|1|Original cull excludes target|
| camera/root X+200 |13|1|2|Second valid coherent view|
| both roots Y=-100 |0|1|2|Original terrain rejection; vehicle remains eligible/consumed|

Fresh-GZF repeat matches complete primary trace and17 sidecars byte-for-byte. Deliberately changing consumed kind6 owner26100000 to26100100 is rejected by the standalone semantic owner check. The verifier never invokes Ghidra or imports producer code.

Complete final standalone result:131,751 checks, including89,098 independent terrain/camera/source/clip checks. Remaining checks authenticate required retail opcodes/dispatch tables, reconstruct typed bucket chains and original mutation chronology, verify record headers/owners through dispatch, source GEO transforms, exact consumer order, five controls and fresh equality. Fixture/PE/GZF/ZFS/MSN/TER identities are authenticated; sparse executed anchors independently match retail PE and source audit compares complete executable sections. Counts exclude predecessor and trusted-unit tests. Source numerical tolerances retain #76's local float32 clipping/projection rules and #70's GEO transform bounds; integer/bytes/ownership/order are exact. See scripts for executable checks, results.json for private trace digests and selected_events.tsv for bounded review events.

## Last measured output and first missing prerequisite

Original terrain polygon submission and vehicle GEO/polygon preparation are verified. Consumer clip/draw callbacks still use declared inherited copy/success services; original terrain header material token0xB4 is not established as a valid texture. No native command, raster, palette, UV/texture or framebuffer claim is made. The next original M06 rendering prerequisite is authenticated terrain material/output initialization and advancing those original downstream consumers without substitution. Full-frame peripheral scheduling remains outside this bounded subset. The observed positive is a shared camera/arena lifecycle, not retail-frame or image equivalence.
