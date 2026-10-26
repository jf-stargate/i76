# Documentation impact — <subsystem / concise topic>

> Template for an artifact within a **new substantive research run**:
> `agent/runs/<track>/<run_id>/artifacts/DOCUMENTATION_IMPACT.md`.
> Record its SHA-256 and byte length in the run's `manifest.json` `artifacts[]`.
> This is a research handoff, **not** a promotion or canonical specification.
> Omit private executable/Ghidra payloads and credentials.

## Research identity
- Run ID: `<run_id>`
- Track: `i76exe | i76edit | shared`
- Original `base_commit`: `<40-hex-SHA>`
- PR / merge commit (if known): `<link or pending>`
- Original binary and annotated Ghidra identities: `<manifest references; no invented hashes>`

## Documentation disposition
- Classification: `candidate update | confirms current text | contradicts current text | no canonical change | unresolved`
- Target `manual/reference/` subsystem(s): `<paths or proposed paths; none if not applicable>`
- Relevant historical `ref/` source(s): `<paths and precise sections, if any>`
- Suggested milestone or dependency: `<accepted runs/findings needed or none>`

## Evidence-linked candidate findings
For every candidate statement, record:
- Finding ID and claim: `<findings.json ID and narrowly scoped wording>`
- Evidence: `<run-relative artifact path, hash, function/VA/offset, method>`
- Status/confidence: `<proven | derived | inferred | unresolved; stated confidence>`
- Documentation impact: `<add | narrow | correct | supersede | defer | none>`
- Reproduction limits and contrary evidence: `<explicit limitations or unknowns>`

## Reconciliation notes
- Agreements or contradictions with existing documentation and other accepted runs: `<links>`
- Questions requiring further original-binary validation: `<details or none>`
- If no change is justified: explain why here. A handoff is still useful.

## Publication boundary
This artifact proposes no edits to `ref/`, `agent/promotions/`, or `manual/reference/`.
A designated documentation steward reviews **merged** runs at a maintainer-requested milestone and creates any separate evidence-backed promotion/reference PR. Only the human maintainer can accept that PR.
