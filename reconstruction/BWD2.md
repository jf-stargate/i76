# Read-only BWD2 mission section inventory (milestone 2)

This implementation is a bounded **structural inspector** for original I76 `.MSN`,
`.SPC`, and `.LVL` BWD2 chunk streams. It does **not** construct a playable level,
load terrain, resolve ODEF/VCF/SDF assets, bind the mission FSM, or execute retail
callbacks. The independent synthetic `I76LEVEL 1` loader remains the only supported
activation format. **Structural parse success is not original-game acceptance.**

## Inspect a locally supplied game directory

```sh
cmake -S reconstruction -B build/i76-debug -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/i76-debug --parallel
ctest --test-dir build/i76-debug --output-on-failure
build/i76-debug/i76 --headless --interactive
```

In the console, mount the directory containing your original mission files:

```text
resource mount /path/to/Interstate76/miss16
level inspect M06.MSN
asset stats
```

Or mount the parent directory and specify the relative path:

```text
resource mount /path/to/Interstate76
level sections miss16/m06.msn
```

`level inspect` selects the BWD2 inspector for `.msn`, `.spc`, and `.lvl`
(case-insensitively), and preserves the synthetic manifest inspection for
`.level`. `level sections <name>` explicitly requests BWD2 inspection for any
resource name. Console output includes the full BWD2 byte count and number of
sections, then an indented inventory with each section's original FourCC,
hexadecimal absolute byte offset, total on-disk length, and recognized revision
value. Output is capped at 128 rows, with the total count still reported.

The directory provider normally uses normalized lowercase ASCII paths. On
case-sensitive filesystems, it also performs an exact-first, case-insensitive
ASCII fallback for each path component, allowing original `MISS16/M06.MSN`
spelling. Ambiguous casefold matches fail rather than selecting an arbitrary
source. Canonical paths remain constrained to the mounted directory; this
fallback does not relax path traversal or symlink checks. This is **not** a
security sandbox against concurrent changes by another local process.

`level load M06.MSN` and `level prepare M06.MSN` deliberately reject retail
BWD2 in this milestone. The reader does not change the world registry, mission
state, prepared level, or renderer/audio state, and any byte-cache lease acquired
for inspection is released before the console command completes.

## File contract and bounds checks

- Stock `.MSN` files begin with an **eight-byte `BWD2` marker** (FourCC
  plus little-endian `uint32_t` size equal to 8). The following top-level
  `REV`, `WDEF`, `TDEF`, `RDEF`, `ODEF`, `LDEF`, `ADEF` and `EXIT`
  records are **siblings**, not payload within the `BWD2` marker. Inspection
  continues through EOF; any incomplete or out-of-range sibling is rejected.
  For compatibility with older synthetic test fixtures, a non-eight-byte
  enclosing `BWD2` root is still accepted only when its declared length spans
  exactly the supplied buffer; extra bytes outside such a root are rejected.
  The original game writer and the repository's previously audited 80-file
  mission corpus both establish the eight-byte marker format.
- Known container tags `WDEF`, `TDEF`, `RDEF`, `ODEF`, `LDEF`, and `ADEF`
  are recursively inventoried within their declared parent byte boundaries.
  `BWD2` is treated as a marker when its size is eight, and as an enclosing
  container only for older synthetic fixtures.
  Unknown printable FourCCs are retained as **opaque leaf chunks**. This is not
  an exhaustive container specification for every retail resource family.
- Recognized revision tags `REV`, `WREV`, `TREV`, `RREV`, `OREV`, `LREV`, and
  `AREV` require exactly one 32-bit payload word, decoded little-endian. Numeric
  revision values are **reported**, not interpreted as a mission-compatibility
  policy. `FSM` payloads, including legitimate empty ones, are opaque.
- A valid record has a total size of at least eight bytes and must fit entirely
  inside its parent. The parser checks all subtraction-based spans before
  touching header/payload bytes; it does not cast serialized bytes to native
  structs. The maximum resource size is 16 MiB, with at most 16,384 chunks and
  a maximum nested container depth of 16.
- No implicit filling of missing sections, no persisted descriptor `seen`
  bits, no attempt to reproduce retail callback-dependent rejection or the
  retail loader's unconditional success return. The original's accepted
  revision/descriptor research is a reference for later semantic validation,
  not an excuse to copy unsafe parsing behavior.
- Parsing returns an explicit error code and offending byte offset. A failed
  parse does not overwrite an earlier successful inventory. All arrays and
  structs start zero/value-initialized, and the inventory contains no borrowed
  pointers into file contents.

The reader consumes source-provided bytes from the memory or directory provider.
There is no ZFS/PIX/PAK index decoder yet. To inspect compressed/packed original
missions, provide a previously extracted *local* copy through a directory mount;
never add game assets to the public repository.

## Testing, GDB, and evidence limits

`unit_bwd2` covers the retail BWD2 marker followed by sibling records,
legacy enclosing-root fixture compatibility, root/nested offsets and parent indices;
revision endianness;
empty FSM; unknown tags; zero/short/oversized/out-of-parent lengths; corrupted
FourCC; truncated headers; trailing bytes; chunk/depth/byte caps; repeat calls;
rollback on error; and resource lease cleanup. `unit_bwd2_commands` exercises
CLI inspection, original active-world preservation, a real temporary directory
with uppercase `MISS16/M06.MSN`, malformed resource diagnostics, and (where
permitted by the OS) a symlink escape probe. A process-level test builds a tiny
synthetic BWD2 `.MSN` fixture **inside the build directory** and inspects it
through the actual executable.

Debug the parser with:

```sh
gdb -tui --args build/i76-debug/i76 --headless --interactive
(gdb) break i76_bwd2_parse
(gdb) break i76_bwd2_read
(gdb) run
```

The 8-byte retail marker contract is supported directly by the original
`004B4840` BWD2 writer (initial BWD2 header declares size 8), the independent
[corpus inspector](../scripts/ghidra_emulation/audit_loader_corpus.py), and the
80-file [mission inventory](../ref/mission_execution/evidence/CORPUS_LOADER_INVENTORY.tsv).
The inventory and this reader remain structural analyses, not claims of retail
engine acceptance for malformed input.

The accepted research sources are
[resource acquisition](../manual/reference/engine/resource_acquisition.md),
[mission loader validation](../ref/mission_execution/LOADER_VALIDATION_AND_FAILURE_CONTRACT.md),
and the historical [BWD2 extraction reference](../ref/level_format/i76_runtime_level_and_terrain_format_notes.md).
They establish the eight-byte chunk header, nested mission families and the
source of known revision tags. Actual retail parsing and failure behavior have
separate semantics and are not claimed reproduced here.
