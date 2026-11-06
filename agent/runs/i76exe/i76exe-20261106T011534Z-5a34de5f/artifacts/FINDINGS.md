# Findings and bounded result

668 independent-model/native cases pass: retail M06, CD-authenticated M02, controlled repeated-page M06, and controlled bit12 M06 (167 each). The Ghidra executions independently verify 1,724 observed height/source reads and four complete 16,384-slot grids. The M06 fresh-emulator repeat is byte-identical. The later native oracle establishes arithmetic more precisely than the earlier FISTP-corrected emulator.

New: explicit source row/column/global/world contract; no duplicate sample at page edges; zero default page in the initialized image; safe negative/default and unsafe flattened-index distinctions; exact native x87/rational agreement including admission double rounding; measured Ghidra rounding differences after FISTP correction; controlled alias and bit12 negative results; CD M02 terrain validation. See finding records and the four contract/handoff documents.

Confirmed: 80×80 ZMAP at runtime +24/+24, 128×128 samples/page, little-endian 16-bit stride, X/Z spacing5, low12 height times float32 0.1, high3 class, four-corner bilinear interpolation. Source geometry remains lattice/low12 before camera transform in previously accepted visual evidence.

Contradicted assumptions: +24 implies an additional source-world origin shift; a page has a duplicated 129th edge sample; FF means the original query fails; a repeated page ID supplies world position; hardware FISTP correction makes every emulated height exact; a single ordinary round() reproduces the x87 admission sequence. These are potential implementation assumptions, not claims that maintained reconstruction already contains these errors.

Unresolved: global bit12 purpose, arbitrary mission/state/generalization, full native normal/CRT parity, extreme or unusual floating-point states, unsafe negative-slot reads, full-game default-page writes/lifetime, renderer topology/materials/UVs and rasterization. No loader or mesh implementation, canonical promotion, shared tooling change or merge is included. Next implementation PR should add the checked lattice resolver, explicit default-page provenance and global-neighbor sampler with the documented safety and precision policy.
