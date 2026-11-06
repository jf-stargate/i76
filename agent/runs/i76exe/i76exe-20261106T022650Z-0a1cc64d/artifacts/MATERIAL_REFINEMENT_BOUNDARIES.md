# Class refinement, defaults and repeated references

Findings F-CLASS and F-GEOMETRY. Evidence: [native cases](../evidence/scan_cases.jsonl), [geometry comparisons](../evidence/geometry_comparisons.json), [leaf regions and loops](../evidence/geometry_details.json). Inputs/mutations are recorded separately; only `retail` geometry is authentic unchanged terrain.

Classes2/3/4/6/7 cause subdivision after earlier visibility, distance and height tests pass and side>4. Classes0/1/5 pass. Controlled bit12-set words at each of the four sites trigger exactly the same special classes. This establishes bit12 irrelevance for this predicate, not its general purpose. The class is the packed high three bits, not a material descriptor or rendered texture index. Class-trigger refinement inspects boundary samples only, with duplicated corners and short-circuit order specified in ADAPTIVE_BOUNDARY_SCAN.md.

The initialized default backing is zero, giving class0. Normal aligned default scans therefore do not themselves force subdivision. Default **heights**, camera distance, and neighboring ordinary sample lookups can still change refinement. Repeated ZMAP IDs reuse a borrowed pointer without page allocation, deduplication logic, equality shortcut, or special class treatment. Local coordinates reset for ordinary lookups at a repeated-page seam. For normal aligned scans, pointer and per-coordinate scan addresses agree exactly, including repeated and default pages.

Independent per-sample class queries can disagree with the raw scan for injected unaligned ranges. Horizontal/diagonal class3 controls and the repeated-reference control yield original leaf versus independently resolved split in both missions. Vertical agreement in one M06 case depends on coincident ordinal/geographic adjacency; M02's corresponding vertical control disagrees. These observations concern a class query at each intended lattice location, not interpolation of discrete class values or a claim that `004927B0` scans boundaries itself.

## Complete source-geometry experiments

All six M06 configurations use #140's original controlled stock-bus camera fixture, original root `(512,9568)`, side128, and original planes. This is not a mission spawn pose. All non-retail copies clear only class bits, preserving low13; additional edits:

- `clear`: no further edit.
- `class2` / `class5`: set one packed class at lattice `(543,9695)`, on the far interior corner of the side32 region at `(512,9664)`.
- `alias`: set ZMAP row75,col4 to row74,col4's ID, creating repeated backing across Z=9600.
- `default`: set ZMAP row75,col4 to255, creating an active/default transition across Z=9600.

| Geometry case | Vertices | Edges | Leaves | Unequal-LOD shared segments | Emitter attempts |
|---|---:|---:|---:|---:|---:|
| Retail | 171 | 464 | 79 | 48 | 181 |
| Clear classes | 167 | 453 | 79 | 49 | 184 |
| Class2 point | 171 | 464 | 79 | 48 | 181 |
| Class5 point | 167 | 453 | 79 | 49 | 184 |
| Repeated page | 100 | 265 | 37 | 29 | 80 |
| Default page | 70 | 181 | 22 | 20 | 58 |

The class2 point restores the exact retail source graph; class5 is bitwise identical to the cleared graph. Equal leaf count79 does not mean equal topology: vertex identities, edge arenas, loop boundaries and emitter attempts differ. Alias/default controls also change height data at ordinary sample positions; their geometry differences cannot be attributed solely to the class predicate.

For every configuration the independent numerical predicate recreates every original decision and complete source XYZ/index sequence; all interleaved edge/leaf arena bytes and original flattened loops match. Every original material-read address/word/site sequence matches the independent bounded scan. Late shared-edge flattening gives identical reversed vertex indices across unequal-size neighbors; exact geometric overlap checks find no partial T junctions. A second fresh GZF import with added adaptive pre-read guards reproduces all78 private trace/sidecar files byte-for-byte. The retail fixture also matches #140's published primary source hash.

## Geometry implication of crossing

Normal class scans do not cross page boundaries, so the raw-pointer/per-coordinate distinction introduces **no scan-crossing topology difference under the recovered caller invariant**. Physical seams still change ordinary endpoint/midpoint heights, and a special class on either region's scanned footprint can change subdivision and hence shared-edge geometry. The executed class2/clear comparison proves such topology sensitivity without an unsafe crossing. Shared parent edges propagate refinement to the adjacent coarser loop.

Injected unaligned scans demonstrate different original branch decisions; by the recovered subdivision path these can select different graphs. No complete unaligned source-graph execution is claimed here. Unsafe attempts have no fabricated resulting subdivision. Full facing/shading, clipped output equality, framebuffer output and native full-geometry numerical parity remain outside the verified scope; emitter attempts are observed counts, not a complete independent emission oracle.
