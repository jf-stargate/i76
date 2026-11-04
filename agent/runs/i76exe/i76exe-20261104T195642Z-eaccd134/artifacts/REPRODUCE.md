# Reproduction and publication boundary

Requirements: Python 3 standard library for the reader/tests. Corpus comparison
also uses the two pinned historical scripts and system liblzo2, accessed through
the historical extractor. Original EXE, v100 GZF and base-game ZFS/extracted
resource root remain private. Ghidra 12.1.4 is required for a fresh instruction
extraction; no installation/download is performed.

From this checkout, substitute the actual run directory for `$RUN`:

```sh
python3 -B "$RUN/scripts/test_pix_reader.py"
python3 -B "$RUN/scripts/reproduce.py" \
  --workspace /media/neon-remote/prj/i76 \
  --private-output /media/neon-remote/prj/i76/pix-pak-private/fresh-reproduction \
  --headless /media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
```

`reproduce.py` makes a fresh disposable private Ghidra project, imports the GZF
with `-readOnly -noanalysis`, and executes the run-owned read-only audit script.
It compares all instruction bytes/range hashes to original PE bytes, regenerates
aggregate corpus/example checks, checks exact deterministic public JSON results
(excluding Ghidra's session-specific modification number), and hashes EXE/GZF/ZFS
and historical scripts before/after. Outputs contain private details and must
stay outside the public checkout. Alternatively `--audit /private/audit.json`
reuses a previous private extraction and reports that it did so.

The reader itself can report selected metadata and hash without exporting bytes:

```sh
python3 -B "$RUN/scripts/pix_reader.py" \
  /media/neon-remote/prj/i76/zfs/resources/a1flag1g.pix A11_FLG1.GEO
```

`inspect_corpus.py` emits only aggregate statistics and ten reviewed entries.
Its optional `--private-details` includes per-file identities/ranges; never
commit that output. `validate_examples.py` independently seek/reads every span,
compares reader bytes, tests a top-level CBK, and reconciles ten selected assets
through the historical vehicle resolver. `verify_instructions.py` emits only
reviewed instruction windows and function-body digests, not full decompilation.

Private analysis did not alter accepted GZF annotations or original bytes.
`reproduction.json` records fresh-run input identities and checks; `validation.json`
records test groups. Protocol/integrity validate the Git object diff separately.
No Windows/retail execution, full source-selection harness, or original-resource
export was performed. These limitations are part of the specification.
