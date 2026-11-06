# Original adaptive boundary scans

Run `i76exe-20261106T022650Z-0a1cc64d`, track i76exe, advisory TER/GEO. Base `19c755a77db404ba9cb0ab51f307b4261e983aff`, after merged research [#140](https://github.com/jf-stargate/i76/pull/140) and [#141](https://github.com/jf-stargate/i76/pull/141). Research evidence, pending human acceptance; no canonical promotion.

**Finding F-SCAN:** the four scans retain one page pointer, but ordinary camera-generated adaptive regions cannot cross sample 127 during these scans. This follows from the root phase and subdivision invariants, not an explicit scan-end bound check. Unaligned injected regions demonstrate both wrong-coordinate reads and out-of-backing accesses. These injected regions are diagnostic states, not retail camera outputs.

## Exact address rule

At `00491556`, EBX is half-size h, ESI/EDI are integer center X/Z. The instructions subtract h to obtain origin x,z and set EDX=`2*h-1`. For the normal dyadic regions let side s=`2*h`; EDX starts at s−1. After adding 3072 on each axis:

```
X = x + 3072; Z = z + 3072
grid_slot = (Z & ~127) + (X >> 7)
local_sample = (Z & 127)*128 + (X & 127)
P = pointer_grid[grid_slot] + 2*local_sample
```

`004915CA` performs the single page-pointer load. There is no pointer-grid lookup in the loop. Rows below mean increasing Z in the lattice, without a screen-space top/bottom interpretation.

| Load PC | Register | First byte address | Iteration i address | Byte stride |
|---|---|---|---|---:|
| 004915F7 | EBX | P+2(s−1) | P+2i | −2 |
| 0049160F | EDI | P+258(s−1) | P+256(s−1)+2i | −2 |
| 00491627 | ECX | P+256(s−1) | P+256i | −256 |
| 0049163F | ESI | P+258(s−1) | P+2(s−1)+256i | −256 |

Each iteration reads in precisely the table order. i descends s−1 through zero. A passing scan makes **4s reads**, counting duplicated corners (4s−4 distinct lattice locations for s>1). A triggering word short-circuits the remaining sites and iterations. The loop decrements at `00491655`, steps pointers at `00491656`–`00491662`, and repeats at `0049166A`. This is the perimeter of the **s×s half-open sample footprint** `[x,x+s)×[z,z+s)`, not the inclusive geometric vertex square whose far edges are x+s and z+s. Scanning inclusive endpoints would change refinement.

Each load zeroes EAX first, loads AX, tests EAX>=0x4000, then masks with 0xFFFFE000 and compares to 0xA000. Classes 2,3,4,6,7 trigger; 0,1,5 pass. Bit12 does not affect this predicate. JNZ sites `0049160B/23/3B/53` target `0049166C`; nonnegative EDX proceeds to `00491674` and subdivision. Exhaustion leaves EDX=−1 and `0049166E` jumps to leaf path `004917B4`. The native suite records all conditional next PCs, word values, attempted addresses, and terminal decisions.

## Guards and normal reachability

Earlier in `004911E0`, h>=32 forces a split (`004912F0`), and the post-height guard `00491550` bypasses class scans at side<=4. Thus ordinary class scans have side 8,16,32. Visibility, distance and height decisions can bypass scanning even at these sizes; surface classes do not override an earlier leaf/cull decision.

`004929B0` aligns both root origins with AND ~31, then subtracts32 (`00492CB9`–`00492CC2`). Its side is a power of two. After forced descent to side32, each origin is divisible32; bisection preserves divisibility by each child's side. For s=8/16/32, s divides128 and translation3072 is divisible128. Therefore local origin+s−1<=127 on both axes. `verify_public.py` exhaustively checks all local origin residues, four boundaries and all three sizes (14,336 sample positions). The proof assumes the recovered ordinary root/bisection path and bounded finite source coordinates, not arbitrary direct calls or memory corruption.

The scan's own guard checks origin x,z in inclusive `[0,10240]` via sign bits (`0049156C`–`0049157B`), flattened page slot in `[0,16384)` (`004915A3`–`004915B0`), and local sample index in `[0,16384)` (`004915B6`–`004915C4`). It also checks EDX nonnegative. It does **not** check x+s−1/z+s−1, page-local end, page-pointer identity, allocation ownership, or default identity. Local sample bounds are redundant for ordinary masked coordinates. The inclusive origin10240 accesses default backing in the measured setup and remains aligned. Origin guards alone do not make an injected unaligned region safe.

## Evidence and method

[instruction_anchors.tsv](../evidence/instruction_anchors.tsv): 122 instructions checked byte-for-byte against the authenticated PE; fresh Ghidra import also verifies the entire executable section. [scan_cases.jsonl](../evidence/scan_cases.jsonl) and [results.json](../evidence/results.json): 124 cases on a native i386 CPU, unchanged `00491556` onward, supplied Linux/image/grid environment, guarded before every terrain dereference. Native slice entry deliberately bypasses earlier LOD/height tests, so an unaligned native split is not evidence that the normal caller can generate that state.

[geometry_comparisons.json](../evidence/geometry_comparisons.json): six complete original-instruction Ghidra runs with #140's declared services; each graph, decision, flattened loop, and complete class-read sequence equals the independent bounded oracle. Native scan evidence and emulated full geometry are distinct evidence tiers. No retail Windows, whole-renderer, or native full-geometry claim follows.
