# I76 multi-agent repository protocol v1.0.0

**Accepted on `main`; deployment partially verified.** Protocol instructions are normative after merge, while live GitHub enforcement requires independent verification. See [deployment record](../../manual/roadmap/ENFORCEMENT_STATUS.md).

Start at [AGENTS.md](../../AGENTS.md), read [access.yaml](access.yaml), then [BOOTSTRAP.md](BOOTSTRAP.md) from the same pinned `main` SHA.

- `manual/`: curated reference, decisions and status.
- `agent/runs/<track>/<run_id>/`: isolated, append-only evidence belonging to a single research run.
- `agent/tools/`: analysis tooling; `agent/baselines/` and `agent/promotions/`: candidate/accepted provenance and promotion records as populated.
- `ref/`, `scripts/`, `snapshot/`: still-active historical reference trees; consult before repeating analysis.
- All v1 merges require PR review. No agent may directly update `main`, merge its own work, or change governing policy without approval.
- Multiple manually supervised conversations may overlap in subject matter, but cannot rewrite one another's runs. Git SHAs and PRs, not chat memory, anchor state.
- Ruleset 25664125 is currently recorded as active and requires an `integrity` check; the separate-credential negative access test remains incomplete.

The original research schema version is 1.0.0. A later, separately reviewed extension may add versions without rewriting historical records.
