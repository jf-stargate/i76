# Separate shared-tooling proposal

Standalone migration and disposable-only fixture: **[PR #107](https://github.com/jf-stargate/i76/pull/107)**, head **be7c7fcfdd30df2809694c173da96e7410da0078**, base **9576fc573964bed624a08d878886ccad40a63d7a**. Files live under agent/tools/ghidra/terrain-storage/ on that proposal branch. The production script requires no companion.

This research-run PR owns only its new run directory. Shared tools are deliberately not copied into the run as an alternative publication route. Retrieve PR #107's exact commit; compare production SHA-256 with VALIDATION.md and tooling_identity.json. The tested source matches the proposed source byte for byte.

Local trusted-base pr_integrity.py accepted the four shared-tool files as review-required. GitHub trusted integrity and mergeability must be checked for the exact head before human acceptance. This record does not claim merge or promotion. Both proposals remain unmerged, and #106 is untouched.
