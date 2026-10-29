# I76 — proposed project objectives

**Status: decision proposal, not an accepted project charter, technical finding, protocol amendment, or authorization for maintained reconstruction.** Prepared from accepted `main` `9312486b92f15305d814c2bf0551f3cf1e233f48` on 2026-10-29. Human maintainer review must settle the project's intended final product, fidelity and priorities. See [capability roadmap](CAPABILITY_ROADMAP.md) for measurable integration gates and [existing technical milestones](ENGINE_SUBSYSTEM_MILESTONES.md) for bounded Codex experiments.

## Working mission

Recover Interstate '76's original behavior through original-binary analysis and reproducible experiments, then use explicitly reviewed behavioral contracts to support a validated, independently maintained reconstruction **if and when the maintainer authorizes that implementation work**. Prefer an increasingly complete, authentic gameplay path over pursuing every isolated function before integration. The retail `i76.exe`, `i76edit.exe` and `i76shell.dll` remain distinct research binaries; advisory engine subsystem IDs are not recovered source modules.

This is a **proposed priority choice**, not evidence the user has approved a playable rebuild as the final deliverable.

## Project-level goals and success measures

| ID | Goal | Observable program outcome | Authority/limits |
| --- | --- | --- | --- |
| **OBJ-01** | Trustworthy original-behavior research | Key original paths have versioned inputs, original-instruction boundaries, independently checked state/event traces, explicit substitutes, and reviewable evidence | Research authorized; merged runs remain evidence, not automatic canonical truth |
| **OBJ-02** | One integrated authentic gameplay scenario | One retail mission reaches resource/mission setup, object creation and registration, frame scheduling, player-control effect, environmental response and inspectable camera/presentation state with deterministic trace checks | Near-term integration target; a staged original-instruction harness is not a full Windows gameplay claim |
| **OBJ-03** | Contract-driven independent reconstruction | Independently maintained components can replace bounded services and agree with selected original scenarios under shared, reproducible differential tests | **Not authorized by this document**; separate scope/design/ownership review required |
| **OBJ-04** | Expand gameplay fidelity and coverage | Deliberately broaden beyond the first scenario: vehicles, mission/FSM, AI, combat, polygon collision, environment, renderer, audio and potentially network behavior, each with declared fidelity | Priorities depend on evidence, dependencies and the adopted desired end state |
| **OBJ-05** | Recover companion program behavior | Investigate editor and shell with their own original binary baselines and publications; integrate interfaces only when established by evidence | No assumption that either is an engine subsystem or needs full reconstruction |

## Priority principles

1. **Integration-facing evidence before exhaustive cataloging:** prefer tasks that unblock an agreed capability gate, provide a reusable oracle, or resolve a high-impact contradiction. Do not follow every interesting newly discovered function automatically.
2. **Original behavior remains the oracle:** distinguish binary-static, original-instruction emulation with supplied services, independent models, and unmodified retail runtime. Preserve negative results.
3. **One clear reviewable outcome per Codex run:** task IDs map from project objective → capability gate → bounded technical experiment → immutable run/PR. The run is not the milestone itself.
4. **Research and implementation are separate decisions:** exploratory emulators, stubs, models and comparators are legitimate research tools; promoting them into maintained reconstruction is separately authorized.
5. **Cross-track independence:** engine, editor, shell and shared research can advance concurrently, while one explicit engine integration critical path guides priority.
6. **No time/percentage guesses from check counts:** 3,807 or 76,205 assertions describe datasets, not percentage of complete gameplay behavior.

## What is *not* established by current evidence

- Full WinMain/gameplay startup and live input lifecycle; a selected player's original post phase and peripheral initialization.
- End-to-end polygon-candidate ownership or general road/terrain collision.
- Original rendering through final pixels as part of one integrated original frame.
- General fidelity across missions/vehicles; full original hardware, OS, audio, or multiplayer behavior.
- An authorized maintained engine replacement or a promise of asset redistribution.

The [architecture transition proposal](ARCHITECTURE_TRANSITION_PROPOSAL.md) is useful historical planning context, not new authority. Protocol, immutable evidence and promoted technical contracts are governed separately.

## Strategic decisions for explicit maintainer acceptance

1. **End state:** is the primary desired deliverable a playable standalone reconstruction, comprehensive original-binary documentation, original game preservation/compatibility, or a prioritized combination?
2. **First demonstration:** is an authenticated *state-trace-only* M06 vertical slice sufficient as the first integration milestone, or must it already include visible rendering and live player controls?
3. **Fidelity and scope:** prioritize behavioral equivalence for representative scenarios versus strict original numerical/hardware parity; choose the early mission/vehicle and whether editor/shell are required for the first product.
4. **Implementation:** decide whether/when to authorize the maintained reconstruction workstream and reusable validation infrastructure. This proposal alone does not do so.

Until those are ratified, the [capability roadmap](CAPABILITY_ROADMAP.md) is a **provisional sequencing model**, not a blanket instruction for autonomous agent task selection.

## Stewardship

The coordination conversation owns the proposed objective/capability ordering and requests reviewed planning PRs. Individual Codex research conversations discover accepted `main`, select a bounded task, publish only their owned immutable evidence, and hand off documentation impact. The maintainer alone accepts publication or strategic changes. Evidence promotion follows [documentation workflow](DOCUMENTATION_WORKFLOW.md). This document does not change `AGENTS.md` or `agent/protocol/`.
