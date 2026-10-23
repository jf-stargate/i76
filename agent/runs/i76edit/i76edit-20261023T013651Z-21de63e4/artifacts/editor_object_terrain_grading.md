# Original I76EDIT.EXE object grading: native-binary v21 continuation

Status: proposal-only research evidence, not an accepted v21 milestone or canonical documentation. Track: i76edit. Repository base: af747a9fed757f8030c34d0f05441702352f5f8c. Publication protocol 1.0.1; research record schema 1.1.0.

## Original binary identity and method

The original BUILDER/I76EDIT.EXE MD5 is 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA-256 is 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. The private annotated Ghidra 12.1.4 snapshot, I76EDIT.EXE.gzf (program I76EDIT.EXE), has SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. A read-only headless analysis confirmed the Ghidra program MD5; the newly inspected routines were also checked against independent disassembly of the original PE. No original binaries or Ghidra database are included in this run.

## New, original-instruction-supported results

The Ghidra name i76edit_refresh_exportable_object_zone_ids, attached to function 0040A6E0 (thunk 004011E5), is narrower than its actual behavior. The native routine iterates workspace object buckets, filters object classes 2, 3 and 0x50-0x53 at 0040A72F-0040A754, and reads an object sample into offset +0x0C. It reads two ASCII dimensions at object +0x64 and +0x6D through atoi at 0040A780 and 0040A792. Both dimensions must be positive. The routine performs ceil(dimension/5) integer conversions and rotates four rectangle corner points via thunk 0040126C to 00412CF0, using negative object orientation from offset +0x18. It then takes a bounding X/Z rectangle enclosing the rotated corners (0040A88C-0040A8CA). This region is an axis-aligned integer grid rectangle, not indexed GEO polygon clipping.

At 0040A905-0040A99B the routine searches the grid region for an existing non-sentinel 16-bit height in work plane 1 (global 0043C554, unset marker 0x8000). If no usable height is found, it falls back to object +0x0C; a zero fallback is promoted to one. At 0040AA5C it fills the selected region in work plane 1 with that uniform height. The exact x87 integer-rounding behavior for rotated boundaries has not been exhaustively measured, and the grid loop includes padding around the rotated extrema.

The native four-entry class jump table at 0040AB00 has entries 0040A9D5, 0040A9D5, 0040A9DF, 0040A9DF, for class values 0x50, 0x51, 0x52, 0x53 respectively. The first two dispatch to material index 6, the latter two to index 7. At 0040AA73 this nonzero material causes a call through thunk 00401474 to 0041F4A0, which writes the class to terrain surface plane selector 2 (0041F4E7, 0041F510). Other eligible object classes 2 and 3 perform height stamping here but do not select a material in this dispatcher. Direct height write and conditional material write are proven from native instructions, not merely from UI labels.

Scheduler 0040E3C0 calls 0040A6E0 at 0040E4C1, invokes the road-grading path 00420EE0 at 0040E4D9, and calls 0040A6E0 again at 0040E4FE, followed by four road smoothing passes. Merge helper 004125F0(0) copies non-sentinel plane-1 heights into plane 0. Export helper 0041AAA0 reads plane 0 for height and plane 2 for surface data when packing 128x128 terrain zones. Final object refresh thunk 0040103C to 0040AC20 at 0040E65E is different: 0040AC33 obtains selector-0 plane and 0040AC4F updates object +0x0C from its current height; no rectangular write occurs in that function.

## Reconciliation and limitations

This resolves the narrow v20 question whether the two 'Grading Objects' stages are mere object-coordinate refreshes. They are not: both passes can stamp height, while intersection types also stamp material 6/7. The v16/v20 shipped mission observation that WRLD material parameters 6/7 are equivalent to those of paved/unpaved road classes 2/3 now has a concrete possible editor writer. However, there is no demonstrated byte-identical editable .I76 workspace round trip, and the shipping missions could have been authored with a different editor revision. Therefore no causal attribution of individual retail terrain cells or specific v20 polygon mismatch fixtures is proven.

This run does not settle whether game intersection scene GEO faces participate in physics collision. Game scene registration 004925F0 and rendering traversal 0048E900, together with terrain wheel probe 00440740, require a separate collision-consumer trace.

## Follow-up

Trace how class 0x50-0x53 object dimensions and orientation are populated; inspect work plane initialization, object processing order and road-overlap precedence; correlate exact stamped rectangular areas with the 386 existing polygon-footprint cases and surface 6/7 boundaries. Retain a provisional source neighborhood 0040A6E0-0040AC61, but do not invent a C translation unit.

Reproduce via scripts/verify_editor_grading.py against a private original PE; the other script emits decompilation/xrefs from the private annotated Ghidra project and must not be mistaken for the original source.
