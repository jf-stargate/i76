# Original I76EDIT.EXE CRT allocation and constructor lifecycle

Status: proposed original-instruction research (not canonical). Original accepted base main 61c9b3b425010615755a18302cb27068850377c6; protocol 1.0.3. Follows accepted v31 teardown run i76edit-20261023T153200Z-64b4e9ad (PR #35) and private v32 constructor checkpoint.

Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe, SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private annotated Ghidra 12.1.4 original I76EDIT.EXE.gzf SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Read-only project, no autoanalysis.

## Native allocator call chain

Original editor constructor 00409840 calls CRT _malloc at 004232E0 with a 0x78-byte (120-byte) payload request. Wrapper 004232E0 passes retry mode global 00438678 to 00423300. CRT 00423300 rejects sizes above 0xFFFFFFE0, substitutes one byte for a zero request and retries failed allocations only when new-handler mode is enabled and original 00426230 obtains a nonzero callback result from callback global 0043C158.

Original CRT 00423350 rounds size up to a 16-byte multiple with (size+15)&~15. For the editor object payload the resulting actual request is **0x80 (128) bytes**. If the rounded size is within the configured small-block threshold at 00438674, 00423350 first calls original 00425310 with size/16 (=8) units; a failure falls back to Windows HeapAlloc IAT 016444AC, flags 0, CRT heap handle 016424F0. These globals were *configured synthetically* for the tests; actual original editor startup CRT threshold and heap state have not been established.

## Original machine-instruction execution, eight independent allocator cases

Ghidra 12.1.4 EmulatorHelper executed ORIGINAL 004232E0/00423300/00423350 and ORIGINAL 00426230 new-handler dispatcher. Only CRT small-block allocator 00425310, Win32 HeapAlloc, and the application new-handler callback were isolated.

- SBH eligible, success: 1 SBH request, zero Win32 allocations, returns pointer.
- SBH eligible, failure then fallback: 1 SBH request and 1 Win32 request, returns pointer.
- SBH disabled: 1 Win32 request, returns pointer.
- Win32 failure and retry disabled: 1 Win32 request, returns null.
- Win32 fails once, callback returns true: 2 Win32 requests, 1 callback, returns pointer.
- Win32 fails and callback declines: 1 Win32 request, 1 callback, returns null.
- Zero-size malloc: normalized to one byte and requests 16 bytes from Win32 heap in tested configuration.
- Size 0xFFFFFFE1: rejected immediately, no allocation or callback.

## Original constructor -> destructor with native CRT malloc

In the SAME Ghidra emulator instance, original 00409840 enters original CRT _malloc, which allocates a synthetic 128-byte payload through the original Win32 HeapAlloc dispatch; original 00411BA0/00411B30 allocate/reuse zone ID 0; original 0041C430 allocates a distinct 12-byte linked-list node; original constructor initializes payload and inserts node. After construction, original 00409DC0 -> 00409A60 -> 0041C480 -> 00422FA0 runs the original unlink/destructor/CRT _free branches. Recorded release order: NODE 70004100, PAYLOAD 70004000; final zone list head null. Original CRT small-block *lookup on free* and final heap free services are substituted; native branch decisions are not. The experiment is original-instruction execution with synthetic services, not full Windows heap execution.

## Allocation-failure ownership gap

With original CRT malloc returning a valid 128-byte synthetic payload and subsequent 12-byte node HeapAlloc returning null, original 0041C430 returns null; original constructor writes null list head and returns. Breakpoints at original CRT _free 00422FA0 and the HeapFree callback did not fire *during this constructor call*. This establishes an unchecked failure-path cleanup gap in native control flow, but **not an observed retail Windows process leak**; real heap bookkeeping, exception handling and allocation-failure likelihood were not measured.

Independent static native disassembly at 00409881 -> 0040989A shows that constructor payload fields are written without a null check after _malloc. Earlier v32 null-malloc emulation allowed writes to low addresses; it cannot prove the precise original Windows fault outcome.

## Evidence / limits / future tests

Private local v33 checkpoint: i76_editor_v33_crt_lifecycle_20261026.zip, SHA256 1578289fe63e8f0396a6094c300b42cbef30b4450960541b0f7cb2460edac17e. Contains exact Ghidra Java script, full eight-case trace, execution log, validator, 32 native opcode signatures and Ghidra/input hashes. **46/46 checks passed locally**, comprising original byte anchors, case assertions, normal and failure constructors and event ordering. No original binaries/GZF committed. The public run intentionally carries summary evidence and private-checkpoint references, so reproducibility is partial.

Still unresolved: actual CRT SBH threshold and small-block metadata initialization, native 00425310 small-block implementation, actual Windows HeapAlloc/HeapFree runtime, normal allocation failure handling, malformed list/resource ownership, exact authoring/export behavior with a genuine editable .I76 workspace. This research is editor-only, not about retail engine vehicle or scene objects.
