# v100–v102 semantic reconciliation

Standalone guarded Ghidra **12.1.4** migration for retail `i76.exe`, based on exact v99 GZF SHA-256 `ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710`. Research aliases are not original developer names. Original code and live GUI database are untouched by the published research.

Install **only `I76_Reconcile_v100_v102_20261103.java`** in Script Manager. No TSV, JSON, input executable or companion script is needed at runtime. Back up/export the open program, run **PREVIEW**, inspect individual actions/conflicts, then explicitly choose **APPLY**. The GUI choice defaults to PREVIEW; GUI execution remains untested. Headless no-argument execution defaults to PREVIEW. Supported arguments: `PREVIEW|APPLY [ALL|TERRAIN|V100|V101|V102]`. Use ALL for the integrated migration. Named phases support review of staged disposable trials; prerequisites must already exist for APPLY of a later phase.

Expected on exact original v99: **54 eligible = 2 terrain corrections + 52 historical operations; 4 deferred**. Repeat: **0 edits, 54 already, 4 deferred**. The three v100 pointer slots are credited as ALREADY when subsumed by the fully verified v102 array. Existing analyst edits are preserved by aborting/rolling back the entire application on a conflict, rather than forcing a historical count. PREVIEW constructs candidate datatypes in memory without saving them or starting a mutation transaction.

## Guard and scope

- Authenticates toolchain, retail metadata, architecture/base, every one of the original **2,102 function body ranges/byte hashes**, complete 27-row dispatch bytes, 12 existing semantic layouts, and full affected signature arity, calling convention, names, types and storage.
- Validates newly existing type components/prototypes by recursive semantic layout, ignoring descriptive comment differences; independently validated v99 shapes need no strict `isEquivalent()` match.
- Retains all old comments and analyst symbols except the specifically reviewed resolver alias correction at `0045F0F0`; retains unrelated signatures, EAX normal ABI, packed stack arguments and numeric ST0 height return.
- Exact data footprints; whole-table pointer values; scalar/overlap checks at every table byte; preserves two existing table labels, three comments and **all original outgoing references**. Whole-body/table guards also run after mutation.
- New world-node extent **0xB0**, class-list **0x0C**, active-world entry **0x78**, descriptor **27 × 0x34**. `class_runtime` and contextual `+0x68` remain opaque; class-specific prefixes stay library-only. Descriptor is engine dispatch data; no C++ vtable claim.
- Any unexpected failure rolls back the whole transaction. `checkpoint()` is an empty test override hook; no destructive fixtures live in this production directory.

## Four deliberate deferrals

| Historical parameter | Reason |
|---|---|
| v100 `00457FF0` | Trial assigns camera fields to unrelated active entries/scratch lists |
| v100 `00474C60` | Trial gives DWORD copy loops misleading repeated field access |
| v100 `00472C10` | Float-plane traversal becomes byte-array casts without a readability gain |
| v101 `00409980` | Active-entry pointer variable becomes a numeric bucket index |

The script never undoes an existing analyst annotation to enforce these deferrals. Their original signatures remain intact on exact v99. See [research operation ledger](../../../runs/i76exe/i76exe-20261103T030709Z-1758109b/evidence/operations.tsv) and [readability review](../../../runs/i76exe/i76exe-20261103T030709Z-1758109b/artifacts/READABILITY.md). That research PR may remain unmerged independently of this tooling proposal.

Source lineage: accepted `readability-v100`, `readability-v101`, `readability-v102` tools at `430ef59c8396db9880cd95e6f6ba9d1bd81e9c20`; accepted terrain correction from PR #107. Their historical baseline was v98-derived and is not evidence that the maintainer already applied them to v99. This tool changes no canonical reference or baseline identity.
