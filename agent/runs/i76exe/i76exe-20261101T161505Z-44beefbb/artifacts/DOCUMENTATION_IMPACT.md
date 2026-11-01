# Documentation impact — TER semantic sampling pilot A

## Research identity

- Run: `i76exe-20261101T161505Z-44beefbb`, track `i76exe`, advisory subsystem TER.
- Original base: `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`, protocol 1.0.4. PR pending at record creation; no merge claimed.
- Binary/GZF identities: [manifest](../manifest.json) and [provenance](../evidence/provenance.json). Actual supplied GZF was imported into a disposable project and inspected.

## Disposition

**Candidate update**, with no canonical edits in this PR. Proposed separate reference: `manual/reference/engine/terrain_sampling.md`, plus a later TER discovery-index link. The designated steward should reconcile this run with accepted M06 #51, semantic v98/v99–v101 tools and renderer terrain work before promotion. Existing `manual/reference/engine/m06_visual_terrain.md` covers a different rendering milestone; this handoff does not broaden it to general terrain/collision proof.

Historical sources: `ref/level_format/i76_runtime_level_and_terrain_format_notes.md` terrain model and old transform-helper label; May preserved snapshots of `00493160`, `004931C0`, `00493550`; v49 historical rename script. Keep those records intact.

## Candidate findings

- **TER-A-layout**, derived/high: publish the minimum page/pointer model and +3072 coordinate offset, borrowed-page setup and FF default behavior. Original anchors A1–A7/A22 in [ORIGINAL_CODE.tsv](../evidence/ORIGINAL_CODE.tsv), original PE-range digests in [code_ranges.tsv](../evidence/code_ranges.tsv). No editor 0x8004 stride; no claim about default-page initialized contents. Clarify that 004931A4 is an interior load and 00493160 returns masked height12 despite its current alias.
- **TER-A-height-abi**, derived/high: preserve numeric ST0 return, floor-directed FISTP and float X-row intermediates. Anchors A8–A12 and [readability audit](READABILITY_AUDIT.md). Double is an ABI presentation, not recovered declaration/final rounding. Existing v99 float selection should be qualified, not described as an established final float store. Existing M06 hardware FISTP qualification remains mandatory; those runtime tests were not rerun here.
- **TER-A-normal-material**, derived/medium: document different rounded material and triangle-normal behavior, outside class5 versus invalid-index class0, normal fallback and caller buffer. Anchors A13–A21. Preserve literal unscaled world-minus-index triangle test and branch X-sign differences; do not replace them with a conventional derivative or claim broadly validated numerical correctness. CRT ftol implementation unavailable locally; ordinary truncation is a library-contract assumption.
- **TER-A-readability**, proven/high for this trial only: 19 guarded changes, unchanged dry-run capture, idempotent repeat and correct packed stack offsets, five unchanged original function bodies. [capture_checks.json](../evidence/capture_checks.json), [metrics](../evidence/readability_metrics.tsv), [symbol decisions](../evidence/SYMBOL_DECISIONS.tsv). The applied project remains private and disposable; no baseline promotion requested.

All linked evidence artifacts have SHA-256/byte entries in the manifest; findings contain direct artifact digests. New claims are static/derived; M06 corroboration remains original-instruction emulation under its separately documented substitutions. This run contributes no new mission execution or full collision result.

## Reconciliation and open questions

Confirms M06's bilinear height/material/normal distinction, runtime page stride, scaling and rounding caution. Narrows misleading historical helper labels and distinguishes source-declaration uncertainty from x87 ABI certainty. Further work may establish normal branch intent, imported CRT details, bit12 meaning or lifetime/default-page initialization, but none is necessary to review this bounded semantic pass. No change to vehicle suspension, renderer topology or polygon collision documentation is justified by this run.

The maintainer-designated steward may promote reviewed claims in a separate fresh-base PR after this run merges. This artifact does not modify `ref/`, existing runs, `manual/reference/`, protocol, shared tooling or promotions, and grants no merge authority.
