# Retail I76 native spatial render queue → world/GEO traversal → polygon submission

**Scope:** original retail `i76.exe` original x86 instructions emulated by Ghidra 12.1.4 against the privately supplied annotated v97 program, with actual GTSi and bus VCF, GEO and TMT resource bytes. The result is a deterministic **controlled emulator** test, not live Windows gameplay, on-screen pixels or a full original frame.

## Parent research and starting boundary

Builds on the merged vehicle VCF/GEO/TMT evidence at `agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/` (v2.4.0), and separately reproduces the stronger material-to-raster experiment from draft PR #26 / run `i76exe-20261023T044729Z-42a0573a`. Does not promote either earlier draft PR or modify its run.

## Original frame-control sequence: source-backed

The two frame paths `00401CC0` (software) and `00401FA0` (D3D/hardware) call `00457FF0` for active-world-object visibility and geometry queue construction. Each later calls `0048FAC0` to consume sorted spatial work buckets. 

`00457FF0` walks active world entries, tests visibility, and creates 0x??-sized work records: a verified **kind 6** at record `+0x0C`, scene object at `+0x1C`, variant/mode value at `+0x30`, flag at `+0x34`, leaf indicator at `+0x38`, and linked/prior cache state at `+0x3C`. Other kinds (3, 5, 7, 11) are also present. Do not read their precise semantics solely from names. `0048FAC0` checks the bucket head and count, processes a record of kind 6 using indirect dispatch at `004FACA8 + kind*4` (kind 6 = `004FACC0`), and clears the bucket. `004FACC0` targets `0048F4C0`, which selects `0045D100` primary when record `+0x38` is nonzero, otherwise `0045D530` secondary.

`0045D100`/`0045D530` reset the per-pass render globals, walk owner/child geometry, call native section builders, arrange scratch render records in a depth tree, call original `0044A290` for material lookup when a textured record requires it, and call `00471FD0` for nonempty polygons. The clip/draw callbacks selected by `00471FD0` were intercepted in this experiment. The parent `00457FF0` itself was **not executed** during a full frame, and its actual visibility output was **not** used as input to the subsequent synthetic work-record test.

## Grounded render context and lifetime

At `00402F98–00402FAC` the game calls virtual region allocator `00498940` and stores its returned pointer to `005DD320` (transformed-position scratch). A second call at `00402FCA–00402FE3` stores a pointer to `005DD324` (render-record scratch). These are **allocated once as render-support memory**, while each traversal resets the record cursor and depth-tree root. The replay substitutes separately allocated memory of sufficient size at the same globals; the original game allocation and genuine camera state were not executed. The 16-float view context plus embedded matrix remain an identity-like synthetic test fixture.

## Original-instruction executions

For each vehicle, original `004AD6F0` constructs the full VCF graph, original GEO selection loads its exterior/cockpit body geometries, and the original TMT object/material bindings survive. Unlike PR #26, this run does **not manually call** the material binder or polygon wrapper to walk output records. Original dispatcher `0048F4C0` enters the complete primary/secondary render traversal, which walks the depth tree and issues its own material/submission calls.

| Vehicle / pass | Scratch bytes created | Native GEO builders | Native texture lookups | Polygon wrappers |
|---|---:|---:|---:|---:|
| GTSi primary cockpit (group 4) | 8,136 | 1 | 3 | 40 |
| GTSi primary exterior (group 0) | 1,320 | 1 | 1 | 1 |
| GTSi secondary on VCF root (group 0) | 1,656 | 1 | 0 | 0 |
| Bus primary cockpit (group 4) | 15,240 | 1 | 0 | 90 |
| Bus primary exterior (group 0) | 456 | 1 | 1 | 1 |
| Bus secondary on VCF root (group 0) | 1,224 | 1 | 0 | 0 |

**Important:** 132 native polygon submission wrapper invocations across the four primary traversals, **not** 132 textured polygons or rasterized pixels. The 90 bus-cockpit records submitted untextured under this controlled view context; the previous five-textured-submission figure counted a narrower manual handoff. Both numbers are valid for their respective experiment scopes.

A second experiment inserted a **synthetic original-layout kind-6 queue record** referencing the real GTSi or bus exterior body into a bucket at a fixed depth. Running **original `0048FAC0` instructions** consumed it, called the original dispatcher/tree/build/bind/submit sequence, and cleared the bucket's head/count. Each vehicle reached one additional native polygon submitter, one intercepted clip call and one intercepted draw call. This shows queue **consumption**, not native queue *production* or actual culling.

The eight original entrypoint test phases (six direct dispatcher traversals, two queued flushes) produced 134 original polygon-submission-wrapper invocations. Across two cold Ghidra replays, private traces were **byte-identical**, SHA-256 `ff42b1a90597d49e8ea12fed5cf7aa02da32c341af721fc998eedb7852d1dc46`. The 64 resource fixtures were independently extracted from an unchanged retail `I76.ZFS`. Private Ghidra input and full emulated trace are never committed.

## Unresolved and limitations

- **No true scene camera:** the projection context, culling and visibility are synthetic. The original producer `00457FF0` is statically traced but not executed over the full active-world registry.
- **No decoded pixels:** `004474B0` VQM acquisition, M16 fallback, CRT and Windows allocation, palette/light helpers are intercepted per the inherited VCF harness.
- **No true raster callback:** original `00471FD0` is entered, but its `0047C2F0` clip and `00487EA0` draw targets are substituted. No pixel/correctness or GPU output claims.
- **Original-mode conditions:** the camera-mode and spatial priority scheduling paths are not globally initialized. Other work kinds and object class paths are not exhaustively tested.
- **Ghidra x87 warnings:** not a bit-exact original floating point processor state; results are branch- and test-context-specific. No original game executable was run under Windows.

## Highest-value next original-code tests

Execute `00457FF0` with a minimal authentic active-world-object registry and controlled view data, capture actual emitted kind-6 work records and bucket indices, then run `0048FAC0` **without constructing the work record by hand**. Independently derive the original view transform setup from game camera constructors; only after this should the raster clip and VQM decode boundaries be progressively enabled.
