# I76 publication enforcement status

**NOT ACTIVE:** merge guards have been proposed but are not yet authoritative or required.

- Protocol on main: commit 8885274be05f6570f8f12272fd86bd5cad16d5a7.
- GitHub main protected: false (last verified prior to this PR).
- Rulesets: none (last verified prior to this PR).
- Trusted CI workflow: introduced by proposed PR; must be merged and required in ruleset.
- Separate agent identity and independent maintainer reviewer: not established.
- Autonomous merge: prohibited by protocol v1.

## Required activation

1. Review and merge the trusted CI PR.
2. In GitHub Settings > Rules > Rulesets, create an Active branch ruleset for main requiring PR, an independent approving review, CODEOWNERS review, stale-approval dismissal, and required integrity status check; prohibit force push and deletion; constrain bypass.
3. Publish with agent credentials distinct from maintainer credentials; confirm direct main pushes and self-review fail.
4. Submit harmless test run PR and verify required CI checks exact head SHA. Intentionally submit a malformed test run separately to demonstrate rejection.
5. Record verified rule ID, date, reviewer identity, and negative-test PR links in reviewed documentation.

## CI boundary

Workflow uses a read-only pull_request_target token and executes only protected base code; it fetches candidate commit as Git objects, inspecting data without executing PR scripts. Static secrets/proprietary checks are limited and cannot replace review. A passing result is NOT merge authorization.
