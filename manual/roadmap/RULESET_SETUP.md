# Verify or recover I76 main-branch protection

The active ruleset is already installed as [25664125](https://github.com/jf-stargate/i76/rules/25664125). The versioned `.github/config/main-ruleset.json` is a desired-state reference only. **Do not import it again**, which could create duplicate and conflicting rules.

For this small manually supervised experiment verify GitHub **Settings → Rules → Rulesets** reports:

- Branch ruleset active for `refs/heads/main`
- Pull requests required, **0 required approving reviews**
- Mandatory CODEOWNERS and last-push approval **off**
- Required review conversations resolved
- `integrity` required with strict up-to-date checks
- Deletion and non-fast-forward updates blocked; no bypass actors

If this ruleset must be recreated, first verify a trusted GitHub Actions `integrity` check runs successfully; then create a replacement from the current reference JSON using administrative permissions. Update the dated enforcement record with the new ID and live test results. Merely committing a JSON file does not configure GitHub.

No additional account is required for manual maintainer review and merge. This intentionally does **not** provide independent credential separation for unattended agents.
