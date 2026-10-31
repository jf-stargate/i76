# Documentation impact — independent M06 transform and polygon handoff

Run: i76exe-20261031T002156Z-133da9a8; track i76exe; base `3e10251444a117c8d9da053b6887245a2bc4dbcf`. Original PE/GZF/M06 identities are in the manifest. PR pending at artifact creation. No canonical changes in this run; no milestone or acceptance-gate amendment.

Candidate claims for a future TER/RND reference, after human review and separate promotion:

- **F1-transform:** original `00490EED → 004937C0 → 00494E20` transforms authentic M06 vertices with a declared proper controlled affine matrix. Exact source-to-float32 checks and original writer events demonstrate this bounded result. This advances #69's deliberate stop; it does not establish original camera compatibility.
- **F2-allocation:** untouched `00490590` returns null; original `0048F9B0` with supplied diagnostic heap backing creates usable cursor/table state. Keep missing runtime initialization separate from Ghidra's permissive null writes and from real OS/frame lifecycle.
- **F3-clip-bin:** original `00491A30/004922F0` create source-owned candidates. Zero clip interval rejects; explicit projection/depth fields allow original `0047BF00/0047B8C0` and original `0048FE10` to insert actual records. CRT memcpy is supplied only at its original external boundary. Independent source/projection/clip checks and retired bucket writes/final chains support acceptance at this bounded primitive boundary.
- **F4-material-limit:** B4 is an original literal distinct from TER classes. Original alternate selector `004923F0/00471F00` sees a null descriptor pair with texture initialization omitted; original `004924B0` header is observed. No texture, UV, palette or pixel provenance can be promoted.

Evidence for each claim: `artifacts/REPORT.md`, `evidence/results.json`, `evidence/instruction_anchors.tsv`, selected original events and versioned producer/verifier; their exact hashes are in the manifest and findings references. Confidence is high within original-instruction emulation with declared services; full retail frame/material/image remains unresolved.

Historical reconciliation target: `ref/level_format/i76_runtime_terrain_lod_reference.md`; future curated TER/RND section under `manual/reference/engine/` after steward review. No existing canonical texture assertion is inferred or contradicted. #69's pre-transform result is confirmed then extended; #70 provides interface context only. PRs #71/#72 were deliberately excluded and require a later independent comparison by the maintainer.

This is **not G-RND-05 closure**, RND-v1 completion, ratification of M-RND-06 as a new gate or reconstruction authorization. A designated steward may reconcile **merged** runs in a separate fresh-base promotion/reference PR. Only the human maintainer can accept it.
