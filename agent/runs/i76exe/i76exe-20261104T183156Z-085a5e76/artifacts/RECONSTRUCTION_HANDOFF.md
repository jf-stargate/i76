# WRLD handoff for the WebUI reconstruction thread

Implement a read-only owned WREV9 WRLD summary first. The contract is a **331-byte payload / 339-byte chunk**, with no prefix revision inside WRLD. Use the packed byte layout and complete `fields.json` table; all offsets are payload-relative. The existing milestone3 deliberately keeps WRLD opaque and must retain its transactional resource leases and active-world separation.

Safe now: decode the eleven bounded 13-byte name slots, signed audio selection, signed environment selector, eight rows of three float32 values / four opaque bytes / signed int32, and signed projection input. Retain the original payload (or all opaque/padding bytes) so the 16-byte tail and eight unknown words survive exactly. Use neutral scalar labels, not inherited friction/roughness or time labels without additional semantic evidence. Do not make every word a float, or label the first word as WREV.

Require complete bounded BWD2 sibling chunks through EOF, exactly one four-byte WREV=9 in WDEF and exact 331-byte WRLD for this candidate. Unknown revision/size must produce an explicit unsupported-layout outcome while broader inventory may keep it opaque. Reject truncated headers/payloads, lengths below8 or outside parent, names without an in-slot NUL, and non-ASCII bytes before the NUL until an encoding policy is specified. Empty names remain representable. Keep post-NUL bytes and unknown regions verbatim. The research script is stricter than retail deliberately; do not reproduce unsafe game parser behavior.

Extend dependency reporting with direct ACT(+1e), LUM(+2b), TBL(+38), retained NPT(+45), sky(+52), derived scrounge(+5f), derived terrain defaults(+6c), display-derived map(+79), optional horizon manifest(+86). Keep acquisition category and availability status separate. Never report “loaded” just because a field ends in a known extension. The primary record supplies literal names, and actual route/cache/resource behavior remains an independent service.

Later loader integration needs: bounded ACT/TBL sizes (retail copies 768/65536 bytes); a separately audited LUM callback implementation and length; five terrain defaults from changing index4 to2..6 (or bounded fallback table); a bounded HZD manifest reader with 16 texture entries; independent .M16 dependencies in high-color mode; a display variant name helper for the map; separate NPT/UI and movie lifetimes. PCF comes from a separate mission-name preload operation and TER from TDEF/ZONE, not WRLD fields. WRLD itself has no high-color flag.

Suggested next implementation sequence:

1. Add an owned wire decoder with exact-length/revision checks and synthetic fixtures modeled on `scripts/test_wrld.py`, preserving unknown bytes and retaining current error rollback.
2. Add summary output with named slots, neutral scalar values and explicit opaque ranges. Add dependency rows using the verified categories and the deferred/derived qualification above.
3. Add directory-provider synthetic resources with intentionally different ACT/LUM/TBL stems and mode-specific sky/HZD values. Verify missing/empty resources remain distinguishable, all leases release, and inspection never activates a mission.
4. Integrate texture/table or terrain-scene behavior only after its separate resource grammar and ownership contracts are audited. Do not silently simulate successful rendering or mission activation.

Fixtures should cover 330/331/332-byte WRLD, WREV8/9/10, 12-character+NUL and 13-character unterminated names, empty strings, non-ASCII before/after NUL, distinct names in every slot, arbitrary unknown words/tail, finite float patterns, signed integers, and exact payload round-trip. Use synthetic data only in public tests.

Faithful rendering still needs LUM mathematical interpretation and callback selection, physical material meanings, unknown tail meaning, display-variant table policy, safe HZD grammar and end-to-end load/teardown validation. None blocks a bounded diagnostic decoder. This handoff proposes no maintained code changes, annotation changes or canonical promotion; research requires human review.
