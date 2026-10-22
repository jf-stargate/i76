# Manual publication enforcement — protocol v1.0.1

The versioned access policy is trusted only when read from a pinned accepted `main` SHA. The GitHub ruleset must be independently checked through Settings or the API. On 2026-10-22, ruleset [25664125](https://github.com/jf-stargate/i76/rules/25664125) was verified active for `main` with a required PR and strict `integrity` check, **zero formal approving reviews**, no mandatory CODEOWNERS or last-push approval, and no bypass actors.

## Operating contract

- Agents submit candidate branches and PRs; they never autonomously merge or directly update `main`.
- GitHub CI must pass for the exact candidate head on its current base; the human maintainer explicitly inspects and merges.
- Governance, canonical references, promotions and baselines need deliberate maintainer acceptance. A green CI check verifies format, not research truth.
- Existing merged runs are immutable; reject cross-run modification, force pushes, proprietary binaries and secrets.
- For fewer than roughly ten supervised conversations, no separate identity, lock service or automated publication broker is needed.

## Evidence

See [enforcement observations](../../manual/roadmap/ENFORCEMENT_STATUS.md). Passing and failing live CI test PRs have been recorded. Empirical direct-push rejection and real canonical technical promotion remain untested.

The committed `.github/config/main-ruleset.json` is a reference copy, not a GitHub configuration action. **Do not import it a second time** while the live ruleset exists.
