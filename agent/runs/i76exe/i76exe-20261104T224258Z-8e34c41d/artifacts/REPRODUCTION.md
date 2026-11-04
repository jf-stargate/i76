# Reproduction

Run-owned research scripts require Python 3.11+ standard library, system liblzo2 exposing safe X/Y APIs on Linux LP64, authenticated private game inputs, and Ghidra 12.1.4 headless with a working JDK. Recorded host/backend identities are in ../evidence/provenance.json. No proprietary inputs are downloadable from this public run.

From this run's directory, set the installation-specific paths and run:

```sh
python3 -B scripts/reproduce.py \
  --workspace /media/neon-remote/prj/i76 \
  --private-output /media/neon-remote/prj/i76/zfs-private/reproduce-new \
  --headless /media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless \
  --compare
```

The private output directory must be outside the public checkout. The workspace contains orig/i76.exe, orig/I76.ZFS, orig/I76.ZIX, scratch_data/i76exe_v100.gzf, zfs/resources and zfs/zfs_extract_manifest.json. The historical comparator is read from this checkout at scripts/game/i76_zfs_extract.py, not rewritten. The reproduction verifies all four original input identities before analysis and hashes them plus comparator/prior manifest before and after. It does not alter original files.

The script:

1. Runs 38 synthetic archive-reader tests and 12 analytical source-model tests. Runs six separately reported historical-comparator fixture comparisons.
2. Safely traverses every table/slot, decodes all 6,116 logical resources, resolves every normalized/case-varied key and compares bytes/hashes with all extracted files and historical decoder results. Writes complete inventory only to the private output directory.
3. Compares all installed ZIX keys/source ordinals with the archive.
4. Creates a new disposable Ghidra project, imports the supplied GZF with `-readOnly -noanalysis`, extracts 37 function audits plus the narrow callback range00470D30..00470ECD and path-token data privately, then verifies all extracted instruction bytes and full function-range hashes against PE sections. The original GZF is not a mutable project and is never saved.
5. Produces public-safe summaries with selected symbolic assembly, byte lengths/hashes and function-range identities; **no opcode bytes**. With --compare, requires exact structural equality to this run's corpus, ZIX, instruction, synthetic-result and historical-difference JSON artifacts.

The standalone reader can also be imported without any Ghidra dependency:

```python
from zfs_reader import Archive
archive = Archive.open(private_archive_path)
entry = archive.lookup(logical_name)
logical_bytes = archive.read_entry(entry)
archive.close()
# logical_bytes remains independently owned and usable.
```

It never extracts files to disk. `survey.py --archive ... --extracted ... --historical ... --private ... --summary ...` runs only the corpus phase, requiring outputs outside the checkout. Tests alone use `python3 -B -m unittest discover -s scripts -p 'test_*.py' -v`. To rerun PE authentication from an existing private audit use verify_evidence.py with --exe, --gzf, --audit, --ranges and --output.

Ghidra launcher writes its user JDK/configuration cache even in read-only program mode; the host sandbox may require permission for that environment access. Read-only refers to the imported program/GZF. A successful headless process is not enough: the script requires both output files, unchanged program modification number and exact executable/GZF identities. Failed imports must not be treated as validation.

The first complete import and a later fresh deterministic comparison both succeeded. See ../evidence/reproduction.json and synthetic_tests.txt. Original-instruction execution was not attempted. Output safety depends on the external safe decoder implementation; original algorithm selection depends on inspected instructions. Host-specific private paths and logs are not part of deterministic corpus/instruction equality. Regenerating the private inventory must reproduce the published canonical digest; never commit that inventory, the GZF, full audit or original payloads.
