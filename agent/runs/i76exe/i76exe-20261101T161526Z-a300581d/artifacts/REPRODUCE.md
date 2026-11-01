# Reproduction and provenance

This is static semantic research plus a disposable Ghidra readability experiment. **No original-instruction execution**, full gameplay or new interpreter behavior test was performed. C compile checks validate layout arithmetic and syntax, not semantic equivalence.

Required private inputs:

- Original retail `i76.exe`: SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, MD5 `a640ea0097dbb62e0c77b7f2847c7161`.
- GZF `i76_mission_v97_verified_names.gzf`: SHA-256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`; imported program `i76_mission_v97_verified_names`. Measured from the supplied private file, not inferred from its name.
- Ghidra 12.1.4. This run used installed OpenJDK 27-ea (2026-09-15) and the system C compiler. No Ghidra distribution was edited.

Public inputs: repository at pinned base `8b16e9f81159c9f0f4dea63e16d69d79355b6d49`; exact source paths/digests are in `evidence/SOURCE_PROVENANCE.tsv`. v94 corpus counts are inherited from that checkpoint; game resources were not newly parsed for this pilot. No proprietary bytes, complete decompiler files, GZF or project are included in the run.

Set shell variables to your own locations. RUN is the absolute path of this run; PRIVATE is a new private output directory. First authenticate PE/GZF hashes above and use a **new** project for each experiment.

```bash
mkdir -p "$PRIVATE/project"
"$GHIDRA/support/analyzeHeadless" "$PRIVATE/project" research \
  -import "$GZF" -noanalysis -scriptPath "$RUN/scripts" \
  -postScript PilotBAnnotations.java "$PRIVATE/dry" DRY "$EXE"
```

For annotations, import the original GZF into a different fresh project and pass APPLY. The script intentionally refuses to overwrite its existing type, so do not reuse an applied project.

```bash
mkdir -p "$PRIVATE/applied-project"
"$GHIDRA/support/analyzeHeadless" "$PRIVATE/applied-project" research \
  -import "$GZF" -noanalysis -scriptPath "$RUN/scripts" \
  -postScript PilotBAnnotations.java "$PRIVATE/applied" APPLY "$EXE"
python3 "$RUN/scripts/verify_evidence.py" --repo "$REPO" --exe "$EXE" \
  --ghidra-output "$PRIVATE/applied" --output "$PRIVATE/BINARY_VERIFICATION.json"
cc -std=c11 -Wall -Wextra -Werror -pedantic -fsyntax-only "$RUN/artifacts/vm_architecture.c"
```

Ghidra's launcher may need permission to write its normal user preference/log directory. During this investigation that normal write required escalation; it did not authorize changes to other projects. Raw before/after files were kept in the run's sibling private workspace. The public metrics include hashes so a reviewer with the same baseline can compare them without republishing full proprietary pseudocode.

Read instruction anchors alongside the semantic report; byte matching authenticates the evidence, not its interpretation. For the trailing arguments, count every push between the stated call windows, account for register saves and temporary pushes when interpreting ESP offsets, then check cleanup (0x40 or 0x30). Host register-save footprint is 0x10 and interpreter footprint is 0x64. A zero consumer count does not prove an original developer intended no role.

The run is partially reproducible because GZF and retail PE are privately supplied prerequisites, and inherited corpus reports are not independently regenerated here. All run-owned scripts and original-authored sketches are public. No full runtime evidence is claimed.
