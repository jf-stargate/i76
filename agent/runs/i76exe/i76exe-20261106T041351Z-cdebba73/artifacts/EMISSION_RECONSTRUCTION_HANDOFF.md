# Emission reconstruction handoff

This is a research proposal for human review. It does not authorize implementation, promote canonical documentation or establish a renderer.

## Distinct geometry identities

| Entity | Identity / lifecycle |
| --- | --- |
| Source leaf | Original 0x1C linked node, four shared-edge references; 79 primary leaves |
| Boundary polygon | Late-flattened source-index loop; extra edge vertices are incorporated before selection |
| Fan candidate | Anchor plus adjacent boundary endpoints, excluding anchor-adjacent pairs; may be rejected before emission |
| Emitter attempt | Invocation of ordinary `004922F0`; 69 whole +112 triangles in primary; not an accepted arena allocation |
| Scratch work record | `00490590` returns current cursor; rejected attempts can reuse exactly the same address |
| Clip geometry | `0047BF00` performs depth clipping, projection and `0047B8C0` screen clipping; generated vertices need not have source indices |
| Accepted bin entry | Final linked member of `0048FE10`'s bucket table, with advanced persistent arena cursor; 30 primary entries |

The emitter writes kind=0 and literal material/header value 0xB4, reverses source indices into XYZ work vertices, and records the maximum source view Z **before clipping** as bin depth. Scalar shade is copied to vertex+14 unless cached high-color mode selects source aux+08 instead. It invokes the installed clip/projection callback with the retained original view and a six-dword-per-vertex work layout. Clipping can change count, insert vertices and discard all geometry; clipped count must never be confused with source N or attempt count.

Zero clipped count returns zero and does not bin. Positive count calls `0048FE10`, then returns one regardless of that routine's returned cursor. Static bin guards include depth below its minimum, rounded depth bucket offset >0x1000, count>32 and excluded kind 12, with further typed handling outside this selected kind-0 path. Thus positive emitter return is not a universal proof of accepted bins. The bounded fixtures use minimum=-300, ordinary kind0, supported counts and initialized tables; here each positive clip result is accepted. Independent verification uses actual cursor advancement and final bin chains, rather than defining acceptance from EAX alone. General bin exclusion, bucket-boundary 4096 and capacity/exhaustion behavior remain unexecuted in this run.

## Candidate algorithm boundary

`scripts/walker.py` is an independent research algorithm. Given original source edge/leaf geometry, original post-transform view XYZ, retained view projection, light/ambient/attenuation and authenticated numerical constants, it predicts flattening, anchor selection, projected-Y gate, plane signs, shade bands, whole attempt, conditional fallback, ordered triangle attempts, depth/screen rejection and accepted status. The numerical inverse-square-root seed is derived independently from the original initializer's formula. No recorded emitter choices enter `walk()`.

`verify.py` obtains geometry from source-only arena and post-transform sidecars, computes all predictions, then consumes observations. It compares exact per-leaf and per-attempt ordering/indices, score/anchor/bands/fallback membership, clip counts and rejection stage (depth rejection has no original projection stores; screen rejection follows projection), EAX, cursor retirement and final bin membership. It checks all original plane outputs within stated numerical bounds and compares their signs exactly. `check_public.py` repeats prediction for four compact, asset-free, derived numerical fixtures and rejects six classes of corrupted claims per fixture.

The model still receives original view-space geometry and camera/root decisions; independent camera-to-root coverage is a different investigation (open #144 at bootstrap), and boundary scans are open #143. Their unmerged results are not assumed here. Merged #140 remains the source graph predecessor; its eight common scenarios have **76 sidecars byte-identical** to this fresh import, including source graph, transformed vertices and accepted bins.

## Original versus supplied boundaries

Original retail instructions execute VCF/GEO object construction and registration, two camera updates, inverse/frustum/projection setup, inverse-square-root table initialization, terrain loader/source subdivision, transform, leaf walker, ordinary emitter, depth/screen clip and bin insertion. The import's entire executable section equals private retail PE. It is Ghidra execution of original instructions, not native Windows or the complete retail frame.

Supplied: licensed input bytes through resource/Win32 file and mapping services; deterministic heap/scratch memory and 640x480 viewport; root pose and velocity; selected CRT/OS/resource services; omitted WRLD peripheral/texture initialization and failed palette acquisition. The narrow inherited host x87 service handles FISTP at 004935EE/00493608 and FPATAN at 00492EAF; inherited FTOL and trigonometric services remain explicit. Initial FPU control word is 037F. Original clip output is copied through a supplied CRT memcpy. No geometry decisions are substituted. `shade` and `high` add named supplied light/resource controls, not authentic lighting discovery. Consult the inherited #140 SERVICE_LEDGER.md and #76 provenance for the complete scaffold; `I76_CameraBase.java` is copied unchanged from #140, the observer extends its selected instruction logs and controls.

Python binary64 plus explicit float32 stores approximates x87 intermediate arithmetic. Every selected decision matches, but nearby shade/facing ties, other FPU control words, degenerate geometry and nonfinite values remain outside certification. High-color per-vertex data, successful alternate emitter, authentic mission lighting, additional-center, C.end/D.end anchors, output textures, palette/UVs, draw services and framebuffer pixels remain unresolved. No C++, canonical manual, shared tool or old run changes are proposed.
