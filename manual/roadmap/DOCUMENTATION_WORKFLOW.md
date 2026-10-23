# I76 documentation reconciliation and promotion workflow

This is an operational guide, **not** a new publication protocol or an automatic approval mechanism. The authoritative requirements remain the current pinned `main` copies of [AGENTS.md](../../AGENTS.md), [access.yaml](../../agent/protocol/access.yaml), and [BOOTSTRAP.md](../../agent/protocol/BOOTSTRAP.md). Re-check the current default-branch commit, open PRs and ruleset before proposing changes.

## Three distinct records

| Record | Where | What it means |
|---|---|---|
| Research evidence | `agent/runs/<track>/<run_id>/` | Immutable submitted observations, procedures, provenance, limitations and proposed findings. A merged run does **not** certify its conclusions. |
| Promotion decision | `agent/promotions/` | Explicit, independently inspectable mapping from accepted evidence to conclusions selected for current documentation, including conflicts and evidence limits. |
| Current technical reference | `manual/reference/` | Subsystem-oriented living specification of the best-supported current understanding, citing promotion decisions and original evidence. |

Historical `ref/`, `scripts/`, and `snapshot/` remain accessible sources. Do **not** relocate, rewrite, or imply they are completely migrated. Keep navigation to them until individual content is reconciled.

## Procedure

1. **Discover:** Pin the accepted `main` SHA; inspect documentation indexes, relevant merged runs and open research/documentation PRs. Identify the exact subsystems and source baselines. Unmerged branches are candidate evidence only.
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

## Suggested cadence

- **Each substantive investigation:** publish immutable research through its own run/PR.
- **As needed:** fix broken navigation or demonstrably stale status with a narrow documentation PR.
- **At subsystem milestones:** create a promotion + canonical reference PR after sufficient evidence accumulates; do not force weekly promotion.
- **On contradiction:** preserve both source runs and either defer promotion or document a qualified conclusion and explicit open question.

See [research acceptance](RESEARCH_ACCEPTANCE.md) and [promotion-record guidance](../../agent/promotions/README.md). No shared lock server, new agent credentials or automatic merger is required for this manually supervised project.
