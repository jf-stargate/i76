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
