# Reproduce M-RND-10

Use a checkout containing this run as SRC, an unused private directory as WORK, licensed EXE/ZFS and annotated GZF paths, and Ghidra 12.1.4 PUBLIC analyzeHeadless as HEADLESS. Source inputs are authenticated before execution. No original payload is published.

```bash
python3 "$SRC/agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
```

The driver runs PR77's full reproduction unchanged in WORK/baseline77, including original numeric failure, native raster bytes, predecessor source/command/span verification and all inherited controls. Then it extracts/authenticates m02.act, runs raw failure, resource-backed positive and guarded missing-input cases, imports a separate fresh GZF and repeats the positive. It requires exact full trace/framebuffer/guard equality. It audits original instructions from the fresh GZF and runs the standalone verifier. Ghidra can return shell status zero for script errors; the driver checks exact scientific markers and SCRIPT ERROR text. XDG config/cache are private writable paths. Raw and missing cases are expected script exceptions, not concealed tooling failures.

```bash
python3 "$SRC/agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/verify_palette.py" --trace "$WORK/positive.tsv" --palette "$WORK/fixtures/m02.act" --exe "$EXE" --audit "$WORK/opcodes.tsv" --baseline "$WORK/baseline77/diagnostic.tsv"
python3 "$SRC/agent/runs/i76exe/i76exe-20261031T161016Z-2f47de0e/scripts/audit_inputs.py" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --out "$WORK/input_provenance.json"
```

The first command is independent of Ghidra and the Java probe, and requires corruption rejection. The second parses retail PE imports and constants directly and authenticates all three input digests. Versioned summarize_evidence.py creates bounded public measurements from WORK; it does not copy source palette, full framebuffer or GZF payloads. It was executed separately during assembly. Full private traces and image buffers remain private.

Completed final execution used /media/neon-remote/prj/i76/mrnd10-private/final. Earlier baseline77 and explore directories retain exploratory and failed experiments; they are not rewritten as final output. Resume history uses one run/branch only. A full final driver execution passed after bounded exploration; publication assembly and input audit were separate commands.

Publication preflight uses the unchanged trusted code at base 6d151459f92b75aaadd5221dc8edd8e4776651ff: protocol validator, .github/tests (38 tests), protocol tests (11), and .github/scripts/pr_integrity.py against the complete exact proposed commit SHA, --repo SRC --trusted-root TRUSTED --base-sha 6d151459f92b75aaadd5221dc8edd8e4776651ff --head-sha HEAD --branch agent/i76exe/i76exe-20261031T161016Z-2f47de0e. Manifest.validation must equal standalone validation.json. Final GitHub required integrity is checked on the published head; the PR is left unmerged.
