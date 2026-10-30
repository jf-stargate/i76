# M-RND-06 — M06 terrain transform and polygon-candidate handoff

## Result

**Partial, bounded to original pre-clip polygon work records.** Authenticated M06 adaptive leaves survive the original `004937C0` transform, traverse the original `00491A30` walker, and reach original polygon emitter `004922F0`. With an explicitly initialized test-owned polygon-work arena, the original emitter writes 139 candidate polygon work records before calling the original clip routine. Their vertex tuples independently match the transformed source indices and source TER pages.

The original clip callback at `0047BF00` rejects all 139 candidates (`EAX=0`); original bin helper `0048FE10` is never reached. The primary run also shows the allocator prerequisite: original `00490590` reads a zero cursor from `006543C0` and returns null 73 times. No accepted renderer submission, material descriptor mapping, texture, UV, framebuffer, or image is established.

This run does not promote proposed G-RND-05 criteria and does not claim RND-v1 acceptance.

## Controlled view and transform

The probe uses an explicit test view record at `0x45000000`. Its affine basis at record `+0x40` is identity; double translation fields at `+0x68/+0x70/+0x78` are zero for the primary, contrast, and reject cases. This is a controlled numerical input, not a game-produced camera record. The original routine composes the basis with its retail terrain scales (X/Z `5.0`, Y `0.1`) and transforms the original 267-entry vertex buffer in place.

The pool diagnostic uses the same identity basis and translation `(-2860,-28,-47900)` to place the sampled M06 source region around camera-space coordinates near the origin with positive Z. This is still a controlled affine, not an original camera capture. The independent verifier checks both transforms directly against the pre-transform bytes captured at `004937C0` entry.

## Source identity example

One original first-leaf boundary uses source vertex indices `23,20,15,22`. The independent verifier resolves them through the M06 `ZMAP` and authenticated TER page 0:

| Index | Source grid X / low-12 height / Z | TER row / column | Word | Material class | Transformed primary XYZ |
|---:|---|---|---:|---:|---|
| 23 | 568 / 300 / 9608 | 8 / 56 | `012C` | 0 | (2840, 30.0, 48040) |
| 20 | 576 / 309 / 9608 | 8 / 64 | `6135` | 3 | (2880, 30.9, 48040) |
| 15 | 576 / 278 / 9616 | 16 / 64 | `2116` | 1 | (2880, 27.8, 48080) |
| 22 | 568 / 252 / 9616 | 16 / 56 | `20FC` | 1 | (2840, 25.2, 48080) |

Heights above are the low 12 bits scaled by the routine’s `0.1` float. The pool diagnostic retains these IDs through the original callback index list and verifies every emitted XYZ triple. TER material class is source provenance only; no class-to-rendered-texture inference is made.

## Retail instruction path

- `00490EED` calls `004937C0`; the return address is `00490EF2`.
- `004937C0` composes the affine and terrain scale, invokes `0046EDC0`, then writes the transformed XYZ triplets in place. Primary execution reaches the retail return at `00490EF2`.
- The caller skips its extra projection block because `005A4618` is zero in this controlled harness, then enters `00491A30` at `00490F82` with original callbacks `0048E190` and `004922F0`.
- Primary traverses the original leaves and reaches `004922F0` 73 times. Its allocator at `00490590` returns null because `006543C0` is zero.
- In the separate pool diagnostic, a zeroed, test-owned 1 MiB arena is installed at `006543C0`; no original routine body is replaced. `00490590` returns that arena address, and original `004922F0` writes candidate records. Immediately before its indirect clip call, the probe snapshots each 0xB4-byte record at `004923AB`.
- The retail indirect call at `004923B1` reads target `0047BF00`. Each of 139 candidate records is rejected at `004923BE`; the `0048FE10` bin helper is not reached.
- Static retail instructions show alternate emitter `004924B0` loads `0059C558` and `0059C548` into its record, but the primary controlled path does not enter it. `00471F00` selects between a pair of renderer resource handles based on a render-context mode field; no evidence connects that handle selection to M06 TER material bits.

Instruction bytes and function disassembly were read from the authenticated Ghidra import; the full executable section was checked against the authenticated retail PE. See `evidence/instruction_anchors.tsv` and the audit script.

## Controls and verification

- Primary controlled view: 267 vertices, 743 shared edges, 172 adaptive leaves; 267 original transformed vertices; 73 primary emitter entries; null allocator control.
- X-shifted valid view: 97 vertices, 256 edges, 41 leaves; original walker returns.
- Rejected below-height view: original bounds result zero and zero vertices/edges/leaves.
- Pool diagnostic: 139 original candidate records, 139 clip rejections, zero bin calls. Every record count/type and indexed XYZ tuple is checked independently.
- Fresh project imported from the authenticated GZF repeats the primary trace and output byte-for-byte.
- The independent verifier reports 2,501 passed checks. It derives source page, row, column, packed word, height, and material class directly from M06.MSN/M06.TER and does not call emulator code.

## Limits

This is a Ghidra original-instruction emulation with explicit host x87 and OS/resource service substitutions. The view is controlled and not scene-authentic. WRLD/palette setup is incomplete; stock palette resource acquisition reports absent ACT/LUM/TBL resources. The pool diagnostic initializes only bounded record memory; it does not initialize the original game camera, clipping/raster state, or resource descriptors. The original clip routine’s all-rejected result is therefore a measured stopping point, not proof that stock runtime rejects the same polygons. No rendering or physics inference is made.
