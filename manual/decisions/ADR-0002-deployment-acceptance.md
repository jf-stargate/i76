# ADR-0002 — Manual supervision and deployment verification

**Status:** Proposed for maintainer approval with this PR
**Date:** 2026-10-22

The I76 multi-agent repository is an experiment run through a small number (normally no more than ten) of manually supervised ChatGPT conversations. Shared GitHub credentials are an explicitly accepted **experimental limitation**, not evidence of independent reviewer identities.

The live `main` ruleset 25664125 is active and requires PR, review, code-owner approval and a successful `integrity` status. PR #5 proved a valid independent run can be submitted and validated, but its draft/blocked merge state does not isolate which review restriction enforced the block. Separate identity and negative direct-push permission tests remain deferred.

Keep versioned accepted runs immutable, operate on isolated branches, use the existing issue/PR interface for coordination rather than a lock service, and explicitly supervise all merges. No automatic canonical promotion. A future operational redesign is warranted only when concurrency or workload justifies it.
