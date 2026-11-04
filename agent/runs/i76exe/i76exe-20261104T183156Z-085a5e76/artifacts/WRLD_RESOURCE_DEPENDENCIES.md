# WRLD resource dependencies

All categories describe demonstrated **attempts or retained state**, not successful loads. Evidence is binary-static on the verified executable/v100 database. `dependencies.json` is the compact machine-readable map; `reviewed_instructions.tsv` contains reviewed instruction selections. The selected resource provider's normal acquire is 0046ffc0; name-based release is 0046fd40. Existing canonical resource lifetime cautions still apply.

| Payload offset / width | Family | Category | Original consumer / result | Condition |
|---|---|---|---|---|
| 01e / 13 | ACT | DIRECT_LOAD | 004b8a37 acquires; 004b8a94 copies 0xc0 dwords to 004fa170; 004b8a9b calls [005dd2c4] with context,0,256,ACT,LUM | Acquire unconditional; copy/callback if ACT non-null |
| 02b / 13 | LUM | DIRECT_LOAD | 004b8a57 acquires; passed to same callback, then released | Acquire unconditional; callback gated by ACT, not LUM |
| 038 / 13 | TBL | DIRECT_LOAD | 004b8acc acquires literal slot name; 004b8af3 copies 0x4000 dwords to 0060afa0 | Copy if non-null; no mode-derived TBL substitution here |
| 045 / 13 | NPT | CONDITIONAL_LOAD | 004b8b86/b8d copies C string to 006094f0; 0045df0b later acquires and parses objective text | UI/text initializer reached and nonempty |
| 052 / 13 | Sky MAP | CONDITIONAL_LOAD | 004b8b63/b6c -> 005dce60; 00404e88 -> 00471c10, output pair 00504c38 | Later sky initialization |
| 05f / 13 | Scrounge SDF | DERIVED | 004b8500 splits path; takes first eight stem bytes; 004ad640 adds .sdf; 004b41e0 acquires derived name | Nonempty and support object creation succeeds; null-prefix reader exemption |
| 06c / 13 | Terrain defaults | DERIVED | 004908f0 fills five slots at 005a45c8; 004909b0 later calls texture acquire for each | Valid name with character index4='1'; otherwise five built-in fallback names |
| 079 / 13 | Map MAP | DERIVED | 005a7ec8 retained; 0049cea2/cedb -> 004703a0 | Map opening path, nonempty name; mode4 instead closes display |
| 086 / 13 | HZD | CONDITIONAL_LOAD | 00401582 acquires text manifest; parses 16 names into 0x18-byte records; 0040168f calls 00471c10 per texture | Empty name returns; non-null acquired manifest enables parse |
| 093 / 4 | Sun/moon MAP | DERIVED | Signed selector -> one of eight rows at 004fa0b4, stride20; 00477b60 acquires built-in name | Every WRLD callback, valid stock selector |
| 004,011 / 13 each | Movies | CONDITIONAL_LOAD | Exact 13-byte copies to 005dd300/310; before/after game branches call 0049a070 at 0040371c/00404265 | Branch reached, no active movie, audio setup succeeds; opener appends even an empty name |
| none | PCF | DERIVED | 004026c0 replaces input extension at first dot with .pcf or _16.pcf; 00402782 acquires | Preload mode 00504bfc==0; suffix selected by 00495060 |
| none | M16 | DERIVED | 00471c10 replaces final extension with .m16; 00471cdd acquires after size query | Primary texture success and high-color predicate true |

The 4-byte audio word and copied scalar block are **STATE_ONLY** at WRLD entry; the former later controls CD playback, the latter is consumed by numeric getters. `projection_integer` is also STATE_ONLY: signed-to-float store, later projection argument. Unknown tail and material +0c semantics are **UNRESOLVED**.

## Important distinctions

ACT and LUM are both requested even in high-color mode; no explicit mode branch appears in WRLD. The palette operation is an indirect context callback. This run establishes its arguments, not the selected implementation's LUM indexing or mathematical transform. No safe LUM source length can be inferred from this call alone. ACT is released after callback and LUM is released independently if present. A missing ACT skips callback; missing LUM does not skip callback if ACT succeeded.

TBL is a direct serialized choice, independent of ACT basename. The 64KiB copy is demonstrated, but its complete renderer mathematics remain deferred. 00478b30 initializes auxiliary tables; 00479780 called with 0xff subsequently overwrites a 256-byte row of the copied destination using identity-table bytes. A loader that merely retains the original TBL pointer would miss that state construction.

Terrain configuration expands the supplied name into five variants by replacing byte index4 with '2','3','4','5','6'. It does not load the serialized '1' name in 004908f0. Later 004909b0 loads the five generated names through 00471c10 and aliases extra runtime slots to an earlier pair. Invalid/empty input installs the built-in defaults (`terr256.map`, `terr128.map`, through `terr16.map`); the exact pointer table at 004fad58 contains terr256.map, terr128.map, terr64.map, terr32.map, terr16.map. The input's fifth character is the rule; do not normalize a resource name before recording the observed derivation.

HZD's demonstrated role is **horizon texture manifest**, not generic hazard metadata. The handler parses 16 tokens/strings and only marks enabled at 00504838 after all 16 texture calls return nonzero. The unsafe retail text scanner and token-size handling are not a safe public text format specification. Later implementation needs a separate bounded HZD reader.

Map display is another derived-name case: 0049cea2 passes (name,1,4,...). At 00470412 the helper replaces byte index4 of the copied name with the byte at 004f8aaf + (00654b80 & 255), then calls 004478b0 at 0047046e. The serialized zmap6... name is therefore a template, and its embedded 6 need not be the resource actually acquired. Full display-variant table policy remains deferred.

Movies use a separate Smacker file-opening path: 0049a070 builds a cutscene/smk path and calls SmackOpen at 0049a1f2 (with a local fallback at 0049a295). It does not reject empty names before composing the path. Do not infer generic resource-cache acquisition for movies.

PCF is not any of the eleven WRLD name slots. Its input is the selected mission name passed from global 005049f0 (0040396b), and suffix selection is external. No TER sidecar is identified in WRLD; existing TDEF/ZONE ownership remains the demonstrated terrain-file source. The legacy list under WRLD mixed serialized names, associated resources, and later pipeline inputs; this run narrows that list.

High-color predicate 00495060 tests 005dd2a8==1. It does not parse a flag from WRLD. 00471c10 obtains the primary texture first, then optionally constructs .m16 and checks its size; missing companion may return only the primary. FULLRES.LST is another built-in downstream dependency, not a WRLD slot. The miss8/miss16 resource-name differences are already in the files: avoid automatically replacing their palette, sky or HZD names based on mode.

Signed environment selection computes `trunc((((selector+2) % 24)*8)/24)` using signed division semantics. Rows 0/1 reference `nk_1mon1.map`, remaining six `nk_1sun1.map`. Clock/hour semantics are inferred; the arithmetic and names are directly observed. No arbitrary negative or overflowing input is safe merely because the stock values work.

## Limits and falsification

All offsets/types are high-confidence static facts plus corpus agreement. Actual resource readability, retained cache lifetime, successful object creation and visual correctness are unmeasured. Missing source names, null callback inputs, disabled preload, map teardown mode, empty HZD/SDF and optional M16 all falsify blanket “loaded successfully” claims. Filename extensions are corpus observations corroborated by consumers, not type dispatch rules for these slots. No whole-program “there can be no other reader” claim is made for unknown ranges.
