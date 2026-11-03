# Documentation-impact handoff

No canonical change in this research-run PR. No baseline promotion, modification of PR #106, or mutation of merged evidence. Separate shared-tooling proposal contains the standalone data migration. Human maintainer acceptance remains required.

Candidate claims and evidence:

1. **V99-AUDIT-state:** measured exact v99 identity and mixed migration coverage; BASELINE_AUDIT.md, migration_coverage.tsv, baseline_inventory_summary.json, selected_functions.tsv and capture_validation.json. This supports replacing #106's "not audited" caveat with a link to this audit only after research acceptance. It does **not** support saying v99 contains v100–v102: those 56 operations are absent. Five consolidation qualification comments are partial; provenance of execution remains unknown.
2. **TER-SPACING-float:** 006442C0 holds float bits; writers/readers and 006442C4 reciprocal traced. TERRAIN_AUDIT.md and spacing_references.tsv. Candidate revision to proposed manual/reference/engine/terrain_sampling.md and its pending promotion record: distinguish the int type in the exact input from the validated float correction in a disposable derivative. Preserve original x87/ownership qualifications.
3. **TER-AUD-literal:** 004ED7EC is the string `aud` plus NUL, not a semantically meaningful interior terrain pointer. Ten caller sites across six audio functions confirm address passing. TERRAIN_AUDIT.md, selected_functions.tsv and readability_digests.tsv. This corrects the interpretation in semantic-consolidation/CONFLICTS.md without editing that accepted report. A future promotion can cite both and explicitly supersede only the interior-pointer explanation.
4. **TER-ABI-retain:** 004931C0 already uses explicit +4/+8/+16 and EAX alias return; 00493550 already has two doubles and numeric ST0. Keep both unchanged. Original declared precision, exact normal intent and bit12 remain unresolved.

Recommended revisions for the **pending #106 promotion record**, reported here only: add this measured input identity/inventory and operation crosswalk; retain v100–v102 coverage gaps; cite the separate proposed storage migration and its test limits; replace the accidental-interior-pointer explanation; change spacing conflict wording only conditionally on maintainer acceptance/application. The existing #106 source findings and documentation proposals are neither overwritten nor duplicated.

Acceptance boundary: research-run evidence is not canonical authority; shared-tooling and baseline changes need explicit maintainer decision. No new mission VM or resource behavior is promoted. Next investigation: a separate mission VM semantic/readability audit with live-versus-import phase boundaries retained, after terrain review.
