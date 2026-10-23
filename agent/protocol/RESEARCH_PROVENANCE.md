# Research evidence format v1.1.0

This is an **additive record-schema revision**. The independently versioned publication protocol is **1.0.2** (existing records may retain their original protocol_version, including 1.0.1). Existing `manifest.json` and `findings.json` files declaring `schema_version: 1.0.0` remain valid and immutable, and continue to be checked with the original schemas. The new v1.1.0 schemas reside in `agent/protocol/schemas/v1.1.0/`.

## Research grade

Use `schema_version: "1.1.0"` for new substantive research runs. The run record requires:
- A pinned Git `base_commit`.
- `inputs[]` with actual retail/executable names and both MD5 and SHA-256. Never invent checksums. For `i76exe` and `i76edit`, at least one input is required.
- `baselines[]` with Ghidra version, program name, precise baseline identifier and digest. For those two tracks, at least one baseline is required. Store Ghidra database bytes privately; commit *only hashes/identities*.
- `artifacts[]` with relative run paths, content SHA-256, sizes and kind. CI verifies all blobs and rejects unlisted extras.
- `reproducibility` status, script references, methodology and limitations. If an exact environment cannot be provided, state `partial` or `unavailable` and explain why.
- `findings.json` with the same run ID, evidence references to addresses, scripts, immutable blobs or test results, confidence/status, limitations and optional relations. Proven or derived findings must have at least one cited evidence record; this does **not** prove their correctness.

Proprietary binaries and mutable Ghidra databases **must not** be committed to this public repository. Empty `inputs` and `baselines` are permitted only for `shared` infrastructure runs, where reproducibility may be unavailable.

Research run IDs are not milestones. Original historical reports imported from `ref/` must retain historical provenance and never acquire invented original run metadata.

## Verification and limitations

Schema verification detects structural consistency and valid content hashes; it cannot certify that user-supplied executable hashes actually match binaries that are not in Git, or that a stated baseline is available. Such verification is a separate, explicitly recorded reproducibility activity.

All repository changes remain PR-only, human-reviewed, with no autonomous merge. Earlier `1.0.0` schemas never change retroactively.
