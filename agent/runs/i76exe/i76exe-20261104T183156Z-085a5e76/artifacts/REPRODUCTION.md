# Reproduction and publication boundary

Run `i76exe-20261104T183156Z-085a5e76` owns only its new run directory; base `7406234ef017a3fbb3539f2cc29cfd9e601dddbd` was independently fetched from GitHub main. Live ruleset25664125 requires PR+integrity and resolved review threads, with zero formal reviews. Human merge only. PR#125 was already merged at bootstrap; no open PRs were returned. The shared remote checkout's pre-existing reconstruction/build directory was untouched.

Verified private sources:

- `/media/neon-remote/prj/i76/orig/i76.exe`: SHA-256 bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3; MD5 in manifest.
- `/media/neon-remote/prj/i76/scratch_data/i76exe_v100.gzf`: SHA-256 f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0.
- Original mission roots `/media/neon-remote/prj/i76/orig/miss8` and `orig/miss16`; all 80 specimen MD5/SHA-256/lengths are in evidence/corpus.json. They are unpacked files from the user's private installation; no archive provenance beyond those measured files is asserted.
- `/media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless`; disposable project `/media/neon-remote/prj/i76/wrld-private/project/research`, domain file `i76exe_v100`, internal program name `i76.exe`. Reanalysis disabled. Initial import saves only the disposable copy; later exports/verification use -readOnly -noanalysis. Scripts never create instructions, labels, annotations, types or data.

From the repository root, replace RUN with this run's path and PRIVATE_WORK with a new directory outside the public run:

```sh
python3 RUN/scripts/reproduce.py --exe /private/orig/i76.exe --gzf /private/i76exe_v100.gzf --corpus-root /private/orig --work PRIVATE_WORK
```

Append `--headless /path/to/ghidra/support/analyzeHeadless` to repeat GZF import, read-only targeted export, byte comparison and cross-reference inventory. Java/Ghidra may need writable per-user configuration/cache. The script authenticates both inputs first, refuses to reuse an existing project, and keeps complete private exports outside the run. It never saves changes to the original GZF. Full private decompilations/corpus bytes are intentionally excluded from publication; reviewed instruction selections and summarized observations are public.

`wrld.py ROOT --output /private/survey.json` regenerates corpus metadata. `check_fields.py ROOT` cross-checks the published corpus hashes, every field extent, eleven name offsets and complete raw-byte preservation in all80 specimens. `python3 -m unittest discover -s RUN/scripts -p test_wrld.py -v` runs the synthetic strict-reader suite. Each unittest method may include multiple boundary cases; validation counts methods, not each subcase.

`WrldAudit.java` exports only selected functions and metadata, `WrldRefs.java` gathers bounded state/table references, and `WrldVerify.java` verifies instruction bytes against authenticated PE sections. `evidence/reviewed_instructions.tsv` is the human-reviewed subset, not the complete export. `review_selections.json` and `select_evidence.py` can reproduce the selection from full private exports using the paths/targets recorded there. The 28-body byte check includes some larger caller bodies for source authentication; detailed manual interpretation remains confined to WRLD-related paths.

Evidence limits: no native mission/resource load executed, no original resource payloads published, no annotation mutation, no complete interpretation of opaque bytes, no renderer/physics equivalence claim. Protocol/schema/hash checks validate packaging, not scientific truth. Research PR acceptance does not promote a maintained format specification automatically.

Prepublication main advanced to `6a8147191fece8c61a813b42d0f7bcd39875f584` via reconstruction-only PR#126 (ZONE prefix correction). No overlap with this owned run; original captured base is retained under the isolated-run publication protocol. That correction reinforces keeping unproven fields opaque.
