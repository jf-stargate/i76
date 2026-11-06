# Reproduction

Requires licensed inputs matching manifest.json, Ghidra 12.1.4, a JDK supported by it (measured 27-ea+34), Python3, cc/x86-64 x87 and the accepted extraction script's liblzo2 dependency. Proprietary inputs, full traces and projects remain private.

From a checkout including the pinned main and this run, with absolute paths:

```
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --exe "$EXE" --gzf "$V100_GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --repo "$REPO" --work "$NEW_PRIVATE_DIRECTORY"
```

The work directory must not exist. This authenticates all input hashes, extracts the accepted 64 stock fixtures, compiles the narrow inherited x87 service, imports a new owned project, compares the entire retail executable section, executes all 20 scenarios and verifies predictions against original observations and published scenario summaries/trace hashes. `--cases primary contrast shade high` selects a shorter reproduction. `observe.py` can use the same owned project and private fixtures with --headless/--work/--msn/--ter/--cases; it is not permission to use another worker's mutable project.

Asset-free predictive review:

```
python3 "$RUN/scripts/check_public.py"
python3 agent/protocol/tools/validate_protocol.py "$RUN"
```

The four public fixtures contain derived edge/leaf relationships, view-space vertex numbers, projection constants and scalar light controls; they contain no executable, archive, complete camera dump or terrain payload. Predictions are recomputed, not a replay of emitted index lists.

Full observation mutation controls:

```
python3 "$RUN/scripts/check_corruptions.py" --cases "$PRIVATE/cases" --exe "$EXE" --out "$PRIVATE/corruptions.json"
```

The inherited unchanged #140 verify_context_v100.py can independently check this run's primary/contrast/below with the same argument names and its existing instruction anchors. Its version and manifest hash are pinned by merged #140; it is not copied or modified here. It reports 89,150 passing source/camera/clip/bin and corruption checks for these outputs.
