# I76 — authenticated M06 original-renderer image oracle and validation plan

**Status: planning proposal, NOT a promoted original-engine finding, captured retail frame, RND-v1 acceptance record or permission to implement a renderer.** Research track: **i76exe**; advisory RND/TER/GEO/RES/OBJ/VEH interfaces. Proposed against protected main **3f06c23744765a5b209e4363add0a28853371f2a** (2026-10-31). Applicable governing documents: [agent entry](../../AGENTS.md), [publication policy](../../agent/protocol/access.yaml), [bootstrap](../../agent/protocol/BOOTSTRAP.md), [documentation workflow](DOCUMENTATION_WORKFLOW.md), [RND-v1 contract](subsystems/RND_ACCEPTANCE.md), [RND discovery](subsystems/RND.md) and [capability roadmap](CAPABILITY_ROADMAP.md). The proposed fixture, metrics and gates below need a separate **maintainer fixture/threshold decision before scoring any future independent implementation**. The existing SC-RND and RND-R1/R2/I1/P1 criteria remain unchanged.

## 1. Objective, source boundaries and evidence policy

Define a falsifiable, independently replayable **camera → visibility → original M06 terrain and stock vehicle → clipping/draw → indexed image** test involving at least one original stock bus or GTSi, an authenticated M06 terrain region, and **two distinct reproducible camera/root configurations**. This document specifies the oracle-acquisition and validation protocol, not the renderer or a substitute for acquiring the oracle. Neither a plausible bitmap nor a verifier's successful structural count proves original retail image equivalence.

Four source tiers must never be silently combined:

- **RET — authenticated retail execution:** real licensed original retail executable/software-render path producing a captured state/frame with proven capture, palette, stride, timing and surface ownership; **no such complete M06 image is evidenced in the inspected accepted runs**.
- **O — original-instruction execution:** authenticated retail x86 instructions retired in Ghidra with traceable original writes and explicitly supplied OS/resource/math/device services. Valid for the exact executed boundary only; not automatically RET.
- **D — original-derived diagnostic / independent model:** independently computed projected vertices, bins, spans, byte addresses or analytical expected bytes from O traces and authenticated source assets. A model is a checker, **not a second original observation**.
- **X — controlled or substituted:** harness-authored roots, time, heap backing, chosen resource/palette/context, optional material/texture/clip callbacks and synthetic diagnostic shade tables. Every byte and service owns its declared provenance; X is never promoted to O/RET by passing a test. **U** denotes unresolved ownership/value.

**Accepted evidence, explicitly bounded.** [#67][p67] executes persistent 472-byte camera state at 004C2730 across supplied roots; [#69][p69] identifies adaptive M06 TER source vertices/leaves; [#70][p70] executes camera→original vehicle queue→GEO in one state; [#73][p73] measures native vehicle projection; [#74][p74] measures terrain transform/clip/bin under separately authored view inputs; [#75][p75] measures original vehicle draw commands and packed spans; [#76][p76] executes one original camera→M06 terrain clip/bin; [#77][p77] executes 210 native indexed writes into an allocated **diagnostic** 640×480 buffer with a synthetic shade table; [#80][p80] executes original M06 terrain and stock-vehicle producers and consumers together, **but substitutes downstream clip/draw services**; [#81][p81] executes original shade generation for **one color column** from authenticated M02 ACT bytes installed by a harness, followed by 210 native indexed writes. The inherited GEO nearest-color service still controls the command color. Thus **no accepted complete terrain-plus-vehicle native M06 framebuffer, authenticated M06 palette/material-to-RGB mapping or retail software-frame image exists**. Consult the [M06 reference](../reference/engine/m06_visual_terrain.md) and [software renderer reference](../reference/engine/software_renderer.md); their dated status descriptions must not override newer immutable runs.

**Scope exclusions:** do not infer mission spawn, physics-produced poses, full selected-player post/WinMain, a retail device lock lifecycle, textured/UV output, arbitrary camera modes, hardware-backend parity, UI, sky, roads, weather or complete lighting merely from this selected software-render path. If an excluded pass contributes to pixels in the final fixture, either authenticate it or declare a reviewed exclusion/mask; never silently omit it.

## 2. Proposed fixture identity and ownership contract

**Fixture ID:** proposed **M06-RND-IMG-v0**, experimental, with versioned fixture decision required to become authoritative. Every field below is mandatory in the eventual machine-readable manifest. Missing fields must be an explicit **null / U with blocker**, not guessed or filled from image appearance. All paths to licensed inputs are private logical references, not material to publish.

| Field group | Required immutable data / ownership |
| --- | --- |
| Specification and execution | Schema/version, fixture version, reviewer decision commit, original proof/run IDs, source repository main/branch commit, selected software path and specific call sequence; Ghidra version/program/GZF identity for O; host/OS/runtime/CRT versions and original PE section hash. |
| Retail resources | Per-file SHA-256 and byte count for i76.exe, I76.ZFS, miss8/M06.MSN, miss8/M06.TER; archive member names, offsets, extraction algorithm and **per-member** SHA-256 for VCF/VDF/VLOC/GEO/TMT, WRLD/TDEF/ZMAP/ZONE, required MAP, palette ACT/LUM, texture VQM/M16 if used. Distinguish retail source digest from independently generated extracted-file digest. No generic TMT name implies texture/color identity. |
| Scene and object graph | Original-created VCF root IDs, selected/unselected spawn status, registry entries, child/body/GEO owner IDs, source resource names/section and face IDs, world basis/translation float formats, world/draw order; hashes of the **full registered state snapshot**, not just convenient visible objects. |
| View and camera | Original 00405970 builder, 00406AB0 call order, full 472-byte 004C2730 pre/post samples, out-of-record smoothing/history, roots as exact typed bytes with original writer PCs or X source, camera +40 matrix (9 float32, padding, 3 float64 translations), camera origin +160, frustum/local/world corners, projection scales, center, near/far, pose time/delta/velocity/mode/angles and record byte hash. |
| Terrain | Exact M06 page-pointer grid, sampled ZMAP cell/page, TER offset/packed 16-bit word, height/class/bit provenance, leaf/edge/index chronology, grid and world coordinates, source-to-transform chain, selected region bounds, original emitted primitives and materials/UV/texture descriptors where actually known. |
| Surface, palette and image | Backend selector and documented original software call path; viewport **640×480 proposed only**, inclusive maxima **639/479**, pitch and 8-bit indexed top-down or empirically verified alternative; descriptor +00/+14/+1C/+20/+24/+28, full allocation/guard/lock provenance and lifecycle; ACT/LUM/context selection, palette/index conversion, shading table and writes; capture time and RGB expansion rule with source. Never infer RGB from 8-bit values alone. |
| Controlled services | Per-boundary address/PC/callee, input/output bytes, allocation size/base/initialization, side effects, call count, deterministic RNG/time/x87/CRT/trig settings, forbidden host writes, explicit native-versus-host math, optional null resources, callsite predicates and failure behavior. |
| Oracle and evaluation | For each layer, original writer/source-PC evidence, source tier, trace/buffer/hash, canonical byte order/float rounding, expected record counts, signed-mask/coverage definition, independent verifier revision/hash, approved threshold-policy version, blind evaluation set, known missing fields and artifact-level SHA-256. |

**Known retail inputs** (hashes transcribed from accepted [#80 manifest][m80], not remeasured here): i76.exe SHA-256 **bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3**; I76.ZFS **0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d**; M06.MSN **923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f**; M06.TER **fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea**; annotated Ghidra 12.1.4 v97 GZF **b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce**. The full M06 material/ACT/LUM/texture input digest set is **not** authenticated for an image.

### Illustrative nonauthoritative manifest (YAML sketch, NOT executable acceptance input)

~~~yaml
schema: proposed-render-image-oracle/v0
status: illustrative-only
fixture_id: M06-RND-IMG-v0
publication_base: 3f06c23744765a5b209e4363add0a28853371f2a
ownership: {retail: RET, original_instructions: O, model: D, controlled: X, unknown: U}
private_inputs:
  executable: {name: i76.exe, sha256: bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3}
  archive: {name: I76.ZFS, sha256: 0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d}
  mission: {name: miss8/M06.MSN, sha256: 923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f}
  terrain: {name: miss8/M06.TER, sha256: fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea}
  ghidra: {version: "12.1.4", baseline: i76_mission_v97_verified_names,
           sha256: b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce}
  per_asset_sha256: null  # U: required; do not derive from filenames
scene:
  mission: M06
  terrain_region: {page_grid: null, ZMAP_cells: null, bounds: null, source: "PR80 controlled M06", ownership: U}
  objects:
    - {role: selected_camera_root, kind: stock_bus, source_vcf: nobus1.vcf,
       source_vdf: vxbus.vdf, root_id: "26000000", entry_id: "00542830", constructed_by: "0045EBD0/004AD6F0/004572B0"}
    - {role: unselected_visibility_target, kind: stock_bus, source_geo: xb11bdym.geo,
       root_id: "26100000", entry_id: "005428A8", constructed_by: "0045EBD0/004AD6F0/004572B0"}
  registered_state_sha256: null  # U: full snapshot required for each pose
surface:
  backend: original_software_proposed
  descriptor_contract: "00474C60 / 0047CB00"
  viewport: {width: 640, height: 480, x_max_inclusive: 639, y_max_inclusive: 479}
  pixel_type: indexed8
  pitch: 640  # X: diagnostic only until actual selected output surface is measured
  original_device_lock: null  # U
camera:
  builder: "00405970"
  update: "00406AB0"
  calls_per_pose: 2
  view_record: "004C2730"
  full_view_bytes: 472
  history_snapshot_sha256: null  # U: pin before scoring
  externally_supplied: {dt_f32: 0.016, velocity_f32: [2, 0, 1], angle_integers: [1, 1, 1]}
poses:
  - id: A
    origin: "PR80 visible case"
    selected_root_translation_f64: [2952.5, 60, 48152.5]
    target_root_translation_f64: [2952.5, 60, 48202.5]
    target_basis_f32_rows: [[0, 0, -1], [0, 1, 0], [1, 0, 0]]
    full_root_bytes_and_view_hash: null  # U: required
  - id: B
    origin: "PR80 contrast case; camera/root X+200"
    selected_root_translation_f64: [3152.5, 60, 48152.5]
    target_root_translation_f64: null  # U: export actual contrast-state bytes; do not guess
    target_basis_f32_rows: null       # U: export actual contrast-state bytes
    full_root_bytes_and_view_hash: null  # U: required
services:
  inventory_ref: "PR80 SERVICE_LEDGER plus new pixel-path ledger"
  native_callback_substitutions: null  # U: must be eliminated/explicitly gated
  crt_ftol_semantics: null             # U: pin implementation and observed range
palette:
  intended_M06_ACT_LUM_and_context: null  # U: PR81 m02.act is NOT an M06 decision
  material_color_binding: null           # U: no verified original GEO color mapping here
  exact_indexed_image_sha256: null       # U: no complete M06 image
  palette_to_RGB_mapping_sha256: null     # U
oracles: []                 # U: populated per layer with RET/O/D/X and evidence hashes
threshold_policy_sha256: null  # U: maintainer-approved before implementation scoring
~~~

The values in this sketch describe **source-backed candidate conditions and deliberately unfilled fields**, not a valid end-to-end fixture. In particular #80's contrast must be replayed to export **both** roots, view and registered state for B. The two poses must differ in measured camera projection and terrain/vehicle contribution, with stable service parameters. Do not reuse #69/#74's synthetic view, #70's near=0/far=4095 consumer bound or #77's diagnostic indexed result as if it were #80's M06 pixels. #76 derives original camera near=0.1/far=150 for its fixture; original terrain depth bounds, scan limits and framebuffer descriptor dimensions have separate provenance.

### Required final two-pose freeze

Create independent **cold runs A and B** and a same-state **A→B (and B→A) sequence** only if its camera-history semantics are explicitly modeled. Seal and hash original full view+out-of-record smoothing, original object registry, terrain grid, source pages, constructed GEO/TMT, arena state **before production**, and output descriptor. A/B root poses must be selected from source-backed #80 exact replay or a newly approved measured setup, not optimized after output inspection. Require nonzero scene content for A and a distinguishable material/geometry/coverage change for B; if that does not occur, report the negative and request a reviewed fixture revision rather than choosing another favorable camera. Running the original callback twice with unchanged input is not a two-pose test.

## 3. Seven independent comparison layers

Produce **separate oracle records** for each layer. For every record store: fixture_id/pose/case, phase, owner, writer PC or RET capture point, source tier, baseline/input IDs, endian/width/coordinate system, raw and typed artifact hashes, expected+observed counts, comparisons, differences and blocker. Run each verifier **without invoking the experiment's producer/Ghidra code**. Preserve both chronological events and final state: event sequence is not a substitute for final bytes and vice versa.

| Layer | Required source oracle and representation | Independent check | Decision / boundary |
| --- | --- | --- | --- |
| **L1 Camera / projection** | O 00405970/00406AB0, 472-byte 004C2730, history/global inputs, root object snapshots and writer PCs; float32 matrix and float64 camera/corners, derived transform equations. [#67][r67], [#76][r76]. | Exact unchanged fields and typed float/ULP comparisons with explicit x87 rounding model, transpose/translation/frustum/pose differential; no NaN accepted for positive cases. Check x/y viewport ordering (639/479). | **Exact** original-owned bytes when same instruction emulator/config; **numeric-bound** only after separately characterized runtime/platform differences. History drift and manufactured view → fail. |
| **L2 World visibility and queue** | O 004572B0 registry, 00457FF0 visitation/classification, 0048F9B0 arena and 0048FE10 kind-6/kind-10/terrain work records, owner and bucket/link bytes; O 0048FAC0 consumption/clearing. [#70][r70], [#80][r80]. | Exact discrete object and record identities, source PCs, spatial bucket chains/ordering, final reset; negative cull/empty. Pointer relocation normalized **only** through an agreed stable object-ID map, not by ignoring owner mismatches. | Any missing/misowned record, synthetic insertion or unauthorized store → **fail**, even if final screenshot resembles reference. |
| **L3 GEO / terrain source and emitted geometry** | RET resource digests + O ZMAP/TER grid, packed 16-bit height/material, adaptive shared edges/leaves, 004937C0 world transforms, 00491A30 emitter, VCF/GEO face/source indices; primitive identity/vertex list JSON+binary. [#69][r69], [#74][r74], [#80][r80]. | Recompute page/row/col→word→height and material, confirm original writer PCs; exact source indices and winding, counted/ordered accepted primitives, float32 transform at measured storage boundaries. | Correct raster color with wrong terrain page, omitted faces or altered winding **fails L3**, cannot be masked by perceptual scoring. |
| **L4 Clipping, order, projection and materials** | O polygon wrapper 00471FD0, native 0047C8D0/0047BF00 and 0047B8C0, ordered post-clip 24-byte vertices and flags; original material/UV/texture descriptor bytes when available. [#73][r73], [#74][r74], [#76][r76]. | Typed vertex screen X/Y/q, source-attributed clip intersection, near/far/viewport boundaries, winding, exact draw submission order; material descriptor provenance and UV semantics independently decoded. | Separate **geometry**, **quantization** and **material-unknown** outcomes. BF00 fallback without an actual intersection is not positive clipping-intersection coverage; TMT name is not texture proof. |
| **L5 Draw, scan, interpolation and packed spans** | O 0047CE40, original 96-byte draw commands, 32-byte edges, shade planes; 00473640/00474380 packed spans, stores and finalizer/callback chronology. [#75][r75], [#77][r77]. | Exact packed (x,length,y), command index/order/links/allocations/guards, original vs recomputed scan conversion, shade-index trajectory and per-pixel write addresses. Decode packed fields instead of comparing only counts. | Strict span equality when same rounding/runtime; if x87 differences measured, separately classify one-stage numeric divergence **before** considering a proposed tolerant span metric. |
| **L6 Palette/shade and native indexed bytes** | O 004791E0 per-column shade stores, 0047CB00 table lookups, 0047CC62 indexed byte writes, input palette/context/LUM provenance, full indexed buffer, pitch/base/guard and write trace. [#77][r77], [#81][r81]. | Authenticate resource palette **and** its scene selection, expected command color, native table index→byte, compare full buffer and per-write PC/address/value, nonwrite sentinels and guards. Distinguish PR77 supplied synthetic table from PR81 one original-produced column. | Where deterministic native indexed input is proven, **exact byte equality** is the preferred pass criterion. A synthetic table or harness-installed M02 palette can validate a bounded O writer but **not** authentic M06 color. |
| **L7 Final RGB / captured image** | Only RET captured original software surface with authenticated palette/DAC, scanline pitch, orientation, display conversion, clipping and capture timestamp; or separately approved O fully native M06 image oracle with all X effects declared. | Exact RGB expansion of verified indexed bytes/palette first; only then masked pixel mismatch, edge/coverage maps, spatial/perceptual metrics and cross-pose difference maps. Authenticate display compositor/scaler/gamma path independently. | **Blocked until provenance exists.** If palette/transfer/retail capture is U, report **not comparable**; an attractive RGB image or SSIM/LPIPS score cannot pass L1–L6 or prove original RGB fidelity. |

**Standard outcome vocabulary for each layer/case:** **PASS-EXACT**, **PASS-APPROVED-BOUND** (with threshold-policy ID), **FAIL-SEMANTIC**, **FAIL-NUMERIC**, **FAIL-IMAGE**, **INCONCLUSIVE-REFERENCE**, **INCONCLUSIVE-SERVICE**, **NOT-APPLICABLE** (reviewed exclusion). An artifact hash match alone is not a source-ownership result; absence of a ground-truth reference cannot be recorded as PASS. Final suite PASS requires *all mandatory independent layer gates*, not an average score.

## 4. Image and numerical metrics: conditional, not interchangeable

| Metric | Best use and limitations | Proposed policy |
| --- | --- | --- |
| Full indexed-frame equality, per-byte SHA-256 | Gold standard for same source palette/commands, deterministic emulation and exact surface pitch; sensitive to one genuine byte and correct background/sentinel. | Compare raw width×height×pitch and owned writes **exactly** if both sides have source-authenticated identical index interpretation. Hash equality is a shortcut, not a substitute for provenance. |
| Coverage mask, foreground occupancy, missing/extra masks | Separates absent scene geometry from color changes; image-derived segmentation alone can mistake palette black for background. | Prefer original write/face-ID coverage oracle; compare missing and spurious contributions per object/terrain, including zero-output controls. |
| Source-space and projected edges/vertices | Reveals wrong transforms, culling and clip failures before rasterization. | Compare identifiers/order and numeric coordinates; record quantization phase and per-stage ULP/absolute/relative residuals, not arbitrary pixel allowances. |
| Pixel mismatch count/rate and channel absolute error | Diagnoses index or RGB mismatches after exact size/layout/palette established; a low mismatch percentage can hide a missing small vehicle. | Report global and **per-contribution ROI** rates, mismatch coordinates, histograms, heatmaps and worst connected component; cannot alone pass. |
| Boundary distance / symmetric Chamfer / Hausdorff / IoU | Diagnoses small edge shifts and missing shape; may hide missing thin objects or topology. | Only secondary spatial diagnostics, with per-object coverage and topology/count checks. Distinguish camera displacement from raster rounding. |
| SSIM / multiscale SSIM / LPIPS or other perceptual measures | Useful for observational RGB fidelity only after source geometry/palette/reference proven; insensitive to some missing tiny objects and permissive to recoloring. | **Never** sole criterion. Compare only explicitly registered, non-rescaled images using preregistered masks; retain exact and coverage results. |
| Numeric per-stage tolerances | Float32 storage, x87 intermediate, projected q/clip and screen raster rules may yield different legal rounding across platforms. | Pin function-specific ULP/absolute/relative rules **using original-vs-original controlled repeats or independent numerical error budget**, not against the future implementation. No universal tolerance exists. |

**Failure triage order:** validate input/region/pose and original service ledger → L1 matrix/camera → L2 visibility and object ownership → L3 source geometry → L4 clipped vertices/material → L5 spans/addresses → L6 indices and palette → L7 RGB. Source palette mismatch with exact geometry, spans and index addresses is **COLOR-PROVENANCE**, not geometry pass or generic pixel regression; changed records/buckets are **CULL/VISIBILITY**; same primitives but moved vertices are **TRANSFORM/CLIP**; same geometry but altered packed x/length is **RASTER/QUANTIZATION**; wrong palette conversion with byte-identical indices is **RGB-INTERPRETATION**; stubbed clip/material/table/lock is **SERVICE-SUBSTITUTION**. For each failing layer retain the **first divergent original PC/event**, input-state diff and affected downstream pixels. Never adjust a pass mask to exclude a newly failing object.

### Threshold pre-registration and approval

1. **Collect calibration independently of replacement output:** repeat fresh-original emulations of identical input with same and changed host/floating-point configurations; independently run numerical reference equations and measure stage-specific residual distributions; obtain paired RET captures if feasible. Log stability at typed fields, spans and pixels; do not treat across-platform drift as harmless without cause.
2. **Propose per-field policies** with provenance, exact integer/byte sets, coordinate units, float decoding and rounding/storage points, acceptance coverage, worst-case calibration residual, guard bands and identified reason for every exception. Candidate thresholds may be expressed as formulae/ULP budgets, not selected magic constants. Include exact/strict fallback and rejected alternatives.
3. **Freeze a versioned fixture, calibration dataset, source-oracle hashes, policy JSON and independent-verifier hash before testing an independent renderer.** A human maintainer explicitly reviews/approves them in a distinct PR/decision; the freeze commit and timestamps become required run input. The worker writing a renderer must not approve its own tolerance.
4. **Hold out at least one authenticated repeat/control** and use deliberate false outputs to test whether each bound rejects missing geometry, flipped winding, wrong palette, one-byte/index mutations, shifted spans and stale state. An overpermissive bound fails calibration.
5. After scoring, **no silent threshold tuning**: changes require a separately reviewed new policy version, justification against source-only calibration, and side-by-side scores of old/new suites. Previously failed results remain recorded. If original nondeterminism prevents a justified bound, classify **INCONCLUSIVE**, not pass.

Historical #67/#74/#76 numerical tolerances are **their own source-run verifier rules**, not a blanket authorization for image parity. PR77 exact diagnostic bytes and PR81 native single-column color table are valid *bounded calibration exemplars*, not thresholds for final M06 images.

## 5. Reference-oracle acquisition alternatives

| Candidate | Strength | Limit / permissible claim |
| --- | --- | --- |
| **A. Authenticated retail software-render capture** | Best potential RET image truth if original software backend, resources, timing, palette, viewport, memory surface and capture provenance are independently verified. | No accepted source establishes it today. Desktop screenshots alone may contain compositor/gamma/scaling effects; must prove actual original frame and capture chain. Retail environment/licensing and instrumented capture are prerequisites. |
| **B. Deterministic Ghidra original-instruction fixture** | Replays precise executable instruction PCs and original-owned camera/records/geometry/spans/index writes with source-byte audits and negative controls; independent verifiers possible. | Substituted OS/heap/x87/CRT/resource/display, chosen poses, stubs and missing M06 material path may diverge from RET. Valid O evidence only through executed boundaries; original-instruction code plus external native calculation is not a full original retail image. |
| **C. Original-derived primitive/span/indexed-byte traces** | Can validate narrow stage outputs and per-store ownership without a full retail frame; accepted #73/#75/#77/#80/#81 provide useful precedents. | No complete scene semantics if producer stages are separately sourced or callbacks substituted. Do not concatenate independent runs to manufacture one native M06 image or conflate diagnostic synthetic colors with authentic colors. |
| **D. Independent numerical models** | Robust, inspectable checks of source page/height decoding, projection, clipping, packed spans, shade recurrence and expected buffer addresses; detect deliberate trace corruption. | Model predictions are D, never RET/O. Shared assumptions with implementation create correlated error; independent code, different algorithmic derivations and source fixtures are required. |

**Preference:** attempt A (where lawful and reproducible) and B as complementary anchors. Use C for narrow exact-byte gates, D for stage interpretation and negative controls. If A remains unobtainable, require a reviewed decision that specifies what authenticated B/C evidence can serve **each exact acceptance layer**; no blanket assertion of retail parity or authentic RGB. For every selected oracle include executable SHA, private-source acquisition authority, copyright/licensing basis, extraction member digests, trace custody (producer/version/time/host), output SHA, independent recomputation and the precise original instruction boundary. Public commits contain only allowed small derived summaries, hashes and scripts; keep proprietary executables, resource bytes, ACT/LUM payloads, GZF databases and large raw framebuffer dumps in authorized private storage with digest pointers. Never redistribute a proprietary screenshot/asset absent permission.

## 6. Positive, differential and negative control matrix

All cases use versioned immutable inputs and distinct cold emulator processes except explicitly labeled continuity tests. **Expected original behavior** must be measured and frozen; values listed from accepted historical runs below are examples within their **own** scopes, not invented future image expectations.

| Case | Scene intervention | Required observation / nonpass condition |
| --- | --- | --- |
| P-A | Candidate original selected camera bus, unselected registered target and M06 terrain, pose A | O camera→both producers→consumer identity and source polygons; eventual original clip/draw/index output when actually obtained. Current [#80][r80] reports **30 terrain records, one kind-6 and two kind-10** in this controlled case, but only through substituted downstream callbacks. |
| P-B | Exact measured #80 contrast pose B (camera/root X+200), unchanged remaining service ledger | Distinct view and terrain records; #80 reports **13 terrain records, one kind-6 and two kind-10**, not image bytes. Pin both complete roots and preserved camera history in future fixture. |
| P-repeat | A and B repeated in separately imported GZF + fresh process, separately re-extracted resource identity checked | Byte-identical native stage trace/sidecars where deterministic; record any nondeterminism and refuse exact pass absent normalization justified from source. |
| P-history | A→B, B→A and cold-B with all camera smoothing data preserved/reset **as specified**, no silent reinitialize | Contrast valid temporal change from stale view, suppressed callbacks or different smoothing history ([#67][r67]). |
| N-empty / N-camera-only | Empty world; selected camera object without second target | No target kind-6; authenticated optional camera-owner kind-10/terrain may remain when appropriate; don't demand empty entire scene if original still draws terrain ([#70][r70], [#80][r80]). |
| N-behind / N-below | Move target behind view; move both roots below sampled terrain | Verify actual original cull/rejection; #80 behind retains 30 terrain/zero target kind-6, below retains target kind-6/zero terrain. Treat original-owned light records separately. |
| N-invalid | Zero/nonfinite root basis, null VLOC/live pointer, invalid/broken view | Rejection or explicitly measured failure; no finite-camera positive assertion. Guard unsafe reads before contact with foreign memory. |
| N-resource | Wrong M06.TER page/word/asset hash, missing GEO or palette/context | Fail provenance before comparison, or report guarded original failure; **never** use placeholder palette or fabricated texture to pass image stage. |
| N-corruption | Tamper record owner/bucket/link, source vertex, camera matrix, clip coordinate, material, span x/length, pixel value, palette table store destination | Each independent layer rejects tamper with a specific earliest mismatch, even if total draw count remains constant; require separate corruption controls for terrain and target. |
| N-surface | Missing descriptor/base; invalid pitch/offset/viewport; undersized allocation | Guard failure / zero permitted writes as measured. For authorized writes require intact 16-byte or stronger pre/post sentinels and exact owned range. Original #77 missing-surface stops **before** unowned read; this is a probe guard, not a retail error handler. |
| N-service | Deliberately replace native clip/draw with success stub or swap synthetic shade table/palette context | Explicit **INCONCLUSIVE-SERVICE**, never native image PASS. Show exact affected layer and resulting artifact differences. |
| N-cross-pose | Deliberately present A view with B terrain/vehicle or stale framebuffer; swap camera scene hashes | Fail linked fixture identity and cross-pose provenance even if perceptual image similarity is high. |

Reject controls should cover semantic mutations (not only corrupted JSON) and the **independent verifier must demonstrate actual rejection**. Negative evidence that a function cannot run under an unsupported import is not a claim that retail would fail.

## 7. Reproduction and artifact contract

A future original-instruction worker should publish a new immutable **i76exe run** following current protocol; this *planning PR itself is not a run*. An oracle dataset must be exportable from authorized private storage and independently validated without historical chat or access to a concurrent agent's scratch workspace.

**Required outputs per fixture version, pose and control** (small derived tables/hashes may be public; private raw payloads remain private): 

1. **manifest.json**: fixture ID, original main/commit, PE/ZFS/MSN/TER/member/GZF hashes and sizes; camera/object/state exact typed byte hashes; backend and viewport; full X service ledger; original/controlled provenance tags; original PC/stop/RET chronology; reference fixture and threshold-policy IDs, private storage logical identifiers.
2. **service-ledger.md/json**: every external service by import/callsite/PC, arguments/results and range, allocation/guard/time/math/floating-point and device/palette acquisition; host write guards on sealed queue/view/geometry/framebuffer. Include unserviced failures and intentional substitute behavior. Report first original opcode/host boundary after which the claim stops.
3. **layer-L1..L7**: schema-versioned typed JSON/TSV events and (when authorized) binary snapshots for camera matrices/history, registry/records/buckets, source terrain/GEO and transformed vertices, clipped primitive lists/material/UV descriptors, commands/edges/packed spans, table-column writes/indexed buffer with exact pitch/guards, and RGB with its conversion decision. Each row carries stage PC, field width, source tier and owner. Empty/unknown layers get an explicit machine-readable blocker, **not fabricated zero-valued images**.
4. **references.json + thresholds.json**: per-field original vs model provenance, oracle source hashes/paths, approved exclusions and pre-implementation freeze/maintainer decision link. Score results are written separately from immutable expected values.
5. **results.json**: per-layer verdict/diff counts, per-object coverage, maximum coordinate residuals, first diverging PC, palette-vs-geometry classification, repeat-stability results, negative/corruption outcomes, blocked/missing references and old/new scores for any policy revision. Never collapse fail and not-measurable into success.
6. **reproduce and verify scripts**: versioned precise commands/environment dependencies to regenerate from **licensed private inputs**, without internet/chat requirements; independent verifier does not import the original trace producer or invoke Ghidra; peer can validate public metadata/hashes when private inputs are unavailable.
7. **SHA-256 inventory**: byte size + hash for every raw and derived artifact, manifest, verifier, threshold policy, trace, frame, guard file and negative run; fresh-state repeat must compare hashes after clearly documented safe normalization (no wholesale removal of mismatched original fields).

**Reproduction procedure:** verify access/licensing and hashes → clean private Ghidra import of authenticated PE → source opcode audit → initialize only declared services → execute A/B and all controls → seal output ranges → collect pre-instruction/original-store/event/final raw state → replay against independent decoder and numeric checker → verify guard regions and scene/palette consistency → run deliberate corruption tests → compare fresh-state exact hashes → emit per-layer verdicts and unresolved block list. Store full commands and tested tool versions. Failure at any prerequisite yields an explicit stop boundary and reason, not a blank synthetic replacement. Reproduce only legally held material; original bytes are never required to be pushed to this public repository.

## 8. Evidence and acceptance-dependency matrix (as of pinned main)

**Labels:** **established** means that particular bounded observation is present; **partial** means at least one subdependency is demonstrated but the *scenario/gate as a whole is not passed*; **missing** means no authenticated reference/output for the required boundary; **approval** means explicit future maintainer decision/authorization is required. No gate statuses are changed by this plan.

| Existing scenario or gate | Current dependency state | Specific evidence and remaining requirement |
| --- | --- | --- |
| **SC-RND-01** camera/two poses | **Partial** | Established O camera continuity [#67][r67], coherent native M06 view/differential [#76][r76], unified controlled A/B [#80][r80]; freeze complete A/B root/view/history/scene bytes and original vs supplied cause before declaring this *proposed* fixture accepted. |
| **SC-RND-02** registry, visibility and cull | **Partial** | Original stock visibility/queue [#70][r70]; #80 original M06 terrain+target buckets and behind/camera-only. Original scene fixture, all relevant owners/buckets and human case review still required. |
| **SC-RND-03** source GEO/material consumer | **Partial** | [#69][r69] terrain source, [#74][r74]/[#76][r76] transform/clip/bin, [#70][r70] GEO; [#80][r80] same-state terrain+vehicle consumption. Source-authenticated **displayed** material/UV/texture descriptor remains incomplete; #80 substitutes downstream callbacks. |
| **SC-RND-04** vehicle + terrain interpretable native output | **Partial / missing image** | Vehicle projection [#73][r73], commands/spans [#75][r75], native indexed diagnostic writes [#77][r77] and one resource-backed shade column [#81][r81] are **established only for separate stock-vehicle diagnostic**. #80 M06 downstream clip/draw is X. Combined original M06 native raster and authentic material/image **missing**. |
| **SC-RND-05** second-pose output | **Partial / missing image** | [#76][r76]/[#80][r80] A/B original terrain and visibility differential established. No two-pose authenticated native framebuffer or original-to-image comparison; repeat/threshold policy **missing** and **approval required**. |
| **RND-R1** camera + visibility research | **Partial / approval** | Camera and original producer evidence [#67][r67], [#70][r70], [#80][r80] strong for controlled conditions; final ratified M06 scenario cross-check, source promotion and human gate review absent. |
| **RND-R2** geometry/material/output research | **Partial / missing** | Original source→clipped/binned primitives and separate native spans/bytes supported by [#69][r69], [#73][r73], [#74][r74], [#75][r75], [#76][r76], [#77][r77], [#80][r80], [#81][r81]. Valid native **M06** material/palette and joined final boundary missing; requires source promotion/approval. |
| **RND-I1** one same-state original pipeline | **Partial / missing** | [#80][r80] reaches original terrain+vehicle producer/consumer in same camera/arena; clip/draw callbacks X and no complete same-state native palette/index buffer. [#77][r77]/[#81][r81] cannot simply be appended as a virtual same-state run. Human acceptance decision required after new integration evidence. |
| **RND-P1** maintained image parity | **Missing / approval** | Original-to-image fixture, authenticated M06 reference, approved metrics and independently maintained renderer do not exist as accepted completion here. **Separate implementation authorization** and [RND-v1 contract](subsystems/RND_ACCEPTANCE.md) and maintainer approval remain mandatory. |

**Gap ledger aligned to RND-v1 (not new gates):** **G-RND-05** needs authenticated terrain/environment **material→native draw→framebuffer** continuity; **G-RND-06** needs approved **original-to-image reference and threshold version**. Actual palette/LUM selection and GEO nearest-color command-color input, original native M06 clip/draw callbacks, full shade-table/populated color columns as needed, device/surface capture chain and two-pose references are direct, testable prerequisites. Original Windows/selected-player scheduler belongs to the separate CAP-CONTROL/CAP-SLICE integration unless proven indispensable to the selected image fixture. See [CAP-CAMERA-01 and CAP-SLICE-01](CAPABILITY_ROADMAP.md).

## 9. Minimal actionable prerequisite handoff for original-instruction workers

- [ ] **Freeze A/B input snapshots:** replay [#80][r80] with fresh licensed inputs; export *both* original root poses, registry, exact 472-byte camera/history and pre/post arena snapshots, source M06 page/primitive IDs; confirm two distinct views and target+terrain contributions, with hashes. Do not guess #80 contrast target coordinates.
- [ ] **Establish M06 displayed material/color ownership:** instrument original WRLD ACT/LUM/context selection, original GEO 00446C90→004796A0 binding, texture/UV/material descriptor lookup and 004791E0 column/table update, showing whether selected palette differs from [#81's M02 ACT][r81]; capture original PC and bytes, not just resource names.
- [ ] **Connect native M06 output:** starting with #80's one-state trace, remove/characterize inherited clip and draw success services; execute original terrain and stock-vehicle draw/span callbacks and palette-backed indexed writes into a guarded measured surface; preserve all negative/retail opcode anchors. Do not splice #77/#81 outputs from another state.
- [ ] **Acquire/verify reference:** attempt lawful direct retail software-frame/surface extraction with complete palette/display metadata, or produce a newly accepted O image fixture with fully marked X services. Record exact failed import/guard if impossible; never substitute a generated screenshot.
- [ ] **Measure and submit independent calibration:** source-only fresh repeats, A/B differential, bad-owner/height/palette/span/guard controls, per-stage numeric and byte stability, independent verifier and digest inventory; propose thresholds in a separate pre-implementation human-reviewed freeze decision.

**Stop and review rule:** if an essential field cannot be measured, publish the bounded negative result, source PC and service dependency; mark the affected layer **INCONCLUSIVE** and the corresponding existing SC-RND gate **not demonstrated**. Nothing here amends the [RND-v1 contract](subsystems/RND_ACCEPTANCE.md), changes a finding, certifies an image or grants a self-merge.

## Evidence directory and immutable reproduction anchors

Each source entry links an accepted research PR, original run manifest, report, declared services and independent verifier. These are original evidence locations, not a joint image capture. Consult the run's own artifact hash list before trusting a copied sidecar.

| PR | Run evidence | Measured boundary and limit |
| --- | --- | --- |
| [#67][p67] | [manifest][m67] · [report][r67] · [services][s67] · [verifier][v67] | Full camera/history across controlled poses; no scheduler. |
| [#69][p69] | [manifest][m69] · [report][r69] · [services][s69] · [verifier][v69] | Authentic M06 adaptive source/leaf; controlled nonnative view and no image. |
| [#70][p70] | [manifest][m70] · [report][r70] · [services][s70] · [verifier][v70] | Original camera/vehicle producer-consumer/GEO; clip/draw X. |
| [#73][p73] | [manifest][m73] · [report][r73] · [services][s73] · [verifier][v73] | Native stock-vehicle projection and fallback; no native draw. |
| [#74][p74] | [manifest][m74] · [report][r74] · [services][s74] · [verifier][v74] | Original terrain transform/clip/bin with authored affine view. |
| [#75][p75] | [manifest][m75] · [report][r75] · [services][s75] · [verifier][v75] | Native draw commands/edges/spans; callback not executed. |
| [#76][p76] | [manifest][m76] · [report][r76] · [services][s76] · [verifier][v76] | One original camera + original M06 terrain bin, not consumer. |
| [#77][p77] | [manifest][m77] · [report][r77] · [services][s77] · [verifier][v77] | Original indexed writer with synthetic diagnostic shade table. |
| [#80][p80] | [manifest][m80] · [report][r80] · [services][s80] · [verifier][v80] | Same-state M06 terrain and stock vehicle through producer/consumer; downstream X. |
| [#81][p81] | [manifest][m81] · [report][r81] · [services][s81] · [verifier][v81] | Original single-column shade and native indexed writes with harness-installed M02 palette/controlled GEO color. |

[p67]: https://github.com/jf-stargate/i76/pull/67
[m67]: ../../agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/manifest.json
[r67]: ../../agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/artifacts/CAMERA_CONTINUITY.md
[s67]: ../../agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/artifacts/SERVICES.md
[v67]: ../../agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/scripts/verify_continuity.py
[p69]: https://github.com/jf-stargate/i76/pull/69
[m69]: ../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/manifest.json
[r69]: ../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/VISIBLE_TERRAIN.md
[s69]: ../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/SERVICE_LEDGER.md
[v69]: ../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/scripts/verify_visible_terrain.py
[p70]: https://github.com/jf-stargate/i76/pull/70
[m70]: ../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/manifest.json
[r70]: ../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/REPORT.md
[s70]: ../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/SERVICES.md
[v70]: ../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/scripts/verify_integration.py
[p73]: https://github.com/jf-stargate/i76/pull/73
[m73]: ../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/manifest.json
[r73]: ../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/artifacts/REPORT.md
[s73]: ../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/artifacts/SERVICE_LEDGER.md
[v73]: ../../agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6/scripts/verify_polygon.py
[p74]: https://github.com/jf-stargate/i76/pull/74
[m74]: ../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/manifest.json
[r74]: ../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/REPORT.md
[s74]: ../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/SERVICE_LEDGER.md
[v74]: ../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/scripts/verify_handoff.py
[p75]: https://github.com/jf-stargate/i76/pull/75
[m75]: ../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/manifest.json
[r75]: ../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/artifacts/REPORT.md
[s75]: ../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/artifacts/SERVICE_LEDGER.md
[v75]: ../../agent/runs/i76exe/i76exe-20261031T011731Z-307babbf/scripts/verify_draw.py
[p76]: https://github.com/jf-stargate/i76/pull/76
[m76]: ../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/manifest.json
[r76]: ../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/REPORT.md
[s76]: ../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/SERVICE_LEDGER.md
[v76]: ../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/scripts/verify_context.py
[p77]: https://github.com/jf-stargate/i76/pull/77
[m77]: ../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/manifest.json
[r77]: ../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/artifacts/REPORT.md
[s77]: ../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/artifacts/SERVICE_LEDGER.md
[v77]: ../../agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/scripts/verify_raster.py
[p80]: https://github.com/jf-stargate/i76/pull/80
[m80]: ../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/manifest.json
[r80]: ../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/REPORT.md
[s80]: ../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/SERVICE_LEDGER.md
[v80]: ../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/scripts/verify_unified.py
[p81]: https://github.com/jf-stargate/i76/pull/81
[m81]: ../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/manifest.json
[r81]: ../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/artifacts/REPORT.md
[s81]: ../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/artifacts/SERVICE_LEDGER.md
[v81]: ../../agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/verify_palette.py
