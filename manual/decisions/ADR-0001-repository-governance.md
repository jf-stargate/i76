# ADR-0001 — Repository knowledge split and concurrent-agent publication

**Status:** Accepted via PR #1; original independent-review conditions superseded by ADR-0003  
**Protocol version:** 1.0.0  
**Repository baseline:** `78168dfcefb146b1c7b95e5e7571100c8458d536`

## Context

Interstate '76 has multiple concurrent research tracks, multiple conversations using separate Ghidra working copies, a substantial source-of-truth reference tree, and accumulated versioned ZIP snapshots. The project needs durable research provenance without forcing agents to recover previous chat memory or granting every connected agent unilateral write access to accepted documentation.

## Proposed decision

- Two principal content namespaces, `manual/` and `agent/`, are separated at the repository root.
- Root `AGENTS.md` provides universal agent bootstrap; the current protected-default-branch `agent/protocol/access.yaml` is the machine-readable policy.
- Accepted `manual/` documentation is curated and points back to immutable machine-readable findings and evidence.
- Independent conversations own independent `agent/runs/<track>/<run_id>/` records and isolated branches. Branch creation is atomic; run IDs are UTC timestamp plus random hexadecimal suffix, not sequential milestones.
- Research topic overlap is allowed. GitHub PR merging arbitrates authoritative state; contradictory findings are preserved and reconciled during separate promotions.
- All changes require PRs; v1 permits **no autonomous merges**. Protocol, baselines, promotions, `.github/`, and manual canonical conclusions have specific maintainer approval requirements.
- Public Git contains only lawful, non-sensitive derived evidence and scripts; original binaries and annotated Ghidra databases are identified by immutable checksums and stored separately.
- Legacy `ref/`, `scripts/`, `snapshot/` remain accessible; no migration occurs in the governance bootstrap.

## Consequences

Benefits: source provenance survives chat resets; contributions are isolated and replayable; accidental last-writer-wins is avoided; cross-track runs share reference evidence without sharing mutable Ghidra state. Costs: more manifests, CI/review overhead, user approval for promotions, and need for independently verified GitHub branch rules. `AGENTS.md` alone does not force every AI system to read it or enforce permissions.

## Adoption criteria

Explicit maintainer approval of this ADR and access matrix, bootstrap commit, protected `main` rules, required trusted CI checks, reviewer identity separation, CODEOWNERS review, and a negative permission test of the agent's credentials. These were the original proposed conditions, **superseded for the small manual experiment by ADR-0003**. Consult the accepted policy and live ruleset for current requirements.