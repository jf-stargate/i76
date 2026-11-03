# Reproduce on private inputs

Use exact GZF/PE digests from BASELINE_AUDIT.md, Ghidra 12.1.4 and a new writable disposable project. Do not operate on the only copy or live GUI project. No historical migration needs application. All output directories below must remain outside the public checkout.

Prepare a private script directory with this run's TerrainBaselineInventory.java and TerrainShapeAudit.java, plus these **unmodified pinned-main** files:

- agent/tools/ghidra/semantic-consolidation/{ConsolidationAudit,ConsolidateSemantics}.java
- agent/tools/ghidra/semantic-v99/I76_SemanticPass_v99.java
- agent/tools/ghidra/readability-v100/I76_SemanticTypes_v100.java
- agent/tools/ghidra/readability-v101/I76_ObjectDispatch_v101.java
- agent/tools/ghidra/readability-v102/I76_ClassDispatch_v102.java

Also copy the separately proposed terrain-storage production script and TerrainSafety.java. Check their SHA-256 against VALIDATION.md/tooling handoff. Audit scripts can depend on pinned companions; the **production migration itself is standalone**.

General commands (replace uppercase placeholders with private paths):

```sh
analyzeHeadless NEW_PROJECT audit -import EXACT_V99_GZF -noanalysis \
  -scriptPath PRIVATE_SCRIPTS -postScript ConsolidationAudit.java CAPTURES/before \
  -postScript TerrainBaselineInventory.java CAPTURES/preflight-extra
analyzeHeadless NEW_PROJECT audit -process IMPORTED_DOMAIN_NAME -readOnly -noanalysis \
  -scriptPath PRIVATE_SCRIPTS -postScript I76_SemanticPass_v99.java \
  -postScript I76_SemanticTypes_v100.java -postScript I76_ObjectDispatch_v101.java \
  -postScript I76_ClassDispatch_v102.java
```

The import domain name in the executed trial was i76_mission_v99_verified_names; embedded program name is i76.exe. The v102 preview rejects absent v101 types; do not turn APPLY on. Run ConsolidateSemantics separately in **preview** using pinned bundle directory, authenticated retail PE and private log; it will report stricter equivalence/qualification differences described in BASELINE_AUDIT.md. Run TerrainShapeAudit.java with CAPTURES/type-comparison.tsv.

For preview invariance, run the production migration with **PREVIEW**, then ConsolidationAudit.java CAPTURES/preview. For each negative mode `type`, `label`, `boundary`, `guard`, `identity`, `rollback`, `arguments`, invoke TerrainSafety.java MODE in a separate script transaction. A single headless process may execute multiple -postScript invocations; do not check rolled-back fixtures inside their own script. Then capture CAPTURES/negative-final and CAPTURES/negative-final-extra with the two independent audit scripts.

Apply the production migration with **APPLY**, capture CAPTURES/after and CAPTURES/after-extra, apply again and capture CAPTURES/repeat and CAPTURES/repeat-extra. Keep all six phase tables/C directories private. Use the same noanalysis/default decompiler settings throughout. Ghidra may exit zero despite a script error: inspect log text and require expected summaries. Save the final negative tests' log as negative-final.log and preview/apply/repeat log as apply-final.log.

```sh
python3 scripts/validate_captures.py --captures CAPTURES \
  --pe PRIVATE_RETAIL_PE --gzf EXACT_V99_GZF --output PRIVATE_VALIDATION_JSON
```

This checks all 2,102 original body hashes against the PE, preview/rollback/repeat invariance, analyst preservation, exact two data changes, packed normal/numeric height ABI, expected changed C set and twelve normalized structure shapes. Manual review remains necessary for semantic interpretations and downstream caller readability.

Capture-index digests hash sorted `filename<TAB>byte_length<TAB>sha256<NEWLINE>` records, UTF-8. Full inventories/C are private; the public validation table gives aggregate indexes and individual table digests. Host-generated Ghidra/Java diagnostics/timestamps are not claimed deterministic. Existing baseline metadata can contain private source paths, so raw logs/databases must not be published.

On the maintainer's GUI database: back up/export first, add **only I76_TerrainStorageAudit_20261103.java** to Script Manager, choose PREVIEW, inspect both actions, then choose APPLY after acceptance. Expect changed=2 (or fewer if already present), then zero new changes on repeat. On any conflict, keep the database unchanged and inspect the preserved annotation. The GUI dialog is untested; headless compilation/application/rollback is verified. The script checks original program identity and 28 original body/boundary hashes and has no baseline-promotion operation.
