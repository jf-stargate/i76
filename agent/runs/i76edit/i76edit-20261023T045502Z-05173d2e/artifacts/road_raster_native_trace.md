# Original editor: isolated native road raster and neighbor repair (v27)

Status: proposed research, not accepted canonical documentation. Pinned base f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a, protocol 1.0.1, research record 1.1.0. Supplements v25 classifier PR #20, v26 grid/x87 PR #25 and six-mode grader PR #19 without editing their evidence.

## Input identity
Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private read-only annotated Ghidra 12.1.4 editor GZF SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. No original binaries or database are committed.

## Execution boundary
Ghidra EmulatorHelper runs original 00421DF0 rasterizer instructions and original 00409210 integer classifier; the native-neighbor experiment ALSO runs original 00421BE0. This is not a decompiler-derived reimplementation of any of these functions. Four isolated terrain service thunks are substituted: 00401046 (surface read), 004013C0 (height read), 00401244 (height write), 00401474 (material write). The substituted calls preserve the caller's cdecl stack/return behavior. For native-neighbor tests, a synthetic Java terrain map stores writes so later original code sees the changed cell state. Separate exploratory raster-only tests also stub 004010EB only to count neighbor calls. External zone/resource infrastructure and Windows editor UI are not run.

## Original rasterizer observations
Synthetic endpoint vectors A=(20,20), B=(22,20), scale=1, section index=1, section seed height=250, road surface=2. In original code:
- Mode 0: incremented processed section count, no raster calls.
- Mode 1 with a valid seed: 9 classifier visits, 14 height reads (includes anchor reads), early exit.
- Mode 2 with all work-height cells unset: 49 classifier visits, 7 height reads, seven height writes of 250 and seven surface writes of 0 at X=20, Z=19..25.
- Mode 2 with only (20,20) initially height=777: same 49 classifier visits, 7 height reads, only six height/material writes, preserving that cell.
- Mode 4 with all unset: 49 classifier visits, 3 height reads, zero height writes, three road surface=2 writes at X=20, Z=19..21.
- Mode 4 with (20,20) height valid: only two material writes; no height writes.
- Mode 3 and mode 5: respectively 56 and 24 native eight-neighbor thunk invocations, matching 7 and 3 qualifying cells times eight. Raster-only run stubs neighbor call.
- Reverse endpoint case still produces three mode-4 surface writes; degenerate A=B returns 0 and makes no classifier/terrain calls.

These counts show original raster control flow and wider preparatory vs narrower surface pass for a single simple geometry, NOT universal strip pixel extents. Exact floating-point quantization remains limited by the independently identified v26 Ghidra x87/hardware discrepancy.

## Native neighbor execution with persistent synthetic terrain
A second experiment lets original 00421BE0 execute. Start with work-height 600 only at (20,20); other cells are unset. When seed surface=6, the original mode-3 path made 56 neighbor-helper calls, 264 height reads, 25 height writes, 53 material writes, leaving 26 valid-height cells total. All 25 new height writes had value 600 and locations within X=19..21, Z=18..26. Subsequent native calls see the height values written by earlier native calls in the SAME raster traversal. Thus an isolated valid seed can propagate farther than its immediate eight neighbors in a single pass. The original seed's material 6 was preserved.

With original mode-5 neighbor code, 24 helper calls made 200 height reads and no height writes. With seed height=600/material=6, 16 material writes occurred and original seed stayed material 6. Changing only seed material to 0 yielded 18 material writes and the valid-height seed was painted to road surface 2. The difference directly exercises original valid-height material gating.

## Validation, limitations and next research
The local captured transcripts passed 16/16 assertions across 10 raster scenarios and three original-helper scenarios. Private checkpoint i76_editor_v27_original_raster_20261022.zip contains full emulation scripts, service transcripts, and validation source. This public run includes one reproduction script plus aggregated evidence, and therefore declares reproducibility partial. There is no original editable .I76 workspace, no full original engine/editor execution, and all territory read/write services are substitutes. Never confuse synthetic map effects with measured retail missions.

An unresolved native dependency remains at 00422127/004221A3: reads from [esp+0x18] in mode >=4 had no prior local initialization identified by the static trace; Ghidra warned on an unseeded stack. Artificially changing the initial local value did not change the tested short horizontal or diagonal write sets. Do NOT label this a proven original retail bug; establish all possible aliases/call environments and hardware x87 semantics first.

Next: test wider signed/fractional geometry, pin original service/zone contracts, use exact hardware x87 or validated opcode infrastructure for quantization, and test complete original road pass control against a persistent synthetic terrain state. When a real editable .I76 workspace arrives, test authoring-to-TER fidelity separately.
