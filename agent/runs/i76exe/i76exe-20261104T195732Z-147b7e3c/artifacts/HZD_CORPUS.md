# Retail HZD corpus and resource-mode comparison

`../evidence/corpus.json` is the complete machine-readable identity/relationship table: exact private file paths, lengths, SHA-256, archive record indices/offsets/compression, slot offsets/equality classes, mission paths/hashes and per-specimen availability counts. Original HZD payloads and full texture names remain private in `/media/neon-remote/prj/i76/hzd-private/corpus_private.json`. Public `dependency_inventory.json` contains name hashes and payload identities/locations, not the complete proprietary texture list.

## Scope and authentication

The private installation roots are `/media/neon-remote/prj/i76/orig/miss8`, `orig/miss16`; extracted resources are `/media/neon-remote/prj/i76/zfs/resources`. A recursive survey of `orig`, `game`, `zfs` found74 HZD files, all in that extracted root. The independent survey also enumerates every live HZD record in `orig/I76.ZFS` and all WRLD-selected names; no selected HZD is unresolved. ZFS SHA-256 is `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`, length55,535,506. Each HZD is freshly decompressed from that archive with the pinned accepted ZFS reader and compared byte-for-byte to its extracted file. This authenticates extraction identity, not a signed distribution provenance or every historical retail release.

| Population | Count |
|---|---:|
| Mission files / mode pairs | 80 / 40 |
| Nonempty HZD fields | 78 (39 per mode) |
| Distinct WRLD-selected logical HZD names | 36 |
| Distinct selected payload hashes | 19 |
| All HZD logical files / distinct payload hashes | 74 / 33 |
| Files with 16 records / 224 bytes / all 12-byte names | 74 |
| Files with 8 unique references / with 16 | 32 / 42 |
| Empty names / blank records / trailing bytes / non-ASCII | 0 |
| All-corpus distinct logical texture names | 272 |

All32 duplicate files repeat slots0..7 at8..15; the public equality-class arrays capture this without publishing original lists. Many logical manifests share identical bytes, so “74 specimens” and “33 distinct payloads” must remain separate counts. No alternate record type or extra parameter was observed.

## M01 and M06 anchor comparison

Both miss8/M01 and miss8/M06 select **p01.HZD**, not t01/t06 inferred from mission numbers. miss16/M01 selects **p01_16.HZD** and miss16/M06 selects **p06_16.HZD**. Each has224 bytes, sixteen records, sixteen unique names, no empty fields or duplicates.

| HZD logical name | SHA-256 | Availability per 16 unique names |
|---|---|---|
| p01.hzd | 05371a2881a7b43e72d3a0383be2be519b14875f199b1761249a934edee951b0 | 16 direct MAP candidates |
| p01_16.hzd | c329fddaadb49166083c8aed71a22d2a4c0d8083924604e61eddcb7333974d71 | 16 VQM +16 M16; all VQM CBKs resolve |
| p06_16.hzd | c97c3a34de7359867648734c29e5e5f4c99d496938581fd6648d2dbbdfcfd113 | 16 VQM +16 M16; all VQM CBKs resolve |

These manifests select different texture names across modes and across the two miss16 missions. The manifest name and contents already encode those choices; 00401540 does not derive a `_16` HZD suffix. The renderer/resource pipeline has an additional independent global high-color predicate.

Of40 mode pairs,38 change logical HZD and payload. M15 has an empty field in both; T04 selects the same t01.hzd in both. Thus neither “every miss16 HZD differs” nor “mode always adds `_16`” is correct. All80 mission/HZD mappings, including additional missions, are in the corpus table.

## Resolution evidence

Surveyed1,758 live PIX indexes, their referenced PAKs and top-level ZFS/loose inventory. All272 names have a primary candidate:104 have direct MAP members and168 have VQM members with CBK payloads and M16 members. **All primary/M16 payloads are PIX/PAK members** in this inventory; the CBKs resolve as top-level ZFS records. Looking for standalone MAP files would misreport every reference as missing. For every used slice, the survey bounds-checks its PAK offset/length and hashes the actual payload. The PAK itself is read/decompressed from the authenticated archive. Availability does not select the active mounted source or run the retail decoder.

Across each specimen's unique names (928 total, counting a shared name again in another manifest),472 have direct MAP candidates and456 have VQM+M16 candidates with resolved CBKs. These are not928 globally distinct names. No unresolved primary candidate or referenced CBK remains. M16 is optional to the original loader; its inventory presence does not prove high-color use. No original textures are published.

Limits: no native game execution; mission roots are identified installed files, not archive-authenticated mission extraction. Corpus coverage is this accessible installation. No claim that all media/patch/region versions are covered.
