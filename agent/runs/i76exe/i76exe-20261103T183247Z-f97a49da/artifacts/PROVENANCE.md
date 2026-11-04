# Retail source-provenance inspection

The authenticated retail PE provides **no useful original source-file identifier for these regions**. No original filename is assigned. Inspection preceded heuristic grouping. Results are binary-static observations; the Ghidra names/types are later research annotations.

| Observation | Result and evidentiary limit |
|---|---|
| Retail identity | 1,050,624 bytes; SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`; MD5 `a640ea0097dbb62e0c77b7f2847c7161` |
| COFF | i386 `0x014c`; characteristics `0x010f`; symbol pointer 0, symbol count 0; no COFF `.file` records available |
| PE debug directory | RVA 0, size 0; no debug entries to resolve |
| CodeView/PDB | No `RSDS`, `NB10`, `NB09` or `NB11` signature bytes found; no PDB filename recovered |
| Linker header | Version fields 5.10; raw PE timestamp 887926892; image base `00400000`; entry RVA `000BA0E0`. These identify build metadata, not source files or an exact whole-game compiler configuration |
| Rich build metadata | `Rich` at file offset `0xA8`; XOR key `800D1BCB`; decoded raw compid/count records `00021C87:95`, `00000000:420`, `00060684:1`. These are retained without claiming a compiler-product mapping or interpreting counts as TU counts |
| Library compiler banner | ASCII at file offset `0xBF301` identifies LZO 1.00 built February 12, 1998 by Microsoft C 1100. This is direct embedded library build text; it does not prove every game function used that compiler or identify the library's source files |
| Source/object filename strings | ASCII extension/compiler-pattern scan found 264 matches: one library banner and 263 `.map` asset-name/extension strings. No C/C++/header/object/library/PDB/debug source filename was recovered. The corresponding UTF-16 source-extension scan found none |
| `.map` ambiguity | Names such as terrain-resolution image maps, texture-face names, `input.map` and `gamekey.map` are incidental game resource/configuration names. A `.map` suffix alone is not an original linker map artifact |
| PE sections | `.text`, `.rdata`, `.data`, `.rsrc`; dimensions and characteristics in `pe_provenance.json`. They are not per-object contributions |
| Accepted history | Filename-only search of ancestry reachable from pinned main for OBJ/LIB/PDB/DBG/MAP/ILK/MAK/DSW/DSP artifacts found no non-run candidate paths. Original objects, libraries or linker-map artifacts were not available in that search. No PR branch or Pilot 1 content was searched |

Reproduction: `scripts/provenance.py` parses the PE with Python's standard library, traverses COFF auxiliary records if present, inspects the debug directory, searches ASCII/UTF-16 provenance patterns and decodes raw Rich records. The public compact result is [pe_provenance.json](../evidence/pe_provenance.json); the bulk list of asset strings stays private. The history search examines filenames, not the contents of unrelated research runs. It is not an exhaustive forensic search of deleted/unreachable Git objects, untracked files or private maintainer archives. Absence here does not prove original debug artifacts never existed.

Environment: `/media/neon-local/bin/ghidra_12.1.4_PUBLIC/support/analyzeHeadless`, Ghidra **12.1.4 PUBLIC**, Java >=21 requirement (actual runtime: OpenJDK 27-ea+34-1-Debian). Private inputs were verified at the provided paths before importing: `scratch_data/i76exe_v100.gzf` SHA-256 `f21ce157703cb33ef265c2ddc98e5079c24f254f5ab7dd6ee87eaabe9d115bb0`, and `orig/i76.exe` with the retail hash above. A disposable `-noanalysis` import produced program `i76.exe`, language `x86:LE:32:default`, compiler specification `windows`. That compiler specification is an analysis configuration, not recovered developer build provenance.

The program database was opened only with `-readOnly -noanalysis`. The maintainer's GUI project and source GZF were never opened for modification. The unchanged program page-file digest, unchanged modification counter and identical independent captures establish non-mutation at the measured database/content levels; project backup index/journal housekeeping changed and is disclosed. Exact validation measurements appear in `validation_results.json` and `fresh_reproduction.json`.
