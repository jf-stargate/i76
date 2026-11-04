# Retail corpus comparison

All accessible private mission files under `/media/neon-remote/prj/i76/orig/miss8` and `orig/miss16` were surveyed: **80 files, 40 basename pairs**. Families per directory: A=1, M=15, S=7, T=17. No mission or WRLD parse failures. This is a structural/field-consistency survey, not an asset-availability or gameplay test.

`evidence/corpus.json` records every specimen path relative to the private root, byte length, SHA-256 and MD5, WDEF/WRLD offsets and lengths, WREV, numeric selection words, and bounded name values. Those are identity/observation metadata, not mission captures. No payload hex, mission file or support asset is published. `numeric_observations.json` records numeric value sets and the four required specimen observations.

All root REV values are 2; all WREV=9; WDEF total=367, WRLD total=339, payload=331, WRLD header offset=0x28. No alternate sizes or layout revisions were observed. Each WDEF has WREV, WRLD, EXIT. These independently confirm the WRLD offset calculation against the instruction pointer convention.

## Required four specimens

| Specimen | File bytes | WRLD chunk/payload | WREV | ACT | Sky | Terrain base | HZD |
|---|---:|---|---:|---|---|---|---|
| miss8/M01.MSN | 25770 | 339/331 | 9 | t17.ACT | nk_1cld2.MAP | tt171sd_.MAP | p01.HZD |
| miss8/M06.MSN | 47814 | 339/331 | 9 | t01.ACT | nk_1cld2.MAP | tt181sd_.MAP | p01.HZD |
| miss16/M01.MSN | 25770 | 339/331 | 9 | t17_16.ACT | nk_6cld2.MAP | tp031db6.MAP | p01_16.HZD |
| miss16/M06.MSN | 47814 | 339/331 | 9 | t09_16.ACT | nk_6clde.MAP | tp051dr6.MAP | p06_16.HZD |

M01 audio selection=9; M06=1; all four environment selectors=15 and projection integers=600. Both movies are empty in M01/M06. Both use ngscrng1.sdf and zmap6m00.MAP; M01 uses t17.LUM/TBL while M06 uses t01.LUM/TBL. M06 miss16 ACT is t09_16.ACT, not a mechanical t01_16.ACT substitution.

## All mode pairs

| Changed name slot | Pairs with different serialized slot bytes |
|---|---:|
| slot_04 | 0 / 40 |
| slot_11 | 0 / 40 |
| palette | 35 / 40 |
| luminance | 1 / 40 |
| blend_table | 0 / 40 |
| notepad | 0 / 40 |
| sky | 39 / 40 |
| scrounge | 0 / 40 |
| terrain_default | 38 / 40 |
| map_name | 0 / 40 |
| horizon_manifest | 38 / 40 |

39 pairs have some WRLD difference; T04 is byte-identical across modes. Outside name slots only S01 changes byte +0x000 (the audio selection). No material-row, environment-selector, projection-integer or unknown-tail bytes differ within corresponding miss8/miss16 pairs. This does not imply those ranges are constant across different missions.

M14 is the sole pair differing in the LUM slot: miss8 stores `m05.LUM`, miss16 `m05.lum`. This is a case-only spelling change, not evidence of different logical resources. S01 audio changes from2 (miss8) to1 (miss16). TBL never changes within a pair. Palette names are unchanged in M04, M12, T04, T06, T12. M15 keeps terrain and HZD names while sky/palette change. These are counterexamples to an unconditional mode suffix replacement algorithm.

## Stable, variable and zero spans

`zero_spans`, `stable_nonzero_spans` and `variable_spans` in corpus.json are a disjoint bytewise partition of the entire 331-byte payload (half-open decimal offsets). They compare all 80 payloads, not only the four initial samples. Stable numeric zero regions are observations, not reserved-field declarations. The final +0x13b..+0x14b tail includes variable bytes and remains uninterpreted. All eleven name slots terminate within 13 bytes; all bytes before termination are ASCII. No mission has a populated direct PCF or TER slot in this recovered layout.

## Pair inventory

| Mission | Differing fields (names only) |
|---|---|
| A01.MSN | palette, sky, terrain_default, horizon_manifest |
| M01.MSN | palette, sky, terrain_default, horizon_manifest |
| M02.MSN | palette, sky, terrain_default, horizon_manifest |
| M03.MSN | palette, sky, terrain_default, horizon_manifest |
| M04.MSN | sky, terrain_default, horizon_manifest |
| M05.MSN | palette, sky, terrain_default, horizon_manifest |
| M06.MSN | palette, sky, terrain_default, horizon_manifest |
| M07.MSN | palette, sky, terrain_default, horizon_manifest |
| M08.MSN | palette, sky, terrain_default, horizon_manifest |
| M09.MSN | palette, sky, terrain_default, horizon_manifest |
| M10.MSN | palette, sky, terrain_default, horizon_manifest |
| M11.MSN | palette, sky, terrain_default, horizon_manifest |
| M12.MSN | sky, terrain_default, horizon_manifest |
| M13.MSN | palette, sky, terrain_default, horizon_manifest |
| M14.MSN | palette, luminance, sky, terrain_default, horizon_manifest |
| M15.MSN | palette, sky |
| S01.MSN | palette, sky, terrain_default, horizon_manifest (+audio word) |
| S02.MSN | palette, sky, terrain_default, horizon_manifest |
| S03.MSN | palette, sky, terrain_default, horizon_manifest |
| S04.MSN | palette, sky, terrain_default, horizon_manifest |
| S05.MSN | palette, sky, terrain_default, horizon_manifest |
| S06.MSN | palette, sky, terrain_default, horizon_manifest |
| S07.MSN | palette, sky, terrain_default, horizon_manifest |
| T01.MSN | palette, sky, terrain_default, horizon_manifest |
| T02.MSN | palette, sky, terrain_default, horizon_manifest |
| T03.MSN | palette, sky, terrain_default, horizon_manifest |
| T04.MSN | none |
| T05.MSN | palette, sky, terrain_default, horizon_manifest |
| T06.MSN | sky, terrain_default, horizon_manifest |
| T07.MSN | palette, sky, terrain_default, horizon_manifest |
| T08.MSN | palette, sky, terrain_default, horizon_manifest |
| T09.MSN | palette, sky, terrain_default, horizon_manifest |
| T10.MSN | palette, sky, terrain_default, horizon_manifest |
| T11.MSN | palette, sky, terrain_default, horizon_manifest |
| T12.MSN | sky, terrain_default, horizon_manifest |
| T13.MSN | palette, sky, terrain_default, horizon_manifest |
| T14.MSN | palette, sky, terrain_default, horizon_manifest |
| T15.MSN | palette, sky, terrain_default, horizon_manifest |
| T16.MSN | palette, sky, terrain_default, horizon_manifest |
| T17.MSN | palette, sky, terrain_default, horizon_manifest |
