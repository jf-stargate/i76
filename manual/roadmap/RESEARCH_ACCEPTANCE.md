# Research publication readiness

**Structural validator:** PR submission and immutable append-only run checks are active on `main` at the recorded configuration. `agent/protocol/schemas/v1.1.0/` is a proposed additive research-grade schema until its PR has been reviewed and merged.

**Research confidence:** CI validates schemas and file integrity, not the truth of binary-reversing conclusions. Each substantive run should record original file hashes, precise Ghidra program/baseline digest, methods and reproducibility limits, source addresses, scripts, and proof status. Empty input/baseline arrays belong only to infrastructure `shared` runs.

**Promotion:** A reviewed and merged run is historical evidence; it does not automatically change `manual/reference/` or the annotated Ghidra baseline. Promotion requires a separate manual decision.

**Migration:** Existing `ref/`, `scripts/`, and `snapshot/` stay authoritative in their current locations pending individual evidence-provenance review. Recover missing full editor history reports from genuine archives before attempting to import them. Do not synthesize historical records.
