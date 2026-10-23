# Original editor overlap inheritance and zone-local smoothing

Status: proposed original-binary research, not an accepted milestone. Supersedes neither PR #14 nor PR #15. Primary executable: BUILDER/I76EDIT.EXE, SHA-256 69b7ce537cbc702bcdc81792f6d96ea25092cffe7a994044c70a49c6f08689df. Private read-only Ghidra 12.1.4 editor GZF SHA-256 792aab66e134aee91ca90844ee66cdc280477793631f6d0a319f2c3438f1a44f.

## Native editor findings

The grader 0040A6E0 visits 80 object buckets in increasing numeric zone index, starting with the bucket array at 00439BE8. It traverses node+0 next pointers. Object insertion 00409840, workspace loader 00409EB0 and cross-zone relocation 00409A90 all use head insertion via 0041C430. In an unchanged same-zone list, later insertions are processed before older nodes, so older nodes can be the last material writer. Across zones, numeric bucket order matters instead. Retail ODEF does NOT establish original editable workspace insertion order.

Eligible classes 2,3,0x50,0x51,0x52,0x53 first refresh object+0x0C from terrain plane 0 at the anchor cell (0040A754-0040A77D), then parse ASCII dimensions at +0x64/+0x6D. After rotating corners and finding extrema, native X-major raster loops scan X minX-1..maxX, Z minZ+1..maxZ+2 inclusive, when minima are nonzero. A zero minimum is incremented to one before the scan/write loops, shifting that axis. The signed integer rectangle comes from an enclosing AABB, not clipped SDF/GEO polygon faces.

The first work-plane-1 sample !=0x8000 encountered in X-outer/Z-inner scan order becomes the one height assigned to every cell of the region at 0040AA5C. If none exists, fallback is the plane-0 anchor height (not necessarily the previously stored object height), with zero promoted to one but 0x8000 not made valid. Overlapping objects can inherit and propagate an earlier height into previously untouched cells, including through A-B-C overlap chains lacking any direct A-C overlap. Which height wins depends on existing non-sentinel cells and scan ordering, not just insertion sequence.

The same per-cell pass writes material 6 for 0x50/0x51 or material 7 for 0x52/0x53 through 0041F4A0 (0040A9C4-0040AA73). Classes 2/3 write height only. Therefore surface material and height have different provenance and overwrite rules; a later object can assign its own material to a height inherited from an earlier object.

At 0040AAA4 EAX is cleared; 0040AAA8 loads AX from a 16-bit plane-1 sample; 0040AAB0 compares full EAX with 0xffffffff. The comparison cannot be equal after zero extension, so 0040AAB5 writes object+0x0C unconditionally on that path, including for 0x8000. The UI effect has not been dynamically measured.

## Scheduling and cross-zone boundaries

Scheduler 0040E3C0 orders object grade 0040E4C1, road grade 0040E4D9, second object grade 0040E4FE, four smoothing sweeps at 0040E52C/0040E56A/0040E5A8/0040E5E6, and height-plane merge 0040E605. The 00421DF0 road writer has mode-specific guards: its mode 2/4 raster path writes work heights only when previously 0x8000; do not generalize this to all road modes.

Smoother 00422870 uses work-plane-1 heights and plane-2 material, selecting only valid center heights on materials 2,3,4. A 3x3 world-coordinate neighborhood can sample valid height from material 6/7 cells. Within each zone, the 128x128 result is buffered, then copied to work-plane 1 at 00422BDA-00422BDF. The scheduler processes zones 0..79 sequentially in each pass, so a later zone can sample border values updated by an earlier zone *during that same pass*, where neighboring zones are active. This is not a globally synchronous smoothing sweep. The numerical illustrative scheduling case does not emulate the actual kernel or measure any real game border artifact.

## Shipped corpus sanity check

Historic private v20 survey TSV: 386 first-LOD intersection placements, 381 with some surface 6/7 footprint sample. Among the 19 largest worst-point height gaps (>0.25 world units), worst-point material counts are 0:4, 1:11, 2:1, 6:1, 7:2. Thus material 6/7 presence alone is not diagnostic of severe mismatch; 15/19 worst points were on material 0/1. This does not attribute individual retail anomalies to any authoring process.

## Evidence quality and next actions

43 static instruction/jump-table assertions against the original PE passed; seven analytical branching/scheduling cases passed, and legacy v20 diagnostic counts were recomputed from actual saved TSVs. Static opcode validation and analytical tests are NOT original-code execution. The original game archive did not contain an editable .I76 authoring workspace; no workspace export roundtrip, exact x87 rounding validation, runtime collision experiment, or original source filename recovery is claimed. Next examine source workspace identity and controlled editor runtime execution, road writer modes, and border-zone smoothing with exact original sample fixtures. Retail scene-GEO collision remains a separate unresolved path.
