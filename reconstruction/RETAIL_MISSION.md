# Retail mission semantic reader — milestone 3

**Implementation scope:** read-only, C++20, synthetic tests plus opt-in retail
smoke testing. This does not claim to emulate the original mission-loader callback
behavior, and no original game resources are part of the repository.

## CLI

```text
resource mount /path/to/i76
level sections miss16/M06.MSN
level summary miss16/M06.MSN
level terrain miss16/M06.MSN
level dependencies miss16/M06.MSN
```

- `level summary` uses the bounded BWD2 reader and creates a typed,
  **owned** value: mission revision, recognized top-level sections and their
  direct-child revisions, section lengths, WRLD/OBJ/RSEG/FSM record counts,
  and validated terrain index metadata. It does not decode opaque WRLD,
  ODEF, RSEG or FSM payloads. The original BWD2 inventory remains available
  via `level sections` / `level inspect`.
- `level terrain` requires ZMAP and ZONE; validates the 6,400-byte index
  array and the 13-byte sidecar name, resolves the sidecar in the mission
  directory, and checks an exact 32,768-byte page size for each declared page.
  Height is `sample & 0x0fff`; the surface flag is bit 12 and the surface
  class is bits 13..15. Statistics scan all sidecar pages, not only those
  referenced from the grid. This is a diagnostic reader, not mesh generation.
- `level dependencies` reports the one currently verified reference, the
  ZONE .TER sidecar, with its lookup and integrity status. Remaining WRLD
  references are explicitly unparsed, not fabricated from guessed offsets.

## Validation and compatibility

This first semantic decoder handles **retail-style BWD2-marker streams**;
it intentionally rejects the enclosing-root form used by some older synthetic
BWD2 structural tests. It is deliberately independent of the synthetic
`I76LEVEL 1` prepare/activate pipeline.

ZMAP payload is exactly 6,401 bytes (active page count + 80×80 indices).
A cell value of 0xff means unused; every other cell must be below the ZMAP
active-page count. ZONE payload is 14 bytes (an **opaque prefix byte** followed
by a 13-byte filename). The original retail ZONE handler (004939D0) reads the
filename at chunk offset +9 and uses the ZMAP-derived global page count; it
does **not** compare ZONE payload byte 0 with the ZMAP count. An earlier
implementation mistakenly enforced that equality and rejected real missions at
the ZONE chunk offset (e.g. 0x1aa0). The byte is retained as
`zone_prefix_byte` for diagnostic inspection without assigning an unverified
meaning. Names use existing resource-key normalization and traversal guards.
All read operations release byte leases on success and error. Partial decoding
never commits into the caller's previous definition.

Tests use a synthetic mission with the observed BWD2/REV/WDEF/TDEF/RDEF/
ODEF/LDEF/ADEF/EXIT layout, a tiny WRLD blob, a fixed 80×80 ZMAP, and a
single 128×128 .TER page. Malformed records and dangling sidecar references
are negative tests. A full retail installation is not required in CI.

Evidence: [runtime mission/terrain reference]
(../ref/level_format/i76_runtime_level_and_terrain_format_notes.md),
the existing [BWD2 inspector](BWD2.md), and
[shipped corpus validation]
(../ref/mission_execution/evidence/CORPUS_LOADER_INVENTORY.tsv).
Field-offset claims beyond these are intentionally deferred.

## Next milestone

Decode additional WRLD references only after verifying their serialized
offsets; then prepare a terrain-only scene with tested resource ownership
and independent renderer/simulation lifetimes. Retail activation and mission
FSM execution remain unsupported.
