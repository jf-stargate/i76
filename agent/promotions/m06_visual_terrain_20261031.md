# Proposed promotion — M06 visual terrain and original camera-to-bin contract

**Status:** Candidate — requires explicit human maintainer acceptance; not authoritative until merged  
**Date:** 2026-10-31  
**Original accepted base commit:** `6d151459f92b75aaadd5221dc8edd8e4776651ff`  
**Research track:** `i76exe`; advisory TER/RND/VEH interface  
**Target:** [M06 visual terrain technical reference](../../manual/reference/engine/m06_visual_terrain.md)  
**Publication:** separate documentation PR, unmerged

## Scope and decision proposed

Propose the **bounded original-instruction M06 source-terrain → adaptive leaves → single original-built camera → affine transform → polygon candidate → original depth/screen clip → spatial-bin insertion** as the currently best-supported visual-terrain contract. This is a technical **research contract**, not a claimed retail frame, a reconstructed renderer, or a released fidelity implementation.

The positive integration is evidenced by **#76**, with #69 (source/LOD), #74 (independent transform and diagnostic polygon handoff), #67 (persistent camera continuity) and #70 (separate vehicle producer/consumer queue semantics) preserved as earlier, narrower milestones. All five PRs were merged; none of their immutable runs is edited here. Their services and controlled inputs are not collapsed into “original retail execution.”

**Not promoted:** interpreted TER class as a displayed texture; texture IDs, material descriptor identity, UV, palette, frame color or pixels; original mission-spawned root pose; complete selected-camera scheduler, gameplay frame, actual OS-backed renderer allocation/teardown, common terrain-and-vehicle integrated frame, hardware-wide x87 parity, full draw/consumer/pixel path or RND-v1 completion.

## Accepted sources and finding-level crosswalk

For compactness, artifact SHA-256 values below are those declared by each accepted immutable `manifest.json` / `findings.json`. Links target **accepted merge-commit trees**, not mutable working branches. The original PR base and reproduction limits remain in each manifest.

| Run, merged PR (merge commit) | Finding IDs | Original anchors and scope | Principal immutable artifact / declared SHA-256 |
|---|---|---|---|
| [#67](https://github.com/jf-stargate/i76/pull/67), [`437fcb0`](https://github.com/jf-stargate/i76/commit/437fcb0af169dfcf68b2dee9696c5180bf48bfe0) — [run](../runs/i76exe/i76exe-20261030T020546Z-e1909f11/manifest.json) | `rnd02-persistent-camera-pose-response`; `rnd02-view-field-provenance`; `rnd02-controls-and-repeat`; `rnd02-live-camera-gap` | `00406AB0`, `00437F90`, `00472990`, `00494F70`, `00472D30`, view `004C2730`. Camera continuity in controlled registered bus/GTSi, *not* M06 | [CAMERA_CONTINUITY.md](../runs/i76exe/i76exe-20261030T020546Z-e1909f11/artifacts/CAMERA_CONTINUITY.md), `c0e90ce72f6c29d7b1adefe7b1b8777a3355624dffa3c19de321abc4c38d326d`; [opcode anchors](../runs/i76exe/i76exe-20261030T020546Z-e1909f11/evidence/opcode_anchors.tsv), `abb2adbdfe580cbc656f43ed8953c473183cd72eaeca29c2edd423ce6b5c89e8` |
| [#69](https://github.com/jf-stargate/i76/pull/69), [`3e10251`](https://github.com/jf-stargate/i76/commit/3e10251444a117c8d9da053b6887245a2bc4dbcf) — [run](../runs/i76exe/i76exe-20261030T025441Z-8f2b292d/manifest.json) | `F1-original-visual-leaves`, `F2-source-provenance`, `F3-render-material-boundary`, `F4-downstream-prerequisites` | `00490A00`, `004929B0`, `004911E0`, `00491810`, `00493160`; 267 vertices/743 edges/172 leaves. Stops **before** `004937C0` | [VISIBLE_TERRAIN.md](../runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/VISIBLE_TERRAIN.md), `fa6d151fff37a44f27fc7850a4fbd29e2cc363b4627e87324ab28e34f574bfa5`; [anchors](../runs/i76exe/i76exe-20261030T025441Z-8f2b292d/evidence/instruction_anchors.tsv), `8ff32a28cd07be007010ed0749be8f5c65c9d8389a9ed8c50582b89bf9be39a4` |
| [#70](https://github.com/jf-stargate/i76/pull/70), [`d17f82a`](https://github.com/jf-stargate/i76/commit/d17f82a610f24950b8bc043fcfad63bc6048e9cf) — [run](../runs/i76exe/i76exe-20261030T025421Z-351de3fe/manifest.json) | `F1-continuous-kind6-integration`, `F2-kind10-lifetimes`, `F3-controls-and-source-verification`, `F4-rnd-output-gates-open` | `00457FF0`, `0048FE10`, `0048FAC0`, `0045CBE0`, `00471FD0`; two registered stock bus roots, kind-6/10 queue and original consumption, **no M06** | [REPORT.md](../runs/i76exe/i76exe-20261030T025421Z-351de3fe/artifacts/REPORT.md), `57a7ea26ffa8211b59c84345023b162e815b8fbe00dabf51d5e17153cc7be959`; [events](../runs/i76exe/i76exe-20261030T025421Z-351de3fe/evidence/events.json), `7dd2fc3235cec1180b93abd3e8952e870e76825f8243ce5708041ae98ed97378` |
| [#74](https://github.com/jf-stargate/i76/pull/74), [`abd6927`](https://github.com/jf-stargate/i76/commit/abd69273611721dceaab88005d750f1930c2713a) — [run](../runs/i76exe/i76exe-20261031T002156Z-133da9a8/manifest.json) | `F1-transform`, `F2-allocation`, `F3-clip-bin`, `F4-material-boundary` | `004937C0`, `00494E20`, `00491A30`, `004922F0`, `00490590`, `0048F9B0`, `0047BF00`, `0047B8C0`, `0048FE10`; controlled non-coherent affine/visibility and projection | [REPORT.md](../runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/REPORT.md), `a51898d389c1e79eb331e81ca25ca537576fe94ce9564c0f6351c1aea28546fb`; [anchors](../runs/i76exe/i76exe-20261031T002156Z-133da9a8/evidence/instruction_anchors.tsv), `72f95516575b6986857225262e2c70ac7c93c96499630c739eda812b91f4b38b` |
| [#76](https://github.com/jf-stargate/i76/pull/76), [`f2bcfbf`](https://github.com/jf-stargate/i76/commit/f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019) — [run](../runs/i76exe/i76exe-20261031T011728Z-b887fccd/manifest.json) | `F1-coherent-camera`, `F2-field-ownership`, `F3-native-arena`, `F4-output-prerequisite` | `00405970`, `00472220`, `00472400`, `00472530`, `00406AB0`; source `00490A00` through original `0048FE10` with **one retained** `004C2730` | [REPORT.md](../runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/REPORT.md), `9533863b94267ff02032c5c13d54e1b829bf6011b41b8c659d6d409da9e587c2`; [anchors](../runs/i76exe/i76exe-20261031T011728Z-b887fccd/evidence/instruction_anchors.tsv), `d061f8a89ea0880d0813114329b57b6374d9752792a518f3ac446befd170e68c` |

All five `findings.json` files, `manifest.json` files, [#69 service ledger](../runs/i76exe/i76exe-20261030T025441Z-8f2b292d/artifacts/SERVICE_LEDGER.md), [#74 service ledger](../runs/i76exe/i76exe-20261031T002156Z-133da9a8/artifacts/SERVICE_LEDGER.md), [#76 service ledger](../runs/i76exe/i76exe-20261031T011728Z-b887fccd/artifacts/SERVICE_LEDGER.md) and documentation-impact handoffs form the linked provenance chain. #76 explicitly checked prior artifact inventories/digests and re-executed #74's driver (including #69) before its new combined work; this promotion does **not** claim a fresh private-Ghidra replay by the documentation steward.

### Original binary and fixture identity (as measured in source runs)

- `i76.exe`: MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`.
- `I76.ZFS`: MD5 `6dd57b1627d73e814247c0d9521f9778`, SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`.
- `miss8/M06.MSN`: MD5 `d8801a3c9d2c79187b67e2f4b818b7db`, SHA-256 `923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f`.
- `miss8/M06.TER`: MD5 `5307dc057a8bbc53569c04d89bd7ca2e`, SHA-256 `fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea`.
- Ghidra 12.1.4, `i76_mission_v97_verified_names`, annotated retail v97 GZF baseline SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. These private files are **not** reproduced, redistributed or rehashed by this documentation change.

Relevant existing context (not additional executed M06 visual evidence): [historical runtime LOD](../../ref/level_format/i76_runtime_terrain_lod_reference.md), [level/terrain formats](../../ref/level_format/i76_runtime_level_and_terrain_format_notes.md), [editor road and terrain serialization](../../ref/editor/road_terrain_serialization.md), [editor intersections and physical surfaces](../../ref/editor/intersection_geometry_and_driving_surface.md), [TER discovery](../../manual/roadmap/subsystems/TER.md), [RND discovery](../../manual/roadmap/subsystems/RND.md), [RND acceptance](../../manual/roadmap/subsystems/RND_ACCEPTANCE.md), [curated class-1 frame scheduling](../../manual/reference/engine/frame_scheduling.md), [mission architecture](../../ref/mission_execution/README.md). Editor `i76edit` serialization and engine `i76exe` rendering remain distinct executables.

## Reconciliation / explicit contradictory and superseded readings

| Current selected statement (tier) | Historical / competing statement | Proposed disposition |
|---|---|---|
| `00490A00` creates original shared-edge adaptive M06 leaf structures; `00491A30` later flattens them. Original-instruction (#69, #74, #76) | Historical LOD reference described the same graph analytically and called its adaptive exporter diagnostic | **Confirm and extend**, but do not label the historical exporter faithful or claim direct triangles at the #69 stop |
| Runtime page pointers are built from ZMAP / TER and sampled at step 5 (X/Z) and float32 0.1 (height); class bits are source predicates | Legacy exporter approximate height factor `409.5/4096`, editor material-plane and road color hypotheses | **Supersede use of approximate exporter scale for original engine arithmetic**, retain diagnostic exporter and editor-specific context |
| TER bits 15–13 are source surface *class*, and original predicate reads class-bearing words. Ordinary emitter uses literal header `B4`; alternate uses separate descriptor state (#69/#74) | Historical M06 class 3/7 road-correlated hypotheses; implicit class→displayed texture or class→UV assumptions | **Narrow** class/road correlation to physical/authoring metadata; rendered texture, UV and palette remain **deferred**; no class→texture mapping is promoted |
| Camera `view+108 = 0.1f`, `view+138 = 150f` in #76's original-constructed fixture, with original `004725A1/0047270F` stores | #74 injected near=1 and far=4095 to enable diagnostic clipping; older wording sometimes called these original values | **Correct/supersede as camera field semantics**, preserve #74's valid but controlled diagnostic |
| Viewport descriptor maxima are **X at +24 = 639**, **Y at +28 = 479**, center (320,240), width=640 height=480 in #76's mode-2 fixture | #67 inherited descriptor max X=479/max Y=639 and width dword zero despite verbal “640×480” | **Correct fixture-axis interpretation** using `00472444..4A` and `00472530` readers; #67's measured camera history remains valid in its documented controlled inputs but is **not** a correct 640×480 viewport proof |
| Terrain bin minima/maxima `006543AC / 006543A4` are written by `004938DF / 004938FF`; source-dependent depth bounds are separate from the camera near/far | #70 intentionally set `006543A4 = 4095` to scan a controlled vehicle queue; #74 injected `view+108/+138 = 1/4095` | **Separate owners**, not one native far plane; never propagate `4095` as an original camera far value or terrain-derived native bin maximum |
| #76 uses a coherent original-origin/affine/corner record across M06 selection and clipping (30 and 13 binned records for controlled poses) | #74 separately authored visibility origin (Z=48152.5) and affine origin (Z=47800), producing 182 accepted records | **Supersede any assertion of coherence for #74**; preserve its 182 records as controlled original instruction evidence, not an image-fidelity comparator |
| `0048F9B0`, `00490590`, `0048FE10` execute original state mutation on supplied backing; `0048FAC0` reset is source-audited in #76, dynamically consumed for vehicle kinds in #70 | #74's untouched null cursor; possible misinterpretation that failed allocation is a retail defect; mistaken need to reset queue after terrain before vehicle | **Explain lifecycle and substitution**; reset-after-consumption is source-supported and vehicle-observed, not executed in an integrated M06 frame |
| Software dispatcher `00401CC0` calls terrain at `00401DE1`; interior `00403E64` pushes view pointer rather than being a function entry; `00472220` builds projection context | Historical “AI/frame-update” and “raster command context” function labels | **Correct names by original instructions**; no claim that entire dispatcher is executed in #76 |

These differences are *evidence history*, not errors to be erased from accepted runs. The type/extent of original source execution is reported separately for each row in the curated reference. #74's experimental projection is not an invalid observation, only an invalid **native-camera interpretation**.

## Proposed reference change

Create only [`manual/reference/engine/m06_visual_terrain.md`](../../manual/reference/engine/m06_visual_terrain.md) in tandem with this proposed record. It provides fields, VA-level producers/consumers, actual limits, controls, service ledger, source lineage and contradictions. **No global documentation index, software-renderer reference, existing promotion, research run, protocol or Ghidra annotation changes.** A future index link may be made by the designated index owner.

## Reproduction, residual risk and review boundaries

Evidence is original retail opcode/static reading plus **Ghidra 12.1.4 original-instruction emulation** with controlled input state and service substitutions, independently verified numerical/source/record checks and fresh-project repeats. Source runs include reported standalone assertions: #67 9,457, #69 105,139, #70 1,402 research assertions (manifest 1,440 inclusive of trusted tests), #74 209,140 and #76 89,114. These are coverage of each run's checks, *not* percentages or global renderer completion. #76's predecessor replay is reported separately from #76's count.

The source scratch buffers and renderer allocation backing are supplied; CRT memcpy at original `0047BED9` is externally performed on **original-computed clip output**, and localized x87 FISTP/FPATAN, sin/cos, ftol, file mapping, resources and heap have explicit service boundaries. Negative/rejected views do not write an image. No original WinMain end-to-end M06 draw, verified road texture/palette, pixel comparator, or actual shared terrain+vehicle work queue execution follows from these results.

**Open research proposals not treated as accepted evidence at this base:** none identified in the live open-PR inventory during bootstrap. Distinct accepted work beyond these five may inform later reconciliation; this PR deliberately does not override another renderer steward's file.

## Acceptance checklist

- [x] All five cited research PRs confirmed merged; exact merge commits and immutable run paths identified.
- [x] Findings, report/anchor SHA declarations, original VAs, binary and baseline provenance cross-referenced.
- [x] Historical LOD, format, mission and editor distinctions reviewed; contradictory claims explicitly retained.
- [x] No conclusion extends beyond its evidenced original-instruction / static / controlled tier.
- [x] Exactly two new dedicated files proposed; no shared renderer reference or index touched.
- [x] No original executable/TER data, GZF, private trace or material/pixel payload published.
- [ ] Trusted `integrity` green on this exact PR head against current base.
- [ ] Human maintainer scientific/documentation review, explicit acceptance and manual merge.

**Decision:** Pending human review. This record itself neither accepts nor proves the findings.
