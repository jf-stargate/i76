# Reproduction

Use Ghidra 12.1.4, Java >=21 (measured OpenJDK 27-ea), Python 3, liblzo2, licensed retail i76.exe/I76.ZFS and the private annotated v97 GZF identified in manifest.json. Never upload these private inputs. Repository shell networking was unavailable here; GitHub connector reads/writes were used. The shared checkout and configured scratch under /media were read-only, so analysis used isolated `/home/z/i76-research/` outside the public repository. Ghidra imported a private copied GZF and all later processing used `-readOnly -noanalysis`; original databases and names were unchanged.

Let SRC be a checkout of the pinned main, RUN this run directory, WORK a writable private scratch, HEADLESS Ghidra's support/analyzeHeadless, EXE/GZF/ZFS the private files. Set absolute paths. Copy GZF to WORK before import: packed GZF import needs an adjacent lock. The transient /var/tmp Ghidra-cache warning in this environment did not prevent import or scripts.

Extract resources using the accepted script, unchanged:

```bash
python3 "$SRC/agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/scripts/extract_private_fixtures.py" --zfs "$ZFS" --out "$WORK/fixtures" --metadata "$SRC/agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/retail_resource_digests.json"
"$HEADLESS" "$WORK" research -import "$WORK/i76_mission_v97_verified_names.gzf" -noanalysis
```

Original timer sweep (output is safe derived data):

```bash
"$HEADLESS" "$WORK" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_TimerSubdivisionProbe.java "$WORK/subdivision.tsv"
```

Replay: final arguments are vehicle, selected=1, native-root=1, native-registry=1, mode. Run each invocation against the same read-only baseline; each script creates a fresh emulator. Generate `final_legacy.tsv` (bus/legacy), `final_math.tsv` (bus/math), `final_math_repeat.tsv` (bus/math), `final_gtsi_math.tsv` (gtsi/math), `final_pop.tsv` (bus/pop), `final_contact.tsv` (bus/math-clock-pop-contact). Example:

```bash
"$HEADLESS" "$WORK" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_FramePhysicsProbe.java "$WORK/fixtures" "$WORK/final_math.tsv" bus 1 1 1 math
```

The contact mode deliberately records EXPECTED_TERRAIN_PREREQUISITE_STOP and exits the scenario at original 00493550. It is not a failed assertion or a completed ground-contact frame. The pop mode changes only integer-conversion x87 consumption; math mode executes original 00493C50. Clock mode executes original 0049C7F0, 0049CBE0, 0049C920 with substituted GetTickCount; it does not inject the reciprocal table or frame delta.

Static audit writes private full decompilation/instruction output (do not publish it):

```bash
"$HEADLESS" "$WORK" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_FrameScheduleAudit.java "$WORK/audit.txt" 00493c50 00495000 00494710 00493da0 0049cbe0 0049cc20 0049cca0 00463120 00463800 0043bdf0 00438fd0 00440740 0043a5d0 004935aa
python3 "$RUN/scripts/verify_frame_initialization.py" --run "$RUN" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --private-traces "$WORK"
```

Verifier checks identities, sparse PE opcodes/direct call targets, descriptor words, all timer cases, source-to-public filtered events, all Gram products, exact independent repeat and guarded positive-time entry. Published private hashes are environment-specific replay anchors, not portable promises across emulator versions. Raw private traces and full dumps are deliberately excluded. `evidence/provenance.json` records resource and replay digests.

Harness lineage: I76_FramePhysicsProbe.java derives from PR #49's I76_MovingVehicleTwoFrameProbe.java at its exact head and SHA-256 listed in provenance.json. It is copied into this owned run for standalone continuation, not executed from or written into another agent's branch. The existing source is candidate infrastructure; the observations here were independently rerun. No engine implementation is introduced.
