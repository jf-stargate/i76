# Reproduction

Use the pinned source base and this run's versioned scripts. Private prerequisites: authenticated orig/i76.exe, scratch_data/i76exe_v100.gzf, original I76.ZFS and extracted resources under zfs/resources. The driver independently rereads the three selected ACTs from authenticated ZFS records through the accepted extractor and verifies the #133 corpus hashes. Generated tables and imports/traces remain private. Do not commit them.

Tested environment: Linux x86-64 with executable32-bit compatibility, gcc16, `/lib/ld-linux.so.2`, `/usr/lib32/libc.so.6` and `/usr/lib32/libm.so.6`, Ghidra12.1.4/JDK27-ea. Exact observed runtime/library digests are recorded in results.json; exact compiler version is in environment.json. The C runner intentionally avoids32-bit development headers/start files and provides its own ELF32 entry point. It links the identified runtime libraries. Other libm builds may change conditional gamma hashes, which is a result to identify, not silently accept as retail parity.

From the isolated repository root, set RUN to this new run's path and ROOT to the private installation root. Select a nonexistent WORK directory outside the repository worktree:

```
RUN=agent/runs/i76exe/i76exe-20261105T021647Z-1b2aac18
PYTHONDONTWRITEBYTECODE=1 python3 "$RUN/scripts/reproduce.py" \
  --root "$ROOT" --repo "$PWD" \
  --exe "$ROOT/orig/i76.exe" \
  --gzf "$ROOT/scratch_data/i76exe_v100.gzf" \
  --headless /path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless \
  --work "$WORK"
```

The driver authenticates inputs, compiles native.c, creates six selected palettes, executes20 native cases, checks every LUM conversion/output, checks independent C outputs, validates all gamma service inputs and post-service arithmetic with exact rationals, imports a fresh private GZF without reanalysis, runs curated static/unserviced-import probes, executes four full Ghidra cases, runs the fixed-replay CW control, and executes10 standalone tests. Ghidra uses read-only project processing. The input EXE/GZF digests are checked again afterward. No maintained repository files or existing runs need be written. On hosts with sandboxed ELF32 calls or Ghidra configuration writes, obtain the environment's required execution permission; do not bypass it.

Expected positive Ghidra cases are permuted/ties/m05 atCW037F; every byte and every power operand matches native. The PC24 case intentionally records2,556 power-input mismatches: its mode-specific replay can conceal final-byte differences, so it is a negative precision control. Fixed-PC64 replay gives the same gamma under emulatedCW037F/007F; actual native modes differ. Unserviced imports intentionally fail after successful original thunk execution. These are expected bounded controls, not overall experiment failures.

Public-only tests require Python3 and no proprietary inputs:

```
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover \
  -s "$RUN/scripts" -p test_model.py -v
```

`model.py` generates synthetic tables independently with rational arithmetic. Standalone fixtures distinguish row/column generation, cache history, first ties, gamma integer thresholds and missing spill precision. Native library/CRT-dependent outputs require the private experiment; no public test pretends to execute MSVCRT.

`scripts/collect.py PRIVATE_WORK INSTALL_ROOT` curates only metadata into this owned run; it never copies runtime/resource payloads. `scripts/package.py` regenerates artifact digests and schema records. These are authoring tools; do not use them to mutate a merged run. Reproduction should compare newly generated private results to the immutable published JSON, not overwrite accepted evidence. Re-run trusted protocol/hash validation and exact-head integrity before publication. The PR is for human review and must not be self-merged.
