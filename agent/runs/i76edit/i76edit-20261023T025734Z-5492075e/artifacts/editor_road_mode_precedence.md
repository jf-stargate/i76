# Original editor road grading: six-mode precedence contract

Run i76edit-20261023T025734Z-5492075e; status: PROPOSED research, not a canonical accepted milestone. Base e26d643994db8ddd7e9cbde1e2f74fcf16647fce, protocol 1.0.1, research schema 1.1.0. Builds on accepted ref/editor/road_terrain_serialization.md, v16/v20 evidence and the independent editor findings from PR #15; PR #14 and PR #17 are still unmerged proposals.

Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe, SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private annotated Ghidra 12.1.4 I76EDIT.EXE.gzf SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Read-only Ghidra 12.1.4 decompilation/xrefs were cross-checked against the original PE native objdump disassembly. No executable or Ghidra database is committed.

## Original chain and mode state

0040E3C0 (terrain scheduler) -> 00420EE0 (road chain) -> 00421070 (mode controller) -> 004215C0 (straight) or 00421830 (curve) -> 00421DF0 (raster) -> optional 00421BE0 (eight-neighbor helper).

The controller iterates modes 0..5, stored in global 0043C12C at 00421188. 0043C130 holds a per-pass section count; 0043C114 points to 12-byte section records, allocated in mode 1. 004379FC stores material by kind: road kind 0/3 => surface 2; kind 1 => 3; kind 2 => 4. The names in Ghidra are analyst labels, not recovered source symbols.

Mode 0 counts road sections. Mode 1 finds the first non-0x8000 plane-1 height in the strip and stores it in the current section record. Mode 2 for missing height writes section-record height to work plane 1 and writes surface 0; it skips both writes when height is already valid. Mode 3 invokes 00421BE0 on eight neighboring cells for classified strip samples after the first section. Mode 4 for class-2 strip samples only writes road-kind surface 2/3/4 WHEN work height is still 0x8000, without a height write. Mode 5, again only for class 2, invokes 00421BE0 on eight neighboring cells, where valid-height surface 0..5 is repainted with road-kind material.

00409210 classifies a candidate cell as 0, 1, 2, or 3. 00421DF0 uses ANY nonzero classification in modes 1-3 (00422402-00422429), but REQUIRES return value exactly 2 in modes 4-5 (00422416). Do not infer identical geometric reach for height generation and final surface assignment; exact x87 conversion of strip boundaries remains unverified.

## Center height versus surface conditions in helper 00421BE0

Reads original terrain work plane 1 height at 00421C05; reads surface plane 2 at 00421BF5. If center height is unset 0x8000 and at least one of eight neighbor heights is valid, mode 3 calculates signed integer average, writes center work height and sets surface 0 (00421CF8-00421D1A). Mode 5 leaves center height UNSET but writes surface 0 (00421D2A-00421D30). If no valid neighbors, neither mode makes these writes.

If center height is valid, the helper's surface condition 00421D40-00421D4C allows writes only for material values 0..5. In mode 3 it clears material to 0; in mode 5 it writes the selected road-kind material 2/3/4. Valid-height materials 6/7 are preserved; this protection is NOT applied in the unset-height branch. 0041F3A0 is the plane-1 height writer (selector 1), while 0041F4A0 is the plane-2 material writer (selector 0).

## Conditional intersection invariant

Original editor object grade 0040A6E0 stamps valid height with material 6 or 7 for object classes 0x50..0x53 (separate proposed PR #14). In this valid-height/material-6-or-7 case: direct road modes 2/4 skip, neighbor modes 3/5 leave material unchanged, second object grading follows roads, and smoother 00422870 selects center surfaces 2/3/4 only. Correctly stamped intersection cells are therefore protected by these specific road and smoothing branches. HOWEVER a cell that still has height 0x8000, even if its material is 6/7, can be changed in road mode 4 and neighbor mode 3/5. Other independent grading/paint/cliff writers have not been excluded.

Validation: 47/47 original PE native opcode checks and 13/13 analytical decision fixtures passed locally. The analytical model is NOT original-code execution, and matching opcodes alone do not validate behavioral causality. No original editable .I76 workspace, exact builder roundtrip, live collision/vehicle test, or recovered original C translation unit is claimed. Priority next: reproduce x87 strip geometry classification with original code, and test mode-specific effects on authentic editable workspace inputs.
