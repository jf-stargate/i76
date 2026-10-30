# Fresh reproduction

Requires licensed private retail i76.exe, I76.ZFS, annotated v97 GZF; Ghidra 12.1.4, compatible Java (tested OpenJDK 27-ea), Python 3, liblzo2. Exact identities and all 64 fixture hashes are in evidence/results.json. No mission/MSN/TER input is used. Proprietary payloads must remain outside the checkout.

Check out original base d2072e673492b8fa72b268028890e6ef51dc2537 plus this run. Set absolute SRC (checkout), RUN (owned run), WORK (**nonexistent**, private directory outside SRC), HEADLESS (Ghidra support/analyzeHeadless), EXE, GZF, ZFS. Ghidra needs permission for its normal user configuration/compiler cache; use the host's normal approval mechanism if sandboxing denies it.

```bash
python3 "$RUN/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 "$RUN/scripts/verify_producer.py" --source-repo "$SRC" --run "$RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 -m unittest discover -s "$SRC/.github/tests" -v
```

The driver verifies the three private input hashes, invokes the immutable accepted extractor at agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/scripts/extract_private_fixtures.py with that run's evidence/retail_resource_digests.json, copies/imports the GZF into a new project, then executes four sequential separate read-only/noanalysis processes: visible, repeat, behind, empty. It rejects nonzero exit/ERROR and requires an explicit PRODUCER_COMPLETE event. Ghidra exit status alone is insufficient.

The verifier independently checks PE bytes, resource source identities, original writes and same-record ownership, typed transforms/frustum halfspaces, zero/culled controls, all work-bucket summaries, original cursor/table behavior, warning scope and byte-identical repeat. Expected final output: passed, test_count=196, passed_count=196. Trusted-base unit suite: 38/38. To regenerate reviewed derived JSON into the owned evidence directory, add --emit (194 scientific checks before the two exact-artifact comparisons); inspect the result before publication. No raw resource/database/full trace is public.

The test invokes each original entrypoint explicitly. It preserves a single emulator state from original construction/registration/projection/arena through producer within each case, but does not run a live frame or consumer. A prior unsuccessful sandbox import and development probes are private diagnostics, not additional publication runs. The final complete replay used a fresh independent project; full reproduction is independent of those diagnostics.
