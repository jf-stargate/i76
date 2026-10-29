# ENG / VEH / TER — evidence-backed research milestones

**Status:** proposed research-planning document, **not** a behavioral promotion, reconstruction authorization, or new original-binary finding. **Binary track:** `i76exe`; advisory functional areas: [ENG](subsystems/ENG.md), [VEH](subsystems/VEH.md), [TER](subsystems/TER.md). **Accepted source `main`:** [`0219bbc2eb3348736e0c7d1aa31c3b54a0397d60`](https://github.com/jf-stargate/i76/tree/0219bbc2eb3348736e0c7d1aa31c3b54a0397d60), verified 2026-10-28. **Policy:** [AGENTS](../../AGENTS.md), [bootstrap 1.0.4](../../agent/protocol/BOOTSTRAP.md), [access policy](../../agent/protocol/access.yaml), [documentation workflow](DOCUMENTATION_WORKFLOW.md). The earlier [architecture proposal](ARCHITECTURE_TRANSITION_PROPOSAL.md) is historical planning context: its then-pending shell track is **already accepted** under current protocol 1.0.4 / research schema 1.2.0.

This is the first milestone pilot, not an all-thirteen-subsystem plan. ENG/VEH/TER are overlapping research responsibilities, **not** exclusive permissions, recovered C modules, or separate publication tracks. Original-code investigations may follow any cross-subsystem call. Editor and shell are separate binary tracks; editor data-format evidence is cross-track context, not proof of engine physics.

## 1. Accepted baseline and cold-start discovery acceptance

The [architecture inventory](SUBSYSTEM_INVENTORY_20261028.md), [subsystem discovery index](subsystems/README.md), immutable merged runs and [one promoted vehicle construction reference](../reference/engine/vehicle_construction.md) are the entry points. A merged research run is evidence **not** a promoted contract; a finding named `proven` in its JSON still requires a separate human-reviewed promotion. Historical `ref/`, `scripts/` and `snapshot/` retain useful material but are not silently canonical.

**Transition Step 4: read-only repository-discovery test completed, assessed 8/8 passed** in the managing conversation. A fresh Codex CLI session, without preceding conversation history, discovered the repository and protocol, VEH scope and ENG/TER interfaces, key original addresses/structures, the construction promotion, later unpromoted vehicle evidence, Ghidra harnesses and private requirements, and the M06 terrain/suspension boundary; it proposed a bounded continuation. GitHub access worked even where shell Git was unavailable. See [bounded acceptance record](BOOTSTRAP_DISCOVERY_ACCEPTANCE_20261028.md).

**Scope:** this was an observation about *documentation discoverability*, **not** independent rerunning of any Ghidra binary, private-input provisioning, or full reproducibility. The original session report was supplied to the manager outside GitHub; no immutable run, independent log, or execution result is claimed here. Known issues: provision private retail/Ghidra inputs, repair older reproduction guides when needed in *new* evidence, correct misleading historical annotations, and locate a verified polygon-contact fixture.

### Assessment vocabulary

Each capability below is evaluated on **six independent axes**: **D** original-code discovery; **B** bounded behavioral understanding; **X** original-instruction execution with stated substitutions; **R** reproducibility documentation and inputs; **C** promoted behavioral contract; **I** independent reconstruction.

- **E:** established *within the specifically linked scope*, not global fidelity; **P:** partial; **U:** unverified/unresolved; **N:** not undertaken, not a prohibition; **—:** not applicable.
- `R=P` commonly means instructions, harnesses, checksums and recorded validation exist but private licensed inputs/Ghidra baseline are necessary, and this task did **not** independently rerun them.
- `C=E` means an accepted human-reviewed promotion exists; `C=U` does **not** negate scientifically useful merged-run evidence. `I=N` means no authorized maintained replacement is established by these records.

### Capability baseline (status order D / B / X / R / C / I)

| Area and capability | D | B | X | R | C | I | Evidence and exact limit |
| --- | :---: | :---: | :---: | :---: | :---: | :---: | --- |
| **ENG** math/clock initialization and current-frame subdivision | E | E | E | P | U | N | [Frame report ``F1/F2``](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md), [subdivision events](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/evidence/subdivision.tsv), [reproduce](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/REPRODUCE.md); 16 controlled timing cases, substituted tick/ftol, no live clock. |
| **ENG** WinMain phase map and class-descriptor dispatch | E | P | U | P | U | N | [Frame report ``F3``](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) and [anchors](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/evidence/instruction_anchors.tsv); **static phase ordering**, original callbacks separately invoked; no queue-driven gameplay frame. |
| **VEH** VCF/VDF/VTF/CDF, GEO, TMT and bounded body-group reuse | E | E | E | P | E | N | [Promoted reference](../reference/engine/vehicle_construction.md), [promotion](../../agent/promotions/vehicle_vcf_geo_tmt_20261023.md), [source manifest](../../agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/manifest.json); stock GTSi/bus only, substituted services, no pixel assignment or teardown. |
| **VEH** persistent root pose / class-1 active integration | E | P | E | P | U | N | [Two-frame report](../../agent/runs/i76exe/i76exe-20261027T033452Z-2f8c31f5/artifacts/VEHICLE_TWO_FRAME_ORIGINAL_SIMULATION.md) and [later math correction](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md); original root mutations under controlled inputs; old non-unit basis is explained by missing `00493C50` startup, not established retail behavior. |
| **VEH** M06 wheel suspension, original filter and contact-mode updates | E | P | E | P | U | N | [M06 report ``F3/F4``](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md), [results](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/evidence/results.json); 32 callbacks per vehicle, four slow frames / 12 substeps; positive tire mode-0 compression, not general collision or authentic input. |
| **VEH** general polygon-contact and response | P | U | U | P | U | N | [M06 open bridge finding `F5`](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/findings.json); special `00440740` four-point probe returned zero for tested upright vehicles; no polygon-positive fixture or candidate provenance. |
| **TER** authentic WRLD/TDEF/ZMAP/TER initialization | E | E | E | P | U | N | [M06 report `F1`](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md), [validation](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/validation.json): 16 authentic pages and 16,384 grid pointers; one mission, service-substituted mapping. |
| **TER** height/material/normal sampler | E | E | E | P | U | N | [M06 report `F2`](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md), [cross-track correction](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/CROSS_TRACK_REVIEW.md); original bilinear `00493550`, packed material `004927B0` and normal `004931C0` for tested queries; FISTP hardware correction essential. Bit 12 remains unknown. |
| **TER** scene polygon producer / collision candidate linkage | P | U | U | U | U | N | [TER index](subsystems/TER.md), [cross-track review](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/CROSS_TRACK_REVIEW.md); `004925F0/00644200` and `0043E530/0052B94C` are **not proven connected**. Editor-authored visible roads do not imply polygon contact. |

**Numerical and environment qualification:** the [accepted M06 run](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/manifest.json) reports [35,452/35,452 checks](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/validation.json), and [ENG startup run](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/manifest.json) reports [211/211](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/validation.json). These are **recorded source-run validations, not tests rerun for this roadmap**. Original Ghidra x86 instructions run with substituted OS/CRT/resource/time and peripheral services. Hardware x87 `FISTP` and `FCOS` are delegated selectively in M06; do not claim entire program hardware parity or complete Windows execution.

## 2. Dependency map

The arrows below express **experiment prerequisites or data-flow constraints**; they do not assert original C module boundaries.

~~~text
[private i76.exe + v97 GZF + Ghidra + authenticated stock VCFs] [X]
               |                            |
       [math/clock setup] [D]      [vehicle root + VCF/CDF] [D]
               |                            |
       [frame subdivisions] [D]             |
               |                            |
     [original class-1 callback] <-----------+
               |
               +---- [terrain WRLD/TDEF + M06.TER map] [D,X]
               |                   |
               |             [height/material/normal + x87] [D]
               |                   |
               +---------- [suspension / tire filter] [D]
               |
     [actual class dispatch] [OPEN] <-- world object membership [I]
               |
     [WinMain gameplay/input/FSM] [OPEN] (beyond measured callback replay)

[scene geometry registration 004925F0 / 00644200] [STATIC]
               ?  unproven ownership/transfer  ?
[polygon candidates 0052B94C -> query 0043E530] [STATIC]
               |
      [positive polygon contact / collision response] [OPEN, X]
~~~

**[D] directly demonstrated within the cited original-instruction harness:** startup seeds/clock, constructed stock vehicle and persistent state, M06 terrain mapping, sampled heights and controlled suspension. **[STATIC]** original addresses/branches identified without proven dynamic bridging. **[I] inferred** registry membership and dispatch are a necessary engineering precondition for the *proposed experiment*; actual queue semantics need tracing. **[X] external or scoped fixture prerequisite**, not evidence of an internal call edge.

Investigations that can advance **independently**: ENG static descriptor/queue audit; TER M06 sampler boundary cases; private-corpus fixture search; TER scene/candidate producer static dataflow. **Dynamic ENG dispatch** needs constructed/registered object and initialized relevant globals. **Positive polygon contact** needs both a verified source fixture and a demonstrated candidate population path; no assumption that scene geometry itself populates the collision list. **Substitution parity** must be documented per experiment; missing full WinMain is not a blanket blocker to bounded probes.

## 3. Prioritized bounded milestones

Milestone IDs are stable planning identifiers, **not run IDs**. Priority is proposal order, not execution ownership. Each substantive investigation creates its own new `agent/runs/i76exe/<run-id>/` and branch under current protocol; concurrent independent attempts are permitted. "Completion" below concerns *evidence for that one bounded question*, **not automatic canonical acceptance**.

### M-TER-01 — Generalize original M06 heightfield/contact observations (P0; recommended first)

- **Owner / interfaces:** TER primary; VEH dynamics, ENG clock and numerical execution.
- **Question:** Which controlled pose, sampler-page/seam and terrain-material cases reproduce valid original height/normal/material and mode-0 tire results; where do special four-point `00440740` and tire contact diverge?
- **Prior evidence/gap:** [M06 report ``F1–F5``](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) proves original M06 mapping, measured sampler and positive suspension, but only a limited pose/surface domain. `00440740` stayed zero in upright cases.
- **Retail anchors:** `00493910`/`00493080` terrain init; `00493550`, `004927B0`, `004931C0` queries; `00440740`, `00438FD0`, `0046DC10`, `00437230`, `0049E0F0` filter; ENG `0049C920` and subdivision.
- **Reuse and prerequisites:** [M06 probe, input preparer, x87 helper, verifier](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md) and [ENG timing replay](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/REPRODUCE.md). Private hash-checked retail PE/GZF/ZFS, M06.MSN/TER, stock VCFs, `engsnd.dat`; Ghidra 12.1.4, Java, Python, liblzo2, x86_64 gcc/x87. Do not publish input bytes.
- **Experiment:** establish a reproduced baseline control, then change **one** controlled pose/coordinate/page-edge/material condition per case. Trace raw source sample addresses, rounding control, material/normal, wheel contact flags/compression and caller/substep chronology. Retain hardware `FISTP`/`FCOS` service and an independent scalar comparator. Do not synthesize page data while describing it as authentic retail; another mission is optional only if independently hash-proven.
- **Publish:** new manifest/findings/validation/`REPRODUCE`, script(s), sanitized per-case event/branch and numeric tables, fixture digests and source offsets, positive and negative controls, explicit service ledger and [documentation-impact handoff](../../agent/protocol/templates/DOCUMENTATION_IMPACT.md).
- **Complete within scope:** at least one *new* source-verified M06 page-boundary/pose/material case with valid original reads, numerically checked source values and original callback return, plus an explicit countercase or relevant unchanged control; reproduce with a separate invocation and compare original versus independent numerical oracle. Report `00440740` outcomes separately from tires.
- **Partial / inconclusive / failure:** valid sampler but no completed tire callback = **partial**; fixture or state never reaches chosen branch = **inconclusive**; unmapped reads or unexplained numeric divergence = **failed validation** (retain traces, do not claim contact). A zero special-probe result is a **measured negative case**, not a failure if correctly scoped.
- **Dependencies / blockers:** baseline private fixtures and hardware service are hard requirements for positive execution; another mission or road-intersection fixture is **not** required for this M06-only result. **Promotion opportunity:** a bounded TER sampler/vehicle-contact contract after later reconciliation; no automatic promotion here.

### M-ENG-01 — Reach class-1 through original descriptor-driven pre/post scheduling (P1)

- **Owner / interfaces:** ENG primary; VEH, OBJ world membership, MLD/TER initialization where needed.
- **Question:** Can original `00461C80`/`00461D50` invoke class-1 `00463800`/`00463950` through normal descriptor/collection traversal, **rather than** the harness calling callbacks directly?
- **Evidence/gap:** [ENG frame audit](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) statically establishes gameplay-state-5 phase order and descriptor table (stride `0x34`; class-1 `004F777C`). [M06 replay](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) executes callbacks **manually**.
- **Retail anchors:** WinMain `00402B30`/`004039B8`, indirect calls `00461D38`/`00461E08`, descriptor slots `004F7784/88/8C`, world construction `0045EBD0`/`004AD6F0`, ENG clock `0049C920`.
- **Reuse/prerequisites:** [schedule audit + frame physics procedures](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/REPRODUCE.md), [M06 full callback harness](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md); authenticated PE/GZF/stock assets, controlled object registration, clock and chosen explicit Win32/mission/input substitutes.
- **Experiment:** static trace of collection/dispatch and status gates, then execute the **real dispatcher entry point** with a registered class-1 object; log descriptor slot fetched, callback address, object identity, phase and pre/post field diffs. Use direct-callback baseline as a control only. Full WinMain is an optional later test, not a false completion requirement.
- **Publish:** callsite/indirect-target event trace, registry/setup proof, event timeline, state diffs, substituted services, isolated run provenance, reproduction and validated source-anchor map.
- **Complete:** verified original dispatcher performs at least one pre **and** post class-1 invocation in the tested state with correct original descriptor identity and state chronology, without injecting callback entry from the harness.
- **Partial / inconclusive / failure:** only static queue mapping or one dispatch phase = **partial**; no valid registered object = **inconclusive**; unexpected callback target/state or unaccounted synthetic invocation = **failed validation**. Never call a dispatcher slice a completed WinMain run.
- **Dependencies:** constructed object and registry, clock/math startup; terrain if tracing live suspension branch. **Promotion:** ENG dispatch-phase interface once independently reconciled.

### M-TER-02 — Determine scene-to-polygon-candidate ownership (P1, fixture-gated)

- **Owner / interfaces:** TER primary; VEH contact consumer, GEO/OBJ scene registration; separate `i76edit` source/road descriptions only as cross-track input.
- **Question:** Does `004925F0` registering a scene object into `00644200` (or a distinct producer) populate the `0052B94C` polygon candidate list consumed by `0043E530`? Which original owner creates, removes and transforms the candidates?
- **Current evidence/gap:** [TER anchor index](subsystems/TER.md), [M06 source `F5`](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/findings.json), [editor intersection reference](../../ref/editor/intersection_geometry_and_driving_surface.md); the two lists are **different observed structures, not demonstrated connected dataflows**.
- **Anchors:** `004925F0`, `00644200`, `0043E530`, `0052B94C`, `00440740`, terrain fallback `00493550/004931C0`; trace original writers/iterators and ownership before assigning names.
- **Reuse/prerequisites:** [M06 harness](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md), [historical road corridor](../../ref/level_format/i76_rseg_road_corridor_reference.md), [editor road/surface caveats](../../ref/editor/road_terrain_serialization.md). Static original-code tracing needs PE/GZF; **positive polygon execution additionally needs a byte-verified licensed intersection/placement fixture** and its resource/transform construction.
- **Experiment:** first static writer/reader/callgraph and allocation/lifetime audit for both heads. With a verified fixture, execute registration and polygon query; record source object, transformed face/candidate, list insertion, query traversal/branch and a matched heightfield-only control. Treat failed bridge or no candidates as real scoped observations, not fabricated polygon proof.
- **Publish:** original writer/consumer opcode anchors, candidate ownership diagram, list-node dumps sanitized to derived structure, fixture digests, original call/branch events, reproduction instructions, explicit negative/alternative producer analysis.
- **Complete:** an original instruction chain connects a verified source polygon to the exact consumed candidate (or conclusive traced evidence establishes a different source/no connection in that tested scenario), with a control excluding accidental heightfield fallback.
- **Partial / inconclusive / failure:** static producer map only = **partial**; unverified source fixture or inaccessible producer = **inconclusive**; mismatched list identity or synthetic list writes falsely attributed to original code = **failed validation**.
- **Dependencies:** actual registration/transform setup; positive demonstration **blocked** until a suitable authentic fixture is found, but static audit is not blocked. **Promotion:** TER surface ownership and collision-candidate ABI, when warranted.

### M-ENG-02 — Characterize class-1 update gates and time discontinuities (P2)

- **Owner / interfaces:** ENG/VEH.
- **Question:** Precisely when do pre/post, active/inactive branches, pause and distance conditions execute; how do zero, long and restarted frame deltas affect subdivisions and persistent runtime state?
- **Evidence/gap:** [two-frame](../../agent/runs/i76exe/i76exe-20261027T033452Z-2f8c31f5/artifacts/VEHICLE_TWO_FRAME_ORIGINAL_SIMULATION.md) and [frame `F1/F3`](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) cover a constrained selection. “Active” is an **annotation**, not a proven near-camera scheduling semantic.
- **Anchors:** `00406840`, `0044E010`, `00463800`, `00463950`, `0049C7F0/0049C920`, `0049CBE0/0049CC20/0049CCA0`, runtime `+0x444/+0x448/+0x44C`.
- **Reuse / inputs:** [frame clock and callback probes](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/REPRODUCE.md) and original vehicle state; original PE/GZF/stock assets, explicit tick/ftol/OS service ledger; loaded TER only for positive wheel response.
- **Experiment:** paired original-instruction matrix varying only pause, status, camera distance and clock delta. Capture actual branch PCs, timer state, pre/post action, input and root mutation with same-state controls; distinguish direct callback experiments from M-ENG-01 dispatcher result.
- **Publish:** gate truth table with original operands and chronology, original input/clock setup, branch events and numeric checks, documented negative paths.
- **Complete:** at least one verified near/far or pause-related branch transition **and** one delta boundary with original state diffs, independently reproduced and no unexplained numeric faults.
- **Partial / inconclusive / failure:** static gate map or one-sided branch = **partial**; inaccessible state = **inconclusive**; false native scheduling claim or corrupted timer state = **failed validation**.
- **Dependencies:** clock startup and class-1 constructed state; M-ENG-01 improves *normal* scheduling confidence but is not a mandatory lock on isolated gate research. **Promotion:** bounded ENG/VEH callback and timer behavior.

### M-VEH-01 — Test original polygon contact response once candidates exist (P3, conditional)

- **Owner / interfaces:** VEH primary; TER polygon candidates and heightfield control, OBJ/GEO source identity.
- **Question:** Given a verifiably **original-populated** collision candidate, which branch of `0043E530` influences `00440740` and vehicle response relative to heightfield-only fallback?
- **Evidence/gap:** [M06 original tire path](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) and `F5` do **not** demonstrate polygon response, special-probe positive return or complete object collision.
- **Anchors:** `0043E530`, `0052B94C`, `00440740`, `00438FD0/0043A5D0`, `0046DC10`, `00493550`.
- **Reuse/prerequisites:** [M06 reproduce](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md), licensed polygon fixture and validated source registration, full numerical service, valid vehicle pose. **M-TER-02 positive candidate provenance is the gating prerequisite** for a claim of integrated response.
- **Experiment:** same original vehicle state with/without source-registered candidate, trace chosen face/normal, hit flags, contact and wheel/pose deltas, and validate against a terrain fallback control without hand-writing candidate list nodes.
- **Publish:** branch and candidate provenance, signed contact/response numerics, controls, repeatability, service and fixture provenance.
- **Complete:** different original contact branches tied to a verified candidate and source geometry with reproducible original state response and a clean fallback control.
- **Partial / inconclusive / failure:** correct candidate lookup without physical response = **partial**; no positive original source-candidate link = **blocked/inconclusive**; synthetic candidate presented as retail registration = **failed validation**.
- **Dependencies:** M-TER-02 confirmed producer fixture; M-TER-01's terrain/numeric controls strongly recommended. **Promotion:** scoped VEH/TER polygon contact behavior, not total collision-system fidelity.

### M-VEH-02 — Bound control-to-pose and persistent-state semantics (P2)

- **Owner / interfaces:** VEH primary; ENG scheduling, AI/FSM input source as later interface.
- **Question:** For a constructed stock class-1 object, what original drivetrain/control fields and gate outcomes produce consistent two-plus-frame root, wheel and velocity transitions under controlled nonzero input?
- **Evidence/gap:** [two-frame control replay](../../agent/runs/i76exe/i76exe-20261027T033452Z-2f8c31f5/artifacts/VEHICLE_TWO_FRAME_ORIGINAL_SIMULATION.md) has original mutations but artificially injected input/distance; [later startup fix](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/FRAME_INITIALIZATION.md) removes a setup-induced basis defect. [M06](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/AUTHENTIC_TERRAIN_PHYSICS.md) adds physical contact but not live user controls.
- **Anchors:** `00463800`, `00465370`, `0043A3C0`, `0043BDF0`, runtime `+0x70` ownership and root `+0x18`, `00493C50`, `00438FD0`.
- **Harness/inputs:** [frame reproduction](../../agent/runs/i76exe/i76exe-20261028T172133Z-66a1688b/artifacts/REPRODUCE.md), [M06 original physics](../../agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/artifacts/REPRODUCE.md), private verified bus/GTSi and terrain as chosen, clock/math plus numerical service.
- **Experiment:** paired controls (zero/one bounded nonzero), pre/post persistent state and root 9-float/3-double pose, original path and full typed Gram checks. Do not infer real user-input routing unless those native producers execute. Cross-check with M-ENG-01 results if available.
- **Publish:** control-field maps, original event/pose/velocity tables and timing, independent invariant checks, reproducible baseline/negative controls.
- **Complete:** two reproducible distinct controlled inputs produce explainable original persistent state/pose changes over at least two original updates without inherited missing-startup numerical artifacts; document whether contact branch ran.
- **Partial / inconclusive / failure:** state/pose reproduced but control origin unclear = **partial**; missing required startup = **inconclusive**; unexplained NaNs, invalid roots or unmeasured substitutions = **failed validation**.
- **Dependencies:** verified construction and math/clock, explicit control source, optional M-ENG-01 for dispatcher-driven fidelity. **Promotion:** narrowly scoped control/pose invariant after reconciliation.

## 4. Three ranked first Codex assignments

| Rank | Initial objective | Value / feasibility / prerequisite | Decision |
| --- | --- | --- | --- |
| **1: M-TER-01** | Extend original M06 terrain/contact over controlled new pose, seam or material queries with independent oracle | **High reuse, low marginal setup**: existing actual M06 original-code harness, full REPRODUCE, x87 helper, source fixtures; no unverified scene-polygon producer prerequisite. | **First production investigation.** |
| **2: M-ENG-01** | Establish descriptor-mediated class-1 pre/post dispatch from `00461C80/00461D50` | High architectural value, moderate difficulty: original slot/static path known but world registry/dispatch preconditions not yet replayed. | Begin concurrently if private Ghidra/fixtures available. |
| **3: M-TER-02** | Determine scene registration `004925F0/00644200` versus collision candidates `0052B94C` consumed at `0043E530` | Very high physics payoff, **higher uncertainty**: authenticated intersection/polygon fixture is not yet documented and bridge is unproven; static work independent. | Start static writer/reader trace or fixture provenance discovery; defer promises of positive contact. |

Ranking is based on current accepted evidence and resource uncertainty, **not** certainty of the hypothesized outcome. Later changes to available private fixtures can change it; retain IDs and cite new runs. Do not assign a global subsystem lock.

## 5. Reconstruction readiness and blockers

| Subsystem | Already suitable for bounded *exploratory* independent implementation or comparison | Promoted contract usable as an accepted reference | Not ready as a maintained reconstruction API |
| --- | --- | --- | --- |
| **ENG** | Approximate 256-seed math initialization and current-frame subdivision over tested domain; testable original-input trace | **None for scheduling yet** | WinMain ordering under live dispatch, real input/AI/FSM, restart/teardown, timer discontinuities, full original numerical parity |
| **VEH** | Scoped VCF construction, bounded pose/Gram comparisons, M06 tire filter/contact-mode data | **Vehicle construction/GEO/TMT only** for two tested stock vehicles | General drivetrain/control, special/polygon collision, destruction/caches, damage, broad vehicle families and runtime fidelity |
| **TER** | M06 page mapping, sampler interpolation and material/normal oracle over validated inputs; editor formats as explicitly separate evidence | **No promoted TER contract yet** | Multi-mission/edge behavior, road/scene collision provenance, unresolved packed bit 12, full terrain LOD/rendered road interfaces |

Three distinct authority categories: **research-grade experimental code** may be constructed in individual runs; **promoted testable behavioral contracts** require reconciled evidence and human decision; **maintained replacement components** require later explicit architecture/ownership authorization. This roadmap grants no source/layout commitment and proposes no `reconstruction/` or `validation/` directory. An optional future shared extraction of common Ghidra resource/x87/timer services may reduce duplication; it is **not a prerequisite** and must preserve immutable run-owned implementations.

**Hard/conditional blockers:** licensed retail PE, GZF and relevant mission/stock resources must be provisioned privately for original execution; Ghidra-compatible machine and isolated writable scratch needed; M06 sampler fractional cases require measured x87 correction. The polygon integration **positive** experiment additionally needs verified geometry/placement input and original registration. **Scope limit, not blocker:** absence of full Windows gameplay, another mission, newer renderer, or a global source tree does not preclude bounded original-code analysis. Older harnesses missing an exact `REPRODUCE` are not portable merely because scripts exist: inspect provenance or write a new self-contained run. Hardware FISTP/FCOS fixes do not certify other x87 behavior.

## 6. Reusable milestone template and acceptance workflow

When indexing another engine owner, use this compact stable record (without editing or inventing prior run identities):

1. **ID, priority, primary/related advisory owners**, and binary track.
2. **Observable technical question and scenario**: inputs, original-code anchors, owned data, target branch or invariant.
3. **Evidence baseline**: promoted contracts vs merged runs vs historical references, with finding IDs and limitations.
4. **Execution dependency list**: original PE/Ghidra baseline, private inputs/digests, environment, substitutions, upstream interfaces; mark proven dependencies versus inferred ones.
5. **Experiment and controls**: original instructions actually invoked versus independent model or stub, concrete events/states to compare.
6. **Evidence bundle**: append-only run with manifest/findings/validation, scripts, raw/derived provenance, reproduction guide and documentation-impact note.
7. **Completion and noncompletion conditions**: positive or bounded negative result, independent checks, partial, inconclusive, blocked, failed; avoid speculative percentages.
8. **Promotion candidate** and risks: what *separate* review could add to `manual/reference/`, contradictions and unresolved domains.

**Publication:** start every Codex conversation with the repository URL and milestone ID, then independently pin current `main` and policy 1.0.4 or its successor, read the subsystem index and linked evidence, inspect active PRs, allocate a **new** unique `i76exe` run branch for substantive research, and write only to that run directory. Original-instruction stubs and experimental models are permitted; never modify another run, original binary or private GZF or promote claims in the same run PR. Review required `integrity`, current mergeability and manual human decision; no self-merge. For the separate **roadmap PR**, this document and bootstrap acceptance note are planning records only. Direct evidence links are a navigational crosswalk, **not** newly executed validations.
