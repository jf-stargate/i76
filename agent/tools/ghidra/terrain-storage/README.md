# Guarded terrain storage correction for audited private v99

Two data annotations correct misleading C output: 006442C0 int → float spacing, and 004ED7EC generic pointer → four-byte terminated `aud` string. The latter prevents an accidental text-as-pointer value from being labeled as an interior terrain-grid pointer. No function, parameter, calling convention, grid ownership, VM, resource or class-dispatch type is changed.

Research evidence: run **i76exe-20261103T011951Z-e8b8ea6e**, submitted separately. Accepted base `9576fc573964bed624a08d878886ccad40a63d7a`. Exact tested input GZF SHA-256 `ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710`, 6,500,304 bytes. Retail executable SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`. Source annotation authorship/execution history remains unresolved.

Production artifact **I76_TerrainStorageAudit_20261103.java** is standalone: no companion TSV, PE file, historic migration or helper script required. Program metadata, x86/base/version, 28 original function-body/range guards, the original literal, known spacing label and exact data boundaries are checked. Different preexisting types/analyst labels produce explicit conflicts and abort the entire apply. Existing comments and analyst symbols remain identical. Changes are transactional; an unexpected failure rolls both edits back.

1. Back up the currently open Ghidra program. Add the production script to Script Manager in Ghidra **12.1.4**.
2. Run without arguments and select **PREVIEW** (default); review individual proposals. A Script Manager argument of PREVIEW or APPLY is also supported.
3. After explicit maintainer acceptance, select **APPLY**. The tested exact v99 copy reports **2 changes**, then **0 on repeat**.
4. Inspect 00493080, 00490A00, 00490FB0, 004937C0, 00425130 and 00425EF0. Height/normal signatures and other target C should remain unchanged. Any conflict preserves the whole program; do not weaken guards merely to force application.

Headless usage: `-postScript I76_TerrainStorageAudit_20261103.java PREVIEW` or `APPLY`. **Only analyzeHeadless compilation/execution was tested**; the graphical choice dialog was not exercised. This is a review candidate for the exact measured baseline, not approval to change the user's live database.

Validation: 2,102 original bodies unchanged and PE-verified; 289 C captures, 10 reviewed changes/279 unchanged; seven negative fixture cases and saved rollback captures; full after/repeat equality. Only the two data rows change; all signatures/types/comments and USER_DEFINED symbol entries remain identical. Research validation includes exact table/C digests, evidence and reproduction commands.

**TerrainSafety.java is a disposable-project test subclass**, not a companion needed in production. It has seven modes: type, label, boundary, guard, identity, rollback, arguments. It deliberately injects invalid state inside rolled-back fixture transactions. Never run it on a live program. The empty production checkpoint provides a subclass-only exception point; there is no failure-injection mode in the production script.

Limitations: no recovered developer source declaration, no hardware x87/game execution, no universal ownership assertion, no compatibility claim for unknown later analyst changes, and no automatic export/baseline promotion. All PRs remain unmerged for maintainer review.
