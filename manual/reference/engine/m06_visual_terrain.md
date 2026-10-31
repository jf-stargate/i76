# M06 visual terrain — original source, camera, adaptive polygon and bin contract

**Status:** Accepted bounded visual-terrain reference (merged PR #78) and unified terrain/vehicle submission extension (merged [PR #83](https://github.com/jf-stargate/i76/pull/83)); **not** an accepted renderer implementation or a complete retail M06 image.  
**Binary:** original retail `i76.exe` (`i76exe` track), advisory TER/RND interfaces; separate `i76edit` and shared renderer investigations are not silently incorporated.  
**Promotion crosswalk:** [historical M06 visual terrain decision (merged PR #78)](../../../agent/promotions/m06_visual_terrain_20261031.md); [accepted unified terrain/vehicle submission decision (PR #83)](../../../agent/promotions/m06_unified_terrain_vehicle_submission_20261031.md). Earlier promotion text is immutable decision history.  
**Evidence:** merged [#67](https://github.com/jf-stargate/i76/pull/67), [#69](https://github.com/jf-stargate/i76/pull/69), [#70](https://github.com/jf-stargate/i76/pull/70), [#74](https://github.com/jf-stargate/i76/pull/74), [#76](https://github.com/jf-stargate/i76/pull/76), and [#80](https://github.com/jf-stargate/i76/pull/80); see linked exact runs, manifests, service ledgers and promotion crosswalks. #80 remains merged *research evidence*; its bounded reference interpretation was separately accepted through merged PR #83.

## Interpretation and evidence tiers

The following is the **demonstrated bounded contract**:

```text
authenticated M06.MSN TDEF/ZMAP/ZONE + M06.TER
  → original WRLD/TDEF handlers and 128×128 page-pointer map
  → 004929B0 visible bounds, 00490A00 source/root setup
  → 004911E0 subdivision + 004918B0/004918F0 shared edges
  → 00491810 linked leaves / original source vertices
  → 004937C0 scale + affine transform using view+40
  → 00491A30 edge flattening/lighting/candidate walker
  → 004922F0 ordinary polygon work-record emitter
  → 00490590 scratch cursor → 0047BF00 depth/projection
  → 0047B8C0 screen clip → external CRT copy
  → 0048FE10 original spatial-bin insertion
  → 00457FF0 original stock-vehicle kind-6/kind-10 production
      (same persistent view and polygon arena; scratch is reusable)
  → 0048FAC0 original descending-bucket consumer
      positive-count terrain: direct 00471FD0 polygon submission
      zero-count kinds 6/10: 0048F4C0/00490640 typed dispatch,
      then original GEO/polygon preparation for the kind-6 body
  → 0048FD6D/0048FD7B bucket clearing and arena cursor reset
  → [NOT demonstrated: original downstream raster, materials or pixels]
```

Original projection and geometry state come from one **retained** camera record `004C2730`, produced by `00405970 → 00472220/00472400/00472530` and two `00406AB0` callbacks on an original-constructed and registered bus with a **controlled root pose**. The camera is not replaced between terrain selection and binning in #76, or between terrain, vehicle and consumer in #80. Earlier #69/#74 artificially authored aspects of that record and remain valid only within their declared diagnostics. Software-frame callsites `00401DE1 → 00490A00`, `00401E2C → 00457FF0` and `00401E8D → 0048FAC0` are **binary-static** scheduling evidence; #80 executes the three bodies directly in order, not the full original frame or intervening passes.

“Original-instruction” here means retail x86 executed under Ghidra 12.1.4 with explicit services; “binary-static” means disassembly/call/dataflow verified but not executed at the stated boundary; “independently derived” means verifier interpretation or reproduction, not itself a retail instruction; “externally supplied” means harness poses, allocations, resources or substituted service outputs; “unresolved” marks evidence not established. Every execution claim is limited to its named run and service ledger. Names are research labels, not original source symbols. No assertion about actual displayed texture or framebuffer follows from a successful bin insertion.

## Retail source identity and terrain scale

These source measurements are recorded by [#69's manifest](../../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/manifest.json) and [#76's manifest](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/manifest.json), not new hashes of private assets:

| Private original input / baseline | MD5 (when measured) | SHA-256 |
|---|---|---|
| `i76.exe` | `a640ea0097dbb62e0c77b7f2847c7161` | `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3` |
| `I76.ZFS` | `6dd57b1627d73e814247c0d9521f9778` | `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d` |
| `miss8/M06.MSN` | `d8801a3c9d2c79187b67e2f4b818b7db` | `923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f` |
| `miss8/M06.TER` | `5307dc057a8bbc53569c04d89bd7ca2e` | `fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea` |
| Annotated Ghidra v97 `i76_mission_v97_verified_names` | not supplied | `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce` |

The original-code audit of the imported annotated program compared its entire **765,952-byte executable section** to the private retail PE; its reported executable-section SHA-256 is `e58a54c0e39b55c2d0110cf8a6d22bedf8c53896a85b10dc7d1e8775cfe1318a`. Source runs independently verified sparse original PE opcode anchors; consult [#69 anchors](../../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/evidence/instruction_anchors.tsv), [#74 anchors](../../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/evidence/instruction_anchors.tsv), [#76 anchors](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/evidence/instruction_anchors.tsv). Ghidra baseline, source executable and terrain payloads remain private.

### Page/grid and packed sample provenance

- Original `004B8A10` WRLD and `00493910` TDEF handler dispatch execute with authenticated M06 MSN/TER; `00471400` file-mapping wrapper uses supplied Win32 file/mapping services. The original `00493080` initializes global grid step `006442C0 = 5`, reciprocal `006442C4 = 0.2f`, and installs **16,384** page pointers at `00644380`.
- `ZMAP` is 80×80 **page indices**; active source cells map to 128×128 runtime pointer-grid positions `(z+24,x+24)`; unoccupied cells use the original loader's default page. The M06 sidecar has **16 active 0x8000-byte pages**, each 128×128 little-endian uint16 samples. Do not equate the page index with the ZMAP cell or the final texture descriptor.
- Source lattice coordinates `(x,z)` use integer sample steps and per-page local row `z & 127`, column `x & 127`; low 12 bits `word & 0x0fff` provide height. Runtime source-to-world X/Z is **5 units/sample**, Y is original `float32(0.1)` times packed low12 (not historical exporter `409.5/4096`). `00493160/004931A4` read the original pointer grid and mask low12; `004927B0` retrieves terrain material classes separately. Packed bit 12 remains unresolved.
- Bits 15–13 (`word >> 13`) classify source *terrain surface material* (0–7). Original adaptive LOD reads the full word at `004915F7/0049160F/00491627/0049163F` and tests `word >= 0x4000 && (word & 0xe000) != 0xa000` (classes 2,3,4,6,7 satisfy this static condition; dynamically observed sample classes 3/7 are included). This is **subdivision predicate provenance**, not renderer texture resolution.
- Concrete #69 sample: first leaf address `440002A0`, flattened indices `23,20,15,22`, four grid vertices `(568,300,9608)`, `(576,309,9608)`, `(576,278,9616)`, `(568,252,9616)`. From TER page 0, offsets `0x0870,0x0880,0x1080,0x1070`, packed words `012C,6135,2116,20FC`, classes **0,3,1,1**. This identifies **mixed** source classes on a single leaf and prevents assigning a singular displayed texture from its source-bit pattern.

The original `00493080` grid and selected page/height/material reads are checked against authenticated TER bytes by the [#69 independent verifier](../../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/scripts/verify_visible_terrain.py) and [#76 verifier](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/scripts/verify_context.py). [Historical format model](../../../ref/level_format/i76_runtime_level_and_terrain_format_notes.md) and [editor material mapping](../../../ref/editor/road_terrain_serialization.md) are corroborating **cross-track/static** context, not original M06 polygon material tests.

## Original adaptive selection and leaf/edge ownership

| Retail function / data | Observed original responsibility | Evidence tier |
|---|---|---|
| `00490A00` (source frame CALL `00401DE1`) | Original terrain entry clears root/leaf/count/arena state, obtains visible bounds, writes four root vertices/edges, recurses, calls transform and walker | Executed through leaf boundary #69; through bin insertion #74/#76. Software-frame call source-audited |
| `004929B0` (call `00490B1E`) | Height/region guard, source position+frustum-corner hull, aligned root origin/exponent and plane globals | Executed #69/#76; invalid below-height view rejects without leaves |
| `004911E0` | Bounds-plane culling, scale/distance/height error, source material predicate, shared-edge refinement/leaf decision | Executed #69/#74/#76; static predicate addresses above |
| `004918B0 / 004918F0` | Allocate 0x0C-byte shared edge and split edges with original height sample/midpoint; preserve shared ownership | Executed #69 and successors |
| `00491810` | Allocate 0x1C-byte linked leaf, last link-zero store `00491892`, increment leaf count | Executed #69 and successors |
| `0049199D`; root stores `00490C2D/00490CB8/00490D45/00490DD0` | Original float32 source XYZ writes (including midpoints); **not injected vertex arrays** | Executed; original writer chronology checked |
| `00491A30`; `00492270/004922B0` | Walk original leaf list, flatten child edge trees into variable-length polygon indices, perform source visibility/facing/shading decisions, call selected emitter; possible triangle fallback | Binary-static #69, executed #74/#76 |
| `00654B8B`, branch `00490F6F..00490F9B` | Select ordinary callback pair (`0048E190` RET, `004922F0`) versus alternate (`004923F0`, `004924B0`) | Binary-static #69, original ordinary path executed #74/#76; alternate limited #74 |

**Data layout (original writes; field naming partly descriptive):**

```c
struct source_xyz { float x, packed_low12_y, z; };  // 0x0c
struct edge { int16_t a,b; edge *child_a,*child_b; };  // 0x0c
struct leaf { int16_t first,last; int32_t delta; leaf *next;
              edge *e0,*e1,*e2,*e3; };               // 0x1c
```

Leaf offsets: `+00/+02` coordinate/range, `+04` delta, `+08` next link, `+0C/+10/+14/+18` edge pointers. Forward edge flattening recurses child-a then child-b and emits vertex-a on terminal edge; reverse recurses child-b then child-a and emits terminal vertex-b. Original walker orders leaf edges **+14 forward, +10 forward, +18 reverse, +0C reverse**. It does not simply connect independently subdivided quads; shared-edge preservation avoids assuming a faithful triangle mesh from a diagnostic adaptive exporter.

Original globals: `005DD320` XYZ base, `005DD2EC` auxiliary base, `005DD324` temporary arena base, `00654380` leaf/edge arena cursor, `0059C560/+574` leaf head/tail, `0059C568/+56C` edge/leaf counts, `006442EC` vertex count. Original entry writes counts/list/cursor and later original code advances them; **backing and pointer bases are controlled** in the experiments. Aligned selection globals `006442E0/E4/E8/F0` and plane globals `00644308...` are original bounds outputs.

The #69 **controlled**, non-camera-authored scene returned **267 XYZ vertices / 743 edges / 172 leaves**, X-shifted 97 / 256 / 41, rejected 0 / 0 / 0. Its deliberate stop is **at original `004937C0` entry**, before the first transform or polygon. Those counts are source adaptive **leaves**, not raster polygons. #76's coherent native-camera-derived visibility yields **171 vertices / 79 leaves** (primary) and **93 / 30** (X-shifted); different camera and near/far/visible volume, **not a regression or fidelity ratio**. See [#69 result](../../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/VISIBLE_TERRAIN.md) and [#76 report](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/REPORT.md).

## Projection/camera construction and exact viewport corrections

**Record address:** `004C2730`, **118 dwords / 472 bytes / 0x1D8**, last byte at `004C2907`. Adjacent `004C2908` is the active-world entry pointer, **not part of the record**. Original `00405970(0)` invokes `00472220` with original FOV constant `3FC90FDA`, mode-selected aspect and far-distance argument 150; `00405A2D` copies 118 dwords. `00472220` is the view/projection builder (an older “raster command context” annotation is overly broad). Two `00406AB0` callbacks on one original-created, VCF-attached, registered bus update that same record and preserve out-of-record smoothing at `004C2964..297B` and `0052B93C..47`. `00472990 → 00494F70` constructs/copies the inverse affine; `00472C10` is a source-audited frustum classifier.

| View offset / width | Proven original writer and meaning in #76 | Observed coherent controlled M06 fixture |
|---|---|---|
| `+00/+04` float32 | `00472220` `00472311/1F`: center of viewport | (320,240) |
| `+08/+0C` float32 | `004724E6/E9`: X/Y projection scales | (+320.0000305175781, -320.0000305175781) |
| `+1C/+20/+24/+28` float32 | `00472599/59E/5AD/5B6`: inclusive screen rectangle min X/Y then max X/Y | (0,0,639,479) |
| `+2C/+30/+34` float32 | original FOV tangent, aspect, zoom (builder + `00472441`) | `3F7FFFFF` tangent, aspect 1 (mode 2), zoom 1 |
| `+3C` pointer | viewport descriptor pointer installed by original builder | `005DCEC0` (descriptor contents controlled) |
| `+40..+60` nine float32 | `00472990/00494F70`, inverse orientation basis, copied at `00472C05` | original callback-derived, finite; slight measured nonorthogonality |
| `+64` 4 bytes | part of 16-dword matrix copy | padding/meaning **not established** |
| `+68/+70/+78` three float64 | `00494F70/00472C05`, negative rotated inverse translation | original callback-derived |
| `+80/+88/+90` three float64; `+98` float64 | `00472B6F/80/86`, `00472BF0`: center/radius over origin + four world corners | independently reproduced; rounding retained |
| `+A0..+FF` | six frustum-plane data; original `00472530` writes, `00472C10` reads | independently tested incidence/nondegeneracy; not normalized by verifier |
| `+100..+12F`, `+130..+15F` | local near/far corner data from original `00472530` | original near/far, not injected visibility rectangle |
| `+108` float32 | **`004725A1`: original near clip Z** (also first near local corner Z) | **0.1f = 0x3DCCCCCD** |
| `+138` float32 | **`0047270F`: original far clip Z** (also first far local corner Z) | **150f** |
| `+160/+168/+170` three float64 | `004729AD/B6/BF/CE/FD`: world camera source position | (2952.0923249721527, 62.02251482009888, 48155.97027873993) |
| `+178..+1D7` four 3×float64 corners | `00472A40/62/85`: local frustum corners transformed by same camera basis and position | four original world points; no independently fabricated bounds in #76 |

The original view uses a **row-vector affine convention**: row point times 3×3 orientation, then translation. The inverse code uses a **transpose-based** orientation inverse and negative rotated translation (`-Rᵀt` in the relevant convention); it does **not** reorthogonalize or compute a general inverse of a non-unit basis. The #76 after-callback basis has determinant `1.000026841538967` and max measured Gram error `6.014088080711841e-5`. Its original camera origin is offset from the supplied root translation by native VLOC/callback work. Frustum plane normals are slightly approximate, and **must not** be silently normalized.

**Viewport correction:** #67 verbally described 640×480 but its *supplied* descriptor had **max X=479, max Y=639** and width word zero. #76 audits `00472444..0047244A` (descriptor X handling) and `00472530` (max X at descriptor +24, max Y at +28), supplies **width=640, height=480**, inclusive clip extrema **639/479**, and records those original projection outputs. The earlier #67 continuity observations remain source evidence for their inputs, but its viewport is **not** proof of a correctly authored 640×480 screen. Descriptor and view offsets are distinct namespaces.

**Near/far correction:** #74 explicitly *supplied* view +108=1 and +138=4095 and projection scales (320,-320), clip rectangle (0,0,640,480) to demonstrate original clip/bin under a diagnostic camera. Those values were **never native camera recovery**. #76's original `004725A1/0047270F` stores establish native **0.1/150 for this builder/mode fixture**. The values 4095 in #74's clip and #70's independently supplied vehicle queue scan bound have different owners/experiments.

## Source transform, emission and clipping

Original `004937C0` composes the source lattice scale (X/Z 5; packed height float32 `0x3DCCCCCD`) with the affine `view+40` using `00494E20`; exact final float32 stores for XYZ are `004938A8/004938AA/004938BC`. Both the matrix coefficients and each transformed float32 are independently checked from the **original composed rounded coefficients** in #76. No replacement transform routine runs.

The first #74 controlled affine was deliberately identity with translation `(-2952.5,-200,-47800)`, while its independent visibility position was `(2952.5,200,48152.5)`. This inconsistency is **not** an original camera fact and #74 explicitly disclosed it. It produced **801** verified transformed coordinates for 267 source vertices, and downstream **182 accepted** binned records in 21 buckets on fully supplied projection, but cannot measure coherence of the two camera origins. #76 removes the mismatch using one original camera. These different record totals are not directly comparable.

Original `00491A30` walks source-owned edge loops and hands reverse-indexed transformed XYZ to `004922F0`; it can retry triangles after failed polygon attempts. Original `0048E190` in ordinary callback pair is an actual retail RET. A source candidate is **not** a record until original clip and insertion accept it.

**Ordinary polygon work header and stride** from #74/#76 (word offsets, not generic class semantics):

```c
struct polygon_work_header {
    uint32_t clipped_vertex_count; // +0x00
    uint32_t type_or_material;      // +0x04; ordinary emitter literal 0xB4
    uint32_t flags;                 // +0x08; no general semantic claim
    uint32_t kind;                  // +0x0C; ordinary emitter writes 0
    float    max_unprojected_z;     // +0x10; binning key
    void    *next;                  // +0x14; original bin/list link
    void    *link_state;            // +0x18; original writes/links
    // vertices at +0x1C, each 0x18 bytes
};
struct work_vertex {
    float x,y,z;                    // +00,+04,+08
    float projected_x,projected_y;  // +0C,+10 after clip/project
    float shade_or_attribute;       // +14; ordinary emitter shade store
};
bytes_advanced = 0x1C + 0x18 * clipped_vertex_count;
```

The source emitter at `00492305` writes kind 0, `0049230C` writes **literal B4**, original record allocation `00490590` supplies scratch at `006543C0`. The `+04` header is **not** `TERword >> 13` or a proven texture ID. Original `0047BF00` tests **camera near/far at +108/+138**, classifies depth, projects and invokes original four-plane screen clip `0047B8C0`. Original projection stores at `0047C29D/0047C2AB/0047C2AF/0047C2B6` are traced. The external imported CRT memcpy at call `0047BED9` copies the **original-generated clip stack** into `record+1C`; it is an explicitly supplied copy, not original retail memcpy instruction execution and not authored polygon arithmetic. This service is guarded by exact caller/source/destination/count; up to 32 vertices permitted in the experiment. Original `0048FE10` then validates and inserts accepted records into original linked bucket tables and advances the cursor. Rejected attempts reuse the cursor and may trigger triangle fallbacks; do not convert attempts into accepted polygons.

## Arena, bucket depth and queue lifetime

| Global / original writer or consumer | Responsibility and provenance |
|---|---|
| `00654398/0065439C/006543C0`, `0048F9C2/C7/CC` | Original `0048F9B0` initializes polygon base/active/cursor on **supplied** heap backing; `00490590` reads cursor and clears fresh scratch fields |
| `006543B0/00654384`, `00654388/006543A8` | Original first/second spatial-bucket table base/cursor; first table 4096 entries × 3 dwords. Original zeros stored; second table initializer clears fewer fields than first |
| `00654390/006543B8/006543BC`, `006543A0/006543B4/0065438C` | Original span/effect auxiliary buffers, pointers/limits initialized from supplied backing; consumers not fully exercised in #76 |
| `006543AC` (minimum depth), `006543A4` (maximum depth) | **Terrain producer** `004938DF` writes minimum -300; `004938FF` writes source-dependent max. Additional original entry/reject stores occur at `00490B2F/00490B39`. These globals are not camera view +108/+138 |
| `006442F4`, `004938EA` | Terrain transform minimum packed-height related state; not a translated camera origin |
| `00654380`, `005DD320/2EC/324` | Separate source adaptive leaf/edge cursor and XYZ/aux/arena bases, not polygon cursor `006543C0`. In #76 bases were separately supplied; in #80 original `00402F98..00402FF7` installs **XYZ and +0xD2F0 auxiliary alias** in one 108,000-byte externally backed allocation, plus 524,288-byte leaf/GEO scratch. See unified ownership section. |
| `0048FE10`; `004903E7/00490400/00490421` | Original bucket count/head/tail/links and record-cursor mutations, independently traced/traversed |
| `0048FAC0`, `0048FD6D/0048FD7B/0048FDE2/DEC` | **Binary-static in #76; original-instruction executed in #80:** mixed terrain/vehicle typed consumption and first-table clearing, cursor reset to base, depth sentinels +1,000,000/-1,000,000. #70 previously executed a **vehicle-only** queue, without M06 terrain or pixels. |

The original `0048F9B0` requests buffers sized **370,000, 128,000, 49,152, 49,152, 2,880 bytes**, via original allocation entry points `00498940/00499CE0` with external deterministic zero backing at diagnostic addresses `48000000..48400000`. The original initializer writes table and cursor globals; it does **not** establish retail OS allocation, exhaustion limits or full-frame reuse. The untouched allocator before this setup returns null (shown in #74), which is **missing experiment setup**, not a defect in the retail game.

Depth distinctions are mandatory: **0.1/150** are camera-local clipping values in original view in #76; **-300 / source-dependent maximum** are terrain-written global depth/bin limits; **4095** was intentionally supplied as a queue scan bound in #70 (and as a controlled camera far in #74); **±1,000,000** are audited post-consumer reset sentinels. The original source `0048FAC0` uses shared type-dispatched terrain/vehicle work; reset between producers would lose queued work. **#80 now executes same-emulator M06 terrain+vehicle coexistence and original consumer traversal/cleanup**, with no intervening host queue reset. The experiment directly invokes a bounded software-path subset, **not a fully scheduled same retail frame**, and consumer-selected clip/draw services still substitute downstream rendering; no authentic M06 raster or pixels have been shown.

### Actual bounded results by experiment

| Accepted run | View origin/projection owner | Observed original output | Boundary NOT reached |
|---|---|---|---|
| #69 | supplied visibility/LOD record, invalid affine | 267 vertices / 743 edges / 172 leaves; contrast 97/256/41; rejection 0 | before transform `004937C0` |
| #74 | supplied separate visibility and affine, then diagnostic clip fields/heap | 267 transformed vertices; arena-only 538 clip rejections; diagnostic 182 accepted records / 21 bins / 23,144 bytes | coherent original camera, consumer/pixels |
| #76 | **same original-built camera** after two callbacks, root pose controlled | primary 171 vertices / 79 leaves, 181 polygon **attempts**, **30 accepted records** / 10 bins / 3,792 bytes; X-shift 93/30, 45 attempts, **13 accepted** / 10 bins / 1,732 bytes; below-height 0 | M06 consumer/draw/pixels and genuine frame |
| #70 (adjacent) | original selected camera on one bus; separate unselected bus target, controlled poses | original kind-6 and kind-10 vehicle work records consumed through GEO/polygon wrappers; queue cleared, camera-owner depth -5 rejected under supplied near 0 | original M06 terrain, real native raster/clip pixels |
| #80 (unified) | **one sealed original-built 472-byte camera**, two original-constructed stock buses with controlled poses | 30 terrain + 1 target kind-6 + 2 kind-10 accepted in one arena (33); direct terrain submission, typed vehicle dispatch/GEO, original bucket/cursor/depth cleanup; controls 13/1/2 and 0/1/2 | unmodified original clip/draw, materials/palette, pixels, full retail scheduler/physics |

#76 independently checked final chain membership for **all 43** accepted records over two poses; original stores/links and exact source indices are validated. Counts describe controlled original-instruction experiments, not frame rates, scene fidelity or an automatically ratified RND-v1 gate. Source [#74 report](../../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/REPORT.md), [#76 report](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/REPORT.md) and [#70 report](../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/REPORT.md).

## Unified original terrain/vehicle ownership and consumer (merged research #80; accepted extension #83)

**Evidence classifications:** All statements attributed to [#80's immutable run](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/manifest.json) are **original-instruction emulation with stated substitutions** unless marked binary-static, independently derived, externally supplied or unresolved. Finding IDs [`F1-unified-ownership`, `F2-scratch-lifetime`, `F3-depth-lifecycle`](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/findings.json) crosswalk to the [accepted bounded promotion (PR #83)](../../../agent/promotions/m06_unified_terrain_vehicle_submission_20261031.md). Main source artifacts are [REPORT](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/REPORT.md), [MEMORY_OWNERSHIP](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/MEMORY_OWNERSHIP.md), [original opcode anchors](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/evidence/instruction_anchors.tsv), [selected events](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/evidence/selected_events.tsv) and [service ledger](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/SERVICE_LEDGER.md). Original retail binary, GZF and M06 resources are privately authenticated by the run, **not** independently replayed by this documentation change.

### Same state and retail callsites

**Original-instruction emulation:** #80 retains one Ghidra emulator, two original `0045EBD0/004AD6F0/004572B0` stock-bus construction/registration paths and one selected/registered camera at `004C2730..004C2907`. Original `00405970` and two `00406AB0` callbacks build/update that 472-byte record; its bytes remain unchanged across original M06 load/terrain `00490A00`, vehicle visibility `00457FF0` and consumer `0048FAC0(view,1)`. The camera-owner root is selected, the target bus separately unselected; original status code and registration select those roles. The root poses are **externally supplied**: selected camera `(2952.5,60,48152.5)`, target `(2952.5,60,48202.5)`, target basis rows `(0,0,-1);(0,1,0);(1,0,0)`, with declared shift/behind/below controls. Viewport 640×480, delta .016, velocity `(2,0,1)` and angle integers are also supplied. Neither mission spawn nor physics authored these poses.

**Binary-static scheduling context:** `00401DE1` calls terrain, `00401E2C` vehicle visibility, `00401E8D` consumer in the original software frame. **Original-instruction experiment:** #80 directly calls the three original bodies in that order after original setup and one original `0048F9B0` renderer initialization. No host arena reset, second view, synthetic queue node or copied predecessor trace intervenes. Roads, skids, flamer, dust, tracers, HUD, particles, sky, device and timing passes are explicitly **omitted**, so this is a bounded contribution lifecycle, not full-frame scheduler execution.

### Original source scratch install and memory lifetime

**Original-instruction emulation with externally supplied allocation backing:** The source initialization span `00402F98..00402FF7` requests 108,000 bytes, installs its returned pointer to `005DD320` at `00402FAC`, adds `0xD2F0` at `00402FC5` and writes the **alias** to `005DD2EC` at `00402FD4`. It then requests 524,288 bytes at `00402FD9` and stores that pointer at `005DD324` via `00402FE3`. The host supplies the requested pages, **not a second separately allocated auxiliary buffer**. #76 used separate controlled XYZ/aux/edge backing; that is a prior diagnostic fixture, superseded only as a *native scratch-ownership interpretation*, not as its measured geometry.

| Region / original installer | Measured ownership and lifetime in #80 |
|---|---|
| `42000000..4201A5DF`, `005DD320` | 108,000-byte source/transform and subsequently vehicle-transformed-position backing; original installer, supplied heap |
| `4200D2F0..4201A5DF`, `005DD2EC` | Auxiliary pointer **aliases the upper half of that same allocation**; terrain attributes, not independently allocated memory |
| `44000000..4407FFFF`, `005DD324` | 524,288-byte shared terrain edge/leaf and then vehicle GEO record scratch; `00490A92` starts terrain cursor, `0045D571` reloads backing for vehicle |
| `48000000..4805A54F`, `00654398/39C/C0` | Separate original renderer polygon arena with **supplied** 370,000-byte backing and original `0048F9B0` initializer |
| `48200000..4820BFFF`, `006543B0/384` | Separate primary 4096×12-byte bucket table, original head/tail/count writes and consumer clearing |
| `48100000`, `48300000`, `48400000` families | Separate supplied 128,000-byte span, 49,152-byte secondary bucket and 2,880-byte effects backing; not all downstream uses executed |

**Original-instruction/independently derived ownership check:** Terrain's `0047BF00/0047B8C0` path and narrowly substituted CRT memcpy copy the **original-produced clipped vertices** into variable-stride polygon records (`0x1C + 0x18*n`) before vehicle `0045CBE0` reuses source/leaf/GEO scratch. Queued terrain records retain their own copied vertex bytes and original links; vehicle scratch overwrites do not imply mutation of those queue records. The independent verifier reconstructs the original retired queue writes and checks record identity/order. Allocation failure, overrun/exhaustion, retail Windows heap behavior and lifetime over an actual retail frame are **unresolved**; source buffer ownership does not prove them.

### Original typed insertion, dispatch and retirement

**Original-instruction emulation, primary fixture:** Terrain produces 171 original source vertices, 79 adaptive leaves, 181 polygon **attempts** and **30 accepted** positive-vertex kind-0 records (`0xB4` ordinary header), 10 bins, 3,792 bytes. Arena cursor then equals `48000ED0`. Original terrain `004938DF` writes global minimum depth `006543AC=-300`; `004938FF` writes source-dependent maximum `006543A4`. These globals differ from original camera-local near/far (`view+108=0.1f`, `view+138=150f`) and from #70's **externally supplied** far scan bound 4095.

| Consecutive record | Original header/owner semantics | Cursor after insertion |
|---|---|---|
| `48000000..48000ECF` | 30 terrain polygons, positive vertex count, original bin links, `0xB4` literal **not verified displayed texture** | `48000ED0` |
| `48000ED0` | Camera-owner kind 10, owner `27000E00`, depth **-5**, stride `0x74` (116 bytes) | `48000F44` |
| `48000F44` | Target kind 6, root owner `26100000` / registry entry `005428A8`, stride `0x44` (68 bytes) | `48000F88` |
| `48000F88` | Target kind 10, owner `27006600`, stride `0x74`; its +0x40 is matrix data, not kind-6 registry | `48000FFC` |

**Reconciled depth difference:** #70's vehicle-only fixture supplied near 0 and far 4095; the camera-owner depth -5 kind-10 *attempt* was rejected by original insertion and its cursor reused. In #80 the same class of original camera-owner work **is accepted** because original terrain has first established -300 as the minimum. This is a difference in original insertion **eligibility resulting from prior depth state**, not contradictory conclusions about the kind-10 producer. The reported 33 entries are accepted records, not total attempts, and are not final pixels.

**Original-instruction emulation:** Consumer `0048FAC0(view,1)` walks shared primary buckets in descending bin/link order. Positive-vertex terrain work takes the direct original `00471FD0` submission branch (all 30 records observed). Zero-vertex kind-6 and kind-10 entries use the retail type dispatch table (original `0048F4C0` / `00490640`); the kind-6 target traverses original `0045D530 → 0045CBE0`, source-authenticated `xb11bdym.geo` body at `27006800`, 16 vertices transformed through original body/world plus sealed view, and two polygon wrappers. The kind-10 original +0x3C field is cleared during consumption; no record owner is fabricated. The independently derived verifier checks **exact all-record descending traversal**, headers, source GEO and queue mutation chronology. Original `0048FD6D` zeroes primary buckets, `0048FD7B` restores cursor to `48000000`, `0048FDE2/FDEC` restore +1,000,000/-1,000,000 depth sentinels; cleanup argument 1 clears effects state.

**Externally supplied consumer service boundary:** The original selected consumer clip service copies original vertices and returns a count; the selected draw target returns success. Those are **not original native clip/draw/raster instruction execution**. Original `00471FD0` receipt, stock GEO preparation and consumer cleanup demonstrate submission/retirement only, never displayed materials, textured polygons, framebuffer data or authentic terrain rasterization.

### Controls and verification limits

| #80 fresh control | Terrain records | Kind-6 records | Kind-10 records | Original bounded consequence |
|---|---:|---:|---:|---|
| Primary M06 + target | 30 | 1 | 2 | 33 queued, original typed dispatch, cleanup |
| Target absent | 30 | 0 | 1 | Selected camera light survives; terrain unchanged |
| Target behind | 30 | 0 | 1 | Original target cull; same camera terrain |
| Selected camera/root X+200 | 13 | 1 | 2 | Different coherent original view |
| Both roots Y=-100 | 0 | 1 | 2 | Terrain rejected, vehicle still eligible/consumed |

**Independently derived checks** reported by #80: 131,751 standalone validations, five controls, a fresh imported GZF repeat with identical primary trace and 17 output sidecars, an independently rejected mutated consumed kind-6 owner, and source opcode/dispatch/queue/GEO verification. Prior #76/#70 reproducers and trusted 11 protocol + 38 CI unit tests were separately run, not counted as pixel tests. The [reproduction procedure](../../../agent/runs/i76exe/i76exe-20261031T161025Z-d3f083fc/artifacts/REPRODUCE.md) needs private licensed source files; this steward checked public evidence and manifest hashes, **did not rerun** the private emulator. Native consumer clip/draw, material and original retail frame remain **unresolved**.

## Source classes versus actual rendered materials

The **source** word's 15–13 class, the LOD split predicate, road grading/material planes from the editor, the emitter's literal `0xB4`, an alternate descriptor and the eventual rasterized texture are **different entities**. The ordinary emitter does not copy the TER class to +04; a polygon may span multiple sampled source classes. The alternate selector `004923F0 → 00471F00` reads one of seven descriptor pairs rooted at `005A4588`, writes the selected descriptor to `0059C558`, and `004924B0` copies that global to the alternate record +04. #74 executed only alternate header setup with **null descriptor** because original WRLD texture initializer `004908F0` was intentionally omitted. It did not generate a successful textured polygon.

Historical [runtime adaptive LOD](../../../ref/level_format/i76_runtime_terrain_lod_reference.md) correlates M06 class 3/7 with road/corridor geometry; [editor authoring](../../../ref/editor/road_terrain_serialization.md) maps road kind 0/1/2 to terrain plane indices 2/3/4, and indices 6/7 may have equivalent physical parameters. Such correlations **do not** prove rendered texture names, palette entries or UV mapping. `miss8` and `miss16` may share heightfields while selecting different resource families; this research uses authenticated `miss8/M06` for the bounded terrain chain. Do not infer a sprite/color/pixel from a terrain class or a candidate MAP filename. Bit 12 remains unknown.

**Deferred:** original WRLD material and `004908F0` texture descriptor success, `004923F0/004924B0` complete alternate emission, auxiliary lighting/UV semantics, source palette ACT/LUM/TBL, output buffer format, original consumer raster callbacks and independently checked M06 pixels. This reference does not assign values to any of those missing fields.

## Original execution vs controlled services and validation

| Original retail instructions executed | Explicit external/control boundary |
|---|---|
| `0045EBD0/004AD6F0/004572B0`, original stock vehicle node/VCF graph, registration; `00405970`, `00406AB0`, original projection/camera/frustum/inverse | Supplied original-created bus **root pose** `(2952.5,60,48152.5)` and identity basis (shift control X+200, below Y=-100), `640×480` descriptor, delta 0.016, velocity `(2,0,1)`, angle inputs, stock resource/CRT/OS hooks. Not mission/physics/scheduler-produced |
| Original `004B8A10/00493910/00493080/00490A00` and source/adaptive transform/walk | Authenticated private M06 MSN/TER via supplied Win32 file handles/mapping; source scratch backing; WRLD peripheral/texture initialization omitted; palette acquisition fails to null and original error paths run |
| Original numerical terrain bounds/sampler algorithm and FPU-sensitive callsites | Narrow host x87 FISTP at `004935EE/00493608`, FPATAN at `00492EAF`, original CRT ftol at external `004BA090`, Java sin/cos service at `0049D400`, emulated x87 control word initialized to `037F`. **No hardware-wide x87 claim**; raw untreated FPATAN fails in Ghidra, not retail |
| Original `0048F9B0/00490590/0047BF00/0047B8C0/0048FE10` | Supplied deterministic memory for five heap allocations; imported CRT memcpy of original-produced clipped stack; no reconstructed geometry and no original OS frame allocation guarantee |
| Static frame dispatch `00403E64/00401C90/00401CC0` and software callsites; **#80 executes original scratch install, mixed producers, original `0048FAC0` and reset instructions** | Original software frame schedule is audited, not invoked in its entirety; consumer-selected clip/copy/draw services remain substituted. No full WinMain, authentic M06 raster or framebuffer copy |

Note `00403E64` is **inside** its containing FSM frame code: a PUSH of `004C2730`, followed by call `00401C90` at `00403E69`, **not** a function entry. `00401C90` selects `00401FA0` or software `00401CC0` by flow-state tests; `00401DE1` is the original software terrain call. Labels like “AI/frame-update” were superseded by the audited instructions. This audit alone does not prove that the full frame schedules the particular controlled #76 experiment.

Independent verifiers authenticate original source/typed writes, page-pointer maps, source heights/material, 118-dword camera and out-of-record history, inverse/frustum corners, original affine coefficient and exact rounded XYZ, depth/plane/screen clip, external copied bytes and **final** linked-bucket membership. #76 allows one float32 ULP per projection stage, up to eight ULP per clipped coordinate through six planes, and checked operation-magnitude bounds for original double corner/radius arithmetic; these are **experiment-specific tolerances**, not general rendering acceptance criteria. A separately imported Ghidra project reproduces the #76 positive trace/buffers byte-identically; corrupted height/inverse/emitter inputs are rejected.

Detailed run-by-run service inventories: [#67 camera services](../../../agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11/artifacts/SERVICES.md), [#69 terrain services](../../../agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/SERVICE_LEDGER.md), [#70 vehicle queue services](../../../agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/SERVICES.md), [#74 clip/arena services](../../../agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/SERVICE_LEDGER.md), [#76 combined services](../../../agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/SERVICE_LEDGER.md).

## Contradiction register and remaining prerequisites

1. **Viewport axes (#67 → #76):** #67's max X/Y reversal and zero width are accepted experimental fixture facts. Superseded as correct 640×480 interpretation by #76's instruction-verified X +24/Y +28 and supplied true dimensions.
2. **Native clip planes (#74 → #76):** 1/4095 were controlled #74 projection depths. For #76's original builder, +108/+138 are 0.1/150. Do not relabel 4095 as native far.
3. **Terrain bin depths vs camera depths (#70/#74/#76):** `006543AC/+A4` terrain writes, `view+108/+138` camera fields, #70 4095 supplied scan bound and post-consumer reset sentinels have different ownership.
4. **Visibility vs affine origin (#74 → #76):** separate #74 Z=48152.5 visibility and Z=47800 affine origin were diagnostic. #76 replaces that *interpretation* with one original camera record, not the earlier measured results.
5. **Material class vs displayed texture:** historical class/road spatial correlations survive, but rendered texture/UV/palette assignment remains unproved. Retain older LOD exporter as diagnostic only.
6. **Arena and reset (#70/#76 → #80):** #74 null allocator before init reflects missing backing/setup; #76 supports terrain bins with separately supplied scratch; #70 supplies vehicle-only consumer execution. #80 now executes **one shared original terrain+vehicle arena and consumer cleanup** with original source-scratch alias installation; no complete retail frame or original raster is proven.
7. **Kind-10 camera-owner depth (#70 → #80):** #70's supplied near=0 rejects camera light depth -5. M06 `004938DF` sets minimum -300 in #80, making the same kind of original light work eligible. Do not mistake reuse of a rejected record cursor in #70 for a permanent owner/record identity.

**First missing rendering dependency:** authenticate original M06 WRLD material/output initialization (including `004908F0` and descriptor success) and advance the **currently substituted consumer clip/draw operations**, then demonstrate actual texture/UV/palette/output buffer/framebuffer behavior with independent pixel comparisons. The shared producer/arena/consumer subset is now executed in #80; what remains is downstream material/output and authentic native drawing. Separately unresolved: original full-frame peripheral scheduling, selected-player/physics M06 poses, retail OS allocation/exhaustion lifetime, source bit 12, hardware x87 parity and non-M06 generalization. No run authorizes reconstructive code or proves RND-v1 completed.

Further navigation: [RND subsystem and acceptance](../../roadmap/subsystems/RND.md), [TER and physics boundary](../../roadmap/subsystems/TER.md), [RND acceptance gates](../../roadmap/subsystems/RND_ACCEPTANCE.md), [original class-1 scheduling](frame_scheduling.md), [original vehicle VCF](vehicle_construction.md), [mission format and execution](../../../ref/mission_execution/README.md), [historical LOD and renderer notes](../../../ref/level_format/i76_runtime_terrain_lod_reference.md), and [editor road/terrain data](../../../ref/editor/road_terrain_serialization.md).

**Promotion status:** the earlier visual-terrain contract was accepted in merged PR #78; the bounded #80 unified submission interpretation was subsequently accepted in merged PR #83. The promotion records preserve their original candidate-at-authorship status as immutable decision history. Neither acceptance establishes native terrain draw/raster, authentic scene color, complete image output or RND-v1 completion.
