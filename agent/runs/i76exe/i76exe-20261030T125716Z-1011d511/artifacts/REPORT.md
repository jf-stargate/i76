# M-RND-04 — original kind-6 projected-vertex preparation

## Result

**Complete for the scoped target.** Starting with the accepted PR #70 integrated original-instruction case, this run removes exactly one substitute: kind-6 clip/prepare callback `0047C8D0`. The original retail body executes and returns twice on four-vertex polygons built from the original registered stock vehicle and authenticated `GEO` section vertices. The native function writes 96 bytes (four 24-byte projected vertex records) to its supplied output buffer, returns `EAX=4`, and leaves its source array unchanged. Both 96-byte outputs differ from the pre-call buffer, are repeat-identical in a separate fresh process, and have finite screen/depth fields with positive reciprocal depths.

This is original projection/clip-preparation execution, **not a claim that the primitive underwent a clipping-plane intersection**. The measured case kept all four vertices and returned four. The original `0047C8D0` listing divides the view scale by each input vertex depth, multiplies source x/y, adds view offsets, stores projected coordinates and reciprocal depth, and copies an attribute dword; the trace confirms writes to the separate render destination. No framebuffer or pixels are inferred.

## Continuous source-backed state

The positive trace records selected stock vehicle registration at `00542830`, original camera entry `00406AB0` and view `004C2730`, separate unselected bus registration `005428A8`, producer completion, original kind-6 record traversal and `GEO` owner `27006800`, then original polygon wrapper `00471FD0`. At wrapper time, its actual retail dispatch table selects `0047C8D0` for the observed kind-6 flags `0x101`; the first native call's source is `2D000528`, output is `3001C76C`, and view is `004C2730`. The second call uses source `2D000480` and the same destination. The consumer-owned queue and source geometry are not host-written after producer/consumer sealing. Evidence is in `evidence/positive.tsv`; the private full reproduction traces are reproducible but are not published.

## Dispatch reconciliation

The target address depends on the wrapper's mode/table index. `00471FD0` indexes the original clip and draw tables using `flags & 0x1ff`:

- Kind 6, flags `0x101` (index 1): clip/prepare `0047C8D0`, draw `0047CE40`.
- Kind 10, flags `0x80` (index 128): distinct Z/project clip `0047BF00`, draw `0047D110`.
- Earlier mode `0x15` (index 21): distinct lit textured Z/screen clipping `0047C2F0` and draw variant `00487EA0`.

The earlier references do not conflict: they describe another mode. This run retains the kind-10 clip and both draw substitutes; only the kind-6 callback body is original. Exact retail instructions and function identities are preserved in `evidence/retail_instructions.tsv`.

## Control and repeat

The separate `behind` case uses the same probe and fresh emulator reset with the unselected vehicle behind the view. Its kind-6 geometry is rejected before polygon submission: there are no wrapper or native clip events (`evidence/negative.tsv`). A fresh headless process with the visible pose reproduces both native outputs byte-for-byte (`evidence/repeat.tsv`). This control distinguishes visible original projection from a no-submission case; it does not claim coverage of a partially clipped polygon.

## Limits

Licensed EXE, ZFS, GZF and the Ghidra project remain private. The accepted PR #70 reproduction was executed first from a fresh private project and its verifier passed 1402 assertions. This run's exact native probe uses the same read-only annotated GZF and retail EXE. Controlled scene poses/depth range and documented CRT, OS, resource, texture/material, allocation and drawing services remain harness-supplied. Kind 10 clipping and all drawing remain substituted. A Ghidra warning records one inherited uninitialized read at `004461E0` in construction; the exercised polygon path is backed by independently authenticated GEO vertices. No live game frame, hardware raster output, terrain tessellation or full-framebuffer reconstruction is claimed.
