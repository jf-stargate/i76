# Non-destructive migration plan

Phase 0: Draft this protocol on an isolated PR; do not move existing data.
Phase 1: Reviewed bootstrap adoption; then verify branch rules, CODEOWNERS and trusted checks.
Phase 2: Import original research reports and reproducible evidence with provenance; never fabricate historical run IDs.
Phase 3: Curate `manual/reference`, `manual/roadmap`, and history from `ref/`; preserve compatibility links.
Phase 4: Gradually move `scripts/` to `agent/tools/` and represent external baseline bytes through content checksums in `agent/baselines/`.
Each phase requires a separate reviewed PR and validation. Never force-migrate `ref/`, `scripts/` or `snapshot/` in the bootstrap commit.
