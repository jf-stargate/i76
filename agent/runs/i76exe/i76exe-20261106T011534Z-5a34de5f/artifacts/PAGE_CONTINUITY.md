# Page boundaries and ownership

Finding F2, evidence S/E/H/D as defined in the coordinate contract. Each of four configurations has 167 cases; the boundary subset is `evidence/boundary_cases.jsonl`. Both retail TERs contain unique active-page ordinals, so active-page aliasing is tested in a **controlled** M06 ZMAP variant, not invented as a retail observation.

## Exact seam rule

At global X=`128*c+126, +127, +128, +129`, with an ordinary fixed Z:

| Lattice X | Serialized column | Local X |
|---|---:|---:|
| 128*c+126 | c | 126 |
| 128*c+127 | c | 127 |
| 128*c+128 | c+1 | 0 |
| 128*c+129 | c+1 | 1 |

Z follows the identical row rule. At a diagonal crossing, each of `(ix,iz)`, `(ix+1,iz)`, `(ix,iz+1)`, `(ix+1,iz+1)` resolves its **own** page pointer and local offset. Executed load sites, in that order: `00493652`, `004936A5`, `004936F8`, `0049373D`. They are inlined lookups, not four calls to `00493160`.

The data layout has 128 samples per page, not 129. No duplicate-edge convention is used by this lookup. A page origin is 640 world units after the preceding origin; its last sample is at local 635. The remaining five-unit cell uses the next page's first sample. A mesh should share vertices by global lattice identity and resolve neighbors across pages. Reusing local sample 127 as sample 128, using a 127-sample page period, or stitching independently clamped pages changes the original coordinates.

This establishes address ownership and a continuous conceptual piecewise bilinear surface over neighboring lattice vertices, not equal heights at local127 and neighbor0, slope continuity, equality of edge payloads, nor bit-exact continuity after the original rounded interpolation stages. Raw terrain heights may differ sharply across a five-unit cell.

## Default pages and populated edges — F3

Initializer `00493080` first fills all 16,384 pointer slots with `0059C588`; valid ZMAP IDs overwrite selected slots. ZMAP value 255 leaves the default. Runtime slots outside the embedded 80×80 region also retain it. Both tested missions contain many default cells; active-to-default transitions are explicitly queried on both sides and diagonally at the first active page's origin.

The default is a 32,768-byte zero-filled page in this executable image: the complete region lies beyond `.data`'s raw file bytes and within its virtual size. Original parsing/setup leaves all 16,384 words zero in every tested configuration. There is no harness write to that page in the Ghidra experiment. Its digest is `c35020473aed1b4642cd726cad727b63fff2824ad68cedd7ffb73c7cbd890479`. Native replay explicitly installs the observed default backing as an environment substitution. Static direct references found by Ghidra point to grid initialization, not a terrain-content writer; no claim about all possible indirect writes or full-game lifetime follows.

A valid default slot therefore yields height12=0 and class=0 in the tested initialized state. This differs from the reconstruction's serialized-ordinal `0xff` failure policy. A missing/invalid TER resource is a separate loading failure and was not simulated as a successful default scene.

The source region ends at lattice 10239 in each dimension. Lattice 10240 belongs to runtime page 104, outside ZMAP, and uses default backing. The world query admits some positions around world 51200 because it tests rounded indices against inclusive 10240; it does not clamp the four corners to 10239. Direct lattice negatives within the larger grid similarly resolve default backing; near-negative admitted world queries can have floor=-1.

## Repeated references

The `alias` configuration copies the first active horizontally adjacent cell's page ID into its right neighbor in a private copy of M06 ZMAP, before original TDEF parsing and grid initialization. The original initializer creates identical borrowed pointers in those slots. At the seam, local addressing resets from 127 to 0 of that same page. There is no new page allocation, edge duplication, neighbor special case or page-ID-derived origin. The independent model and native CPU outputs match the controlled original execution.

These fixtures demonstrate mechanism, not proof that any other mission repeats active IDs. M06 and CD M02 have 16 and 12 active references respectively, each referencing its own unique ordinal.

## Unsafe and rejected coordinates

The helper's flattened upper-bound check returns 0 for tested high indices, but cannot safely classify arbitrary int32 inputs: it omits a negative-slot check and permits X row spill. Cases include -1, -128, -3072, X=-3073 with a still-valid flattened slot, 10239/10240 and runtime-grid edges. Negative flattened slots are retained as a static unsafe behavior and are not executed.

World admission is separate. A rejected world-height query returns zero without four reads; rejected material query returns class 5, and rejected query normal writes (0,1,0). Default class 0 must not be conflated with this class-5 rejection. See the numeric contract for the precise bias conversion and its boundary rounding.
