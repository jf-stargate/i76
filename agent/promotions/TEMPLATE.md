# Promotion: <subsystem and precise milestone>

**Status:** Candidate — not accepted until explicitly merged by the human maintainer  
**Date:** <YYYY-MM-DD>  
**Original accepted base commit:** <40-character main SHA>  
**Research tracks:** <i76exe / i76edit / shared>  
**Target documentation:** <manual/reference/...>  
**Publication:** <promotion PR number, if known>

> Copy this file into a new named promotion record under `agent/promotions/`. Remove instructional placeholders. Do not modify the template when adding a promotion.

## Scope and decision proposed

Briefly state which conclusions are proposed as current reference, and **which observations are not being promoted**. Distinguish scope (static assembly / original-code emulation / retail run) and assumptions.

## Source evidence and provenance

| Research run (immutable path) | Merge PR + merge SHA | Finding ID | Address(es) / source evidence | Artifact path + SHA-256 | Evidence class / limitations |
|---|---|---|---|---|---|
| `agent/runs/<track>/<run_id>/` | PR # / full SHA | <stable finding id> | <original VA(s)> | <path> / <digest> | <native-static / original-instruction emulation / corpus / derived> |

Original retail executable name and MD5/SHA-256: <verified hashes; never invent>  
Ghidra version, program name, baseline identifier and SHA-256: <verified details, or explicitly unavailable>  
Relevant historical documentation: <links to ref/, snapshot/, scripts/>  
Open research PRs considered but **not accepted**: <PR numbers or none>

## Reconciliation of claims

| Selected conclusion | Status/confidence and bounded evidence | Prior reference or competing finding | Disposition |
|---|---|---|---|
| <precise claim> | <support + limitations> | <path / finding ID / unresolved> | <confirm / narrow / correct / supersede / defer> |

Document what has changed, why the new conclusion is stronger (or only different), and any unresolved disagreement. Never erase or rewrite old run records.

## Proposed reference changes

- `manual/reference/<subsystem>.md`: <sections/addresses/links>
- `manual/reference/README.md`: <navigation adjustment, if necessary>
- Ghidra annotation changes: <none, or separate explicitly reviewed proposal>

## Reproduction and unresolved risks

State what has *actually been replayed or cross-checked*, what depends on private fixtures/stubs, what remains inferred and which downstream tests/experiments remain open. A passing PR integrity check is **not** a scientific acceptance test.

## Acceptance checklist

- [ ] All cited research runs are merged and have immutable Git identifiers.
- [ ] Claims have precise evidence pointers (paths, findings, VAs and hashes).
- [ ] Historical documentation and any contradictory runs have been evaluated.
- [ ] Claims do not exceed the demonstrated execution or input scope.
- [ ] Exact target reference and index changes are reviewed.
- [ ] No proprietary bytes or private assets are committed.
- [ ] Trusted `integrity` check is green against current `main`.
- [ ] Human maintainer explicitly decides whether to merge this promotion.

**Decision:** Pending human review; the act of writing this record does not promote a finding.
