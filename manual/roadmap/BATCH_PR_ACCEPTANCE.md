# Manually accepting independent I76 research PRs in batches

**Prerequisites:** protocol 1.0.2 merged by the maintainer and **live** ruleset 25664125 changed to loose required `integrity` checks. Until both steps occur, strict freshness remains in force.

Independent research PRs are not normally stacked: each creates one fresh `agent/runs/<track>/<run_id>/` directory. Human acceptance is still **per PR**, but unrelated additions should no longer require rebasing every other run.

## Research-only review checklist

1. Confirm the PR is intended for acceptance: open drafts are not implicitly approved, and the maintainer may mark a particular draft ready only after reviewing it.
2. Check **Files changed**: only newly added files inside one owned run ID; no modifications to previously merged runs, governance files, scripts shared with other runs, canonical references, or another agent's branch.
3. Inspect provenance, verified executable and Ghidra identity, artifact integrity, methods, findings, evidence limitations, possible contradictions. `integrity` validates structure, **not research truth**.
4. Verify **current head SHA** is the one with a successful required `integrity` check, GitHub reports no merge conflict, and discussion threads are resolved. A changed head requires new CI. If the trusted validator/security model changed materially, request a fresh run even for unchanged heads.
5. Human maintainer deliberately merges one accepted PR, then rechecks the next PR. No automated or delegated merge rights are created.

## Canonical/shared exception

For `manual/`, `agent/promotions/`, `agent/baselines/`, `agent/tools/`, `agent/protocol/`, `.github/`, historic `ref/`, `scripts/`, `snapshot/`, or mixed-scope proposals: **refresh the branch to current `main`, rerun trusted validation, inspect the resulting diff and explicitly accept the exact conclusions or configuration change**. GitHub loose checks do not enforce this per-path exception.

The October 23 backlog contained ready PRs #19/#20, research drafts #21 and #24–#33, and documentation drafts #22/#23. This is *context, not blanket approval*. Review any ready research individually; review #22's documentation process before #23's separate technical promotion, each with fresh-base checks. Old and superseded runs remain immutable evidence; promotion is separate.

Never disable `integrity`, auto-merge drafts, force-push, or create a duplicate ruleset.
