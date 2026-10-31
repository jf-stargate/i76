# Reproduce bounded original raster output

Use a checkout containing this run as `SRC`; use a *nonexistent* private directory as `WORK`. Locate the licensed `i76.exe`, `I76.ZFS`, annotated `i76_mission_v97_verified_names.gzf`, and Ghidra 12.1.4 PUBLIC `analyzeHeadless`. The driver authenticates all three private inputs against the manifest before any experiment.

```bash
python3 "$SRC/agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
```

This first runs PR #75's entire accepted reproduction **unchanged** in `$WORK/baseline`, including its inherited source/projection, native draw/span, behind-camera, fresh-import and corruption controls. Only after it succeeds does the run-owned probe execute: unserviced original heap init, original surface constructor plus original palette-producer failure, positive diagnostic, X-offset variation, behind-camera, absent-surface and fresh-GZF positive repeat. Expected blockers are exact: `000C0FE2` for raw `HeapCreate`, `000C0BFC` for original palette float-to-integer, and guarded first destination read `0047CC25` for absent surface. Ghidra may return shell status zero for a script exception; the driver checks exact trace markers and script error text instead of using process status as scientific success.

The driver checks complete diagnostic/fresh trace and framebuffer byte equality, audits GZF instruction bytes, then runs the independent verifier. The latter requires 3,593 positive assertions plus three rejected corruption cases; its mutation-attempt assertion count is reported separately. Private `.tsv` traces and `.tsv.frame` buffers stay under `WORK`; they are never committed. The versioned `summarize_evidence.py` was used during run assembly to publish only bounded derived records and hashes. Ordinary reproduction does not rewrite immutable run artifacts.

The verifier can also be invoked independently after reproduction:

```bash
python3 "$SRC/agent/runs/i76exe/i76exe-20261031T015115Z-8ced0808/scripts/verify_raster.py" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --corruptions
```

The verifier does not invoke Ghidra or import the Java probe. It reads the regenerated accepted PR #75 span trace and new private output, authenticates retail instruction bytes, independently checks source linkage, all 210 destination addresses, table lookups, writer chronology, complete surface bytes and guards. Its three corruption controls alter a writer destination, framebuffer base or output value; each must fail. Public `evidence/` includes all primary byte changes and read-register chronology, command/span and field evidence, but never source EXE/ZFS/GZF or a full framebuffer dump.

Trusted publication preflight uses exact pinned main `f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019`, protocol 1.0.4 and the candidate head. Run the trusted protocol validator, `.github/tests` unit suite and `.github/scripts/pr_integrity.py` with `--repo "$SRC" --trusted-root "$TRUSTED" --base-sha f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019 --head-sha "$HEAD" --branch agent/i76exe/i76exe-20261031T015115Z-8ced0808`. After PR publication, verify GitHub's required `integrity` result on that exact head. Leave the PR unmerged.
