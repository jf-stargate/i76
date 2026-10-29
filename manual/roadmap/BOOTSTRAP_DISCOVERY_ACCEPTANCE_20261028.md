# Step 4 — cold-start subsystem discovery acceptance (2026-10-28)

**Outcome: PASS (8/8 discovery criteria), as assessed in the managing ChatGPT conversation.**

**Evidence tier:** manager-supplied report of a **read-only repository discovery test**. This page is a durable *planning/acceptance note*, not a new original-binary run, a machine-generated test transcript, an immutable Codex session record, or a technical finding promotion.

**Repository and policy:** [`jf-stargate/i76`](https://github.com/jf-stargate/i76), accepted source `main` [`0219bbc2eb3348736e0c7d1aa31c3b54a0397d60`](https://github.com/jf-stargate/i76/tree/0219bbc2eb3348736e0c7d1aa31c3b54a0397d60), protocol [`1.0.4`](../../agent/protocol/BOOTSTRAP.md), independent engine indexes [ENG](subsystems/ENG.md), [VEH](subsystems/VEH.md) and [TER](subsystems/TER.md).

## Method and observed coverage

A fresh Codex CLI conversation without historical conversation content was assigned binary track `i76exe` and advisory subsystem `VEH`. It used GitHub access where shell Git access was unavailable. The managing conversation reports that its read-only bootstrap successfully identified:

1. The correct accepted repository, onboarding entry point and publication rules.
2. VEH's scope and ENG/TER functional dependencies, without falsely treating them as exclusive module boundaries.
3. Original retail-code anchors and relevant data structures.
4. The human-reviewed [vehicle VCF/GEO/TMT construction reference](../reference/engine/vehicle_construction.md) and [promotion record](../../agent/promotions/vehicle_vcf_geo_tmt_20261023.md).
5. Later merged **unpromoted** vehicle simulation, clock and M06 physics findings, rather than conflating merged-run evidence with accepted contracts.
6. Original-instruction Ghidra harnesses, their owned scripts, validation files and reproduction guidance.
7. Private fixture/Ghidra requirements, service substitutions and limits on executable reproducibility.
8. The strongest bounded terrain/suspension integration and a specific feasible next investigation.

**Assessment:** 8/8 for finding and correctly qualifying the existing repository context. There is **no immutable test transcript committed** for this exercise; the eight bullet items are the management-level assessment, not eight independent reproduced test runs.

## Limitations and follow-up

The session **did not** execute retail instructions, reproduce recorded validators, verify an entire Windows runtime, provision every private Ghidra/resource input, or prove original scene-to-polygon candidate transfer. Known remaining obstacles are private GZF/game corpus availability for an arbitrary fresh machine, some older scripts lacking complete standalone `REPRODUCE` steps, misleading historical function labels, and absence of a verified positive polygon-contact fixture.

The test therefore supports the narrower conclusion that **repository-native discovery is usable by an independent research session**, not that all historical experiments are environment-independent. See [milestone baseline, dependencies and ranked Codex assignments](ENGINE_SUBSYSTEM_MILESTONES.md). Its first proposed production experiment is [M-TER-01](ENGINE_SUBSYSTEM_MILESTONES.md#m-ter-01--generalize-original-m06-heightfieldcontact-observations-p0-recommended-first); it must be assigned only after the roadmap PR is merged and accepted, and the investigating session must rebootstrap on current `main`.

## Provenance and authority

The original bootstrap output was supplied in the managing conversation, **not filed as an accepted `agent/runs/` artifact in this repository**. This record does not claim access to an immutable output file, attach invented session logs, manufacture a `run_id`, convert the discovery test into a promotion, or alter any accepted run. It is submitted as shared documentation for explicit human maintainer review.
