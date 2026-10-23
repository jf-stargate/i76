# Small-team manual concurrency contract

Designed for approximately ten or fewer simultaneously active, manually supervised conversations. Do not introduce leases, an issue-based lock registry, separate coordination service, or automatic merge authority without an explicit scalability need.

1. Discover accepted `main` SHA and current open PRs before new work. Treat each open research PR as a potential overlap, not a lock.
2. Create a fresh `agent/<track>/<run_id>` branch from the captured SHA; every run owns its own immutable `agent/runs/<track>/<run_id>/` directory.
3. Other agents may research overlapping functions; do not reuse, force-push, mutate or merge another conversation's branch.
4. Every run records its original base SHA and scripts/binary/Ghidra provenance. As `main` advances, do not needlessly rebase an isolated, unchanged, green-checked run-only PR after unrelated merges; verify mergeability and exact head status before acceptance. Canonical, shared and governance proposals require current-base reconciliation and revalidation.
5. Conflicting findings remain separate; promote to `manual/reference/` or `agent/promotions/` only after deliberate human reconciliation.
6. Use GitHub open PRs to hand off interrupted work, and close abandoned test PRs with a reason. Historical numbering (`v21`, etc.) belongs to accepted milestones, never branch allocation.
7. Protocol governance and shared scripts require explicit review. No central mutable current-state file is required for ordinary work.
