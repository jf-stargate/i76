# Verify or recover I76 main-branch protection

The active ruleset is already installed as [25664125](https://github.com/jf-stargate/i76/rules/25664125). The versioned `.github/config/main-ruleset.json` is a desired-state reference only. **Do not import it again**, which could create duplicate and conflicting rules.

For this small manually supervised experiment verify GitHub **Settings → Rules → Rulesets** reports:

- Branch ruleset active for `refs/heads/main`
- Pull requests required, **0 required approving reviews**
- Mandatory CODEOWNERS and last-push approval **off**
- Required review conversations resolved
- `integrity` required with **loose** up-to-date checks *after* v1.0.2 and the live ruleset edit; before that, GitHub still enforces strict checks
- Deletion and non-fast-forward updates blocked; no bypass actors

If this ruleset must be recreated, first verify a trusted GitHub Actions `integrity` check runs successfully; then create a replacement from the current reference JSON using administrative permissions. Update the dated enforcement record with the new ID and live test results. Merely committing a JSON file does not configure GitHub.

No additional account is required for manual maintainer review and merge. This intentionally does **not** provide independent credential separation for unattended agents.

## Switch existing ruleset to loose required checks (protocol 1.0.2)

**Do this only after the governance PR has been manually accepted and merged under the old strict checks.** Open the **existing** [ruleset 25664125](https://github.com/jf-stargate/i76/rules/25664125) in GitHub **Settings → Rules → Rulesets**. Keep the required `integrity` check enabled, but turn **off** “Require branches to be up to date before merging” (`strict_required_status_checks_policy: false`). Save the **existing** ruleset; never create a duplicate.

Read back the live ruleset. Confirm `integrity` still required, `strict_required_status_checks_policy: false`, pull requests required, review-thread resolution, zero formal approvals, and no deletion/non-fast-forward bypass. With one appropriately reviewed independent run-only PR, verify that a previously green unchanged head stays eligible after a different run advances `main`. Record this observation in a later acceptance-status PR. **The committed JSON is advisory; its change does not alter GitHub settings.**

This setting is global. For `manual/`, `agent/promotions/`, `agent/baselines/`, `agent/tools/`, governance and other shared/canonical modifications, human reviewers must refresh the candidate to current `main`, reconcile changes and run `integrity` again before merge. Loose checks cannot enforce that distinction on their own. If the risk is unacceptable, restore the original checkbox and reconcile the policy/ruleset copy via a new reviewed governance PR.
