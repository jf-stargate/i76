# Research publication readiness

**Structural validator:** PR submission and immutable append-only run checks are active on `main` at the recorded configuration. Research record schema **v1.1.0 was accepted in [PR #9](https://github.com/jf-stargate/i76/pull/9)** and is the default for new substantive research under publication protocol v1.0.1. Historical v1.0.0 run records remain supported and immutable. The updated trusted validator processed a v1.1.0 `shared` run with a checksum-listed artifact successfully in [PR #11](https://github.com/jf-stargate/i76/pull/11) ([passing `integrity` job](https://github.com/jf-stargate/i76/actions/runs/39847085088/job/120063095001)); that test established structural compatibility, not the correctness of substantive reversing findings.

**Research confidence:** CI validates schemas and file integrity, not the truth of binary-reversing conclusions. Each substantive run should record original file hashes, precise Ghidra program/baseline digest, methods and reproducibility limits, source addresses, scripts, and proof status. Empty input/baseline arrays belong only to infrastructure `shared` runs.

**Promotion:** A reviewed and merged run is historical evidence; it does not automatically change `manual/reference/` or the annotated Ghidra baseline. Promotion requires a separate manual decision.

**Migration:** Existing `ref/`, `scripts/`, and `snapshot/` stay authoritative in their current locations pending individual evidence-provenance review. Recover missing full editor history reports from genuine archives before attempting to import them. Do not synthesize historical records.

**Canonical documentation updates:** For a repeatable finding-to-reference review, follow [DOCUMENTATION_WORKFLOW.md](DOCUMENTATION_WORKFLOW.md) and use the [promotion template](../../agent/promotions/TEMPLATE.md). Publish subsystem-level promotions as separate PRs, not as edits inside a research run.
