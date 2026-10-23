# Original editor object teardown and CRT heap ownership (v31)

Status: proposed original-instruction research, not canonical. Pinned main f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a; extends separate v30 compaction PR #33.

Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA-256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private read-only Ghidra 12.1.4 annotated I76EDIT.EXE.gzf SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Original native disassembly and Ghidra decompilation cross-checked.

## Allocation provenance and destructor

Original constructor 00409840 requests a 0x78-byte workspace payload with CRT _malloc at 00409881; it inserts the payload via 0041C430, which separately allocates a 0x0c-byte doubly linked-list node through HeapAlloc (node heap handle 00436994). Node fields +0/+4/+8 are next/previous/payload pointer, and payload +0 is zone ID.

On zone removal, 00409DC0 saves the next node pointer at 00409DD4 BEFORE invoking 004010BE -> 00409A60. The original destructor reads payload pointer node+8, obtains zone ID from payload+0, calls original 0041C480 through thunk 00401500 to unlink and HeapFree the node, then calls CRT _free at 00422FA0 on the separate payload. The original _free invokes CRT small-block finder 00425260; nonzero lookup selects CRT small-block free 004252C0; lookup miss selects Windows HeapFree on the payload using CRT heap handle 016424F0. Node and payload therefore have separate allocation and release domains.

## Direct original x86 emulation: seven cases

Ghidra EmulatorHelper executed original 00411BE0 zone compaction, 00409DC0 list traversal, 004010BE -> 00409A60 object destructor, 0041C480 native unlink, 00422FA0 native CRT _free branch logic, 00409E00 moved-list rebinding, native original slot allocator and readback. One deleted-zone fixture contains two linked objects. A separate surviving last-zone fixture has two linked objects to be moved from zone ID 2 to 1. Original functions, native list links and memory-copy operations execute.

Isolation boundaries: Windows HeapFree IAT 01644538 is redirected to a synthetic stdcall callback that verifies heap handle, flags and pointer, then poisons the 12-byte node or 0x78-byte payload test allocation. CRT ___sbh_find_block (00425260) is intercepted to select miss or synthetic match, and when matched ___sbh_free_block (004252C0) is intercepted at its entry to count service calls. The ORIGINAL CRT _free branch instructions execute in both cases. Status/UI refresh and InvalidateRgn are substituted as in v30. The Windows heap manager, CRT heap metadata and actual allocation/free bookkeeping are NOT executed.

With small-block lookup miss: exactly 2 node HeapFree calls with node handle 0x11110001 and 2 payload HeapFree calls with distinct CRT handle 0x22220002. Native release order: node A 0x70003400, payload A 0x70003500, node B 0x70003800, payload B 0x70003900. With forced small-block match: 2 node HeapFree calls, ZERO payload HeapFree calls and 2 CRT small-block release service calls. Both branches complete successfully; the surviving moved-zone object list and both payload zone IDs remain correctly rebound. Five other zone-control scenarios produce zero heap releases. Original 00409DC0 loop terminates normally in both multi-object deletion cases. Poisoning at the substituted free boundary did not disrupt these tested original-code traversals; it is not a general absence-of-UAF proof.

## Checks and limitations

Exact private original PE hash verification and 62/62 selected native instruction opcode guards passed. Seven original-x86 execution scenarios completed, with 87/87 compaction, metadata, zone-map and surviving-object reference assertions plus explicit two-heap routing and CRT-branch checks. The full unabridged Java Ghidra test harness, native opcode script, trace validator, seven synthetic traces and detailed report are in conversation checkpoint i76_editor_v31_object_teardown_20261023.zip (SHA-256 8fee32fdadb05a47a9f086f711d5379abdd65c7e337b3e49f38db18705c7edf6). Public record is partially reproducible without private PE/GZF and checkpoint bytes.

No full original Windows editor UI, CRT small-block allocator internals or Windows heap calls were executed. Object construction's original _malloc and HeapAlloc were verified statically but not executed in this experiment. Only well-formed 2-node deleted/moved lists and consecutive zone IDs 0,1,2 were tested; corrupt lists, allocator errors, duplicates, and full 80-slot stress remain open. Editor object records in this path are not retail game scene/vehicle objects. No evidence of a user-visible crash is claimed.

Next trace native object creation with isolated allocation callbacks to prove object allocation->list insertion->zone deletion as one original-code lifetime; test safe malformed-list cases and sparse zone-ID histories; await genuine editable .I76 workspace for actual authoring/export validation.
