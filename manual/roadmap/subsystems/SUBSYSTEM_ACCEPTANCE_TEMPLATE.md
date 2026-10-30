# Template — finite subsystem acceptance contract

**Status: optional planning template, not an agent publication protocol, project end-state authorization, or a technical finding.** Copy into `manual/roadmap/subsystems/<ID>_ACCEPTANCE.md` for a new scoped workstream. Replace every instructional placeholder before seeking maintainer review. For a complete example, use [RND-v1 acceptance](RND_ACCEPTANCE.md). Keep `AGENTS.md` and the accepted [agent bootstrap](../../../agent/protocol/BOOTSTRAP.md) authoritative for publication, and [project objectives](../PROJECT_OBJECTIVES.md) authoritative only after their explicit ratification.

## Target and bounded scenario

- **Subsystem ID / advisory owner / binary track:** `<ID>`, `<owner>`, `<i76exe|i76edit|i76shell|shared>`.
- **Version and desired outcome:** `<SUBSYSTEM-v1>`: one observable behavior for a finite authenticated scenario; do not say only “reverse-engineer the subsystem”.
- **Project capability:** link to `manual/roadmap/CAPABILITY_ROADMAP.md` with the relevant objective/gate.
- **Fixture identities and source-oracle class:** retail input hashes, private-access notes, controlled parameters, accepted source behavior and evidence tier.
- **Positive case, contrast case, negative/control case and repeat:** name each scenario (e.g. `SC-<ID>-01`), its specific state, expected output, independent evidence and reproducible verifier.
- **In-scope interfaces:** where adjacent subsystems provide authentic inputs and consume validated outputs. These dependencies need their own original code evidence rather than being assumed.
- **Excluded / deferred features:** name them and state why they are not necessary for the specific v1 scenario.

## Completion levels, not one ambiguous “done”

| Stage | Gate IDs | Objective pass condition | Needed review |
| --- | --- | --- | --- |
| `<ID>-RESEARCH-v1` | `<ID>-R1/R2` | Original behavior and input/output contract sufficiently established over all fixed cases; positive and negative evidence and substitutes explicit | Accepted research + separately reviewed canonical promotion |
| `<ID>-INTEGRATED-v1` | `<ID>-I1` plus research | Genuine original-producer-to-original-consumer chain in one source-backed scenario, with independent state/output checks; no fabricated internal intermediate | Accepted source-backed integration evidence and human completion decision |
| `<ID>-PRODUCT-v1` | `<ID>-P1` plus research and integration | Independently maintained, explicitly authorized implementation passes the fixed scenario regression suite and predeclared fidelity constraints | Separate authorization, implementation review and signed-off acceptance record |

These stages describe **separate achievements**, and none is inferred from a count of research PRs, CI success, syntax of an original function name or the existence of implementation code. Full original retail execution is required only when a gate explicitly states it and evidence actually supports it.

## Acceptance matrix

| Scenario / gate | Input fixture + original producer | Expected observable output and invariant | Positive and negative case | Independent comparator | Linked Codex milestones | Current status |
| --- | --- | --- | --- | --- | --- | --- |
| `SC-<ID>-01 / <ID>-R1` | Explicit digest/ownership | Exact data fields/PCs, not inferred behavior | Fixed test A and control B | Source-backed comparator, predeclared tolerance | `M-<ID>-01` | open |
| `SC-<ID>-02 / <ID>-R2` | … | … | … | … | … | open |
| `SC-<ID>-03 / <ID>-I1` | … | … | … | … | … | open |
| `SC-<ID>-04 / <ID>-P1` | … | … | … | … | … | not authorized |

**Comparison-policy rule:** numerical/visual/performance thresholds require a reviewed justification and fixture version **before scoring**. When no authenticated oracle exists, mark the gate blocked and create a fixture-oracle prerequisite; never invent thresholds or call subjective resemblance a pass.

## Bounded work and gaps

| Gap ID | Mandatory in-scope failed/unknown test | Cross-owner prerequisite | Smallest testable worker milestone | Disposition |
| --- | --- | --- | --- | --- |
| `G-<ID>-01` | `SC-<ID>-01` missing producer | original function/source | `M-<ID>-01` | ready/blocked/deferred |

Milestones are lower-level experiments, not extra acceptance criteria. A worker may publish valid **negative** evidence without passing the positive gate. Add a **blocking** requirement only after reviewed proof it affects a previously fixed v1 scenario. Track other interesting discoveries as v2/backlog. Do not spawn an unbounded sequence of research questions merely to seek completeness of an original binary.

## Completion review and future changes

- Pin current protected `main`, current accepted agent protocol and verified source inputs. Each worker publishes its own immutable research run/PR, with original instructions versus supplied services and independent verification. The evidence remains immutable after merge.
- A designated steward separately promotes selected contracts; the human maintainer reviews both the source crosswalk and the acceptance test result.
- A later completion record (e.g. `<ID>_v1_ACCEPTANCE_RECORD.md`) gives each gate's `pass/partial/blocked/failed/deferred`, evidence PR and merge SHA, fixture and verifier identifiers, deviations, and signed-off level.
- Any v1 scope or tolerance change is an explicit reviewed decision with old/new impact. A gate that cannot pass is blocked or deferred, **not** silently satisfied or renamed.
- Managed reconstruction requires a separate authorization. A research acceptance contract does not grant permission to build or publish a replacement engine.
