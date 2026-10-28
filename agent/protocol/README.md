# I76 multi-agent repository protocol v1.0.4

**Accepted on `main`; deployment partially verified.** Protocol instructions are normative after merge, while live GitHub enforcement requires independent verification. See [deployment record](../../manual/roadmap/ENFORCEMENT_STATUS.md).

Start at [AGENTS.md](../../AGENTS.md), read [access.yaml](access.yaml), then [BOOTSTRAP.md](BOOTSTRAP.md) from the same pinned `main` SHA.

- `manual/`: curated reference, decisions and status.
- `agent/runs/<track>/<run_id>/`: isolated, append-only evidence belonging to a single research run.
- `agent/tools/`: analysis tooling; `agent/baselines/` and `agent/promotions/`: candidate/accepted provenance and promotion records as populated.
- `ref/`: historical checkpoint, preserved rather than routinely rewritten. `scripts/`, `snapshot/`: still-active historical tools/evidence; consult before repeating analysis.
- **Documentation handoff:** new substantive research runs provide a documentation-impact artifact (procedural expectation, not separately CI-enforced); a designated repository/documentation steward generates reconciled `manual/reference/` updates and `agent/promotions/` evidence crosswalks through separate human-reviewed PRs. Start at [the documentation workflow](../../manual/roadmap/DOCUMENTATION_WORKFLOW.md).
- All v1 merges require a PR, passing `integrity` CI on the current head, and an explicit human maintainer merge decision. The proposed **loose** required-status policy avoids redundant rebases for unchanged isolated research runs; canonical, shared-tool, baseline, promotion and governance PRs still require a fresh-base human review and check. GitHub requires zero approving reviews; agents may not autonomously merge, directly update `main`, or change governing policy without maintainer acceptance.
- Multiple manually supervised conversations may overlap in subject matter, but cannot rewrite one another's runs. Git SHAs and PRs, not chat memory, anchor state.
- Ruleset 25664125 must be read live: the committed JSON is a reference and does **not** configure GitHub. Loose required-status checks were observed active on 2026-10-26; future agents must reverify. See [batch acceptance](../../manual/roadmap/BATCH_PR_ACCEPTANCE.md); credential separation remains deferred.

Research record schemas 1.0.0, 1.1.0 and 1.2.0 are supported. New records default to 1.2.0, which activates the independent i76shell publication track. The publication protocol has its own independent 1.0.4 version; historical records and active 1.1.0 investigators need no migration.

## Four publication tracks and evidence boundaries

`i76exe`, `i76edit`, `i76shell` and `shared` identify original binary/publication targets. The shell DLL requires `shell-dll` input provenance and a Ghidra baseline under research schema `1.2.0`. Current engine functional subsystem assignments are advisory and orthogonal to these tracks. Future accepted subsystem discovery indexes can be followed as reference links during bootstrap without modifying run manifests or run-ID syntax.

Experimental emulators, stubs, synthetic intercepted services, models, decoders and differential/regression harnesses remain permitted research tools. A research script or executable algorithm is not by itself maintained reconstruction. Promotion and independently maintained reconstruction require separate human-reviewed authorization. Never backfill historical shell investigations as fabricated runs.

**CI trust boundary:** `pull_request_target` executes the `main` base-commit validator, not a PR's modified validator. Thus the governance PR introducing `1.2.0` can pass current trusted integrity checks without those checks exercising candidate `1.2.0` support. Review the new validators and independently run their unit tests before maintainer acceptance; after acceptance they become trusted for later shell research PRs.
