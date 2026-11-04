# Reproduction and evidence limits

From the pinned repository commit, run the following with the private inputs and a **new** private directory:

```sh
python3 RUN/scripts/reproduce.py --root /private/installation-workspace --repo /checkout --exe /private/orig/i76.exe --gzf /private/i76exe_v100.gzf --work /private/new-color-audit --headless /path/to/ghidra/support/analyzeHeadless
```

RUN is this run directory. The installation workspace must contain orig/I76.ZFS, orig/miss8, orig/miss16, orig/ADDON, and authenticated extracted files zfs/resources. The pinned accepted ZFS reader requires liblzo2. Ghidra12.1.4 needs writable Java configuration/cache; the filesystem sandbox may require explicit escalation for that configuration. No original instruction emulation or native game execution occurs.

The script checks exact EXE/GZF SHA-256, runs the11 synthetic unittest methods, authenticates selected resources, imports GZF without reanalysis into a new disposable project, repeats all12 export requests read-only, validates instruction bytes/body ranges against raw PE, reads descriptor words/constants directly from the PE, and hashes saved program files before/after. Whole-function exports/decompilations remain private. It writes derived metadata into private metadata/ only, never mutating this public run. Reanalysis, annotation updates, types, labels, instructions and transactions are not created by either Java script.

Fresh reproduction passed in this session. evidence/reproduction.json records counts and saved-program hashes; original EXE/GZF hashes were unchanged. evidence/synthetic_tests.txt is the complete synthetic test log. Only curated instruction selections are public; byte-validation hashes for larger private exports do not imply every instruction in those bodies received a complete semantic interpretation.

To reproduce the whole-listing immediate scan, ColorScan.java records instruction operands equal to0x404,005DD2C4 or within the TBL range. ColorAudit.java also enumerates original references to every byte of runtime palette/table ranges and backend descriptors. evidence/table_references.json is the reviewed table-range subset from the investigation exports; some propagated references are duplicate or conditional. It is a discovery inventory, not arbitrary-pointer dataflow closure.

No proprietary resource data, complete instruction/decompilation export, GZF/project database, credentials, native output pixels or screenshots are published. Missing-resource, null-LUM arithmetic, imported power/rounding, external plugin, and complete renderer-dispatch limits remain explicit. Human acceptance of the research PR does not automatically promote these claims into canonical documentation.
