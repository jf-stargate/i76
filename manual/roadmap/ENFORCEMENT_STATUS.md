# I76 publication enforcement — dated verification

**Verified 2026-10-22:** GitHub ruleset [25664125](https://github.com/jf-stargate/i76/rules/25664125) is active for `refs/heads/main`. It requires PRs, strict successful `integrity` CI, and resolved review conversations. It requires **zero formal approving reviews**, no mandatory code-owner/last-push approval, and disallows deletion and non-fast-forward updates. GitHub reports no bypass actors.

| Test or control | Evidence | Result |
|---|---|---|
| Ruleset configured | [Ruleset 25664125](https://github.com/jf-stargate/i76/rules/25664125) | Active and protecting `main` |
| CI required on main | Exact `integrity` context, strict check | Configured |
| Independent approving review | `required_approving_review_count: 0` | Not required, by design |
| Valid cold-start run | [PR #5](https://github.com/jf-stargate/i76/pull/5), [passing job](https://github.com/jf-stargate/i76/actions/runs/39835070763/job/120021112122) | Passed |
| Concurrent second run | [PR #7](https://github.com/jf-stargate/i76/pull/7), based on same starting main as #5 | Passed independently |
| Bad branch ownership | [PR #6](https://github.com/jf-stargate/i76/pull/6) | Live CI rejected |
| Missing manifest track | [PR #10](https://github.com/jf-stargate/i76/pull/10) | Live CI rejected |
| Manual merge under zero-approval ruleset | [PR #8](https://github.com/jf-stargate/i76/pull/8), [PR #9](https://github.com/jf-stargate/i76/pull/9) | Merged by maintainer |
| Research record schema v1.1.0 | [PR #11](https://github.com/jf-stargate/i76/pull/11), [passing job](https://github.com/jf-stargate/i76/actions/runs/39847085088/job/120063095001) | Passed for checksum-backed shared run |
| Denied direct push | Restricted-credential attempt | Not tested |
| Promotion of real reversing findings | Separate technical reconciliation | Not tested |

**Operational contract:** no more than roughly ten manually supervised conversations, isolated run branches, immutable merged evidence, required CI, explicit human merges, no central locks and no autonomous publication. A single GitHub account may publish and accept changes; independent credential separation is not part of this experiment.

This is a dated evidence ledger, **not live GitHub state**. Every new conversation must read current accepted policy at pinned main SHA, inspect actual rulesets and checks, and distinguish a passing format validator from evidence quality.
