# ADR-0003 — Manual publication without mandatory independent GitHub review

**Status:** Proposed for maintainer acceptance (protocol 1.0.1)  
**Date:** 2026-10-22  
**Supersedes:** Independent reviewer/credential requirements from ADR-0001, ADR-0002 and protocol v1.0.0 bootstrap.

## Context

The I76 GitHub repository is an experimental research archive used by approximately ten or fewer manually supervised ChatGPT conversations, often publishing through the same `jf-stargate` identity. Original ruleset 25664125 required independent GitHub approval and blocked PR #8 after CI passed. The maintainer explicitly chose a single-account, human-supervised workflow instead of adding a second publishing identity.

## Decision

Maintain the active main-branch ruleset requiring pull requests, strict `integrity` CI, discussion resolution, and non-fast-forward/deletion protection, with **zero required GitHub approvals**, **no required CODEOWNERS review**, and **no last-push approval requirement**.

The human maintainer inspects changes and chooses whether to merge them. Agents may create their own branches and PRs but never merge autonomously, overwrite merged evidence or promote canonical research without an explicit human decision. Historical and conflicting evidence remains immutable until separate promotion.

Protocol 1.0.1 records this governance-only amendment. Research record schemas 1.0.0 and 1.1.0 and already accepted historical records are unchanged. The versioned ruleset JSON is not automatically applied by GitHub.

## Limitations

A green CI check establishes structural validation, not research correctness. Shared credentials do not supply independent identity-based authorization; that isolation and direct-main push rejection have not been empirically tested. Reconsider the workflow before introducing unattended agents or materially greater concurrency.
