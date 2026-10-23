# Original I76EDIT.EXE road cross-section classifier, original-code emulation

Status: proposed i76edit research record only. Base commit e26d643994db8ddd7e9cbde1e2f74fcf16647fce. It supplements historical ref/editor/road_terrain_serialization.md and draft PR #19 (six road modes) without changing prior runs or accepted conclusions.

Original binary BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA-256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private annotated Ghidra 12.1.4 I76EDIT.EXE.gzf SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Analyzed original x86 function 00409210 (281 bytes), original 00421DF0 raster caller, and x87 conversion helper 004235A4.

## Exact native integer contract

00409210 receives six signed int32 arguments (Ax,Ay,Bx,By,Px,Py). The original instructions implement int32 arithmetic for cross = (Px-Ax)*(By-Ay) - (Bx-Ax)*(Py-Ay), with signed wrap/overflow as in i386. Compute tol=max(abs(Bx-Ax),abs(By-Ay)) using the same signed int32 behavior. If abs(cross) >= tol, it returns class 0. This is a STRICT comparison: points exactly on the ribbon tolerance boundary are rejected. A degenerate A=B also returns 0, even for P=A. Ordinary in-range points within the ribbon return class 1 before A, class 2 at/between A and B (both endpoints included), class 3 after B. The exact original branch sequence prioritizes class 1 conditions and uses signed per-axis comparisons, important for overflow or extreme edge cases. There are NO x87 instructions inside 00409210.

The perpendicular tolerance for ordinary bounded coordinates is tol / hypot(dx,dy), between roughly 0.707 and 1.0 coordinate units. It is not a Euclidean <=1-distance test, and for horizontal/vertical lines the accepted integer positions lie exactly on the corresponding row/column. For A=(0,0), B=(6,0), P=(0,0) and P=(6,0) are class 2, P=(-1,0) is 1, P=(7,0) is 3, and P=(3,+1) is 0.

## Original-code execution evidence

Read-only Ghidra EmulatorHelper against the original I76EDIT.EXE program, entry EIP=00409210, stack containing six native signed-int32 parameters, stopped at the emulated return address, ran 896 deterministic cases seeded 0x1762026. All 896 returned to the stop address, 0 had P-code emulator errors, and 0 disagreed with an independently encoded int32 branch model, including reversed segment orientation, signed input coordinates, narrow segments and 128 extreme signed-int32 stress cases. Return-class distribution: 0:780; 1:64; 2:24; 3:28. A separate exploratory 38-case original-instruction boundary probe completed without errors. 24 native opcode-anchor checks passed against the original PE. These are original-code INSTRUCTION EMULATION of the classifier, not execution of the full Windows editor or an edited .I76 workspace.

## Caller and two terrain widths

00421DF0 passes two integer cross-section endpoints, then a candidate grid coordinate, through thunk 0040141F. Road processing modes 1-3 accept all NONZERO classes; modes 4-5 accept ONLY class 2 (native 00422402..00422429). Thus the accepted cross-section band in the earlier terrain work extends outside the endpoint-bounded region; final road material processing does not. Classes 1/3 are endpoint-region results, not terrain-material identifiers.

The original input argument is 1.0 at the observed 004215C0 and 00421830 road callers. 00421DF0 computes a perpendicular unit normal scaled by 0.5, and uses a factor 5.0 for modes 1-3, constructing cross-section endpoints roughly +/-2.5 world units from centerline (total nominal 5 units); modes 4-5 use +/-2.0 on that same half-normal, or roughly +/-1.0 world unit (total nominal 2 units). These are the EDITOR TERRAIN grading/raster regions, not the rendered 10-unit nominal RSEG road mesh width.

## x87-to-integer quantization

Conversion helper 004235A4 saves the FPU control word, sets truncation toward zero via OR AH,0x0c, executes FISTP qword, and restores the prior control word. Multiple 00421DF0 coordinate conversions first truncate x*10, divide this integer by signed 10 and test whether the signed remainder is >4; if so, the code adds float 1.0 to x before its final truncated integer cell coordinate. For ordinary positive finite inputs this approximately rounds to nearest with half-up tie handling, subject to preceding float32/x87 evaluation. A negative remainder never exceeds 4, so this adjustment branch does NOT symmetrically round negative coordinates. This is a native conversion-path finding, not yet a bit-exact end-to-end float/FPU result or proof negative world coordinates are valid authoring inputs.

## Reproducibility and limits

scripts/V25ClassifierDifferential.java is the original-code emulator harness requiring the private annotated original Ghidra program. scripts/verify_original_anchors.py checks selected native opcodes against private original I76EDIT.EXE. evidence/emulation_validation.json records the aggregate counts. No binaries or GZF data are committed. Full authored road->TER export, exact FPU tie/overflow behavior, original editable .I76 input provenance and retail wheel collision remain unresolved. No original source filename or C translation unit is asserted.
