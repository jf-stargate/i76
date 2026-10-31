# Exact private fresh reproduction

Requires Ghidra 12.1.4, compatible JDK (measured OpenJDK 27-ea+34-1-Debian), Python 3 (measured 3.14), GNU C/x86_64 x87, liblzo2 and protocol dependencies PyYAML/jsonschema. Use the licensed PE, v97 annotated GZF, ZFS and M06 sidecars identified in the manifest. Source binaries, resource payloads, project databases and full audits/traces remain private.

Use this run's accepted history and absolute paths. WORK must not exist. The driver creates private config/cache and copies the GZF before importing; it never opens another worker's mutable project.

```bash
bash "$RUN/scripts/reproduce.sh" "$HEADLESS" "$EXE" "$GZF" "$ZFS" "$MSN" "$TER" "$WORK" "$SOURCE_REPO"
```

First the unchanged immutable #74 driver reproduces all accepted #69/#74 scenarios, independent checks, repeats and corruptions. Then the new driver extracts 64 authenticated vehicle fixtures with the unchanged accepted extractor, compiles the identical host numeric helper, imports a new project, audits original frame/projection/camera/arena bodies, executes primary/contrast/below in separate processes and repeats primary in another fresh import. Within each scene one emulator survives construction → projection → two callbacks → original M06 load → arena init → original terrain return.

A headless zero exit alone is insufficient. The standalone verifier requires every expected completion marker, source/output sidecar and state invariant. The driver compares regenerated results and validation to the published run and runs trusted protocol validation. Expected new standalone count: **89,114**, predecessor #69 105,139 and #74 209,140 separately. Different tools or bytes require investigation, not rewriting expected hashes.

Standalone command (no Java/Ghidra dependency):

```bash
python3 "$RUN/scripts/verify_context.py" --private "$WORK/cases" --repeat "$WORK/repeat/primary.tsv" --fixtures "$WORK/fixtures" --msn "$MSN" --ter "$TER" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --corruptions --emit "$WORK/derived"
python3 "$RUN/scripts/check_publication.py" "$RUN" "$WORK/derived"
```

Corruptions run separate verifier processes and require failure at the named source-height, camera-identity and emitter-source checks. Every source/transform record, six original frustum planes, depth/screen clip candidate and accepted bucket chain is independently checked. Main scientific data stay private; selected complete camera samples and one accepted record per valid case are bounded public review aids, not substitutes for full verification.

Trusted checks, executed from the isolated checkout whose policy/tool files equal the pinned base:

```bash
PYTHONDONTWRITEBYTECODE=1 python3 agent/protocol/tools/validate_protocol.py "$RUN"
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s agent/protocol/tools -p test_protocol.py
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s .github/tests -p 'test_*.py'
python3 .github/scripts/pr_integrity.py --base-sha 4de0c902628535fd91c3a5bd7b15b3af622d7ee8 --head-sha "$HEAD" --repo . --trusted-root . --branch "$BRANCH"
```

Only the new run may be in the PR diff. `validation.json`, regenerated standalone validation and `manifest.validation` must be equal. Artifact inventory/lengths/SHA-256 must be exact. Required GitHub `integrity` must pass for the actual current PR head; human acceptance and merge are separate and are not automated.
