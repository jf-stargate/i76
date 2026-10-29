# Reproduce M-TER-01

Private required inputs are the exact retail PE, I76.ZFS, miss8/M06.MSN, miss8/M06.TER and annotated v97 GZF in `manifest.json`. Inputs and extracted fixtures must stay private. This run does not provision a license or distribute the GZF. Tools: Ghidra 12.1.4, Java >=21 (measured OpenJDK 27-ea+34), Python 3, liblzo2, gcc/x86_64 x87. Source scripts are in this run and accepted parent `agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8/` at base `81bc3b0c16dd93191e59a2d85de5d7b9ea77629e`. Parent manifest SHA checks in the runner reject altered dependencies.

Set SRC to a checkout containing this PR's run and unchanged accepted parent; RUN to this owned run; WORK to a fresh private writable directory outside the checkout. EXE/GZF/ZFS/MSN/TER identify authenticated files; HEADLESS is Ghidra's support/analyzeHeadless. Use absolute paths.

```bash
python3 "$RUN/scripts/replay.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER"
```

The runner verifies identities and parent artifacts, extracts fresh fixtures using the accepted preparer/extractor, compiles the accepted x87 helper with gcc -O2, imports a copied GZF into a new project, then executes all processes sequentially. It refuses an existing research.gpr to avoid reusing/mutating an old project. GZF import requires an adjacent lock; original databases are not touched. Do not run concurrent headless processes against the same project. Every processing command uses -readOnly -noanalysis. The command ledger and all logs remain in WORK.

It generates the exact five accepted baseline outputs (publish_bus, publish_bus_repeat, publish_gtsi, publish_slow, publish_raw) and four new outputs (control, lower, lower_repeat, raised). Each invocation starts a fresh emulator, while its 32 frames retain state. Ordinary tick increment is 16 ms, slow baseline 100 ms. Baseline raw intentionally omits the FISTP host correction while retaining the filter correction.

The new invocation pattern, after fixture/project/helper setup, is:

```bash
"$HEADLESS" "$WORK" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_TerrainPoseProbe.java "$WORK/fixtures" "$WORK/lower.tsv" bus 1 1 1 math-clock-pop-terrain-host-filter-registry "$MSN" "$TER" "$WORK/x87_fistp_service" 32 -0.25
```

For control use offset 0; lower_repeat uses -0.25 again in a separate invocation; raised uses +1. All other parameters must remain identical. Normal/material logging is additive. The original upright basis and X/Z are retained; no TER/ZMAP/material data is modified.

The runner finishes by invoking the comparator without --emit, checking this run's published derived files rather than overwriting them. To validate existing private outputs separately:

```bash
SOURCE_RUN="$SRC/agent/runs/i76exe/i76exe-20261028T174609Z-3f1f83f8"
python3 "$RUN/scripts/verify_pose.py" --run "$RUN" --source-run "$SOURCE_RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --x87-service "$WORK/x87_fistp_service"
```

Expected validation is 40,753/40,753 new checks plus nested 35,452/35,452 baseline checks. To independently regenerate the five safe derived evidence files, copy the run into a private scratch location and pass that copy as --run with --emit. Emission performs 40,748 checks; validation adds five published-file comparisons. Do not mutate the accepted run. Private .grid.bin pointer sidecars, raw traces, resources, binaries and Ghidra projects must not be published. Trace hashes describe this measured environment, not cross-version promises.

Expected first tire-mode-0 frames are 14/26/26/31, with special four-point EAX zero throughout. A different result must be investigated, not relabeled to match. Halt positive claims on unmapped/source-mismatched terrain reads, invalid state, missing original callback returns or unexplained numerical divergence. Normal comparison intentionally tolerates the original inverse-square-root approximation; it does not require a mathematically exact unit vector.

The final full replay procedure was exercised in a second fresh project; all nine trace files matched the primary execution byte-for-byte. Both projects were new private scratch; no accepted run, original binary or baseline was modified.
