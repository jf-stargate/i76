# Executed validation and limits

## Reproduction environment and actual results

Ghidra 12.1.4, x86 little-endian PE32, Java 27-ea; pinned main/protocol and private hashes in BASELINE_COMPATIBILITY.md. Original input copied into fresh disposable projects, imported with `-noanalysis`. The final published implementation was exercised in a fresh end-to-end reproduction; prior rejected trials are excluded from the final metrics.

| Check | Actual result |
|---|---|
| Retail file SHA-256, PE header/i386/base, Ghidra metadata | matched verified retail identity |
| Actual GZF digest and program inventory | d48df73d…e57fbd; i76.exe; 2,102 defined +235 external |
| Accepted prerequisite previews/applications | v99 85/85 (1 preserved comment); v100 14/14; v101 26/26; v102 16/16; zero reported errors |
| New preview | 29 eligible / 1 already / 1 conflict; no committed change |
| New apply | 29 changed / 1 already / 1 conflict; committed |
| Second application | 0 changed / 30 already / 1 conflict |
| All original defined bodies/boundaries | 2,102 before/after; independently section-mapped bytes/hash equal retail PE |
| Preview invariance | functions, symbols, types, comments, instructions and all 279 C captures identical |
| Repeat invariance | same six tables and all 279 C captures identical to first apply |
| Existing analyst annotations | original USER_DEFINED symbol set retained; every old comment retains its text prefix; every old type inventory entry retained |
| Packed normal ABI | EAX:4 return, explicit output +4, doubles +8/+16; no hidden argument or gap |
| Height ABI | existing numeric ST0:10 and two stack doubles preserved |
| VM layouts | VmToken 8, VmNode 0x10BC; host area +1000, live IP +10A8, next +10B8; mixed words scalar |
| VM import-phase non-propagation | 00410490 / 00412500 signatures and complete C unchanged |
| Required ENG/OBJ controls | all four complete C outputs and signatures unchanged |
| Sample decompilation | 279 succeed; 33 changed, 246 unchanged; 14 target improvements reviewed |
| Layout compilation | strict C11 compilation of semantic_layouts.h and Pilot C resource_design.h passed |
| Inventory source validation | all 286 unique IDs, source paths/digests, evidence tiers, dispositions and required target coverage pass |

`capture_digests.json` contains private table digests; `readability_metrics.tsv` contains per-function C digests and defined textual metrics. Action logs are deterministic for a given input. Original runtime behavior was not executed; x87 hardware experiments from earlier M06 research were not rerun or counted here.

## Negative tests and rollback

The final disposable project passed separate script invocations for: analyst parameter preservation, incompatible VmNode layout preservation/dependent skip, corrupt original-body digest rejection, wrong retail file rejection, and injected unexpected failure after adding a sentinel datatype. The production migration has no injection option; the test-only subclass provides the fixture.

A subsequent independent audit verifies **all six capture tables and every one of the 279 C files exactly equal the pre-test state**, including absence of the sentinel type. This tests actual saved rollback, not only a boolean transaction flag. Ghidra's outer script transaction can defer observability; checking for rollback within the same script was rejected as an invalid test method. Fixtures only touched the disposable program and their temporary private files.

## Reproduce checks

```sh
python3 validate.py
cc -std=c11 -Wall -Wextra -Werror -pedantic -c header_check.c -o PRIVATE_OBJECT
python3 reproduce.py --gzf PRIVATE_V98_GZF --pe RETAIL_PE \
  --headless GHIDRA_12_1_4/support/analyzeHeadless --work NEW_PRIVATE_DIRECTORY
python3 validate.py --captures NEW_PRIVATE_DIRECTORY --pe RETAIL_PE \
  --metrics-out PRIVATE_METRICS_TSV
```

For negative tests, invoke each documented MODE separately, followed by `ConsolidationAudit.java PRIVATE_POST_TEST_DIRECTORY`; compare its tables and C with the pre-test capture. Ghidra may exit zero for script exceptions: inspect logs, as reproduce.py does. No private path is needed to interpret the public reports.

Repository checks and trusted PR-head integrity results are recorded with the published PR. Required integrity executes trusted base policy, not this proposal's validator. It certifies repository policy compliance only.

## Limits and outstanding review

The latest user-edited database is unavailable; no compatibility claim for it. No broad dynamic VM/resource/collision proof, complete host ABI, full-game validation, or bit-perfect x87 reconstruction. Spacing int/float conflict, two cosmetic pointer-label regressions, opaque VM words and RES type/return propagation remain review items. No final GZF export was requested or published; the integrated disposable project remains private. No original code bytes, bodies or boundaries are changed by the migration.

Repository-local verification: **38/38** trusted unit tests pass; accepted protocol validator passes; offline inventory validation and strict C11 layout compile pass. See `validation_results.json`. The PR head integrity check is a separate publication gate.
