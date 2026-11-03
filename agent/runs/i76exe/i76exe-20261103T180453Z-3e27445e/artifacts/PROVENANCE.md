# Original source provenance check

Direct provenance takes priority; none recovered in this scan. Retail SHA-256 is in the manifest. COFF symbol table pointer/count are zero, so no COFF file records are exposed there. PE debug-directory RVA/size are zero. Literal RSDS/NB10/NB09/NB11 markers are absent. Printable ASCII source/path candidate scan for .c/.cpp/.cxx/.h/.hpp/.pdb/.obj/.lib returns none; no arbitrary extension string is attributed to an original file. UTF-16, compressed or obfuscated provenance was not exhaustively searched.

PE linker version is 5.10. Rich marker is at file offset A8, with valid XOR-decoded DanS start. Decoded product/build/count tuples: (2,7303,95), (0,0,420), (6,1668,1). Numeric tuples are reported without inventing compiler identities or interpreting count as source-file count. This metadata does not recover source names, object boundaries, COMDAT choices or optimization flags.

Pinned repository tracked-path inspection found no .obj/.lib/.pdb/.map artifacts (case-insensitive suffix check). Annotated GZF and research scripts are analyst-created semantic artifacts, not original source records. Absence is scoped to tracked accepted files, not every private archive.
