# Complete private reproduction

Requires licensed retail PE/ZFS/v97 GZF and miss8 M06 MSN/TER, Ghidra12.1.4 with compatible JDK, Python3/jsonschema/PyYAML/liblzo2 and GNU C x86 x87. Use absolute paths and a new WORK directory outside the checkout. Original payloads and mutable projects remain private.

```bash
bash "$RUN/scripts/reproduce.sh" "$HEADLESS" "$EXE" "$GZF" "$ZFS" "$MSN" "$TER" "$WORK" "$REPO"
```

Driver first reproduces accepted #76 (including #74/#69) and #70 unchanged, then imports own fresh projects and runs five combined controls plus a fresh-GZF positive. Every individual case uses one original-instruction emulator. A zero headless exit is insufficient: the standalone verifier requires original returns, completion markers and exact provenance/record identities.

```bash
python3 "$RUN/scripts/verify_all.py" --work "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --emit "$WORK/derived"
```

This command has no Ghidra dependency and imports neither producer. Regenerated validation/results/opcodes must equal the published evidence byte-for-byte. Individual source/clip and typed queue/GEO verifiers are versioned; accepted predecessor resource extractor and x87 helper are immutable dependencies in the source checkout. Do not replace original resources or silently adjust expected results for different tools.

Trusted publication checks: protocol validate_protocol.py on the owned run, protocol unit tests, .github/tests and exact-candidate .github/scripts/pr_integrity.py from pinned trusted base. Manifest and validation equality plus complete SHA256/byte inventory are mandatory. Publish one run-only PR, require current-head GitHub integrity, leave unmerged.
