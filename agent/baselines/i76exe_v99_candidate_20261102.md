# Candidate private i76.exe semantic baseline: v99

**Status: identity verified; internal Ghidra annotations NOT audited; not a canonical baseline.**
**Recorded:** 2026-11-02. **Original protected base:** `9576fc573964bed624a08d878886ccad40a63d7a`. **Track:** `i76exe`.

## Supplied private file identity

| Field | Value / limitation |
|---|---|
| User-designated filename | `i76_mission_v99_verified_names.gzf` |
| Whole-file SHA-256 | `ca211238170806eda27a2b4ecf6aee2192abb69df27fe56f106b455ac75bc710` |
| Size | 6,500,304 bytes |
| Container | Java serialization header containing one ZIP-style streamed `FOLDER_ITEM` |
| Container verification | Deflated member decompressed; CRC32 `143109bd`, compressed size 6,500,199 bytes and uncompressed size 22,970,368 bytes matched the recorded data descriptor |
| Retail target | Embedded `Program Information.Executable SHA256` and `Program Information.Executable MD5` metadata exactly match the verified retail PE hashes; source GZF schema was not reconstructed or loaded through Ghidra |
| Ghidra version | **Not measured from this GZF in a Ghidra runtime**; previous migrations used 12.1.4 |
| Internal function, symbol, comment and type inventory | **Pending** |
| Storage | User-provided private conversation attachment. Not published or retrievable from this public repository |

The whole-file digest and deflate descriptor verify container integrity. Raw decompressed database bytes also contain retail executable hash metadata matching the independently accepted PE identity and named type/category records. These checks **do not** establish correctness of code bodies, use-site typing, complete program inventory or signature equivalence. The filename `v99` is user-assigned versioning, **not proof** that repository's shared `semantic-v99`, `readability-v100`, `readability-v101`, `readability-v102` or `semantic-consolidation` scripts were applied.

## Limited embedded metadata inspection (not a Ghidra program import)

The decompressed 22,970,368-byte `FOLDER_ITEM` contains unambiguous ASCII property records `Program Information.Executable SHA256` and `Program Information.Executable MD5`, followed by the expected retail hashes. Its type/name table also contains `Interstate76`, `Research-v99`, `SemanticConsolidation`, `VmNode`, `VmToken`, `TER_Page`, and `TER_Normal3f`. These are **presence observations only**; raw byte searching cannot establish field offsets, function signatures, effective decompiler results, how many annotations were applied, or absence of conflicts. The Ghidra runtime audit remains mandatory.

## Relationship to merged evidence

Merged PRs #98–#105 contain separate original-binary research and guarded Ghidra migration tooling. Their confirmed effects belong to the **tested private baselines stated in each PR**, not automatically to this new private v99 GZF. See `agent/tools/ghidra/semantic-consolidation/BASELINE_COMPATIBILITY.md`. No bulk GZF, PE or decompiler output may enter this repository.

## Required audit before authoritative baseline promotion

1. In Ghidra 12.1.4, import the exact private file into a **disposable** project; record its SHA-256 beforehand.
2. Capture program name, executable MD5/SHA-256, language, image base, function counts split into defined/external, symbols with source provenance, signature/parameter storage, datatype components/offsets and relevant comments.
3. Compare exact original addresses and observed signatures with the merged v99–v102 tools, pilots A/B/C and PR #105; classify APPLY / ALREADY / PRESERVE / CONFLICT / DEFER **based on the actual imported v99**.
4. Confirm original function-body bytes against retail `i76.exe` SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3` using independently supplied licensed PE.
5. Retain private full capture; publish only reviewed counts, bounded annotations, anonymized audit digests and conflict dispositions.
6. Explicit human decision and separate reviewed baseline-promotion PR required. Do not replace the user's live project.

Until those steps complete, this file is a **candidate identity record** only, not an instruction to apply old scripts or a guarantee of equivalence.
