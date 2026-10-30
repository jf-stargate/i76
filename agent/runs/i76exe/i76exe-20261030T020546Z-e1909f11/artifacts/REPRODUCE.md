# Fresh-project reproduction

Prerequisites: licensed private retail `i76.exe` and `I76.ZFS`, the annotated v97 GZF identified in `manifest.json`, Ghidra 12.1.4, a compatible JDK (measured OpenJDK 27-ea+34-1-Debian), Python 3 and liblzo2. Nothing below uploads proprietary inputs. Use two **new** private projects, not another worker's open project. Preserve accepted source GZF; processing is read-only after import. Ghidra requires writable user configuration/cache and a writable directory beside a copied GZF for its lock. In this managed environment headless launch required sandbox approval for its user configuration; no protected baseline was modified.

Set absolute paths for a checkout containing this run (`SRC`), private scratch (`WORK`), the headless launcher (`HEADLESS`), original inputs (`EXE`, `ZFS`, `GZF`). `SRC` must include original pinned base `d2072e673492b8fa72b268028890e6ef51dc2537`. Set `RUN` to this run. Example shell setup, substituting your input locations:

```bash
SRC=/absolute/path/to/checkout
RUN="$SRC/agent/runs/i76exe/i76exe-20261030T020546Z-e1909f11"
WORK=/absolute/path/to/new-private-scratch
HEADLESS=/absolute/path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
EXE=/private/path/i76.exe
ZFS=/private/path/I76.ZFS
GZF=/private/path/i76_mission_v97_verified_names.gzf
mkdir -p "$WORK/project" "$WORK/repeat"
sha256sum "$EXE" "$ZFS" "$GZF"
cp "$GZF" "$WORK/project/i76_mission_v97_verified_names.gzf"
cp "$GZF" "$WORK/repeat/i76_mission_v97_verified_names.gzf"
python3 "$SRC/agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/scripts/extract_private_fixtures.py" --zfs "$ZFS" --out "$WORK/fixtures" --metadata "$SRC/agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/evidence/retail_resource_digests.json"
"$HEADLESS" "$WORK/project" research -import "$WORK/project/i76_mission_v97_verified_names.gzf" -noanalysis
```

Confirm the three source hashes against manifest before executing probes. The extractor is unchanged accepted main code; its exact SHA-256 and every resulting fixture digest are recorded in `evidence/provenance.json`. It extracts 11 top-level resources and 53 GEO/TMT resources; do not add other files to the fixture directory (the probe intentionally loads its sorted contents).

The three `1` arguments retain scaffold calling compatibility: selected, native-root, native-registry. This new probe always requires/uses that positive construction configuration and controls its own negative cases after construction; changing those arguments does not create a different construction scenario. `all` executes bus persistent, reset, zero, guard, coldB and stationary, each using a fresh emulator. All calls within each scenario share one emulator. Output prefix `final_bus` gains `_<mode>.tsv`:

```bash
"$HEADLESS" "$WORK/project" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_CameraContinuityProbe.java "$WORK/fixtures" "$WORK/final_bus" bus 1 1 1 all
"$HEADLESS" "$WORK/project" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_CameraContinuityProbe.java "$WORK/fixtures" "$WORK/final_gtsi.tsv" gtsi 1 1 1 persistent
"$HEADLESS" "$WORK/repeat" research -import "$WORK/repeat/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$RUN/scripts" -postScript I76_CameraContinuityProbe.java "$WORK/fixtures" "$WORK/repeat/bus" bus 1 1 1 persistent
```

Each scenario must log the original math initializer return, original VCF/world registration, projection init, expected number of CAMERA_RETURN events at sentinel `70000000`, and complete before/after samples. The callback runs through its epilogue and RET, rather than stopping merely at `00406DF4`. Guard control also returns normally, with zero changed-state events. Zero-basis control returns normally with NaN view fields; this is an expected negative outcome.

Standalone verification has two levels:

```bash
python3 "$RUN/scripts/verify_continuity.py" --run "$RUN"
python3 "$RUN/scripts/verify_continuity.py" --run "$RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
```

Public-only verifies byte chronology, typed numerical identities, controls and repeat events from the published bounded records. Full verification additionally checks the private trace-to-public allowlist, source identities, PE instruction anchors, fixture hashes, full private byte-identical repeat and measured probe digest. At the measured environment the full verifier passes **9,457 assertions**. Counts are assertions, not a completion percentage. `--emit` deterministically regenerates only `camera_events.tsv` and `numerics.json` from the named private traces before checking them; use a disposable copy of the run when regenerating, never mutate an accepted immutable run.

To inspect the private original source audit, including the callback that has no Ghidra function definition, without creating functions or changing symbols:

```bash
"$HEADLESS" "$WORK/repeat" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_CameraSourceAudit.java "$WORK/audit_final.txt" 00405970 00437f90 00472400 00472990 00472d30 00472c10 00493c50 00495000 0049c7a0 0049c8b0 00458cb0 00494e20 00494f70 0045ebd0 004572b0 004ad6f0
```

Keep audit output and full raw traces private: they contain full original disassembly/decompilation and construction details. The public event trace is a bounded allowlist of experiment-produced state. Sparse public opcode bytes are independently checked against the PE. If another Ghidra/JDK version changes byte-identical output, investigate and record the difference; do not silently rewrite expected hashes to force a pass. Numerical tolerances in the verifier are explicit and do not stand in for hardware x87 validation.

Known construction warnings at `00438340` (x87 registers) and `004461E0` (optional geometry key) remain. They do not prevent these bounded returns; they limit broader correctness claims. No selected-player post, physics tick, scheduler, queue producer or renderer replay is required or demonstrated by these commands.
