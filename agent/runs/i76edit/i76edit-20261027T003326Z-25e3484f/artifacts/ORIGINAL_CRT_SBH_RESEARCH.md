# Original I76EDIT.EXE small-block allocator, region bootstrap and workspace-object lifetime

**Status: proposed research evidence, not canonical documentation.** Pinned `main` SHA `34a15f060ff585a085619defeffca2fe20969609`, accepted publication protocol 1.0.3. Extends merged editor v31/v33 lifecycle work, including PR #41. No original editor or game reimplementation was performed.

## Input identity and evidence

Private original `BUILDER/I76EDIT.EXE` MD5 `4c7ed9e8a54fcadbf1895f34aa9918fe`, SHA256 `69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df`. Private annotated Ghidra 12.1.4 `I76EDIT.EXE.gzf` SHA256 `792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f`. Original x86 program imported read-only without reanalysis and checked against PE native disassembly. No proprietary binaries, game resources or GZF are committed.

## Region bootstrap: native CRT, OS VirtualAlloc isolated

Original `00425310` (CRT SBH allocator) calls original `00424FB0` to obtain a region when none exists. The ORIGINAL `00424FB0` instructions issued two Win32 VirtualAlloc calls: reserve `0x400000` (4 MiB; MEM_RESERVE 0x2000; PAGE_READWRITE 4) and initial commit `0x10000` (64 KiB; MEM_COMMIT 0x1000; PAGE_READWRITE 4). Only Windows VirtualAlloc responses were synthesized, with returned region address `0x50000000`. Original instructions initialized CRT descriptor/list fields at `00437E58`, descriptor region pointer at offset `+0x810`, per-page counters and 16 committed page headers. These were NOT manually preinitialized in the final experiments.

The region has 1024 4-KiB pages. Each committed page contains 256 bytes of allocator bookkeeping and 240 allocatable 16-byte units (3840 payload bytes). Per-page free capacity is tracked at descriptor `+0x10+page_index`; another per-page metadata byte is at `+0x410+page_index`. Further commit/decommit and region teardown instructions exist, but are not claimed as dynamically validated here.

## Native allocation, free and reuse

The original CRT chain `004232E0 -> 00423300 -> 00423350 -> 00425310 -> 00425590` allocates a 120-byte editor payload as 128 bytes (8 units). Original `00422FA0 -> 00425260 -> 004252C0` locates the owning region/page and releases the allocation. All CRT allocation metadata, size markers, free counters, owner lookup and block selection were managed by ORIGINAL instructions.

Observed first two payload addresses: `0x50000100`, `0x50000180`; free-unit counter changes 240 -> 232 -> 224. Freeing the first payload restores eight units and clears its size marker from 8 to 0. A subsequent allocation initially used a later free block (`0x50000200`), rather than immediately reusing the first pointer.

A full page accepted exactly **30 unique 128-byte blocks**. Once 30 occupied the page (free-unit counter 0), freeing one and allocating again reused its precise freed address, `0x50000280`. Returning all blocks restored page free-unit counter to 240.

An additional **31-live-block** run assigned 30 blocks to page 0 and the 31st at **`0x50001100`** on page 1. After all 31 original CRT free calls, both page free-unit counters returned to 240. The second page was already committed by the original 64-KiB initial commit: no further Windows VirtualAlloc call was needed.

## Normal workspace-object constructor -> native CRT SBH -> destructor

A second independent read-only Ghidra script executed ORIGINAL constructor `00409840`, original zone creation and native 12-byte node insertion `0041C430`, original CRT SBH allocator/initializer, original deletion loop `00409DC0`, original destructor `00409A60`, original unlink `0041C480`, and ORIGINAL CRT free `00422FA0`/owner lookup `00425260`/small-block release `004252C0` in **one emulator instance**.

Native CRT payload pointer was `0x50000100` and separate node pointer `0x70004100`. The Windows VirtualAlloc 4-MiB reserve and 64-KiB commit, Windows HeapAlloc for the 12-byte node, its Windows HeapFree, and a display refresh were the ONLY substituted services. The Windows heap service never handled the object payload. The constructor set the zone-0 list head to the node; after original deletion the list head was zero, payload block marker cleared 8 -> 0 and original free-unit counter restored 232 -> 240. The node's OS heap free was observed once.

## Validation and exact scope

Private reproducibility checkpoint: `i76_editor_v34_native_sbh_20261027.zip`, SHA256 `1b5b2d3f8e06c04b9cfa1380fe706eb91fee9c510eb4bae57d8632c1c78e5a94`. Contains the **exact executed** Ghidra Java scripts `V34NativeReserve.java`, `V34CtorNativeSbh.java`, independent manually initialized-page control `V34SbhRoundTrip.java`, native execution traces and a Python private-PE opcode / trace validator (**45/45 checks passed**). The checkpoint itself contains no original binary/GZF. This GitHub run documents the findings, aggregate evidence and publicly reproducible opcode checks; direct exact Ghidra script reproduction also requires access to the private checkpoint and private editor/GZF baseline, so run reproducibility is marked **partial**.

Do not infer actual Windows virtual-memory bookkeeping, production SBH activation threshold, default CRT startup globals, real heap allocation failure behavior, or full-editor UI integration. Per-page decommit, region cleanup, allocation failures, malformed allocator metadata, concurrency and genuine editable `.I76` workspace exports remain untested. The synthetic pointer values are test fixtures, NOT original static addresses.

Next reverse the original CRT startup path initializing `00438674` and `00438668`, test page commit/decommit and full-region cleanup with an isolated OS boundary; later validate original editable ROAD authoring/export when the workspace is available.
