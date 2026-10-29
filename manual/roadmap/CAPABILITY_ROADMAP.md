# I76 — proposed capability roadmap and Codex selection gates

**Status: proposed planning, not a promoted original-code contract or authorization to build reconstruction.** Prepared from accepted `main` `9312486b92f15305d814c2bf0551f3cf1e233f48` on 2026-10-29. Depends on maintainer ratification of [project objectives](PROJECT_OBJECTIVES.md). This document selects observable **capabilities**, while [ENG/VEH/TER technical milestones](ENGINE_SUBSYSTEM_MILESTONES.md) propose individual experiments. It does not modify immutable runs or silently complete milestones using an unmerged PR.

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
| **CAP-FRAME-01 — Original object-driven pre/post frame** | Original class collection registration and descriptor traversals invoke and return from class-1 pre and post callbacks in a multi-frame authenticated M06 harness; independent direct-callback control | **Candidate only**: [PR #58](https://github.com/jf-stargate/i76/pull/58) demonstrates three bounded **unselected** frames; its required CI currently fails on an inherited trusted-base schema-test regression | Trusted CI recovery, reviewed research acceptance; not selected gameplay |
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
| **M-ENG-01** (candidate PR #58) | CAP-FRAME-01 | Original descriptor-driven pre/post visits class-1; explicitly unselected state; cannot close CAP-CONTROL |
| **M-VEH-02** (existing roadmap) | CAP-CONTROL-01 / CAP-SLICE-01 | Bound input/control-to-pose persistence in original instructions |
| **M-ENG-02** (existing roadmap) | CAP-FRAME-01 / CAP-SLICE-01 | Frame update gates and discontinuities once baseline dispatch is stable |
| **M-TER-02** (existing roadmap) | CAP-SURFACE-01 | Prove or refute ownership/transfer from scene registration to collision candidate collection |
| **M-VEH-01** (conditional) | CAP-SURFACE-01 | Positive polygon contact with authenticated fixture and original candidate path |
| **Future selected-post/input experiment** (ID to allocate at review) | CAP-CONTROL-01 | Focus on exact selected post failure, original peripheral initialization, x87 FSINCOS, ordinary input; no implicit success from unselected cases |
| **Future integrated camera/presentation experiment** (ID to allocate at review) | CAP-CAMERA-01 | Connect actual original frame lifecycle to camera/world-to-render state, with explicit pixel boundary |

Do not rename accepted run IDs or automatically create a new stable milestone ID because a limitation was mentioned. Discovery can continue across subsystem labels; the primary goal is the demonstrable capability.

## Proposed next-action queue

1. **Operational prerequisite, not research:** repair the trusted-base archive test so accepted research schema `1.2.0` is honored. [Draft PR #59](https://github.com/jf-stargate/i76/pull/59) proposes a narrow fix, but existing `pull_request_target` checks run the broken base first; a deliberate maintainer-controlled recovery is required. Never bypass protection autonomously or present advisory candidate CI as the required check.
2. **Review bounded engine evidence:** after trusted CI is restored, reassess [draft PR #58](https://github.com/jf-stargate/i76/pull/58), require current passing `integrity`, then the human decides whether to accept that immutable original-dispatch run. No early promotion.
3. **Ratify the project destination:** choose the user-facing end state, first M06 demonstration boundary, numerical/behavioral fidelity tradeoffs and reconstruction authorization policy in [project objectives](PROJECT_OBJECTIVES.md).
4. **Next critical-path research:** pending (2) and (3), investigate selected-player original post initialization/input and the exact FSINCOS/peripheral-state blockers, with controls and explicit private-input requirements. Concurrent VEH work can proceed independently if not duplicative.
5. **After a coherent evidence milestone:** reconcile accepted findings into a separate promotion/current-reference PR; no technical reference gains authority solely from this plan.

## Task-selection procedure for the coordination layer

1. Pin `main` and check CI/protection, active PRs, latest accepted runs and promotions.
2. Choose **one incomplete capability gate** from the maintainer-ratified plan, not whichever original function was most recently discovered.
3. Identify its smallest missing dependency and source-supported experiment; score by critical-path unblock, reproducibility, cross-subsystem leverage, uncertainty reduction and unnecessary duplication.
4. Assign a new bounded Codex session with exact private-input requirements, original addresses, specified scenario/controls, negative and completion criteria, acceptable substitutions and a fresh owned run/PR.
5. Review the evidence rather than check counts alone; mark evidence status as **proposed, accepted run, promoted contract, or unverified** and distinguish partial completion.
6. If a gate is blocked on new fixture/hardware/selected state, pursue a separately testable prerequisite or parallel research track; do not manufacture positive claims.

## Publication boundaries

Only [current protected-main policy](../../AGENTS.md) and [bootstrap](../../agent/protocol/BOOTSTRAP.md) govern research publication; documentation workflow controls promotion. Proposed strategic planning is reviewed in a documentation PR. Neither this roadmap nor an original-emulation script approves maintaining a replacement implementation, editing merged runs, publishing proprietary assets, weakening CI or merging autonomously.
