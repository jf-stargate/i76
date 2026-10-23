# Original editor object order and terrain-smoothing material gate

Status: proposed immutable i76edit research; not an accepted canonical milestone. Repository base af747a9fed757f8030c34d0f05441702352f5f8c. Follows but does not modify proposed v21 grading run in draft PR #14.

## Provenance and validation

Original BUILDER/I76EDIT.EXE MD5 4c7ed9e8a54fcadbf1895f34aa9918fe; SHA-256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Read-only annotated Ghidra 12.1.4 I76EDIT.EXE.gzf snapshot SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f. Native PE objdump and the Ghidra decompiler/xref closure were independently inspected. A local original-PE opcode audit passed 32/32 checks; the companion verification script reproduces these checks with the private original executable. No editor runtime, edited binary, or original .I76 workspace roundtrip was executed.

## Object dimension provenance

00409840 allocates a 0x78-byte editable object payload and clears two 9-byte ASCII fields at offsets +0x64 and +0x6D. Object-property setters 00409CB0 and 0040F8C0 each copy at most eight bytes with strncpy and write terminating zero bytes at +0x6C/+0x75. The UI dispatcher 00416620 collects edit controls 0x3F4/0x3F5 and invokes these setters through 0040123F and 00401294. The grading routine 0040A6E0 parses the two object fields using atoi, converts positive dimensions into 5-world-unit terrain-cell counts rounded upward, rotates a rectangle, and stamps the bounding cell region. The dimensions are therefore editable workspace object properties, not dimensions computed by clipping indexed SDF/GEO polygons in this routine. Their exact original UI labels are not proven.

00409EB0 reads current object records as 0x78 bytes (revision >1), or legacy 0x70-byte (revision 1) / 0x68-byte (revision 0) records upgraded into the current in-memory representation. Versioned OBJ record layouts had already been researched in v13; this is a specific link from that known ABI to the grading behavior, not a claim to have discovered the record sizes for the first time.

## Linked-list order and overlap

0041C430 allocates a 0x0C-byte doubly linked node with next (+0), previous (+4), and payload (+8). New objects are head-inserted in their zone list by 00409840. Relocation in 00409A90 also detaches and reinserts the object at the destination zone's head. Object grader 0040A6E0 visits zones, then traverses each list from the head via next (+0). An object inserted later is therefore encountered earlier when other ordering operations have not intervened. Overlapping footprints can overwrite previously assigned plane-2 surface materials; there is no per-cell object-ownership mask in the stamping path. Height precedence is not a naive last-writer rule, because each object's grading first searches for an existing non-0x8000 work-plane height and can reuse it.

## Smoothing filter and neighborhood lifecycle

0040E3C0 runs object stamping, road grading, a second object stamping pass, then invokes smoothing kernel 00422870 four times by 004013CF at 0040E52C, 0040E56A, 0040E5A8 and 0040E5E6. Smoothing reads plane 1 for height and plane 2 for terrain material (0042287E/0042288D). Native instructions 004229ED, 004229F7 and 00422A01 require a non-0x8000 height and material 2 <= s <= 4. In particular, indices 6 and 7 stamped for selected intersection classes in proposed PR #14 are excluded as center cells in this kernel.

The kernel samples a 3x3 height neighborhood; sample helper 0041F2B0 maps parameter 100 to plane 1 (as distinct from parameter 99 for plane 0). Heights from neighboring excluded-material cells may therefore still influence eligible road-type cells, although excluded centers remain unchanged. Each pass allocates a distinct 0x8000-byte 128x128 uint16 output buffer, writes calculated samples there at 00422B46, and copies 0x2000 dwords back to plane 1 at 00422BDA-00422BDF after scanning the zone. This is per-pass snapshot semantics, not in-place progressive updates. Surface plane 2 is not itself smoothed by 00422870.

After four passes, the 0040E605 merge (through 004125F0, mode 0) copies non-sentinel plane-1 heights to plane 0. The independent original zone writer 0041AAA0 packs plane-0 heights and plane-2 materials into 128x128 .TER words, with the material index shifted 13 bits and the height masked to 12 bits. Special surface codes >99 take a separate flag path.

## Limits and implications

Binary-proven: property string storage and setters, linked-list head insertion, center material filter, 0x8000 height guard, four passes, distinct scratch output, and eventual work-plane merge. Derived: list traversal can make material writes order-dependent, and protected 6/7 center heights can contribute to neighboring 2/3/4 averaging. Inferred only: these effects may contribute to terrain/pavement mismatch fixtures previously measured in A01/S03/S04. The record does not demonstrate that any particular shipped mission's TER cells came from this builder revision; no original editable .I76 workspace roundtrip or live wheel-contact test exists.

Provisional source-layout grouping: workspace object editing/loading around 00409840-0040A6E0 and terrain helpers 0041F2B0/004125F0/00422870 are separate code neighborhoods. Their original .c or .h names and translation-unit boundaries are unknown.

Next: controlled intermediate-plane snapshots from a genuine editable workspace, order/overlap fixtures, exact object control labels and signed rotation boundary tests. The retail collision consumer of intersection GEO faces remains a distinct unresolved investigation.
