# Provenance and reproduction

## Identity and scope

- Repository: `jf-stargate/i76`, GitHub repository ID `1240020485`.
- Original protected main/base: `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`.
- Protocol: `1.0.4`; research schema `1.2.0`; track `i76exe`; advisory subsystem RES.
- Owned branch: `agent/i76exe/i76exe-20261101T161535Z-22d9956f`.
- Owned path: `agent/runs/i76exe/i76exe-20261101T161535Z-22d9956f/`.
- Retail executable: private `orig/i76.exe`; SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; MD5 measured in manifest.
- Ghidra: 12.1.4 PUBLIC, x86 PE32; private v97 export `eng01-private/project/i76_mission_v97_verified_names.gzf`, SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`; program `i76_mission_v97_verified_names`.
- Actual disposable project: private `pilotc-private/project/research`; source export/database unmodified. Private decompilation and instruction listings stayed under `pilotc-private/`.

`bootstrap.json` records GitHub default branch, exact head, active ruleset and open PR/branch discovery. Ruleset 25664125 is active for main, requires PR, integrity and resolved threads, zero formal approvals, no bypass actors/current-user bypass. Human acceptance is still required. Open PR #101 concerns class-dispatch types and is not accepted resource evidence. Retained historical branch names were inspected as navigation only. `ACCEPTED_SOURCES.tsv` hashes the accepted-tree policy, references, snapshots and adjacent research actually consulted.

The local `remote` checkout initially had older policy files; those were not used as authority. Policy and workflow were read through Git at the pinned accepted commit before creating the fresh worktree. No shared canonical or historical files were changed. No agents were delegated.

## Replay with licensed private prerequisites

Use a new private project directory, not an existing sole database. In the commands below, `HEADLESS`, `GZF`, `EXE`, `WORK` and `RUN` denote absolute paths to Ghidra's `analyzeHeadless`, the verified export, the licensed executable, new private scratch, and this run respectively. Set them in the invoking environment; do not put any private binary/output in the repository. Ghidra may need permission to initialize its user configuration. The first sandbox attempt here failed writing that configuration; the retry was explicitly approved, and used the disposable project.

```sh
mkdir -p "$WORK/project"
"$HEADLESS" "$WORK/project" research -import "$GZF" -noanalysis \
  -scriptPath "$RUN/scripts" -postScript PilotCStaticAudit.java \
  "$WORK/before.tsv" "$WORK/private-before.txt"
python3 "$RUN/scripts/verify_static_identity.py" --exe "$EXE" --audit "$WORK/before.tsv"
"$HEADLESS" "$WORK/project" research -process i76_mission_v97_verified_names -noanalysis \
  -scriptPath "$RUN/scripts" -postScript PilotCParameterNames.java "$WORK/before.tsv"
"$HEADLESS" "$WORK/project" research -process i76_mission_v97_verified_names -noanalysis \
  -scriptPath "$RUN/scripts" -postScript PilotCParameterNames.java "$WORK/before.tsv" APPLY \
  -postScript PilotCParameterNames.java "$WORK/before.tsv" APPLY
"$HEADLESS" "$WORK/project" research -process i76_mission_v97_verified_names -readOnly -noanalysis \
  -scriptPath "$RUN/scripts" -postScript PilotCStaticAudit.java \
  "$WORK/after.tsv" "$WORK/private-after.txt"
python3 "$RUN/scripts/verify_static_identity.py" --exe "$EXE" --audit "$WORK/after.tsv"
cc -std=c11 -Wall -Wextra -Werror -pedantic -fsyntax-only -x c "$RUN/artifacts/resource_design.h"
```

Expected: 24 audited function ranges match retail PE; nine eligible default parameters on dry run, nine changes on apply, zero new/nine already on repeat; 2,335 functions throughout. Compare body ranges and existing names/types/comments before and after. The initial published `STATIC_AUDIT.tsv` contains 23 functions: the size helper `0046FEE0` was added after the release/size asymmetry emerged. The final script and `STATIC_AFTER.tsv` include that 24th dependency. This intentional coverage difference is not a code mutation. All 23 common ranges match. The parameter-only script is unchanged between successful dry/apply/repeat passes.

`verify_static_identity.py` independently parses PE headers/sections using Python's standard library, checks whole-file SHA-256 and compares each audited Ghidra range hash with bytes from the matching PE section. It does not trust the Ghidra executable-hash metadata alone. A wrong executable and a deliberately corrupted first-range digest were each rejected. `STATIC_VALIDATION.json` records those results. These checks establish identity and annotation non-regression, not the truth of every C-level interpretation.

`PilotCStaticAudit.java` writes metadata, prototypes, call/xref addresses and body digests to the TSV, and full private selected decompilation/instructions to its **second** output. Do not publish that second file. Neither script emulates instructions or loads game payloads. No retail resources, PE bytes, GZF/database, secrets or bulk listings are in this run.

## Scientific replay limits

Read the listed original instructions and callers to assess the interpretation. No end-to-end acquisition execution, cold/hit experiment, native file service, archive decoder, mission loader or renderer run was performed. The accepted vehicle harness intercepts this acquisition entry; its resource authentication does not fill that gap. Reproduction requires the private licensed executable and private annotated GZF; this public run does not invent a downloadable baseline or asset source. The public snapshot can corroborate operations but differs in some annotations from v97.

For publication, stage/commit this run only and invoke the pinned-base `.github/scripts/pr_integrity.py` against its exact base/head and branch. The manifest lists every owned artifact with digest and byte size. The PR remains unmerged and does not promote these claims into `manual/reference/`.
