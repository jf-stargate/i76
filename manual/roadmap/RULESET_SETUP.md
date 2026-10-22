# Applying main-branch protection

**Do not apply this ruleset before the trusted CI PR has been reviewed and merged and a first green integrity check is observable.** Otherwise the required check may be unavailable and merges may be blocked.

The proposed ruleset is `/.github/config/main-ruleset.json`. Its enforcement field is `active`; applying the file directly activates protection immediately. GitHub's authenticated admin permissions are required.

After CI is merged, verify that its GitHub Actions job publishes a check named `integrity` on the test-run PR. If GitHub uses a different actual check context, update the ruleset template before submitting it.

From a trusted maintainer machine with the GitHub CLI already authenticated as a repository admin:

```bash
gh api -X POST repos/jf-stargate/i76/rulesets --input .github/config/main-ruleset.json
gh api repos/jf-stargate/i76/rulesets
```

Verify it requires pull requests, code-owner approval, one independent approval, review dismissal for new pushes, strict integrity check, and prevents deletion/non-fast-forward. Never grant broad agent bypasses. GitHub CODEOWNERS and required review are not useful for separation if agents share the maintainer's identity: create distinct agent-publisher credentials or keep all publication manual.

Then exercise restricted-identity negative tests: direct push to main must fail, an unreviewed PR must not merge, a malformed candidate must fail `integrity`, and a governance change must require independent maintainer approval. Record actual rule ID and evidence links in `manual/roadmap/ENFORCEMENT_STATUS.md` through a reviewed PR.

**This file is a configuration proposal, not evidence that a ruleset is installed.**
