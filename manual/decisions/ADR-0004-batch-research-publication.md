# ADR-0004 — Looser merge freshness for supervised research runs

**Status:** Proposed for human acceptance; publication protocol 1.0.2  
**Date:** 2026-10-23  
**Depends on:** ADR-0003, [existing main ruleset 25664125](https://github.com/jf-stargate/i76/rules/25664125)

## Context and decision

By October 23, fifteen independent PRs (#19–#33) shared the same original `main` base. The live ruleset required `strict_required_status_checks_policy: true`, so merging one unrelated research run repeatedly invalidated the other PRs' up-to-date status. These research records typically add **unique immutable directories**, not chained changesets.

Propose switching the **existing** ruleset to `strict_required_status_checks_policy: false` while **retaining required successful `integrity` checks**, required PRs, resolved review conversations, zero approving reviews, prohibition of deletion and non-fast-forward, and no bypass actors. Do not grant agents merge authority.

An isolated run-only PR with a passing check for its unchanged exact head need not rebase after unrelated accepted research advances `main`; the human must still check current mergeability, file scope, head, validation, limitations and scientific claims before manual acceptance.

Canonical technical reference, promotion, baseline, shared-tool and governance PRs still require an **up-to-date manual reconciliation and fresh trusted check** against the current `main`. GitHub's loose ruleset is global; this stronger path-specific condition is a **human procedural gate, not a platform-enforced guard**. A passing check is not endorsement of conclusions.

## Risks, deployment and rollback

Loose checks may remain green after the accepted validator on `main` has changed, since the `pull_request_target` workflow need not rerun on every unrelated merge. This is an accepted tradeoff for isolated run-only append operations; significant validator/security changes should prompt rechecking those pending runs. GitHub will still prevent incompatible/conflicting merges; do not bypass conflict resolution.

First **merge the governance PR manually under strict rules**, then edit the existing ruleset's required-check “Require branches to be up to date” setting to OFF. Read back the live state, test one independent run-only merge without a redundant rebase and record it. The committed ruleset JSON alone changes nothing in live GitHub. If necessary, turn the setting back ON and submit a reviewed policy correction; never import a duplicate ruleset.

Existing 1.0.0 and 1.1.0 research records and hashes are unchanged. No batch bot, automatic merge, extra credentials or global lock service is introduced.
