# I76 publication enforcement — verified state

**As of 2026-10-22:** the repository has an active main-branch ruleset and a successful live run-integrity check. This is **partial verification**, not proof of credential-independent approval or of all negative permissions.

| Control | Evidence | Status |
|---|---|---|
| Repository branch protection | [GitHub ruleset 25664125](https://github.com/jf-stargate/i76/rules/25664125), applies to `refs/heads/main` | Active, confirmed via GitHub API |
| Pull request and code-owner review | Ruleset 25664125: one approval, code-owner review, stale-review dismissal and last-push approval | Configured; approval/merge not exercised |
| `integrity` required check | Ruleset 25664125 | Configured |
| Trusted candidate validation | [PR #5](https://github.com/jf-stargate/i76/pull/5) head `e87571a8927c21f428082eaf664968e017bddada`; [successful job](https://github.com/jf-stargate/i76/actions/runs/39835070763/job/120021112122) | Verified: 13 unit tests and a valid three-file run |
| Main branch unchanged by onboarding test | Commit `0aac01908270728f01258a98b56107073ab038d9` at time of check | Verified |
| Direct main push denied | Restricted credential negative test | Not tested |
| Invalid candidate rejected by live CI | Separate intentionally invalid PR | Test requested; record exact result after observing |
| Two concurrent runs from same base | Separate branch PRs | Test requested; record results after observing |
| Independent publisher/reviewer identity | Current connected account is `jf-stargate` | Not established; manual supervision accepted for this experiment |
| Promotion of authoritative research | Separate review and reconciliation | Not tested |

This file is a dated evidence record, not an automatically synchronized indicator. Subsequent agents **must inspect live rulesets and CI state** at startup and must not infer current enforcement solely from this document.

**Operational scope:** approximately ten or fewer manually supervised conversations, uniquely named per-run branches, no central lock server and no autonomous merges. Existing `ref/`, `scripts/`, and `snapshot/` trees remain in place. Passing `integrity` establishes structural integrity, not truth or publication approval.
