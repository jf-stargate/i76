# Terrain evidence reuse across engine and editor tracks

Pinned accepted base: `458ba43243b48bea87205145ebe8831f5ee2b555`; protocol 1.0.3. Review preceded new reversing. PR #49 was merged at this base; PR #50 was open. Before publication, the human merged PR #50 at 64667f3f168de1d377af8b1adf194dc51c256ffc. Publication retains that accepted tree while preserving the original research base. A merged evidence run is not automatically a canonical promotion.

## Reviewed sources

- `ref/level_format/i76_runtime_level_and_terrain_format_notes.md`, especially TDEF/ZMAP/ZONE, runtime page indirection and packed materials. Its late function table calling 00493550 a transform helper conflicts with its terrain sections and newer editor cross-checks.
- `ref/editor/README.md`, `road_terrain_serialization.md`, `intersection_geometry_and_driving_surface.md`: editor grid/world scale, bit packing, road-heightfield separation, WREV 8/9 and object-surface limitations.
- Accepted editor run `i76edit-20261023T013651Z-21de63e4`: original rectangular object grading, surface 6/7 stamping and distinction from read-only object refresh.
- Accepted editor run `i76edit-20261023T043010Z-a8d70545`: 5x world conversion and measured Ghidra/hardware x87 disagreements; this warning is directly relevant to sampler validation.
- Accepted editor run `i76edit-20261023T062209Z-7504f18b`: native 0x8004 editor work-plane stride, original terrain accessors and retained wrong-stride negative control. Later editor zone-allocation/compaction runs concern editor memory ownership, not retail page layout.
- Accepted engine construction, registration and camera evidence through runs `i76exe-20261022T232710Z-96c58505`, `i76exe-20261023T072053Z-c5725c60`, `i76exe-20261027T031313Z-32de4d1e`, and now-merged `i76exe-20261027T033452Z-2f8c31f5`. PR #50's exact probe is reused as candidate infrastructure and independently rerun, not treated as accepted research.

## Reuse decisions and fresh checks

| Historical conclusion | Reusable here? | Fresh retail check |
|---|---|---|
| 00493910 parses nested TDEF; 00493960 installs ZMAP; 004939D0 maps TER | Yes | Original handlers, generic descriptor dispatcher and original 00471400 mapping wrapper executed over M06 inputs; only OS/CRT/resource services supplied. |
| 00493BD0 calls 00493080; 5-unit spacing and +24/+24 page offset | Yes | Original code produces scale 0x3E4CCCCD, step 5, sixteen active mappings and the complete 16,384-entry expected grid. |
| Runtime pages are 0x8000 bytes; low12 height, high3 surface | Yes | Every logged sampler, normal and material read checked against authentic M06.TER bytes. |
| Editor plane stride 0x8004 | No, not as retail layout | It describes editable separate work planes. Applying it to the TER mapping would be incorrect. |
| Runtime height multiplier 0.1 | Yes | Original 00493550 and independent interpolation agree; historical 409.5/4096 exporter scaling is not substituted. |
| Kind-1 road material index 3; equivalent records 2/6 and 3/7 | Narrowly | M06's first RSEG center (2480,48725) returns class 3. All original WRLD property bytes match the mission, including the two aliases. This is not a new full-corpus road survey. |
| Visible road/intersection mesh equals driving surface | No | Current replay validates heightfield fallback only. Scene/intersection polygon collision remains separate. |
| Ghidra x87 rounding can differ from hardware | Essential caution | The sampler's two FISTP conversions ignore RC in uncorrected P-code. An explicit hardware instruction service resolves the measured discrepancy. |

## Program/baseline separation

New execution uses retail i76.exe SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3` and annotated v97 GZF SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. The separate I76EDIT.EXE and editor GZF were fingerprinted as `69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df` and `792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f`. No new editor execution or shared-baseline changes are claimed.
