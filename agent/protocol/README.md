# I76 multi-agent repository protocol v1.0.1

**Accepted on `main`; deployment partially verified.** Protocol instructions are normative after merge, while live GitHub enforcement requires independent verification. See [deployment record](../../manual/roadmap/ENFORCEMENT_STATUS.md).

Start at [AGENTS.md](../../AGENTS.md), read [access.yaml](access.yaml), then [BOOTSTRAP.md](BOOTSTRAP.md) from the same pinned `main` SHA.

- `manual/`: curated reference, decisions and status.
- `agent/runs/<track>/<run_id>/`: isolated, append-only evidence belonging to a single research run.
- `agent/tools/`: analysis tooling; `agent/baselines/` and `agent/promotions/`: candidate/accepted provenance and promotion records as populated.
- `ref/`, `scripts/`, `snapshot/`: still-active historical reference trees; consult before repeating analysis.
- All v1 merges require a PR, passing `integrity` CI, and an explicit human maintainer merge decision. GitHub requires zero approving reviews; agents may not autonomously merge, directly update `main`, or change governing policy without maintainer acceptance.
- Multiple manually supervised conversations may overlap in subject matter, but cannot rewrite one another's runs. Git SHAs and PRs, not chat memory, anchor state.
- Ruleset 25664125 is currently recorded as active and requires an `integrity` check; credential separation is deliberately deferred during the manual experiment.

Research record schemas 1.0.0 and 1.1.0 are both supported. The publication protocol has its own independent 1.0.1 version; historical research records are not rewritten.
