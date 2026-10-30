# Reproduce the bounded selected-initialization run

Requires licensed private retail i76.exe, I76.ZFS, miss8 M06.MSN/M06.TER, annotated v97 GZF and STRLKUP.DLL; Ghidra 12.1.4, Java >=21, Python 3, liblzo2, gcc and x86_64 x87. Input identities are in the manifest/results. STRLKUP.DLL is hashed and independently PE-parsed, not loaded as a successful lookup service. The original lang.txt startup is a statically validated future dependency.

Check out base `980037f49b348e14ccdde8ba2961174a8647f090` plus this run. Set absolute paths SRC (checkout), RUN (this run), WORK (**nonexistent**, private directory), HEADLESS, EXE/GZF/ZFS/MSN/TER/STRLKUP (licensed inputs).

```bash
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --source-repo "$SRC" --work "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --strlkup "$STRLKUP"
python3 "$RUN/scripts/verify_selected.py" --run "$RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --strlkup "$STRLKUP"
```

The driver reuses the immutable accepted construction extractor, adds authentic support resources and ZSWLS101.TMT, builds the hardware numerical service and separate native oracle, copies/imports the GZF into a new project and uses eight sequential separate read-only/noanalysis processes. It does not mutate the source database or accepted runs. Ghidra configuration/compiler cache may require host permission. Headless exit status alone is insufficient: expected diagnostic logs are checked. Raw proprietary fixtures, complete traces, logs, grid sidecars, project and compiled helpers stay private.

| Case | Original-entry purpose | Expected result |
|---|---|---|
| pending_bus | selected original `00461B80` | six init returns, exact localization stop |
| pending_repeat | independent identical selected process | full trace byte-identical |
| pending_unselected | unselected lifecycle control | same dependency stop |
| peripheral | native class-list owners, original init then post | class31/34 return, no new invalid memory reads |
| noinit | omit both original peripheral initializers | raw posts return **with invalid reads**, negative only |
| postcontrol | direct entire class1 init then selected post | both return; original status predicate true |
| x87 | original `0049D400` with hardware instruction boundaries | 28 pairs equal independent native oracle bit-for-bit |
| rawx87 | same original helper without bridge | expected FSINCOS/fcos P-code stop at `0049D409` |

The source exposes legacy modes for provenance, but only these driver cases support findings. No controls are written at runtime+E4/+104/+AC. The frame loop is not reached by any final lifecycle control.

Verifier independently parses PE sections/imports/exports/opcodes and startup localization sequence, checks original pending→class-node→owner provenance, descriptor targets and return order, validates positive/negative peripheral state and memory warnings, selected class1 transitions, 28 bitwise oracle comparisons and separate trace repeat. `--emit` regenerates three reviewed evidence files in a **copy** of the run (156 checks); ordinary verification compares them exactly (159 checks). Toolchain-dependent raw hashes are anchors, not cross-version promises. Hash evidence/scripts and run trusted-base protocol/integrity inspection before proposing publication. Do not modify this run after acceptance; corrections require a new run.
