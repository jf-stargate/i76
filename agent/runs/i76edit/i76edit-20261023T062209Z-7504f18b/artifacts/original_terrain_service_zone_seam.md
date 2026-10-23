# Original editor v28: native terrain services and zone-seam execution

Status: **proposed research**, not accepted reference. Track: i76edit. Pinned base: f29379db9c7eccef91f6f93bc5984ce9dc6b9e4a. Extends unmerged PR #27; neither that run nor accepted documentation is edited.

## Evidence and original identity

Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe, SHA-256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private annotated I76EDIT.EXE.gzf SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f, Ghidra 12.1.4 read-only/no new analysis. Original i386 objdump and Ghidra decompilation were compared.

## What original code executed

The Ghidra x86 EmulatorHelper executed native rasterizer 00421DF0, original classifier 00409210, original eight-neighbor helper 00421BE0, original surface reader 0041F150, sample reader 0041F2B0, height writer 0041F3A0, surface writer 0041F4A0, zone triplet decoder 00412300 and plane pointer resolver 00412120. The **sole substituted service** at this expanded boundary was original zone backing/allocation 00411BA0: the harness returned success while privately initializing synthetic 128x128 terrain planes and a byte zone map. This is more original code than v27, but is not full editor execution or authentic zone allocation. The mode experiments use the normal plane-1 height and plane-2 material paths; unusual selector modes and allocator failures were not executed.

## Original zone layout

At native 0041212F-0041213B, the plane resolver constructs zone offset (zone << 13) + zone, multiplied by 4: exactly **0x8004 bytes per 128x128 uint16 terrain plane per zone**. The same stride appears for plane 2 at 00412147-00412153 and the other selector cases. Each zone contains 0x8000 data bytes plus four bytes between zone bases. Original 0041232A fetches a signed zone ID from byte map 00439EF0 using world-cell X/128,Y/128 indexing with width 80, and 0041233D / 0041234F mask local coordinates by 127 for nonnegative cells. Original 0041F2B0 returns 0xffffffff immediately for negative X or Y. The script verify_plane_stride.py checks nine original PE anchors, all 9/9 passing locally.

## Zone-boundary differential

Single zone: A=(20,20), B=(22,20), one plane-1 height=600/material=6 seed at (20,20), all other plane-1 samples 0x8000 and plane-2 material zero.

Two zones: shift A/B and seed +107 X to (127,20) -> (129,20), and explicitly set zone map IDs [0]=0,[1]=1 with plane-0/plane-1 backing layout at correct 0x8004 per-zone stride.

For **each** mode 2,3,4,5, translating all non-default single-zone output cells +107 X exactly matches the two-zone output cell set and the height/material values. In both cases mode 3 ended with 26 valid cells: the seeded cell and 25 new height=600 cells, including nine newly populated cells at X=128 in second zone. Mode 5 preserved the one original seed and wrote no extra height. Mode 2 ended with seven valid heights; mode 4 left the seeded material 6 unchanged and applied road material 2 to two unset-height cells. Emulated original zone allocator was the only synthetic call boundary. This is one positive synthetic fixture, not proof of entire 80x80 zone lifetime.

## Deliberately retained negative control

Initial two-zone setup incorrectly assumed height and material zone strides 0x10008 and 0x20010. Native accessor looked at the true 0x8004-stride second zone, whose unset samples had never been initialized and therefore appeared zero. The resulting artificial attenuation (e.g., 150,300,450...) was an **invalid experimental artifact**. Original getter-only tests distinguished this from the corrected setup: X=127 height=600; X=128 and 129 height=0x8000; X=-1 returns 0xffffffff. The full invalid and corrected transcripts reside in the private checkpoint, not as accepted retail observations. This incident is evidence that native address arithmetic must be cross-checked before trusting an emulator trace.

## Fractional and diagonal sections

With native terrain accessors, A=(20,20), B=(22,22) produced seven valid heights in mode 2 and three added road-material cells in mode 4; A=(20.25,20.4), B=(22.75,22.2) produced twelve valid heights and two added material cells. Reversing this fractional pair produced twelve valid heights at different addresses and four added material cells. This **does not establish a retail directionality defect**: Ghidra warned about x87 stack reads and v26 documented hardware/Ghidra FPU disagreements. Exact occupied fractional cells remain emulator-conditional pending hardware-equivalent original x87 validation.

## Evidence boundaries and next steps

Private checkpoint: i76_editor_v28_native_services_20261022.zip contains actual Ghidra script versions, full one-zone/two-zone/fractional/getter transcripts, flawed-stride negative control, and the 26/26 transcript validator. This public run contains a concise report, original-PE plane stride verification script and independently checkable aggregate counts/digests, with reproducibility marked partial. No original binaries, GZF, raw retail mission meshes or private assets are included.

Next: trace actual original i76edit_get_or_assign_zone_map_cell_id backing initialization, first-touch sentinel values, zone-ID lifetime and errors; reproduce x87 raster-coordinate behavior using the native hardware semantics; later test the author's editable .I76 ROAD inputs when available. No reimplementation is authorized.
