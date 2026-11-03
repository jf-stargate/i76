# Reproduction

Requires licensed retail PE and exact private v99 GZF in manifest; Ghidra12.1.4. Keep all capture directories and databases private. Fetch this run's scripts and the separate tooling PR's exact `I76_Reconcile_v100_v102_20261103.java` SHA-256 from TOOLING.md. Production runs without companions; research audit/fixture intentionally use the production source as a compilation dependency.

Import with `analyzeHeadless NEW_PROJECT research -import EXACT_GZF -noanalysis -scriptPath SCRIPTS -postScript RestorationInventory.java CAPTURES/before`. Imported domain name is `i76_mission_v99_verified_names`; embedded program name i76.exe.

Use accepted terrain script from main `430ef59c8396db9880cd95e6f6ba9d1bd81e9c20`: preview/capture, apply/capture, repeat/capture. Independently compare before/preview and after/repeat. Then production `PREVIEW V100`, `APPLY V100`, capture `approved-v100`; `PREVIEW V101`, `APPLY V101`, capture `final-v101`; `PREVIEW V102`, capture `v102-preview`, `APPLY V102`, capture `final-v102`; `APPLY ALL`, capture `final-repeat`. Reopen saved projects between phases as needed. No automatic analysis.

In another pristine import, run `RestorationSafety.java` modes `type`, `prerequisite`, `bytes`, `boundary`, `identity`, `tablebytes`, `overlap`, `signature`, `label`, `rollback`. The last mode deliberately runs **without an outer fixture transaction**, so final capture `final-rollback` independently tests the production transaction. Capture after default no-argument PREVIEW as `final-preview`; `APPLY` and capture `one-shot`; repeat and capture `one-shot-repeat`. Original scratch trials and later final clean trials are distinct; logs are not interchangeable.

`python3 scripts/validate_restoration.py --captures CAPTURES --pe RETAIL_PE --gzf EXACT_GZF --output PRIVATE_RESULT.json` checks completed captures, retail body hashes, reviewed signature/data changes, protected ABI/layouts, analyst symbols/comments, exact pointer references, rollback/preview/repeat and staged/one-shot equality. It expects the final headless log as `CAPTURES/final-tests.log`. Do not start comparison while a capture is still being written. Ghidra can exit zero with script errors; require expected summaries, all ten NEGATIVE PASS records and no ERROR in the final clean log.

The fixed 419-function sample includes primary targets and direct callers of control targets, including the large VM dispatcher; that breadth explains many neutral C changes. Decompiler defaults must match. It is not an all-transitive-call-graph export or all-program C coverage.

GUI Script Manager dialog/application **not tested**. Maintainer should back up the open database, install only production script, preview, review conflicts and explicitly apply only after acceptance. No live program or original export is overwritten by reproduction.
