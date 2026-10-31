# Interstate '76 — Ghidra v97-aware symbol reconciliation (v98 draft)

**Date:** 2026-10-31.  **Target:** original retail `i76.exe`, x86 32-bit, image base `00400000`.  **Ghidra:** 12.1.4.  **Script:** `I76_SymbolSync_v98_GZF.java`, **dry-run by default**.

## Which uploaded GZF is newer?

| Input GZF | Embedded archive timestamp (ZIP-local, timezone unspecified) | Database fingerprint | Annotated state |
|---|---|---|---|
| `i76.exe(2).gzf` | 2026-10-20 11:06:42 | SHA-256 `d48e0bc5194fcb7d4c74c3c9af3b502b495ec9a4d683374a745098f6bee76c03` | 2,097 functions, 2,029 user-defined function symbols, 357 user-defined labels |
| `i76_mission_v97_verified_names(2).gzf` | **2026-10-21 04:03:22** | SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce` | **2,100 functions, 2,034 user-defined function symbols, 380 user-defined labels** |

Both imported successfully using the supplied Ghidra 12.1.4 distribution, with the **same** verified original executable metadata: MD5 `a640ea0097dbb62e0c77b7f2847c7161`, SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. Their image base is `00400000` and architecture is `x86:LE:32:default`. The verified v97 GZF is the newer and better migration baseline. These timestamps come from inside the archive, not file-upload modification times.

There are **67 different symbol address/type entries** between the databases: 36 function-related, 31 label-related. Three addresses that were labels in the earlier export became defined functions in v97; the detailed before/after audit is `I76_GZF_v97_vs_prior_symbol_diff.tsv`.

## What this script changes

This is a **v97-specific safety and annotation reconciliation** of the previously published 151-address research map. It is not a complete recovery of original developer symbol names, and it does not silently rewrite sound v97 names to adopt an arbitrary naming style.

| Accepted tiers P + A | Entries | Default action |
|---|---:|---|
| Explicitly obsolete/underspecified `USER_DEFINED` v97 names | 39 | Rename **only** if the existing name exactly matches the verified v97 name |
| Default/analysis labels | 17 | Rename after address/code/data checks |
| Evidence-backed, disassembled function entries currently missing function definitions | 2 | Create function at `00406AB0` and `00490640` **only** when no enclosing function exists and the original disassembly matches the exact observed `SUB ESP, ...` prologue |
| Other existing analyst names | 54 | Retain as-is; review manually if desired |
| Historical/unpromoted review candidates | 39 | Disabled entirely by default |

The most material corrections include terrain height `00493550`, terrain normal `004931C0`, class-1 post entry `00463950` (not internal `004639A0`), class-31 animation post `0046F420`, previously misleading clock accumulator names, and camera/render producer/consumer interpretation. Read `I76_GZF_v98_migration_audit.tsv` for all existing names, proposed names, evidence tiers and statuses.

**Research baseline:** the 151-address table is the earlier evidence synthesis pinned to merged repository commit [`3e10251444a117c8d9da053b6887245a2bc4dbcf`](https://github.com/jf-stargate/i76/commit/3e10251444a117c8d9da053b6887245a2bc4dbcf), including PRs #69 and #70. Later accepted research must be reconciled in a further evidence pass; this v98 draft does **not** claim to subsume subsequent PRs. `P` = curated reference, `A` = bounded accepted original-instruction findings, `H` = historical/static review candidate.

## Validation already performed

- Imported both GZF files with the actual Ghidra 12.1.4 headless distribution provided by the user, without reanalysis.
- Extracted and compared actual symbol tables, not just filenames.
- Ran the v98 script in **dry-run mode on the untouched v97 project**: **58 proposed, 93 skipped/preserved, 0 errors**.
- Imported v97 to an **independent disposable project** and executed a trial with `APPLY=true`: **58 changed/created, 93 skipped/preserved, 0 errors**.
- Executed a second dry-run on the trial project: **58 already correct, 93 skipped/preserved, 0 errors**. This confirms idempotency for the tested GZF.
- The two newly defined functions were explicitly checked to have disassembled entry instructions and no preexisting enclosing function.

The actual uploaded GZFs were never mutated, and the test project is not included in this package.

## How to apply locally

1. Back up the v97 project/export; open the *v97* program in Ghidra 12.1.4.
2. Add `I76_SymbolSync_v98_GZF.java` to the configured Script Manager directories.
3. Run unchanged (`APPLY=false`) to inspect all actions and discrepancies.
4. Change only `private static final boolean APPLY = false;` to `true`, and run again **on a working copy**.
5. Review logs and compare the final symbol table. Restore the checkpoint if unexpected behavior occurs. All changes use a Ghidra transaction; internal errors cause rollback.

The executable fingerprint guard is mandatory. Existing `USER_DEFINED` labels outside the exact allowlist are preserved. The names are evidence-backed **research aliases**, not historical developer source symbols.

**Remaining scope:** the script updates address-based functions and globals. It does *not* automatically rename stack locals, individual parameters or structure fields; those require per-function storage and type-layout reconciliation, even though the GZF now makes that work possible. It does not relabel all 2,000+ user-defined functions. Further repository research after the pinned baseline also remains to be reconciled.
