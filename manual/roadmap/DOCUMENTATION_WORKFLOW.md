# I76 documentation reconciliation and promotion workflow

This is an operational guide, **not** a new publication protocol or an automatic approval mechanism. The authoritative requirements remain the current pinned `main` copies of [AGENTS.md](../../AGENTS.md), [access.yaml](../../agent/protocol/access.yaml), and [BOOTSTRAP.md](../../agent/protocol/BOOTSTRAP.md). Re-check the current default-branch commit, open PRs and ruleset before proposing changes.

## Three distinct records

| Record | Where | What it means |
|---|---|---|
| Research evidence | `agent/runs/<track>/<run_id>/` | Immutable submitted observations, procedures, provenance, limitations and proposed findings. A merged run does **not** certify its conclusions. |
| Promotion decision | `agent/promotions/` | Explicit, independently inspectable mapping from accepted evidence to conclusions selected for current documentation, including conflicts and evidence limits. |
| Current technical reference | `manual/reference/` | Subsystem-oriented living specification of the best-supported current understanding, citing promotion decisions and original evidence. |

Historical `ref/` is the **frozen legacy research checkpoint**, not the target for routine documentation generation. `scripts/` and `snapshot/` remain historical tools and evidence. Preserve their navigation and provenance; do **not** relocate, rewrite, or imply they are completely migrated. Exceptional corrections/migrations to these trees need separate, explicit maintainer review under `access.yaml`.

## Responsibility split and documentation handoff

- **Research conversation (each new substantive run):** generate immutable evidence and a concise `artifacts/DOCUMENTATION_IMPACT.md` note, following [the template](../../agent/protocol/templates/DOCUMENTATION_IMPACT.md). List it in the run manifest with SHA-256 and byte count, as for other artifacts. Name candidate claims, original addresses, findings/evidence IDs, likely `manual/reference/` targets, contradictions, unresolved questions and whether **no canonical change** is warranted. Do not edit `manual/reference/`, `agent/promotions/` or `ref/` in the same research-run PR. The handoff is a procedural expectation for new substantive runs, **not a newly enforced `integrity` check**.
- **Repository/documentation steward (maintainer-designated management conversation):** on an explicit maintainer request or milestone review, inspect newly merged runs (including historical runs without handoffs), prior promotions, the current reference and the legacy checkpoint; reconcile competing claims; generate appropriate promotion records and curated reference edits in a **separate documentation PR**. Preserve evidence tiers and explain non-promotable findings. The steward prepares changes, never self-approves or merges.
- **Human maintainer:** review individual research and documentation PRs, decide which claims to promote, confirm current-base CI/mergeability and merge deliberately. An accepted research run is not itself a promoted technical specification.

No continuous background watcher, automatic acceptance, new locks, or direct-main writes are implied. A handoff is a prioritization aid rather than proof. Documentation preparation may be requested after multiple related research PRs are accepted, on contradictions affecting an existing reference, or before implementation milestones that the maintainer authorizes.

## Procedure

1. **Discover:** Pin the accepted `main` SHA; inspect documentation indexes, relevant merged runs, documentation-impact notes when present, and open research/documentation PRs. Identify the exact subsystems and source baselines. Do not treat unmerged proposals as accepted findings. Unmerged branches are candidate evidence only.
2. **Select a coherent milestone:** Reconcile by subsystem or architectural boundary (for example vehicle VCF construction), not automatically after every research PR. Structural or navigation corrections may be published sooner without promoting technical claims.
3. **Build a finding crosswalk:** For each candidate claim, name the immutable run ID, merge commit, finding ID, original function/address, evidence artifact path and SHA-256, executable and Ghidra provenance, method, confidence and reproduction limitations. Cite applicable historical `ref/` claims explicitly.
4. **Reconcile rather than overwrite:** Identify confirmation, narrowing, correction, supersession or contradiction. Record all relevant contrary evidence; prefer narrower wording when direct binary evidence and emulator observations support different scopes. Do not silently elevate "native-emulated" to "full retail Windows execution."
5. **Propose two linked outputs:** A promotion record based on [the template](../../agent/promotions/TEMPLATE.md), plus focused changes under `manual/reference/` (and minimal index links). Preserve direct links back to source run files and historical references. If no conclusion meets promotion criteria, publish a gap/assessment record without a canonical claim.
6. **Review in a separate PR:** Use a fresh isolated **documentation/promotion branch**, not the research run's owned branch. Do not modify any merged `agent/runs/`. Identify the original accepted base SHA and all files changed. Avoid mixing unrelated governance or unrelated subsystem edits.
7. **Validate and accept:** Check source existence, link resolution, evidence digests, baseline names, internal consistency and the current PR diff. Require the trusted GitHub `integrity` status for the current head/base and resolved discussions. **The human maintainer alone decides** whether technical interpretation and promotion are acceptable; agents never autonomously merge.
8. **Continue:** As new evidence arrives, keep earlier promotion records as decision history; revise current `manual/reference/` through a later promotion that explicitly links the superseded claim and the new evidence. Original run records stay immutable.

## Evidence scope and writing standard

- Label assertions as **binary-static**, **original-instruction emulation with substituted services**, **retail corpus**, **derived/inferred**, or **unresolved**. Include method-specific limits in the reference itself, not just in a PR description.
- Use exact retail VAs, byte offsets, field widths, ownership and lifecycle qualifications; retain baseline/file hashes when measured. Never fabricate original source files, symbols, private asset paths, direct-runtime verification or dates.
- Make each reference self-contained enough that a new conversation can recover the technical facts, their uncertainty, and the relevant evidence without relying on chat history.
- Preserve older still-useful `ref/` reports. Distinguish their historical confidence from current accepted interpretation; historical text is not automatically invalidated by a newer run.
- No original binaries, proprietary resource payloads, Ghidra databases, secrets, or unreviewed bulk dumps in the public repository.
- `integrity` validates content/path/structure, **not** the scientific truth of promoted conclusions.

## Deriving documentation coverage

For a requested coverage review, enumerate merged run IDs and their merge commits, inspect `agent/promotions/` records for explicit run/finding references, and compare those promotions with current `manual/reference/` links. Report **promoted**, **reviewed/deferred**, **unassessed**, or **needs reconciliation** at the finding/subsystem level. A missing handoff or promotion is not evidence of an incorrect finding; an accepted run is not a canonical promotion. Generate the coverage report from the repository state when requested rather than maintaining a concurrently edited global status file. Do not infer claim coverage solely from matching filenames.

## Suggested cadence

- **Each new substantive investigation:** publish immutable research and a documentation-impact handoff in its own run/PR (procedural expectation; no separate CI gate).
- **As needed:** fix broken navigation or demonstrably stale status with a narrow documentation PR.
- **On maintainer-requested reconciliation or subsystem milestones:** the documentation steward generates a promotion + canonical reference PR after sufficient evidence accumulates; do not force weekly promotion.
- **On contradiction:** preserve both source runs and either defer promotion or document a qualified conclusion and explicit open question.

See [research acceptance](RESEARCH_ACCEPTANCE.md) and [promotion-record guidance](../../agent/promotions/README.md). No shared lock server, new agent credentials or automatic merger is required for this manually supervised project.
