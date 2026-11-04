# Documentation impact — ACT/LUM/TBL color pipeline

## Research identity

Run i76exe-20261104T224244Z-4359bae0; track i76exe; base e7b97c95a21be3657a4f6d3cb993323aa66bde7d. Exact binary/GZF/archive identities and artifact hashes/lengths are in manifest.json. PR pending; human acceptance required.

## Disposition

Candidate update and narrowing of historical material/extraction assumptions. **No canonical change** in this run. Suggested future target: manual/reference/engine/color_pipeline.md linked from resource_acquisition.md, reconciled with accepted WRLD, HZD and PIX/PAK runs. Preserve existing resource-acquisition ordering/lifetime cautions. Historical input: ref/material_format/i76_material_extraction_reference.md, palette/LUM/TBL and alpha sections.

## Evidence-linked candidates

- color.callbacks: five descriptors select four callbacks at0048DC60/00475A30/0042DBE0/004345B0, installed through the context copy00402EBA; correction timing differs. PALETTE_CALLBACKS.md, descriptors_constants.json, reviewed_instructions.json. Proven binary-static, high confidence within identified descriptors; no external-code closure.
- color.act: RGB8 through palette/mask consumers; correction LUT and reserved output indexes; retain separate DIB channel-order discrepancy. ACT_FORMAT_AND_CONVERSION.md, original004797F0/0042D800/00476DB0. Proven/derived arithmetic with explicit imported-CRT precision limits. Narrow “auto” scaling and color-key assumptions; do not promote exact gamma outputs.
- color.lum: supplied copy0061B2A0, source low-byte/shade-row axes, runtime column update00478B80, null-generation structure and first-query nearest cache. LUM_SEMANTICS.md and formulas.json; original004791E0/004796A0 and span samples. Proven static contracts, high confidence; null generator remains unsupported by executable model.
- color.tbl: source-high/destination-low composition, identity source255 row, temporary destination255 column modifications. TBL_SEMANTICS.md, references and reviewed original instructions00479780/0047AA50/00483CC0/00484630. Proven binary-static, high confidence; no fixed-alpha/visual equivalence.
- color.corpus:80 missions,37/18/18 ACT/LUM/TBL names;36/18/18 resolved distinct payloads; missing t013_16.act remains unresolved. COLOR_RESOURCE_CORPUS.md, corpus.json. Authenticated within one base-game archive and available loose roots; no Nitro Pack/history generalization.

Each claim's linked evidence hash is recorded in findings.json and all artifact digests in manifest.json. scripts/color_model.py and test_color_model.py demonstrate bounded integer/copy contracts and counterexamples; they are research code, not maintained reconstruction. Missing computations/consumer limits are in RECONSTRUCTION_HANDOFF.md.

A designated steward should reconcile merged evidence and request separate human acceptance for any future promotion/reference PR. No shared tools, prior runs, original payloads, Ghidra annotations, reconstruction code, ref/, governance, manual/ or agent/promotions/ are changed here.
