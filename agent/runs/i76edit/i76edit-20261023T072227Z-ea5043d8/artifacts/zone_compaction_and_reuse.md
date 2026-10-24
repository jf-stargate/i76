# Original I76EDIT.EXE native zone-release/compaction (v30)

Status: proposed research only. Pinned main f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a. Extends open v29 PR #31. Does not modify accepted reference material.
Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df.
Annotated private Ghidra 12.1.4 original I76EDIT.EXE.gzf SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f.

## Native instructions executed and substitutions

Ghidra EmulatorHelper executed original 00411BE0 release/compaction, 00409DC0 linked-list cleanup/iteration, 00409E00 moved-object list reassignment, original 004117F0 repeated-dword fill, original 00411B30/004125A0 slot reuse, and original 0041F150/0041F2B0 readback. Synthetic 80x80 zone map, occupied headers, all six terrain planes, linked-list nodes and 200-byte auxiliary records were supplied. The x86 DF flag was initialized to zero.

Intercepted side effects were original status-text thunk 00401073, display/height-view refresh thunk 0040124E and Windows InvalidateRgn at 00411FF2. Only in a fixture containing an object in the deleted zone was downstream destructor thunk 004010BE intercepted; therefore object destruction and heap ownership were not verified. The original relocation helper DID execute for objects moved from the surviving last slot.

## Observed release and exact block contract

For contiguous occupied IDs 0,1,2: deleting ID 1 returned 1 and changed zone map [0,1,2] -> [0,255,1]. Deleting ID 0 -> [255,1,0]. Deleting highest ID 2 -> [0,1,255]. Deleting nonexistent ID 9 returned 0 and preserved fixture state. The original code copies the last occupied slot into the removed slot and clears the previous last slot, unless the removed slot was last.

For each move the original rep movsd copied all 0x2001 dwords = 0x8004 bytes of SIX terrain planes: P0 base 009BC820, P1 00EBCAA0, P3 00C3C960, P4 013BCD20, P2 0113CBE0, and work plane PW 0043C550. All bytes were verified against the former last slot. The auxiliary zone record is exactly 200 bytes starting at 0163CE70 + 200*slot; the original code uses an interior base+2 reference but moves the entire record. A preliminary incorrectly aligned 200-byte fixture was fixed before these final tests.

Freed-slot reset dwords are: P0 zero, P1 0x00010001, P3 0x00630063, P4 zero, P2 0x80008000 with its slot header zero, and PW 0x80008000 including its header. Every dword of every freed plane and every byte of its 200-byte metadata was verified. The zone-map entry is set to 0xff; the base-height P0 slot header is zero.

The original object-list helper 00409E00 moved the source-zone list head to destination, cleared the source head, and updated stored zone IDs from 2 to 1. Tested with a one-node list and a TWO-node linked list. The deleted-zone list iteration reached its destructor thunk in one fixture; only that destructor was replaced.

## Reuse and original getters

After deleting ID 1, the original allocator 00411B30 created zone-map location (3,0) in the now-free slot ID 2; it marked its P0 header occupied. Original surface getter 0041F150 returned default material 1 for a cell in the reused zone, and original selector-100 height getter 0041F2B0 returned missing-height sentinel 0x8000 (32768). Only UI refresh was intercepted.

## Evidence and limitations

The private local checkpoint contains exact tested V30NativeZoneCompact.java, original-code synthetic trace and validators. Six native release scenarios yielded 71/71 full-block/metadata/object-reference assertions. Separately, 37/37 fixed original PE opcode anchors passed; reuse and native getters had additional explicit checks. The public record includes aggregate results and native-byte verifier; original Ghidra harness remains in private downloadable local checkpoint, so reproducibility is PARTIAL.

Noncontiguous slot occupancy, duplicate/corrupt maps, full 80-slot recycling, true object heap/destructor behavior, original Windows UI and authentic editable .I76 authoring/export inputs remain UNTESTED. One no-match branch calculates a byte address beyond the nominal 6400-byte map before returning; practical impact is unknown. No original C filename or translation unit is recovered. These integer/memory-copy tests do not depend on disputed Ghidra x87 behavior.

Follow-up: execute 00409A60/00422FA0 object destruction with isolated heap services, and verify sparse/free-zone histories and original authoring export once genuine editable .I76 workspaces are supplied.
