# Reproduction and validation

Use a licensed retail PE, the exact supplied v100 GZF, Python 3 standard library and Ghidra 12.1.4 PUBLIC. This run used OpenJDK 27-ea+34-1-Debian; the installed Ghidra declares Java >=21. Set `RUN` to this run directory and `PRIVATE` to a **new private, nonexistent directory**, outside the checkout used for publication. All Ghidra databases and complete captures remain private. The wrapper rejects an existing directory and verifies both input SHA-256 values before importing.

```bash
RUN=/path/to/checkout/agent/runs/i76exe/i76exe-20261103T183247Z-f97a49da
PRIVATE=/path/to/new-private-directory
python3 "$RUN/scripts/reproduce.py" \
  --headless /media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless \
  --gzf /path/to/i76exe_v100.gzf --exe /path/to/i76.exe --work "$PRIVATE"
python3 "$RUN/scripts/provenance.py" /path/to/i76.exe "$PRIVATE/pe.json" \
  --repo /path/to/checkout --base deaef41589671984c7e65010b2ecde351ad9ddf4
```

The wrapper imports into a disposable project with `-noanalysis`, then runs `TUInventory.java` twice with `-process i76exe_v100 -readOnly -noanalysis`. `TUValidate.java` separately hashes the four complete examined envelopes, including padding/tables and the last anchor's full body. The program's saved display name is `i76.exe`, while its imported project-domain name is `i76exe_v100`.

To regenerate evidence without editing this immutable run, copy the reviewed hypotheses to another private output directory:

```bash
mkdir "$PRIVATE/reviewed-evidence"
cp "$RUN/evidence/hypotheses.json" "$PRIVATE/reviewed-evidence/"
python3 "$RUN/scripts/analyze.py" --private "$PRIVATE" \
  --exe /path/to/i76.exe --gzf /path/to/i76exe_v100.gzf \
  --evidence "$PRIVATE/reviewed-evidence"
```

Hypotheses are human-reviewed inputs; the analyzer does not infer them or establish their correctness. Reports are authored interpretations of the resulting tables. `fresh_reproduction.json` records this run's second independent import and equality to the initial capture; a new replication creates its own wrapper `reproduction.json`. Disposable database-page hashes and incidental project housekeeping may differ between imports; original-body, inventory and detail digests should agree for these exact inputs/tool versions.

## Measured results

- 2,102 defined functions, 235 externals, 42 bounded defined entries; 43 bounded body ranges because the interpreter has two ranges.
- 100/100 factual checks: exact input identities, database counts, bounded coverage, each bounded entry/first decoded instruction, every bounded body hash against retail PE, four full-envelope hashes, repeated captures, unchanged modification counter and program page file, and the three callback pointer values.
- Private whole-inventory SHA-256 `69c4ed9690d108480df936d413bd6ae38a2bf0b40d195a3c13782d84d933ffcd`; bounded-plus-context private disassembly SHA-256 `90d2257237609ab75b628fc77b9b577709da28f5893a019514c6077b57359d16`. Metadata digest and envelope hashes are in the evidence.
- A fresh second import produced byte-identical inventory, detail and metadata; its own two captures also matched. This validates deterministic extraction for these inputs, not original TU ownership.
- Modification counter remained 3→3 for extraction and envelope audit. Disposable program page file remained SHA-256 `9a6b0157b0b21f1b1978b422d8207b0fd917565862eea011e80d74b155d979de`. Backup index `idata/~index.bak` changed and `idata/~journal.bak` disappeared as project housekeeping; the program content/pages did not change. No source GZF/GUI database mutation occurred.
- Six positive relationship reviews (P01–P06), four proposed separation pairs (B01/B06/B09/B10), and six negative/limiting examples (N01–N06) are recorded in the small original-instruction ledger. Each PC/reference was manually inspected. B02 also records a rejected semantic boundary. These reviews establish the cited instruction relationships, not verified original source membership.

## Private capture format and limitations

`inventory.jsonl` records each defined function's address/name, exact body ranges and hashes, size, predecessor/successor and gap, direct calls, outgoing data/control references with Ghidra R/W flags and strings, entry/interior incoming references, computed transfers and thunk targets. Incoming owner null preserves calls from instructions not owned by a defined function. `detail.jsonl` retains selected neighborhoods' instructions and references, not a bulk decompilation. `metadata.json` records program/executable identity and function counts. Neither full capture is published.

The extractor reads references attached to instructions; it does not solve pointer aliasing or propagate reads/writes through every indirect access. An indexed instruction may be labeled DATA (A), and string extents reflect existing Ghidra definitions. The original-byte checks authenticate the defined ranges and four complete envelopes, not the historical accuracy of every Ghidra function boundary. Defined entries are valid database entries and decode at their starts; original author symbol boundaries remain unknown. Thunks, tail branches, jump-table data and the interpreter's excluded interior bytes were preserved without reanalysis or annotation changes.

The run's accepted context consists of the pinned governance, subsystem indexes, promoted terrain/mission/resource references and their accepted semantic/original-instruction research. PR #111 content, scripts, evidence and conclusions were not read. The source-provenance search found no usable source filenames, so no independently verified compilation-unit boundary can be claimed. Trusted repository `integrity` additionally checks publication paths, schemas and hashes; it does not certify the hypotheses.
