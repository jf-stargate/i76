# I76 — proposed capability roadmap and Codex selection gates

**Status: proposed planning, not a promoted original-code contract or authorization to build reconstruction.** Originally prepared against accepted `main` `9312486b92f15305d814c2bf0551f3cf1e233f48` on 2026-10-29; evidence/status reconciled against `980037f49b348e14ccdde8ba2961174a8647f090` after merged PRs #58/#59/#60. The document is merged planning, but the strategic decisions in [project objectives](PROJECT_OBJECTIVES.md) still require explicit maintainer ratification. This document selects observable **capabilities**, while [ENG/VEH/TER technical milestones](ENGINE_SUBSYSTEM_MILESTONES.md) propose individual experiments. It does not promote findings, alter immutable runs or authorize implementation.

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
| **CAP-CAMERA-01 — Observe the authentic frame** | Camera/world transform changes resulting from registered original state and frame, with independently validated output; later extend to native render submission/pixels as separate gate | Prior camera/renderer research is bounded and not one integrated original WinMain path | Connect post/frame lifecycle to camera and original producer→renderer; separate final-pixel acceptance if desired |
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
| **Future integrated camera/presentation experiment** (ID to allocate at review) | CAP-CAMERA-01 | Connect actual original frame lifecycle to camera/world-to-render state, with explicit pixel boundary |

Do not rename accepted run IDs or automatically create a new stable milestone ID because a limitation was mentioned. Discovery can continue across subsystem labels; the primary goal is the demonstrable capability.

## Proposed next-action queue (live status check required)

1. **Restore publication enforcement before further acceptance:** the accepted trusted-base archive-schema test repair is [merged PR #59](https://github.com/jf-stargate/i76/pull/59); at this reconciliation, repository ruleset `25664125` was **disabled** and `main` reported unprotected. The human maintainer should reactivate the existing ruleset and required `integrity` check, and verify the repair with a fresh candidate. This documentation PR is a smoke-test opportunity but cannot itself reactivate rules or attest enforcement.
2. **Use accepted bounded M-ENG-01 evidence:** [merged PR #58](https://github.com/jf-stargate/i76/pull/58) documents original 15-node class-collection/descriptor-driven dispatch over three controlled unselected frames (research merge `e06ca00650c1bf1763fac68542f09e13e3b8e883`). Do not treat its historic `validation.json` CI regression note as proof of a new scientific failure or retroactively rewrite it; a fresh post-fix CI audit can assess repository infrastructure independently.
3. **Next critical-path research, already assigned independently:** CAP-CONTROL-01 selected-player post, pending initialization, peripheral state and original FSINCOS. The newly started CLI agent owns its own work and must cold-start from current `main`; do not duplicate its run. A fresh technical milestone identifier may be assigned when the bounded acceptance question is clear.
4. **Curated reference proposal:** independently reconcile accepted frame/startup/dispatch evidence via a separate promotion record and narrowly scoped `manual/reference/engine/frame_scheduling.md` PR. Only a human merge accepts the selected claims.
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
