# Documentation impact — ZFS logical resources and registered sources

Run: i76exe-20261104T224258Z-8e34c41d; track:i76exe; base:e7b97c95a21be3657a4f6d3cb993323aa66bde7d; research-only PR pending at artifact creation. Executable/GZF/archive identities are in manifest.json and evidence/provenance.json. This is a candidate update, with **no canonical change in this PR**.

Candidate target: manual/reference/engine/resource_acquisition.md, and a future ZFS-format reference reconciled by the designated documentation steward. Historical comparison sources: ref/zfs/i76_zfs_structure_and_extraction_reference.md and ref/game/i76_resource_acquisition_reference.md. Accepted PIX/PAK i76exe-20261104T195642Z-eaccd134, HZD i76exe-20261104T195732Z-147b7e3c and WRLD i76exe-20261104T183156Z-085a5e76 provide dependency context; none is edited or promoted here.

| Finding | Candidate claim / disposition | Evidence |
|---|---|---|
| ZFS-001 | Add exact28/3604/36-byte layouts, sentinel/tombstone rules, signed packed sizes and floor(count/100)+1 table expectation | ZFSF_FORMAT.md, fields.json; original004B9800/004B9B40 |
| ZFS-002 | Confirm mode 2 X/mode 4 Y using distinctive instructions; add both-bit priority, unused output-capacity argument, unchecked actual length and postdecode XOR | ZFSF_DECOMPRESSION.md; original004B9BD0/004B9FC0/004BAA00/004BABD8 |
| ZFS-003 | Close inherited base-game wrapper dependency:6,116 complete decodes/extracted matches, no directory or payload discrepancies | ZFSF_CORPUS.md, evidence/corpus.json, canonical inventory digest |
| RES-001 | Expand registered membership, A/M/C media selection, configured addon/archive/mission ordering and no failed-read source retry | RESOURCE_SOURCE_SELECTION.md, evidence/zix.json, source_model.py; original004B23E0/004B2E00/004B3030/004B3310 |
| RES-002 | Correct baseline helper interpretation: registration calls cache invalidation, can free referenced payloads, and does not normalize keys | RESOURCE_LIFETIME.md; original004B2B3C ->004702D0 ->0046FBE0 |
| ZFS-004 | Propose bounded immutable logical-reader boundary, explicit ambiguity/overlap policy and external codec boundary | RECONSTRUCTION_HANDOFF.md, reader/tests, evidence/historical_differences.json |

Each finding cites hash-listed evidence in findings.json/manifest.json. Original PE bytes were independently checked against a fresh read-only v100 import; only reviewed assembly/hashes are public. Confidence is high for binary-static branches/layouts and observed corpus equality. Source-model tests are analytical, not emulated or native original-path execution. Nonzero XOR and malformed inputs are synthetic/static only.

The historical extractor is fully equal on the authenticated corpus but differs on six synthetic cases: unsupported version, ignored extra chain cycle, both compression bits, unknown flags, nonzero XOR and signed packed length. Its name sanitization and traversal stopping rule must not be promoted as original behavior. Existing manual distinguishes membership/acquisition and PIX/global precedence correctly; this run adds registered-source details rather than replacing that separate precedence system.

Defer original producer semantics for identifier/time word, duplicate bsearch winner, writer/update variants, non-ASCII locale, dynamic media behavior, active-reference runtime invalidation effects, races and complete shutdown compatibility. There is no Nitro Pack/general-release claim, codec correctness proof or maintained provider integration.

Publication owns only this new run. No edits to ref/, manual/reference/, agent/promotions/, baselines, shared tools, reconstruction or governance are proposed. The designated steward should reconcile merged evidence and request separate human acceptance for any authoritative specification update.
