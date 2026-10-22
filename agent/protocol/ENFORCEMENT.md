# Enforcement deployment and verification

**Repository bootstrap does not create effective GitHub permissions.** As of the drafting session, the GitHub connector could not verify branch protection; enforcement status is UNKNOWN.

Before any agent may claim enforced publication policy:
1. Configure main-branch rules requiring PRs, forbidding force pushes/deletion and limiting bypasses.
2. Use an agent publishing identity distinct from the maintainer identity; an administrator token used by an agent does not count as independent review.
3. Require CODEOWNERS approval for `manual/`, `agent/protocol/`, `agent/baselines/`, `agent/promotions/`, `.github/`, and `AGENTS.md`.
4. Require trusted validation from the protected base SHA, not validator code supplied only by an untrusted PR.
5. Disallow edits/deletion of accepted research runs and direct main updates.
6. Dismiss stale approvals and rerun checks when the PR changes or the base advances.
7. Test negative permissions explicitly with agent credentials: direct push must fail, and governance changes must not merge without an independent maintainer.
8. Record verified ruleset identifiers, date, accepted maintainer decision and test evidence in a separate reviewed deployment record.

Until all checks are confirmed: proposal-only, no autonomous merges.
