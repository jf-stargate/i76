# Integrated semantic consolidation pilot

Reviewable shared-tool proposal for retail `i76.exe`, Ghidra **12.1.4**, TER/FSM/RES with ENG/OBJ controls. This integrates selected semantics from merged pilots #102–#104 against a measured v98-derived database with accepted v99–v102 prerequisites. It does not promote a canonical baseline or recover developer source names. Human acceptance is required; leave the PR draft.

Start with [baseline compatibility](BASELINE_COMPATIBILITY.md), [decisions](SEMANTIC_DECISIONS.tsv), [readability audit](READABILITY_AUDIT.md), and [conflicts](CONFLICTS.md). The [inventory](SEMANTIC_INVENTORY.json) and [semantic map](SEMANTIC_MAP.md) preserve original addresses and source provenance. [Validation](VALIDATION.md) distinguishes executed checks from limitations.

## Run on a private working copy

Never use the only copy of a project. No public executable, resources, GZF, project database or raw decompilation is included. The supplied GZF is preserved; all measured changes were made to new disposable projects.

1. Audit the actual program with `ConsolidationAudit.java PRIVATE_OUTPUT_DIRECTORY`. Output includes complete private C for the selected functions and direct callers. Keep that directory outside the checkout.
2. Prepare accepted v99–v102 prerequisites separately, using their own previews and inspecting all skips. Historical scripts remain unchanged. This tool does not concatenate or execute the pilot annotation scripts.
3. Run `ConsolidateSemantics.java BUNDLE_DIRECTORY RETAIL_PE PRIVATE_ACTION_LOG`. **No fourth argument means preview.** Review `APPLY`, `ALREADY`, `PRESERVE`, and `CONFLICT` rows.
4. Run the same command with the fourth argument exactly `APPLY` on the disposable copy. Repeating should produce zero new actions. Any other fourth argument is rejected.
5. Capture the same sample again and run `validate.py --captures PRIVATE_CAPTURE_ROOT --pe RETAIL_PE --metrics-out PRIVATE_METRICS_TSV`. Inspect substantial caller changes before handoff.

For the exact tested export, a reproducible driver creates a new output directory, makes private copies of accepted v99–v102 scripts (changing only class names and their existing APPLY constants), and runs separate preview/application stages:

```sh
python3 reproduce.py --gzf PRIVATE_V98_GZF --pe RETAIL_PE \
  --headless GHIDRA_12_1_4/support/analyzeHeadless --work NEW_PRIVATE_DIRECTORY
```

The driver rejects an existing directory or a different GZF/PE digest. It examines logs because analyzeHeadless may return success despite a script exception. The runtime Ghidra script checks program identity, original PE architecture/image base, original body hashes/bytes, layout constants and exact signatures. An unfamiliar signature is preserved; an original-body mismatch aborts before mutation. Conflicting types skip dependent signatures. All mutations are transactional. Ghidra's enclosing script transaction determines when rollback becomes observable; use a **subsequent script/capture**, not an in-transaction assertion, to verify it.

`ConsolidationSafetyProbe.java BUNDLE PE PRIVATE_LOG APPLY MODE` tests one mode per invocation: `parameter`, `type`, `guard`, `pe`, or `rollback`. Fixtures belong only in disposable projects. Run a separate audit afterwards; its tables and C must equal the pre-test capture. No injection switch exists in the production migration.

## Scope and operation counts

The new migration performs **29 operations**: four types, eleven atomic function-signature/name groups, five data mappings, and nine additive comments. Six RES groups rename **nine default parameters** without changing their types. One data annotation is already equivalent; one spacing-type conflict is preserved and reported. Repeat: **0 new, 30 already, 1 conflict**. Accepted prerequisites add 141 separate operations; those are not counted as new consolidation improvements.

The 286 inventory records include historical migration rows, pilot candidates, executable actions and atlas relationships. They deliberately overlap. Their dispositions are **66 APPLY, 154 ALREADY, 13 PRESERVE, 2 CONFLICT, 51 DEFER**; these are provenance-record counts, not edit counts. The two conflict records describe the same spacing issue at different provenance levels. No record requires MANUAL execution in this release; resolving conflicts may need analyst judgment.

The known spacing conflict is retained, v99's ST0 height presentation is preserved, and normal now explicitly returns its caller output in EAX. Five larger RES types and five propagated return prototypes are separately deferred. No polymorphic runtime pointer is assigned a universal structure.

Portable layout checks: `cc -std=c11 -Wall -Wextra -Werror -pedantic -c header_check.c`. Offline provenance checks: `python3 validate.py`. Source paths/digests are checked against the pinned repository; no network is needed for those checks. Review all limitations before applying to another database.
