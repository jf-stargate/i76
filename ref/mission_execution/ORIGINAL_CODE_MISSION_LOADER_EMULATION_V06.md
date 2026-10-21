# Interstate '76 retail mission loader — original-code emulation checkpoint v0.6.0

**Research scope:** Execute the retail selected-mission loader *suffix*, nested BWD2/ADEF dispatchers, and original FSM importer and finalizer in an isolated Ghidra 12.1.4 x86 p-code emulator. This is a substantial extension of v0.5.0, which tested the generic BWD2 parser by itself. No executable, mission file, or canonical Ghidra database was modified. No Windows/full-game process was executed.

**Program identity:** retail `i76.exe`, executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`, from an independently imported and annotated v97 Ghidra program. All data fixtures are loaded at execution time from the user's own retail `.MSN` files. Neither game executable nor mission file is redistributed in this checkpoint.

## Precisely what executed

- Original selected-mission wrapper instructions **`004B4463–004B4540`**, starting *after* its filename/path preparation, selected-mission metadata, callback-registration and drive-selection preamble. The harness supplies an emulated stack with the original preamble's expected local resource-name buffer. Therefore **the whole wrapper was not emulated from its entry at `004B42B0`**.
- Original root BWD2 descriptor parser `004B3DB0`, once for `BWD2/REV` and conditionally again for the world-section descriptor table. The parser is not reimplemented.
- Original nested `ADEF` forwarding wrapper `004B45F0`, nested callback `004B89B0`, and original `AREV/FSM/EXIT` descriptor parser at `004B3DB0`.
- Original revision callback `004B4610`, `ADEF` exit predicate `004B4290`, world EXIT callback `004B4790`, and no-op `report_error` `0042D5D0`, subject to the world-state stub described below.
- On individual cold test scenarios, original FSM callback **`00409740`**, seven-table importer **`00410720`**, and finalizer **`004125C0`**. The empty `M06.MSN` script uses the retail seven-zero-word empty-FSM branch. The nonempty `T01.MSN` script exercises actual table loads and fixups.

The following operations are **explicitly stubbed** and logged in `instruction_events.tsv`:

| Boundary | Emulated policy | Consequence |
|---|---|---|
| Resource service `0046FFC0`, `0046FEE0`, `0046FD40` | Supply the source `.MSN` bytes/length and release the synthetic cache handle | No Windows resource-cache lifecycle verified |
| `_strnicmp`, `strncpy`, `_splitpath`, `_stricmp`, `_strlwr` | Narrow C-library functionality or a forced nonmatch to select the standard mission path | Real CRT not executed |
| Windows `HeapCreate`, `HeapAlloc` | Synthetic handle and disjoint allocated emulated buffers; preserve the **stdcall** 12-byte stack cleanup | No Windows heap allocator lifecycle, exhaustion or cleanup verification |
| CRT `bsearch` for nonempty FSM | Always return not-found | Media lookups are **not genuine successful media resolution** |
| WDEF/TDEF/RDEF/ODEF/LDEF backing producers | Return success, letting original section-forwarding machinery run | No real world objects, terrain or AI state created |
| Player-present query `00401320` | Return `1` | World EXIT passes despite no instantiated player |
| FSM callback on same-memory **paired** tests | Return success without executing FSM importer | Preserves original descriptor state without inventing FSM shutdown/reinitialization |

In short, **parser control flow and FSM table-reading logic are original instructions; OS services, world producers, and resource availability are modeled**. A successful wrapper return does not prove mission playability.

## Retail fixtures and corpus cross-check

Two unmodified source resources are supplied at runtime:

- `miss8/M06.MSN`: 47,814 bytes, 8-byte empty FSM chunk; root and nested tag structures verified from original archive. In-memory variants remove the first BWD2 chunk, change root REV, change nested AREV, or change a section's four-byte tag. The source file is never rewritten.
- `miss8/T01.MSN`: 140,330 bytes, nonempty FSM chunk of 54,632 bytes. Its loader-produced table counts match the **independent v94 bytecode corpus parser** exactly: 95 commands, 169 media entries, 22 named positions, 11 actor entries, 20 initial VM nodes, 47 initial words, 4,712 tokens. The 22 named positions contain 108 vectors.

The v0.6 emulator uses separate emulated memory regions for the resource payload (`0x20000000`), filename (`0x21000000`), synthetic heap (`0x22000000`), and stack (`0x30000000` region), avoiding overlap with the larger T01 payload.

## Native outcomes: M06

| Scenario | Root parser | World parser | ADEF parser | Native FSM callback | Stored global cursor | Wrapper EAX |
|---|---|---|---|---|---|---|
| W01: stock cold | Called | Called | Called | Yes, completed | End of file | `1` |
| W02: missing BWD2 cold | Called, rejects | No | No | No | `NULL` | `1` |
| W03: wrong root REV cold | Called, rejects | No | No | No | `NULL` | `1` |
| W07: incorrect nested AREV | Called | Called | Called | Yes, completed | End of file | `1` |
| W08: renamed FSM tag | Called | Called | Called | No | End of file | `1` |
| W09: renamed outer ADEF tag | Called | Called, early exit | No | No | Before end | `1` |
| W10: renamed nested EXIT tag | Called | Called | Called | Yes, completed | End of file | `1` |

W07 makes two native `report_error` calls but proceeds through the original FSM importer. This experimentally validates the v0.3 static observation that nested AREV revision-callback failure is not necessarily fatal under that descriptor's flags. W08 is an even stronger illustration of the distinction between parse return and initialization: the parser consumes the entire fixture while **never calling the FSM importer**. W09 demonstrates that a non-null parser cursor may be short of the input end, yet the enclosing mission wrapper still returns `1`.

## Same-memory, two-call sequences

For these **three pairs**, the emulator maintains original descriptor memory between invocations. The second call inherits the first call's writes; the FSM callback itself is stubbed on both calls so no unmodeled FSM teardown is implied.

- **W04a→W04b:** Valid stock BWD2/REV marks root BWD2 flags `0x44 → 0xC4`. A following REV-only resource reaches the original world and ADEF parsers, with non-null final cursor.
- **W05a→W05b:** A first load rejected for incorrect root REV still marks BWD2 seen. The subsequent REV-only fixture reaches world and ADEF dispatch even after that earlier failure.
- **W06a→W06b:** A first REV-only fixture fails when cold and does not set the seen bit. A subsequent valid stock resource is parsed successfully.

This extends the previously tested v0.5 repeated root-parser phenomenon to the **real selected-mission wrapper's parser/dispatch sequence**, but the test does not implement the entire game's mission reset and resource lifecycle.

## Nonempty original FSM: T01

`W11_T01_nonempty` returned to its sentinel normally after **280,090** emulated instruction steps. The original FSM importer and finalizer were both traversed; the output registers and table-count globals were read from emulated program memory, not copied out of a Python decoder.

A total of 48 synthetic HeapAlloc requests occurred (including the initial 19,200-byte actor-table reserve); the `bsearch` substitute was called 338 times and forced media lookup misses; the native no-op error reporter was entered 180 times. Those diagnostic counts are **harness-environment-dependent** because world objects and registered media are unavailable. They are not evidence that retail T01 is defective or invalid.

The nonempty result establishes execution of the original loader's data decoding and fixup pathways far beyond static decompilation. It does **not** validate correct actor ownership, media binding, Windows allocation behavior, world side effects, or running the T01 VM itself.

## Limitations and confidence

**D-E (original-code emulator):** Wrapper-suffix unconditional result for the tested paths, nesting and callback order, descriptor seen persistence, diagnostics/nonfatal paths, empty and nonempty FSM table loading, serialized table counts.

**B (binary static):** Whole-wrapper preamble, resource-cache logic, world loader and actual owner/lifetime paths; these remain supported by native Ghidra disassembly, not by this harness.

**Unresolved:** Windows full-game cold/warm mission loading; whether successful world callbacks change parser status; true missing or duplicate asset behavior; whether caller-visible state is safe to use after a partial load; heap and FSM teardown during actual repeated missions; interpretation of arbitrary corrupt lengths and memory faults; behavior of subsequent VM execution.

**Critical classification:** These test mutations expose absent checks or permissive return paths; no exploit, crash, or ability to play an altered mission is demonstrated.

## Evidence and reproducibility

- `scripts/I76_MissionWrapper_OriginalCodeEmulator.java`: single source file for Ghidra 12.1.4 headless.
- `results/wrapper_outcomes.tsv`: 13 M06 scenarios, including three same-memory pairs.
- `results_nonempty/wrapper_outcomes.tsv`: nonempty T01 original-FSM run.
- `results*/instruction_events.tsv`: original function-entry and descriptor mutation events, all stub-boundary interactions, and failures if encountered.
- `results*/ghidra.stdout` and `ghidra.log`: native tool provenance and completion.
- `evidence/v99_loader_full_instructions.tsv`, `v99_loader_native_decompiled.txt`: previously verified source native evidence retained for architectural context.
- `validation.json`: independent scripted assertions (107 checks, all passed), including retail source-file and PE hash cross-checks.
- `tools/validate_wrapper.py` and `README.md`: regeneration and validation commands. Input game bytes are not redistributed.
