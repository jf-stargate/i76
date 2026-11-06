# Reproduction

Private inputs: the retail PE and v97 GZF in the manifest, authenticated `I76.ZFS`, installed `miss8/M06.MSN`, `miss8/M06.TER`, `miss8/M02.TER`, and `I76_CD1.ISO`. The CD's `MISSIONS/M02.MSN` is extracted privately and checked against its exact digest. Both TERs are independently byte-matched to the CD. Installed M02.MSN differs from CD metadata, so **the final reported second-mission experiment uses the exact CD MSN**, not the loose variant. The measured PE is the separately identified installed executable, not asserted equal to the CD executable.

Requirements: x86_64 Linux with i386 syscall/execution support; Ghidra 12.1.4/JDK >=21, Python3, gcc, GNU as/ld and 7z. Protocol checks additionally need jsonschema/PyYAML. Set RUN to this directory, ORIG to the private original-assets directory, GZF to the authenticated v97 export, HEADLESS to Ghidra support/analyzeHeadless, WORK to a private directory **outside the repository checkout**. Use absolute paths. Ghidra may require permission to initialize its user configuration; native i386 syscalls may be blocked by a sandbox and need explicit execution permission. Never publish the resulting private files.

```bash
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --orig "$ORIG" --gzf "$GZF" --private "$WORK" --run "$RUN"
python3 "$RUN/scripts/negative_controls.py" --private "$WORK" --orig "$ORIG" --gzf "$GZF" --run "$RUN"
```

The script verifies hashes, extracts exact CD M02 metadata, deterministically generates 167 cases per mission, compiles the accepted numerical service, imports a disposable GZF copy if needed, and runs static audit plus M06/M02/alias/bit12/fresh-emulator repeat sequentially in one read-only Ghidra process. Then it builds/runs the private native CPU shim for the four configurations and regenerates bounded public evidence and validation. A preexisting `research.gpr` in WORK is reused; use a new WORK for a fresh import. Do not concurrently process one project. Original source GZF and annotations are never edited.

Safe outputs: case records, sparse instructions, numerical summaries, digests and input/service ledgers. Unsafe/private outputs: mapped image, TER/MSN, GZF/projects, full trace/default/grid buffers and generated executables. JSON case files contain only bounded coordinate/word observations, not page payloads. `original_st0_le` is a 10-byte scalar, not a memory dump. Evidence regeneration is deterministic with this environment; private trace hashes are environment-specific anchors.

Verification alone (no original execution):

```bash
python3 "$RUN/scripts/verify_coordinates.py" --private "$WORK" --orig "$ORIG" --gzf "$GZF" --run "$RUN"
```

Add `--emit` only to regenerate this run's outputs before publication; never modify a merged run. This verifier checks 76,589 assertions; see `validation.json` for the exact count. It compares the entire 765,952-byte executable section and every privately audited instruction to the PE, authenticates inputs, all four initialized grids/default pages, native exact results, original corner addresses/words, class/admission and rounding restoration, normal limited checks, bit12 invariance and a fresh-emulator M06 repeat. `negative_controls.py` makes isolated private copies and proves corrupt sample addresses and CPU results are rejected.

Scientific validation and repository policy/CI are separate. Run the trusted baseline protocol validator and PR-integrity checks before publication; their results are in `evidence/policy_validation.json`. Do not self-merge or edit canonical documents.

Public-only consistency check (no licensed inputs needed):

```bash
python3 "$RUN/scripts/verify_public_cases.py"
```

This checks 18,364 relationships across all 668 published cases and the 488-case boundary subset. It verifies address/attribute decomposition, world coordinates, exact rational native results, both native float32 row stores, admission and rounded materials. It does not independently authenticate private source words.
