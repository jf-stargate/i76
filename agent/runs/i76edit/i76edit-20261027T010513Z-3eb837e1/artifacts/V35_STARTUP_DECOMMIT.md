# Original editor CRT startup, native decommit and region shutdown (v35)

Status: append-only proposed original-binary research. Original base main 34a15f060ff585a085619defeffca2fe20969609; accepted protocol 1.0.3. Builds on independent proposed editor SBH PR #43, without touching its branch or any canonical docs.

Original private BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private annotated Ghidra 12.1.4 I76EDIT.EXE.gzf SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. All code runs were read-only original i386 Ghidra emulation, with synthetic Windows HeapCreate/Destroy and VirtualAlloc/VirtualFree returns only.

## 1. Original executable default and entry

PE initialized data at 00438674 contains 0x000001e0 = 480 bytes, rather than a harness-configured threshold. Original executable entry routine 00424181 calls CRT __heap_init 00424F00, which calls HeapCreate(1,0x1000,0) then native ___sbh_new_region 00424FB0. The original code setter 00424F90 writes the threshold if requested value rounded to 16 is at most 0x780; the annotated Ghidra reference manager found no static executable callers of this setter. This does NOT prove an external or indirect call could never change the threshold.

With threshold left UNMODIFIED in original emulated PE memory, native 00424F00 requested 4MiB VirtualAlloc reserve, then 64KiB commit; original CRT initialized page descriptors. Native malloc(120) allocated pointer 0x50000100 using the small-block heap (free units 240->232), native _free restored 240. Win32 HeapAlloc fallback was not invoked in these fixtures. The pointer 0x50000100 and heap handle 0x22220002 are synthetic addresses returned by isolated OS services, not original runtime addresses.

## 2. Native single-page decommit, shutdown and initialization failure

Native _free of the one 128-byte block increased global count of newly fully empty pages at 00438670 from zero to one. An EXPLICIT call to original ___sbh_decommit_pages(1) at 00425180 decommitted page 15 (0x5000F000) using VirtualFree(page,0x1000,MEM_DECOMMIT=0x4000), marked page descriptor 0xff and returned count to zero. Native CRT heap termination 00424F40 requested VirtualFree(region,0,MEM_RELEASE=0x8000) and HeapDestroy. When the initial 64KiB VirtualAlloc commit was made to fail, original 00424FB0/00424F00 requested release of its preceding 4MiB reservation and destruction of the CRT heap, returning failure. Synthetic OS APIs never released real host memory.

## 3. Natural threshold-triggered reclamation with 931 original allocations

A separate Ghidra script entered native __heap_init with PE default threshold 480, then executed 931 original CRT malloc(120) calls, retaining ALL live pointers. Each allocation rounds to 128 bytes (8 of the 240 16-byte page units). Pages 0..30 each held 30 blocks; page 31 held one block. The original allocator issued a SECOND 64KiB VirtualAlloc commit at 0x50010000 when crossing beyond the 16 initially committed 4KiB pages. A preliminary stub returned the WRONG address for this second commit, causing an invalid Win32 fallback; that rejected harness attempt was corrected by returning exactly the requested commit address. It is not evidence of retail fallback.

Freeing all 931 pointers through original CRT _free sequentially raised original 00438670 by one for each newly emptied page. When it reached 0x20 (32), original 004252FD itself invoked 00425180(16), without an injected counter or manual function call. Native page reclamation requested SIXTEEN 4KiB VirtualFree decommits, descending pages 31..16, and reduced the global count to 16. Native descriptor states were 0xf0 for committed now-empty pages 0/15 and 0xff for decommitted pages 16/31. No allocator internals were substituted; only Windows API calls were intercepted.

We then EXPLICITLY invoked original decommit(16) on the remaining sixteen fully empty pages. Native 00425180 found the entire 1024-page region decommitted, invoked original ___sbh_release_region 00425120, requested a single 4MiB MEM_RELEASE and cleared sentinel region state. Native CRT termination then destroyed the CRT heap and did not request a duplicate region release. The second decommit group was a DIRECT controlled experiment, not a naturally scheduled _free batch.

## Validation and limits

Local private checkpoint: i76_editor_v35_crt_startup_20261027.zip, SHA256 193c98b07a68b922cb8a2a400036a8309e92f346a45216f7ba4124b79182f5d0. Contains exact V35NativeStartupLifecycle.java / V35ThresholdSweep.java original-code scripts, static Ghidra xref inventory, unabridged synthetic Win32 call transcript, detailed report and 48/48 assertions including original PE/GZF identity and 26 original instruction anchors. This proposed GitHub run includes a public short native-byte verifier and aggregate evidence; full exact emulator source remains with the private checkpoint, so reproducibility is PARTIAL.

Original Win32 heap and virtual memory calls were substituted. No Windows editor process, real OS memory manager, full CRT startup/exception environment, malformed allocator state, other SBH region-list stress or editable .I76 authoring/workspace export was executed. Not a reimplementation of original code or assertion of source-file ownership.

Next: original decommitted-page recommit after resumed allocation, second SBH region lifecycle, CRT failure behavior with forced VirtualAlloc errors, and eventually editor authoring roundtrip with a genuine workspace.
