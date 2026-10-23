# Canonical promotion records

A merged run captures immutable evidence, not an endorsed technical conclusion. Promote selected findings only via a separate human-reviewed PR that identifies:
- source run IDs and Git merge commits;
- stable finding IDs, exact address/function context, and evidence hashes;
- reason for accepting one interpretation, including superseded or contradictory findings;
- relevant retail executable and annotated Ghidra baselines;
- paths in `manual/reference/` and any Ghidra annotation scripts to update;
- residual uncertainty and affected tests.

Historical `ref/` material remains readable until the separately reviewed migration process is complete. Do not rewrite the original run to change a conclusion, and do not assign newly invented run IDs to imported historical reports.

For approximately ten supervised conversations, GitHub PRs and explicit reviewer decisions suffice; no shared lock file or background broker is required.

## Promotion workflow and template

Use [the documentation workflow](../../manual/roadmap/DOCUMENTATION_WORKFLOW.md) and start every proposed decision from [TEMPLATE.md](TEMPLATE.md). A candidate promotion can be prepared on a separate branch, but its conclusions are not accepted until the human maintainer merges its PR. Distinguish original-code emulation from full-game runtime verification and link each accepted technical paragraph to its evidence.
