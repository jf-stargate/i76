# I76-MISSION-0.5.0 — Native BWD2 parser emulation

**Status:** Original retail x86 executed with Ghidra's p-code interpreter. This is **isolated executable emulation**, **not** a Windows/full-game test and **not** a rewritten parser model.

## Binary, scope, and trust boundaries

- Source program: imported, annotated v97 GZF for retail `i76.exe`; executable MD5 `a640ea0097dbb62e0c77b7f2847c7161`, independently checked against the original retail executable from the supplied game archive.
- Emulator: Ghidra 12.1.4 `ghidra.app.emulator.EmulatorHelper` (32-bit x86 p-code execution).
- Original code executed: generic BWD2 descriptor parser `004B3DB0`, original revision callback `004B4610`, the BWD2 no-op callback `004B8960`, and the retail error reporter `0042D5D0` (a one-instruction `RET`). Both program code and descriptor bytes originate in the original imported retail image.
- External dependency stubs, **not original Windows CRT execution**: imported `strncpy` (`IAT 004BC28C`), `_splitpath` (`004BC238`), and `_stricmp` (`004BC210`). Stub calls are recorded in `instruction_events.tsv` and implement their narrow C-library behavior. **The parser and revision callback themselves are not replaced or patched.**
- Resource test data: exact first 20 bytes of shipped `miss8/M06.MSN`: a `BWD2` chunk (8 bytes) followed by a `REV` chunk (12 bytes), revision 2. The two modified fixture types are **only in-memory emulator copies**: omit first chunk or change REV data from 2 to 3. Neither the retail game archive nor any user game installation was changed.
- Arguments duplicate the selected-mission caller's cdecl root parser invocation: input pointer, `00500328` descriptors, count 2, null context, `M06.MSN` resource name, sequential mode 1, and bounded end pointer. Initial ESP points to a private emulated stack and a sentinel return address marks normal completion.

## Primary observed result (D-E: independently captured instruction-emulator trace)

All cases returned to the sentinel normally. `EAX=0` indicates parser rejection; other returns are next-cursor offsets into emulator fixture address `20000000`.

| Case | Starting BWD2 flag | Input | Parser return | Final BWD2 flag |
|---|---:|---|---|---:|
| C01 stock, cold | `0x44` | BWD2 + REV=2 | `20000014` | `0xC4` |
| C02 missing BWD2, cold | `0x44` | REV=2 | **NULL** | `0x44` |
| C03 missing BWD2, manually seeded warm | `0xC4` | REV=2 | `2000000C` | `0xC4` |
| C05 wrong revision, cold | `0x44` | BWD2 + REV=3 | **NULL** | `0xC4` |
| **C06a → C06b: same emulator session** | `0x44 → 0xC4` | BWD2 + REV=2, then REV=2 only | `20000014`, then **`2000000C`** | `0xC4` |
| C07a → C07b: same emulator session | `0x44 → 0x44` | REV=2 only, then BWD2 + REV=2 | **NULL**, then `20000014` | `0xC4` |
| C08a → C08b: same emulator session | `0x44 → 0xC4` | BWD2 + REV=2, then BWD2 + REV=3 | `20000014`, then **NULL** | `0xC4` |
| **C09a → C09b: same emulator session** | `0x44 → 0xC4` | BWD2 + **wrong** REV=3, then REV=2 only | **NULL**, then **`2000000C`** | `0xC4` |
| C10a → C10b: same emulator session | `0x44 → 0x44` | REV=3 only, then REV=2 only | **NULL**, then **NULL** | `0x44` |

See `results/emulation_outcomes.tsv` for all 15 individual invocations, exact step counts, revision descriptor flags, native callback invocations, CRT stubs and native error calls.

## Conclusions and specification corrections

1. **Demonstrated in original-code emulation:** the BWD2 descriptor `seen` bit (`0x80`) persists across two consecutive invocations of the retail parser within a single emulated memory context. No manual warm seeding is used in sequences C06–C10.
2. **Demonstrated:** a missing BWD2 section is rejected with a cold descriptor table but can pass the root parser's required-descriptor check after an earlier BWD2 match. This confirms the v0.4 static prediction for the deliberately bounded REV-only fixture.
3. **New important observation:** a **failed** earlier parse with a matched BWD2 chunk and invalid `REV` still leaves `BWD2` marked seen, allowing the later REV-only root fixture to return non-null (C09). Parser failure is not a descriptor rollback.
4. **Demonstrated:** a matching but incorrect revision is still rejected by the original REV callback in both cold and warm states (C05/C08). Thus descriptor persistence does not bypass the separate revision callback.
5. **Not demonstrated:** acceptance of a malformed complete `.MSN`, actual mission initialization, actor and FSM callbacks, cache semantics, exceptions under a real Windows process, or an actual gameplay-session state transition. These parser-only results cannot establish an exploitable condition or a full-game success path.

## Reproduce

Ghidra 12.1.4 with Java 21; `analyzeHeadless`; a project containing the read-only imported v97 `.gzf` (program `i76_mission_v97_verified_names`). Supply the Java script using `-scriptPath` and output directory as a script argument:

```bash
GHIDRA=/path/to/ghidra_12.1.4_PUBLIC
$GHIDRA/support/analyzeHeadless /path/to/projects retail \
  -process i76_mission_v97_verified_names -readOnly -noanalysis \
  -scriptPath scripts \
  -postScript I76_BWD2_OriginalParserEmulator.java /absolute/path/to/results

python3 tools/validate_results.py --results /absolute/path/to/results \
  --game-tar '/path/to/i76_base(1).tar'
```

The game-tar verification option is optional; it checks the supplied retail PE MD5 and verifies the 20-byte fixture against the shipped M06 mission. The harness requires the user's own existing GZF and Ghidra distribution, not a Windows machine. No original-game assets or third-party libraries are embedded in this checkpoint archive.

## Evidence and integrity

- Original-executable instruction trace: `results/instruction_events.tsv` records `004B3F31` flag writes, `004B4160` required checks, `004B4177` error paths, and return-path events.
- Original-code output: `results/emulation_outcomes.tsv` contains 15 scenarios, including five same-memory two-call sequences.
- Ghidra log: `results/ghidra.stdout` and `ghidra.log` contain the run and Ghidra script execution record.
- `results/validation.json`: independent **68/68** deterministic assertions, including original retail game MD5 and matching original mission header.
- Source: `scripts/I76_BWD2_OriginalParserEmulator.java`; verification: `tools/validate_results.py`.

**Proposed specification status:** `BWD2 descriptor state persistence across same-process parser invocations` may be upgraded from static conditional inference (**I**) to **original-code emulator observation (D-E)** with the explicit scope above. Full Windows retail runtime (**D-W**) remains unobserved.
