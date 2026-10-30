# Documentation impact — M-RND-04 kind-6 polygon preparation

## Research identity
- Run ID: `i76exe-20261030T125716Z-1011d511`
- Track: `i76exe`
- Original base commit: `3e10251444a117c8d9da053b6887245a2bc4dbcf`
- PR: pending
- Binary and Ghidra identities: see `manifest.json`; licensed inputs and Ghidra project remain private.

## Documentation disposition
- Classification: candidate update
- Target: `manual/roadmap/subsystems/RND.md`, `manual/roadmap/subsystems/RND_ACCEPTANCE.md`, and milestone M-RND-04 at `manual/roadmap/RND_SUBSYSTEM_MILESTONES.md`.
- Historical references: the original renderer and geometry-traversal evidence linked by the RND index, including the mode-`0x15` callback evidence.
- Suggested milestone: M-RND-04; no broader rendering milestone closure implied.

## Evidence-linked candidate findings
- `F1-original-kind6-projected-output`: On two source-backed four-vertex vehicle polygons in the PR #70 continuous state, native retail `0047C8D0` transforms the view and source vertices into four output records, changes the destination, preserves source bytes, and returns 4. Evidence: `evidence/positive.tsv`, `evidence/retail_instructions.tsv`, `scripts/I76_IntegratedClipProbe.java`, and `scripts/verify_clipping.py`. Status/confidence: proven/high for Ghidra-emulated instructions and bounded output semantics. Impact: add/narrow. Limits: controlled context; no actual clipping-plane intersection, draw, framebuffer or pixels.
- `F2-dispatch-mode-reconciliation`: mode `0x101` selects `0047C8D0/0047CE40`; kind-10 mode `0x80` selects `0047BF00/0047D110`; older mode `0x15` selects `0047C2F0/00487EA0`. Evidence: exact retail listing and wrapper trace. Status/confidence: proven/high for these observed dispatches. Impact: correct/narrow earlier generic callback descriptions.
- `F3-behind-negative`: the distinct behind-view case reaches no polygon wrapper or kind-6 callback. Evidence: `evidence/negative.tsv` and verifier. Status/confidence: proven/high for the controlled case. Impact: none outside the test condition.

## Reconciliation notes
PR #70 established the integrated path while substituting clip and draw. This run replaces only the kind-6 callback body; kind 10 and drawing remain substituted. Earlier mode `0x15` evidence is a different dispatch-table entry rather than contradictory target identity. Do not promote a claim of native polygon clipping intersections or raster output from this result.

## Publication boundary
This is a research handoff only; it changes no canonical documentation, promotion or historical reference. Maintainer review is required before documentation changes.
