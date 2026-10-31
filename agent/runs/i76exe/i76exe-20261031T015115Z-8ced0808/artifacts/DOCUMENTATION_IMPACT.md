# Documentation impact — RND software raster output

## Research identity

- Run: `i76exe-20261031T015115Z-8ced0808`, track `i76exe`, base `f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019`.
- Original binary and annotated GZF identities: `manifest.json` and `evidence/provenance.json`.
- PR and merge: pending human review; no merge or promotion claimed.

## Disposition

Classification: **candidate update** after review, not an automatic canonical change. Likely target is `manual/reference/RND` material on the software raster boundary, subject to the documentation steward's selected path. Relevant accepted predecessors are PR #70/#73/#75; PR #76 supplies structural viewport context. No accepted artifact is rewritten.

## Evidence-linked candidate findings

- `F1-surface-contract`: original `00474C60/00474D32` writes a usable 13-DWORD descriptor when its `HeapAlloc` request receives bounded backing; `0047CB00` uses pitch, base and X/Y offsets at +00/+14/+1C/+20. Evidence: `evidence/raster_results.json`, `evidence/retail_raster_opcodes.json`, `evidence/controls.json`. **Proven for this invocation**, with supplied allocation and zero heap handle; no authentic retail device or ownership chronology.
- `F2-original-pixel-writes`: original `0047CB00` returns twice and writer `0047CC62` makes 210 bounded indexed stores from authenticated native spans. Evidence: `evidence/raster_results.json`, original opcode audit and standalone verifier. **Proven in diagnostic Ghidra emulation**, not authentic palette color or image fidelity.
- `F3-palette-gap`: original `004791E0` reaches imported float-to-integer at `000C0BFC` and stops; the positive uses a declared 8,192-byte diagnostic table. Evidence: `evidence/controls.json`, `artifacts/SERVICE_LEDGER.md`. **Proven blocker and supplied-table limit**; original palette source/init remains unresolved.
- `F4-controls`: behind camera and absent surface produce zero pixel writes; controlled X offset moves all 210 destinations; fresh GZF repeats byte-for-byte; three corruptions reject. Evidence: `evidence/raster_results.json`, `evidence/controls.json`, `scripts/verify_raster.py`. **Proven for bounded fixture**.

## Reconciliation and publication boundary

PR #75's pre-instruction callback boundary is extended, not contradicted. Its pending command+28 span is finalized at `0047CB2F` before pixel reads. The historical descriptor expression is confirmed with field meaning; the surface backing and shade table remain explicitly supplied. No maintained renderer, authentic color/material output or complete image is justified. The documentation steward may reconcile these candidate claims only from merged evidence in a separate promotion/reference PR after maintainer review. This run proposes no edit to `ref/`, `agent/promotions/` or `manual/reference/`.
