# Reproduce privately

Prerequisites: licensed retail executable, exact v100 GZF, Ghidra 12.1.4, compatible Java, Python 3. No pip dependencies for extraction/analysis. Baseline hashes are in manifest.json. Never substitute a later or older GZF. All Java scripts are read-only, without mutation API calls. Use an isolated new project; never pass the maintainer GUI project.

From an owned run directory, set GHIDRA_HOME to the 12.1.4 installation, PRIVATE to a writable private directory, GZF and EXE to the verified input paths. Create PRIVATE/project first. Run:

```bash
"$GHIDRA_HOME/support/analyzeHeadless" "$PRIVATE/project" pilot -import "$GZF" -noanalysis
find "$PRIVATE/project" -type f -exec sha256sum '{}' + > "$PRIVATE/before.sha256"
"$GHIDRA_HOME/support/analyzeHeadless" "$PRIVATE/project" pilot -process i76exe_v100 -readOnly -noanalysis -scriptPath "$PWD/scripts" -postScript TuInventory.java "$PRIVATE/inventory.tsv" -postScript TuAudit.java "$PRIVATE/audit.txt" -postScript TuValidate.java "$EXE" "$PRIVATE/validation.txt"
sha256sum -c "$PRIVATE/before.sha256"
python3 scripts/analyze.py "$PRIVATE/inventory.tsv" "$PRIVATE/derived"
python3 scripts/provenance.py "$EXE"
```

Repeat inventory extraction and compare SHA-256 for determinism. Keep inventory.tsv, audit.txt, projects and complete logs private. Only the reviewed 42-function table, group metrics, minimal instruction anchors and metadata digest/results belong in public output. TuValidate checks 765525 retail .text bytes at VA 00401000 against executable offset 400; this is specific to this hashed binary.

The analyzed branch pins base deaef41589671984c7e65010b2ecde351ad9ddf4. Imported program name is i76exe_v100. Extraction reported 2102 defined/235 external functions. Audit walks bounded regions with limited flanks; this is not a whole-program instruction dump. Selected public anchors were manually reviewed in context with incoming references and data uses. Original filenames and source attribution are not validation assertions.

Schema and repository integrity validation uses the trusted base .github/scripts/pr_integrity.py against the run commit; this validator is not an analysis dependency. See validation.json for executed checks and SHA-256 of private evidence, which are integrity identifiers rather than downloadable payloads.
