# Interstate '76 retail — v95 BWD2 to FSM loader and compiler/consumer contract

**2026-10-20.** Research only; original executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`. Native Ghidra 12.1.4 read-only investigation on the previously annotated v92/v93 baseline, with two semantic naming corrections in a separate writable copy and independently reimport-verified GZF. The shipped corpus inspection read the original mission-file variants already extracted for v94; neither retail game code nor mission resources were modified.

## Executive conclusions

1. **The loader path is now established across all wrappers:** `004B42B0` opens the selected mission -> generic BWD2 parser `004B3DB0` processes header and world-section registry -> top-level `ADEF` handler `004B45F0` calls `004B89B0` -> nested `AREV`/`FSM`/`EXIT` registry dispatch invokes `00409740` -> counted FSM tables at `00410720` -> relocation/finalization `004125C0` -> runtime `004149F0`/`00414670`.
2. **Corrected the previously misread BWD2 descriptor field layout.** A descriptor is `{four-character tag at +0, auxiliary at +4, function pointer at +8, flags at +0xC}` (16 bytes). Earlier v81 raw-pointer scanning recorded entries starting eight bytes before their tag (the *previous* descriptor's callback and flags). Those raw pointers were still real, but the entry-start addresses were incorrect. The `FSM` descriptor begins **00500D30**, with handler **00409740** at **00500D38**. The parent `ADEF` descriptor begins **00500398**; its callback is **004B45F0**.
3. **The stock compiler output identifies host commands by name, not numerical runtime opcode.** The wire format contains up to 40-byte command names; the runtime expands each into a 0x54-byte record and `004125C0` writes the resolved host opcode into `record+0x50` using `00410A10`. The `0x0D` token's payload is the **source command-record index**. E.g., serialized index 5 is `follow`, runtime opcode `0x30`; serialized index 8 is `driveControl`, runtime opcode `0x49`. These are not the same namespace.
4. **All 50 nonempty compiled FSMs contain an identical, ordered list of 95 distinct command names**; 15 mission files per variant legitimately have an empty `FSM` chunk. The original engine recognizes 96 opcode names; the missing stock command is `playScene` (`0x16`), which v89 found dispatched to an error/abort path. This establishes a *stock-output versus engine-recognized* gap, not which exact source syntax `fsmcomp.exe` supported.
5. **All 80 shipped files have the same BWD2 shell**: `BWD2`, `REV`, `WDEF`, `TDEF`, `RDEF`, `ODEF`, `LDEF`, `ADEF`, `EXIT`. Their root revision is `2`, and the nested ADEF children are `AREV` (revision `1`), `FSM`, `EXIT`. All 80 nested chunks parse exactly within their declared extents, including empty scripts; no parser errors.
6. **Input validation is layered but incomplete in locally audited code:** the generic BWD2 parser uses a supplied file-end pointer, sequential tag matching, descriptor flag policies (including `0x40` required/`0x80` seen), revision callbacks, and callback return status. It does not establish a complete nested FSM byte-count guard. The raw FSM importer at `00410720` consumes word counts without checking its unused byte-length parameter, as reported in v94. No malformed mission was executed; no claim of exploitability or runtime failure is made.

## Binary-backed call chain and descriptor ABI

`004B42B0 load_and_parse_selected_mission_resource` opens a named cached resource, obtains its size, establishes `g_current_bwd2_parse_cursor` and `g_current_bwd2_parse_end`, and dispatches the two staged descriptor tables. `004B3DB0 parse_tagged_chunk_descriptor_table` is shared across vehicle, object, world and mission resources. For each descriptor entry, its code compares the incoming chunk's first dword with the entry's first dword (`*pbVar8`) and invokes the callback at `pbVar8+8`; flags at `pbVar8+0xC` control matching, nested-section handling, missing/repeated chunks, callback parameter selection, and error policies. Descriptor stride is `0x10`.

The actual table evidence for the mission-ADEF path:

| Descriptor address | Four-byte tag | Handler at `+8` | Flags at `+C` |
|---|---|---|---|
| `00500328` | `BWD2` | `004B8960` | `0x0044` |
| `00500338` | `REV\0` | `004B4610` | `0x2020` |
| `00500398` | `ADEF` | `004B45F0` | `0x2006` |
| `005003A8` | `EXIT` | `004B4790` | `0x2000` |
| `00500D20` | `AREV` | `004B4610` | `0x2004` |
| `00500D30` | `FSM\0` | `00409740` | `0x0001` |
| `00500D40` | `EXIT` | `004B4290` | `0x1000` |

Note `004B8960` is a **constant-success no-op** shared by `BWD2`, `ISEG`, and `TSEG` registry entries. Its inherited name implied that it loaded route-segment tables, which it does not. Recognition of the `BWD2` tag occurs in the descriptor parser, not in this callback's body.

The ADEF wrapper `004B45F0` calls `004B89B0`, which passes `&g_adef_descriptor_table` (`00500D20`) with count `3` into `004B3DB0`. The FSM callback at `00409740` receives the chunk *header*, uses `chunk+8` as the serialized payload and `chunk_size-8` as its nominal byte length; it creates the FSM heap, loads the seven table groups and calls `004125C0` to resolve commands, bind actor identities, validate media, and relocate initial execution nodes. This exact pathway is independently consistent with all 80 shipped mission files.

### Source command index versus runtime opcode

The serialized 40-byte source name at command table index `i` is not an opcode. At load time, `00410720` allocates `command_count * 0x54` bytes and copies each name into one runtime record; then `004125C0` invokes `00410A10` once per record and stores the numerical opcode at `record+0x50`. `00412CE0` later indexes `command_records + (token_payload * 0x54)` and dispatches according to the resolved value at `+0x50`.

`v95_canonical_compiled_command_table.tsv` contains all 95 stock source indices, names, runtime opcode values, handler addresses and audited domains. In v89 `playScene` was among the 96 recognized names but not a supported normal dispatcher case. It is also absent from every stock compiled command table. **This does not prove that a lost mission compiler had no source-level `playScene` syntax or could not emit a custom table.** It does show the retail compiled missions did not use that name.

### Corpus test

The independent `v95_validate_shipped_bwd2_fsm.py` walks actual outer BWD2 chunk boundaries rather than locating the last byte occurrence of `FSM\0`; it locates the sole `ADEF` chunk, verifies the `AREV`/`FSM`/`EXIT` child sequence, bounds-checks its complete seven-table payload, and compares the command lexicon with the 96-name engine opcode map from v89. Summary: 80 files, 40+40 by variant, 25 nonempty + 15 empty each, all outer revisions `2`, all ADEF revisions `1`, identical ordered 95-name lexicon in every nonempty FSM chunk, no errors. The inspection is **read-only static corpus validation**; it does not execute the game's parser or VM.

### Validation scope and uncertainty

- **High confidence:** exact `0x10` descriptor layout and the corrected pointer offset; staged BWD2/ADEF/FSM callback chain; `record+0x50` name-to-opcode fixup; 95-command stock lexicon; fixed `REV`/`AREV` and all 80 corpus nested chunk boundaries. Native decompilation, incoming calls, descriptor bytes and independent corpus parsing support these conclusions.
- **Medium-high confidence:** parser's use of end pointer and flag-based constraints. Parsing is complicated by sequential descriptors, mutable `0x80` seen flags, special handling of `EXIT`, and the callback return protocol; a malformed-file acceptance/rejection specification is **not** established here. The precise significance of every flag bit is not yet completely characterized.
- **Outstanding:** `fsmcomp.exe` original grammar and error behavior; whether custom-authored source can produce all VM token types; exact externally reachable rejection paths for corrupted length/count fields; alternative resource inputs and content revision variants; whether resource cache or upstream readers provide further invariants or checksum enforcement. Do not conflate the independently implemented `004B35A0` CRC helper with a proved CRC check in this mission-loading call chain.

## Symbol reconciliation

In a disposable writable copy of the annotated Ghidra database, two misleading inherited names were corrected:

- `00410A10`: `initialize_fsm_command_name_table` → **`fsm_resolve_host_command_name_to_opcode`** (pure name-to-ID resolver; does not initialize the table).
- `004B8960`: `load_iseg_tseg_record_table_context` → **`bwd2_accept_marker_chunk_noop`** (constant success with no visible side effects; used for multiple tag classes).

The updated `.gzf` was exported and imported into a **fresh** headless Ghidra project. All 11 function/global/MD5 checks passed. The user's original database and retail executable were not altered. The earlier v81 descriptor-offset interpretation remains recorded historically; the v95 registry replaces it as the corrected authority.

## Good targets for subsequent mission research

1. Characterize the descriptor flag bits and callback-success policy as a *machine-exact parser state machine* for the recognized valid resource cases, without requiring malformed file execution.
2. Audit the FSM's media-name validation and actor-name/identity resolution (`004122D0`, `00412400`) against the serialized resource tables and top-level object load ordering.
3. Define the precise table-index versus pointer-to-runtime-variable ABI for all VM argument token variants; compare usage with compiled mission bytecode where possible.
4. Record additional source-unit grouping evidence separately from confirmed loader semantics.

## Reproducible artifacts

The checkpoint includes four native Ghidra decompilation sweeps, corrected raw descriptor registry, 80-file BWD2/FSM inventory, canonical 95-command lexicon with runtime opcode mapping, Java and Python verification scripts, source-layout notes, the two-change symbol audit, verified GZF export and logs. **The checkpoint does not include retail `.MSN` files or the `i76.exe` executable.**
