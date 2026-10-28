# Research evidence format v1.2.0

This is an **additive record-schema revision**. The independently versioned publication protocol is **1.0.4** (existing records may retain their original protocol_version, including 1.0.1). Existing `manifest.json` and `findings.json` files declaring `schema_version: 1.0.0` remain valid and immutable, and continue to be checked with the original schemas. The original v1.1.0 schemas remain unchanged in `agent/protocol/schemas/v1.1.0/`; the new v1.2.0 schemas reside in `agent/protocol/schemas/v1.2.0/`.

## Research grade

Prefer `schema_version: "1.2.0"` for new substantive research runs; valid existing `1.1.0` runs remain publishable without migration. The run record requires:
- A pinned Git `base_commit`.
- `inputs[]` with actual retail/executable names and both MD5 and SHA-256. Never invent checksums. For `i76exe` and `i76edit`, at least one input is required; `i76shell` requires an explicit `shell-dll` input with measured hashes.
- `baselines[]` with Ghidra version, program name, precise baseline identifier and digest. For those three binary tracks, at least one baseline is required. Store Ghidra database bytes privately; commit *only hashes/identities*.
- `artifacts[]` with relative run paths, content SHA-256, sizes and kind. CI verifies all blobs and rejects unlisted extras.
- `reproducibility` status, script references, methodology and limitations. If an exact environment cannot be provided, state `partial` or `unavailable` and explain why.
- `findings.json` with the same run ID, evidence references to addresses, scripts, immutable blobs or test results, confidence/status, limitations and optional relations. Proven or derived findings must have at least one cited evidence record; this does **not** prove their correctness.

Proprietary binaries and mutable Ghidra databases **must not** be committed to this public repository. Empty `inputs` and `baselines` are permitted only for `shared` infrastructure runs, where reproducibility may be unavailable.

Research run IDs are not milestones. Original historical reports imported from `ref/` must retain historical provenance and never acquire invented original run metadata.

## Verification and limitations

Schema verification detects structural consistency and valid content hashes; it cannot certify that user-supplied executable hashes actually match binaries that are not in Git, or that a stated baseline is available. Such verification is a separate, explicitly recorded reproducibility activity.

All repository changes remain PR-only, human-reviewed, with no autonomous merge. Earlier `1.0.0` schemas never change retroactively.

## Documentation-impact handoff (new substantive research)

For new substantive research runs, produce an `artifacts/DOCUMENTATION_IMPACT.md` handoff using [the template](templates/DOCUMENTATION_IMPACT.md). Include this file in the run's `manifest.json` `artifacts[]` with its SHA-256 and byte count, as with any other artifact. Summarize findings relevant to current `manual/reference/`, historical `ref/` claims, target subsystems, source addresses, contradictory evidence and blockers to promotion. If nothing should change, explicitly record "no canonical change". This handoff is **procedural, not yet a separate CI-enforced schema requirement**, and older immutable runs must not be retroactively modified.

Research PRs carry evidence, not canonical edits. The designated documentation steward reconciles **merged** evidence at milestones via separate promotion and reference PRs; only a human maintainer accepts them. See [documentation workflow](../../manual/roadmap/DOCUMENTATION_WORKFLOW.md).

## Schema 1.2.0 and shell-specific identity

`1.2.0` extends `1.1.0` without changing earlier schemas: track/run prefix `i76shell`, findings scope `shell`, executable input kind `shell-dll`, and mandatory nonempty `baselines` plus an `inputs` entry of kind `shell-dll` for shell runs. Existing required fields identify each source by name, MD5 and SHA-256 and each baseline by Ghidra version, program name, immutable baseline ID and SHA-256. Shell assertions should cite the appropriate shell binary/snapshot explicitly, not claim that the `i76exe` baseline covers a separate DLL. Validators can check digest syntax and schema shape but cannot authenticate privately stored binaries or Ghidra projects.

Research scripts can implement original-instruction execution, substituted external services, independent experimental algorithms, decoders and comparators; their presence does not promote the code to maintained reconstruction. The authority chain remains immutable run evidence, separately reviewed promotions, then curated behavioral specifications. Active `1.1.0` Codex research need not migrate; no synthetic run is created from historical `snapshot/i76shell.dll/` or `ref/` sources.
