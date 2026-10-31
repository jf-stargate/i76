# Exact reproduction

Use accepted main history including #69 and this run. Required: Ghidra 12.1.4, Java >=21 (measured OpenJDK 27-ea), Python 3 (measured 3.14), GNU C on x86_64 with x87, PyYAML/jsonschema for protocol checks. Licensed private PE, v97 annotated GZF, I76.ZFS, miss8/M06.MSN and M06.TER must match manifest identities. The GZF is copied before import. No comparison-branch checkout, old private emulator project or unmerged output is used.

All arguments must be absolute; WORK must not exist:

```bash
bash "$RUN/scripts/reproduce.sh" "$HEADLESS" "$EXE" "$GZF" "$ZFS" "$MSN" "$TER" "$WORK" "$SOURCE_REPO"
```

The driver first runs **unchanged accepted #69** including its complete standalone verification and fresh repeat. It then imports another fresh private project, compares executable bytes to PE, and executes primary/contrast/below transform controls, the untouched allocator baseline, arena-only and projected diagnostics, and alternate descriptor/header diagnostic. Primary source/transform verification runs before the walker cases. The projected positive repeats in another newly imported project. Ghidra exit zero alone is insufficient: complete sidecars/events are required by verification. Private config/cache live in WORK, never in published artifacts.

Standalone verification does not invoke Ghidra, load Java or construct geometry:

```bash
python3 "$RUN/scripts/verify_handoff.py" --private "$WORK/research" --repeat "$WORK/repeat" --msn "$MSN" --ter "$TER" --exe "$EXE" --negative-controls --emit "$WORK/derived"
```

It checks every tested source vertex/page/packed word, original source and transform writers, exact rounded transform, leaf/edge/candidate indices, emitted XYZ writes, original projection math, independent screen clipping, narrowly scoped CRT copy, original bucket mutation chronology, final chains, rejected controls and byte-identical repeat. Deliberate corruptions run separate failing verifier processes; parent counts three executed rejection assertions, without counting child partial checks as passed tests. Accepted #69's 105,139 checks and the protocol/CI unit checks are separate from the new standalone count.

Compare regenerated `derived/results.json` exactly with this run's `evidence/results.json`, and `derived/validation.json` with `validation.json` and `manifest.validation`. Regenerated trace hashes require these exact tools/fixtures. Private final traces/sidecars remain outside Git.

Trusted repository checks (run from SOURCE_REPO):

```bash
python3 agent/protocol/tools/validate_protocol.py "$RUN"
python3 -m unittest discover -s agent/protocol/tools -p test_protocol.py
python3 -m unittest discover -s .github/tests -p 'test_*.py'
python3 .github/scripts/pr_integrity.py --base-sha 3e10251444a117c8d9da053b6887245a2bc4dbcf --head-sha "$HEAD" --repo . --trusted-root . --branch "$BRANCH"
```

The immutable trusted files are unchanged from pinned base. Unit and PR checks do not prove scientific truth. Required integrity must pass for the published unchanged head; no merge is authorized.

Lineage: probe retains the accepted #69 loader, numerical services, source observer and fixture scaffold, extended only inside this new run. The independent Python verifier is authored for this transform/handoff investigation and does not import the producer. Host C service bytes are identical to #69. The accepted baseline is referenced from its immutable path, not rewritten or silently copied from another investigation.
