# I76 — proposed capability roadmap and Codex selection gates

**Status: proposed planning, not a promoted original-code contract or authorization to build reconstruction.** Originally prepared against accepted `main` `9312486b92f15305d814c2bf0551f3cf1e233f48` on 2026-10-29; evidence/status reconciled against `980037f49b348e14ccdde8ba2961174a8647f090` after merged PRs #58/#59/#60. The document is merged planning and the RND workstream was subsequently proposed against accepted `main` `8b0cf1912b3b717e2e2eb7500e44b08f37a2972a`; the strategic decisions in [project objectives](PROJECT_OBJECTIVES.md) still require explicit maintainer ratification. This document selects observable **capabilities**, while [ENG/VEH/TER technical milestones](ENGINE_SUBSYSTEM_MILESTONES.md) propose individual experiments. It does not promote findings, alter immutable runs or authorize implementation.

## Four levels of planning

```text
Project objective  (why / desired outcome)
  -> capability gate  (demonstrable end-to-end behavior)
     -> technical milestone  (specific missing interface or dependency)
        -> immutable Codex research run + PR  (bounded repeatable evidence)
```

Each capability must state a demonstration scenario, independent check, original-versus-supplied service ledger, dependencies, evidence status and completion boundary. A successful run may be **necessary but insufficient** for capability acceptance. A green `integrity` check does not prove scientific correctness, and a merged run is not automatically a curated reference.

## First integrated engine scenario

**Provisional target:** authentic retail M06 mission and stock player vehicle; deterministically reproduce a meaningful sequence from mission resources through registered object, original clock and frame phases, selected control effect, environmental interaction and inspectable camera state. Stage the work through original-instruction Ghidra execution with supplied and clearly labeled OS/hardware/resource services, then independently validate selected state/event traces.

An original dispatcher frame is an intermediate gate; full Windows execution, native final pixels and complete polygon collision are **not** assumed at that gate. The ultimate first demonstration's live-input/visual requirement awaits maintainer decision.

## Capability gates

| Gate | Demonstrable acceptance criterion | Best current evidence / limitation | Next dependency |
| --- | --- | --- | --- |
| **CAP-BASE-01 — Reproducible original-source access** | Fresh agent can locate accepted provenance, private required inputs, original-code harness and independent checks without old chat context | ENG/VEH/TER discovery pilot and M06 replay docs accepted; licensed private inputs still required | Keep reproducibility explicit; no fake asset provisioning |
| **CAP-FRAME-01 — Original object-driven pre/post frame** | Original class collection registration and descriptor traversals invoke and return from class-1 pre and post callbacks in a multi-frame authenticated M06 harness; independent direct-callback control | **Accepted research evidence**: [merged PR #58](https://github.com/jf-stargate/i76/pull/58) (merge `e06ca00650c1bf1763fac68542f09e13e3b8e883`) demonstrates the bounded three-frame **unselected** bus/GTSi dispatcher slice and controls; no separate promoted scheduler contract | Bounded dispatch criterion supported by accepted run; **selected-player post**, complete pending initialization, input and full WinMain remain open |
| **CAP-CONTROL-01 — Selected vehicle/control delivery** | Complete correctly initialized selected-player pre/post scheduling with an original control input path that produces a measured and independently checked vehicle-state change; name all substituted services | Current control fields are harness-provided. PR #58 diagnostic reaches selected post but stops on FSINCOS and incomplete peripheral state | Original selected initialization, class31/34 post ownership, x87 semantics, input and state tracing |
| **CAP-SURFACE-01 — Generalize terrain response** | Independently source-verified height/material/normal and tire behavior over controlled scenarios, plus a separately proved path to polygon candidates before claiming general collision | [PR #57 accepted](https://github.com/jf-stargate/i76/pull/57): bounded M06 pose/tire observations; special probe zero, no polygon contact | Existing M-TER-02 scene/candidate ownership; conditional M-VEH-01 positive original polygon contact. Broader seams/material cases not yet established |
| **CAP-CAMERA-01 — Observe the authentic frame** | Camera/world transform changes resulting from registered original state and frame, with independently validated output; then native scene→visibility→geometry integration, with final pixels as a separate gate | [Native registered camera evidence](../../agent/runs/i76exe/i76exe-20261027T031313Z-32de4d1e/manifest.json) is bounded; [render queue consumer](../../agent/runs/i76exe/i76exe-20261023T062154Z-62e3a718/manifest.json) used a synthetic kind-6 record; native visibility producer and integrated original camera→render remain unproven | **RND workstream:** [M-RND-01 and M-RND-02 ready](RND_SUBSYSTEM_MILESTONES.md), M-RND-03 producer→consumer conditional; later integrate selected-frame camera with CAP-CONTROL-01 |
| **CAP-SLICE-01 — Integrated M06 vertical slice** | One repeatable evidence bundle covers mission resources, registered selected vehicle, original frame scheduler, original control effects, terrain response and camera outputs without manually substituting an entire missing lifecycle. Compare event chronology and state with independent oracles | **Not achieved.** Present results are composable bounded original-code slices, not a full retail frame | CAP-FRAME, CAP-CONTROL, CAP-SURFACE's appropriate scoped contract, CAP-CAMERA; explicit lifecycle and data handoffs |
| **CAP-REPLACE-01 — Validated independent replacement** | One authorized maintainable component implements a promoted behavioral contract and passes shared differential scenarios against a bounded original oracle | **Not authorized / not begun** as maintained reconstruction by this roadmap | Formal implementation authorization and accepted reference contract; no auto-promotion from a research harness |

These status descriptions are **snapshots**, not a manually maintained single source of truth. Before using one to assign work, rediscover live PR states, accepted runs, technical indexes and promotions at a pinned current `main`.

## Technical milestones and their capability contributions

| Technical investigation | Primary capability | Criterion / interpretation |
| --- | --- | --- |
| **M-TER-01** (accepted bounded PR #57) | CAP-SURFACE-01 | New authentic M06 controlled initial-Y cases; positive tire mode-0 does not prove special or polygon contact |
| **M-ENG-01** (accepted bounded PR #58) | CAP-FRAME-01 | Original registration/descriptor-driven pre/post reaches and returns from class-1 for controlled unselected bus/GTSi; **not** complete selected post or CAP-CONTROL |
| **M-VEH-02** (existing roadmap) | CAP-CONTROL-01 / CAP-SLICE-01 | Bound input/control-to-pose persistence in original instructions |
| **M-ENG-02** (existing roadmap) | CAP-FRAME-01 / CAP-SLICE-01 | Frame update gates and discontinuities once baseline dispatch is stable |
| **M-TER-02** (existing roadmap) | CAP-SURFACE-01 | Prove or refute ownership/transfer from scene registration to collision candidate collection |
| **M-VEH-01** (conditional) | CAP-SURFACE-01 | Positive polygon contact with authenticated fixture and original candidate path |
| **Future selected-post/input experiment** (ID to allocate at review) | CAP-CONTROL-01 | Focus on exact selected post failure, original peripheral initialization, x87 FSINCOS, ordinary input; no implicit success from unselected cases |
| **M-RND-01** (new, ready) | CAP-CAMERA-01 | Execute original `00457FF0` visibility producer on real registered stock world objects; no manually inserted spatial record |
| **M-RND-02** (new, ready) | CAP-CAMERA-01 | Original selected-vehicle camera callbacks with controlled pose differentials and persistent `004C2730`; not selected-player post |
| **M-RND-03** (conditional) | CAP-CAMERA-01 | Join original producer and `0048FAC0` consumer using one original-authored record and one emulator state after RND-01/02 |
| **M-RND-04** (conditional) | CAP-CAMERA-01 / CAP-SLICE-01 | Measure original clip/draw entry and output semantics after genuine polygon pipeline; no implied pixels |
| **Future full selected-frame camera integration** (after CAP-CONTROL-01 evidence) | CAP-SLICE-01 | Reconcile original selected gameplay-frame chronology with RND scene, camera and visibility. Not assigned to current RND workers |

Do not rename accepted run IDs or automatically create a new stable milestone ID because a limitation was mentioned. Discovery can continue across subsystem labels; the primary goal is the demonstrable capability.

## Proposed next-action queue (live status check required)

1. **Verify publication enforcement before further acceptance:** [PR #59](https://github.com/jf-stargate/i76/pull/59) repaired the accepted archive-schema test. The ruleset `25664125` was temporarily disabled during recovery, but a subsequent check during review found it **active** again. At acceptance, confirm current ruleset enforcement and a fresh passing required `integrity` check. The roadmap does not itself change GitHub settings.
2. **Use accepted bounded M-ENG-01 evidence:** [merged PR #58](https://github.com/jf-stargate/i76/pull/58) documents original 15-node class-collection/descriptor-driven dispatch over three controlled unselected frames (research merge `e06ca00650c1bf1763fac68542f09e13e3b8e883`). Do not treat its historic `validation.json` CI regression note as proof of a new scientific failure or retroactively rewrite it; a fresh post-fix CI audit can assess repository infrastructure independently.
3. **Next critical-path research, already assigned independently:** CAP-CONTROL-01 selected-player post, pending initialization, peripheral state and original FSINCOS. The newly started CLI agent owns its own work and must cold-start from current `main`; do not duplicate its run. A fresh technical milestone identifier may be assigned when the bounded acceptance question is clear.
4. **RND workers (parallel, nonoverlapping):** [M-RND-01 native visibility producer](RND_SUBSYSTEM_MILESTONES.md) and [M-RND-02 camera continuity](RND_SUBSYSTEM_MILESTONES.md) can be independently assigned to fresh CLI sessions after review. [Merged PR #62](https://github.com/jf-stargate/i76/pull/62) now provides a bounded curated scheduling reference; do not reinterpret it as selected-player execution. Reserve M-RND-03/04 until their prerequisites are accepted.
5. **Ratify strategic decisions:** [project objectives](PROJECT_OBJECTIVES.md) still explicitly leaves playable-reconstruction versus documentation/preservation end state, first visual milestone, and maintained implementation authorization open.
6. **Next research after CAP-CONTROL-01:** evaluate control-to-pose persistence (M-VEH-02) against the selected-player result; pursue integrated camera handoff where independent. TER's scene-to-polygon-candidate ownership (M-TER-02) remains a parallel, fixture-gated path, not a prerequisite for every bounded heightfield scenario.

## Task-selection procedure for the coordination layer

1. Pin `main` and check CI/protection, active PRs, latest accepted runs and promotions.
2. Choose **one incomplete capability gate** from the maintainer-ratified plan, not whichever original function was most recently discovered.
3. Identify its smallest missing dependency and source-supported experiment; score by critical-path unblock, reproducibility, cross-subsystem leverage, uncertainty reduction and unnecessary duplication.
4. Assign a new bounded Codex session with exact private-input requirements, original addresses, specified scenario/controls, negative and completion criteria, acceptable substitutions and a fresh owned run/PR.
5. Review the evidence rather than check counts alone; mark evidence status as **proposed, accepted run, promoted contract, or unverified** and distinguish partial completion.
6. If a gate is blocked on new fixture/hardware/selected state, pursue a separately testable prerequisite or parallel research track; do not manufacture positive claims.

## Publication boundaries

Only [current protected-main policy](../../AGENTS.md) and [bootstrap](../../agent/protocol/BOOTSTRAP.md) govern research publication; documentation workflow controls promotion. Proposed strategic planning is reviewed in a documentation PR. Neither this roadmap nor an original-emulation script approves maintaining a replacement implementation, editing merged runs, publishing proprietary assets, weakening CI or merging autonomously.
