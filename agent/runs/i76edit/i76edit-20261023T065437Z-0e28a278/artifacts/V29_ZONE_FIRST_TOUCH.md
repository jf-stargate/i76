# Original editor v29: zone first-touch allocation and automatic neighbor-zone creation

Status: proposed original-binary evidence, not accepted reference. Base f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a. Follows independent v27 and v28 research PRs #27/#28. No editor or engine replacement code.

Original source identity: BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private Ghidra 12.1.4 I76EDIT.EXE.gzf annotated baseline SHA256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Read-only Ghidra and independent original PE instructions used.

## Core native allocation contract

00411BA0 takes cell X,Y and creation flag, converts positions to 128-cell zone coordinates (signed truncating quotient), then invokes 00411B30. For zone indices less than 80, 00411B30 looks up signed ID byte at 00439EF0 + zoneX + zoneY*80. Existing ID is returned unmodified. An unassigned ID is -1 (stored 0xFF); when the creation flag is nonzero, the original 004125A0 scans 80 base-plane headers at 009BC820 in 0x8004-byte strides. First zero dword marks slot free; the original code writes marker 1, returns its 0..79 index, and 00411B30 stores that byte in the zone map. The first-touch path then calls display refresh through 0040124E with the assigned ID. Only this display-refresh operation was substituted in function-level execution.

Startup default initialization is a DIFFERENT path: 00411810(reset mode 0) zeros base-height slot headers, fills work-height plane 0043C550 with 0x80008000 while clearing its per-slot four-byte markers, fills 80x80 zone map to 0xFF, initializes default surface plane 00EBCAA0 from 00433A70 (initial literal value 1), and sets other plane-specific defaults. 004117F0 performs repeated-dword fills. First-touch 00411B30 does not redo these bulk fills. Dynamic tests manually supply those startup-style defaults; full original 00411810 UI startup was not emulated.

## Original-code emulation

Native 00411B30 and 004125A0 were executed in Ghidra EmulatorHelper. With all map entries unassigned and 80 base-plane headers zero, lookup (0,0) with creation disabled returned 0xFFFFFFFF; first creation at (0,0) returned 0 and marked header0; repeated lookup retained 0 without UI refresh; creation at (1,0) returned 1 and marked header1; out-of-range zone (80,0) returned -1. With all 80 headers marked in use, creation returned -1, left map entry 0xFF, BUT still passed 0xFFFFFFFF as argument to display-refresh thunk. Display routine was not run: observable Windows failure or crash is NOT established. The native entry checks upper bounds but not independent lower bounds; standard terrain sample readers guard negative world-cell inputs.

A separate original-code run also executed terrain height/material readers 0041F2B0/0041F150, writers 0041F3A0/0041F4A0, zone resolution 00412300 and plane pointer arithmetic 00412120, with only display refresh stubbed. Selector-100 (no-create) height reads and material reads of a missing zone returned 0xFFFFFFFF; selector-1 height read created zone 0 and retrieved 0x8000 unset height. Original height writer (flag 1) then stored 600, original surface writer (flag 0) stored 6, and original readers returned 600/6. This demonstrates a read-selector-dependent zone-topology side effect.

## Original road pass across an initially ABSENT neighboring zone

Original 00421DF0 rasterizer + 00409210 classifier + 00421BE0 neighbor repair + all normal native terrain reader/writers + ORIGINAL 00411BA0/00411B30/004125A0 allocator were executed. Synthetic road section (127,20)->(129,20) crosses the 128-cell zone seam. Initially only zone 0 was mapped (ID 0, header occupied); zone 1 map entry 0xFF and header1 zero. Seed height=600/material=6 at (127,20); zone0/zone1 work-height memory was explicitly preinitialized to 0x8000 for reproducibility. The only intercepted routine was the UI display refresh through 0040124E.

Mode 3: 49 classifier visits, 56 native neighbor calls; creates neighbor ID 1 from original native first-touch with creation flag 1; ends with 26 valid heights, including nine new cells at X=128. Mode 5: 49 classifier visits, 24 neighbor calls; ALSO assigns neighbor zone ID 1 with create flag 1, despite leaving only the original one valid-height cell. Mode 2: 49 classifier visits, seven total valid-height cells; no neighbor-zone allocation. Mode 4: 49 classifier visits and three nonzero material cells; no neighbor-zone allocation. These results hold for the specific synthetic geometry and preinitialized plane bytes, not for every original editable road.

This refines v28: its otherwise identical zone-seam parity fixture preassigned both zone IDs, whereas these experiments prove that normal road neighbor processing can trigger NEW ID creation. Importantly, creating a zone is not equivalent to painting a non-default height/material cell.

## Static lifetime follow-up and evidence gaps

Original 00413B20 calls 00411BE0 through 00401262 after an interactive confirmation path. 00411BE0 searches for an occupied zone ID, remaps slot IDs, copies 0x8004-byte plane blocks and object-zone metadata in a nonlast-slot case, and clears released-slot state. This suggests the current Ghidra label initialize_painted_terrain_layers understates a likely zone-removal/compaction role. Full original deletion/compaction, UI behavior and object-list invariants remain UNTESTED and must not be promoted as confirmed.

Allocator exhaustion currently reaches the refresh thunk with ID -1: this is a proven call argument, not a proven crash. Native upper-bound comparison without a standalone lower bound cannot be used to infer user-reachable negative-map corruption because the ordinary sample readers separately guard negative coordinates.

No original editable .I76 authoring workspace, full 32-bit Windows editor, or original UI/runtime graphics path was executed. Ghidra EmulatorHelper x87 inaccuracies documented in v26 still apply to fractional road boundary claims. The local private v29 checkpoint contains the complete Ghidra scripts, transcripts, decompiler excerpts and the deterministic 44-check validator; only nonproprietary aggregates and scripts belong in the public repository.

Local validation: 24 original-PE opcode anchors and 20 original-code emulation transcript assertions, all 44/44 passing. Follow up: execute 00411BE0 slot removal/compaction and test ID reuse, all plane headers, object-zone list remapping, then exact x87 fractional rasters and eventual editable .I76 workspace exports.
