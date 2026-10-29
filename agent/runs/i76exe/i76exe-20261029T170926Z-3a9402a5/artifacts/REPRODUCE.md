# Reproduce M-ENG-01

Requirements: licensed private retail `i76.exe`, `I76.ZFS`, miss8 `M06.MSN`/`M06.TER`, annotated `i76_mission_v97_verified_names.gzf`; Ghidra 12.1.4, Java >=21 (measured OpenJDK 27-ea), Python 3, liblzo2, gcc and x86_64 x87. Manifest and `evidence/results.json` identify every input. Do not commit private inputs, project databases, helper executables, grid sidecars, full traces or logs.

Check out original base `9312486b92f15305d814c2bf0551f3cf1e233f48` plus this owned run. Set absolute paths: SRC checkout, RUN owned run, WORK a **nonexistent** private scratch directory under `/media/neon-remote/prj/i76`, HEADLESS Ghidra's `support/analyzeHeadless`, EXE/GZF/ZFS/MSN/TER authenticated private inputs.

```bash
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --source-repo "$SRC" --work "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER"
python3 "$RUN/scripts/verify_schedule.py" --run "$RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER"
```

The driver refuses an existing WORK, extracts fixtures using the accepted construction-run extractor, compiles the x87 service, copies/imports GZF into a new `research` project, and runs five **separate sequential** headless processes. All processing is `-readOnly -noanalysis`; no source GZF/project mutation. It checks logs because headless exit code alone does not reliably signal script errors. Ghidra may need permission to write its configuration/Java compilation cache; source databases and canonical reference files need no writes. This host required configuration-cache access beyond the filesystem sandbox.

| Output | Vehicle | selected | Mode suffix | Frames | Expected |
|---|---|---:|---|---:|---|
| bus.tsv | bus | 0 | none | 3 | both dispatchers return |
| gtsi.tsv | gtsi | 0 | none | 3 | both dispatchers return |
| direct_bus.tsv | bus | 0 | `-direct` | 3 | direct callback control |
| bus_repeat.tsv | bus | 0 | none | 3 | byte-identical bus repeat |
| diagnostic.tsv | bus | 1 | `-diagnostic` | 1 | expected post FSINCOS/P-code blocker |

Base mode is `math-clock-pop-terrain-host-filter-registry`. Each scenario executes the empty-collection control before construction. Final source is `I76_DescriptorScheduleProbe.java`; no other run's Java source is edited. Direct mode is control-only. Diagnostic mode retains raw peripheral callbacks and suppresses the post-phase trig substitute, producing the recorded incomplete state and unsupported P-code stop. It is **not a passing raw selected-post execution**.

To independently regenerate safe derived output into another copy of this run directory, add `--emit` to the verifier. It writes only `evidence/instruction_anchors.tsv`, `dispatch_events.tsv`, and `results.json`. Without `--emit`, all three regenerated outputs must equal the published records. Measured final verification: 3,807 checks; emit: 3,804. Ghidra raw traces/hashes are environment-specific anchors, not promises across emulator/toolchain revisions.

The verifier reads the PE section table independently, checks fixed expected opcodes and descriptor targets, follows event chronology and original list provenance, compares typed state/Gram matrices and authentic terrain read words, and checks exact independent repeat/direct-control state. It does not certify every x87 operation or selected callback service. The inherited C helper delegates only sampler FISTP and filter FCOS instruction boundaries; Java trig/ftol remain declared services.

After artifact publication, validate run records with trusted base tooling:

```bash
python3 "$SRC/agent/protocol/tools/validate_protocol.py" "$RUN"
```

PR `integrity` must run from protected-base policy. Passing local scientific checks or CI does not promote findings or authorize a merge.
