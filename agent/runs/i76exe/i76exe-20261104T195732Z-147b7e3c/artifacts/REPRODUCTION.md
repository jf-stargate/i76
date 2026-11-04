# Reproduction, integrity and publication boundary

Base commit `5f408a117da6d55e495714b648f41b43d708bf6e` was independently resolved from GitHub HEAD/main before allocation. Protocol1.0.5 and its documentation workflow were read at that commit. Ruleset25664125 is active, requiring PR, integrity, resolved review threads and zero formal approvals. Human maintainer acceptance remains required; no merge is authorized. GitHub returned no open PRs at bootstrap. Run-owned files only; existing worktrees and their build outputs were untouched.

Private original inputs:

- `/media/neon-remote/prj/i76/orig/i76.exe`: SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`, MD5 in manifest.
- `/media/neon-remote/prj/i76/scratch_data/i76exe_v100.gzf`: SHA-256 `f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0`.
- `/media/neon-remote/prj/i76/orig/I76.ZFS`: SHA-256 `0610541842dfd10464ea02307dec9749ac2b31da4019e1af05d5fcfc55d9020d`.
- All74 extracted HZD and80 installed mission paths/hashes/lengths are in `../evidence/corpus.json`. HZD bytes were compared to fresh archive decompression. Complete proprietary names and dependent payload locations/hashes remain in `hzd-private/corpus_private.json`; public inventory uses name SHA-256 and archive record indices/PAK offsets.

Ghidra12.1.4 PUBLIC at `/media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless` imported the original GZF into `/media/neon-remote/prj/i76/hzd-private/project/research`, domain file i76exe_v100, internal program name i76.exe. All commands used `-noanalysis`; later passes used `-readOnly`. Scripts do not edit instructions, functions, annotations or types. Source GZF/EXE hashes were verified before/after. The persisted22,986,752-byte program database `.gbf`, program properties and current indexes were byte-identical before/after read-only sessions. Ghidra changed an index **backup** and removed a journal backup during workspace housekeeping; this is explicitly recorded, not represented as a fully unchanged project directory. `database_integrity.json` contains exact scope and digests.

A complete second reproduction succeeded in a **fresh** project at `hzd-private/fresh-reproduction-final`. It repeated the20 synthetic tests, corpus/archive and inventory survey, original-byte verification over14 function bodies /12,135 bytes, and unchanged program/current-index check. The regenerated corpus, anonymized dependency inventory, reviewed instruction selection, parser constants and byte-validation table were byte-identical to the packaged evidence. See `reproduction_validation.json`. No native retail gameplay or malformed retail execution was performed.

From the repository root, substitute this run's directory for RUN and a new private path for NEW_WORK:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 RUN/scripts/reproduce.py \
  --root /media/neon-remote/prj/i76 \
  --repo /media/neon-remote/prj/i76/hzd-isolated \
  --exe /media/neon-remote/prj/i76/orig/i76.exe \
  --gzf /media/neon-remote/prj/i76/scratch_data/i76exe_v100.gzf \
  --headless /media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless \
  --work NEW_WORK
```

The script refuses an existing work directory, authenticates EXE/GZF, keeps all full exports private, and emits only derived metadata into NEW_WORK/metadata. Java preferences may require a writable user configuration. Omitting --headless repeats the parser/corpus checks only. `survey.py` separately regenerates public corpus/dependency metadata and private full-name joins; its accepted WRLD and ZFS reader references/hashes are recorded in corpus.json. These imported accepted scripts must come from the pinned base commit; they are not modified or republished here.

`HzdAudit.java` exports bounded function bodies privately, `HzdRefs.java` inspects only horizon-state references, `HzdVerify.java` compares Ghidra instruction bytes against authenticated PE section bytes, and `select_evidence.py` selects the reviewed windows. Byte identity authenticates code, not every annotation. The14-body check includes a large containing top-level function only to authenticate the teardown call; renderer interpretation stays bounded to the documented interfaces. No bulk export is published.

`package.py --workspace /media/neon-remote/prj/i76` regenerates run packaging, source-integrity evidence, finding links and manifest digests during preparation. Do not rerun it to change an accepted run. Local protocol/schema/hash and trusted-base PR-integrity checks are additional publication validation; they do not certify scientific conclusions.

Evidence is binary-static plus retail corpus plus independently authored bounded-parser tests. No instruction emulator or substituted service was used to claim execution. Unknown renderer/palette behavior remains unknown. Research-only PR, no canonical/manual/shared/reconstruction/baseline changes, no self-merge.
