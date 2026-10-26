# World-object status 0x10: original vehicle-spawn writers and VLOC eligibility

**Scope:** retail `i76.exe` original x86 behavior from the v97 annotated Ghidra baseline; research proposal, not canonical reference. **Pinned base:** `6b4176dfb289997fae432bb50885adda8d4f6dca`. **Retail PE** SHA256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3`. **Ghidra v97 GZF** SHA256 `b2f76177fbab3d6ddc8c88cb10eac5d331b52155190e120c349508f6032d4fce`. The previous *merged* research run `i76exe-20261024T232546Z-11d4e2ec` established that VLOC type `0x28` creates the optional camera attachment at `runtime+0x398` only when object status bit `0x10` is set, using original `004AE000` and `00458BF0` with its low-level allocator and binder intercepted. This run traces the previously unidentified writers on two principal vehicle creation paths.

## Network and player-vehicle creation: `00451180`

Annotated function: `load_or_create_player_vehicle_entity`. Retail assembly `00451286–004512A1` compares the **low 16-bit** vehicle/player ID with the session-local ID at `00541028`. At `004512A1` it writes `0x10` when they match and `0x20` when they differ, *before the VCF loader call at `004512E5`*. `004512B0–004512C7` adds the `(configuration_status >> 16 & 7) << 16` team encoding. The session local ID global is written by original multiplayer init `00452D79`, read by `get_local_multiplayer_player_id` `00454E30`, and compared by the original `00451180` at `0045128D`. Thus the local player's vehicle **in this network creation path** is the status-`0x10` object; this does not imply every world object with the bit is player-controlled.

Seven Ghidra native instruction probes include four for this path, with matching ID 3/3 and differing ID 2/3 (team 5), a zero ID, and a 16-bit wraparound ID (`0x00010003` vs `0x0003`). All select the expected exact status and subsequently execute the *original* VLOC gate predicate `00458BF0` on the same object. The two external services intercepted to reach the actual VCF call boundary are multiplayer configuration lookup `00454700` and basename formatting `004AD640`. The constructor **itself is not executed** in this new probe. Input team bits at the expected call-stack location were controlled.

## Ordinary/local vehicle creation: `004513C0`

Annotated function: `load_vehicle_entity`. The fifth function parameter controls another policy: original instructions at `00451452–0045146E` produce `0x00020000` if the parameter is zero, and `0x00010010` if nonzero. The status write occurs *before* the VCF call at `0045148B`. Both policies were verified with original x86 instructions and then original `00458BF0` on the same object in three native scenarios (zero, 1, and 9). The only service intercepted between the status write and VCF entry is `004AD640`. The explicit creation parameter is a **local status-selection input in this function**, not proof that bit 0x10 universally represents player ownership.

## Higher-level callers and source roles

Ghidra v97 direct callers of `00451180` include the main game loop at `00403AB8`, `00403CD5`, mission logic at `00456161`, and four networking/spawn handlers (`00456A6C`, `00456BBC`, `00456CEC`, `00456F17`). Calls to `004513C0` include initialization/game-loop entries `00401210`, `004013A1`, `00403670`, and another vehicle context `004518E8`. Exact x86 direct-call displacements are checked against the PE in `evidence/call_edges.tsv`. Source function labels are Ghidra analytical names, **not** recovered original source identifiers.

## Evidence and limits

- Both original-instruction Ghidra headless replays produced identical derived trace SHA256 `0bbae7ee9bbeeb775e0be0c50f4b52a4016d2d22390d8c88c2897f5cb37b471b`. See `evidence/status_flag10_original_x86.tsv` (seven rows).
- The original status assignments, team encoding, selection and VLOC bit predicate execute in the emulator. Calls to the two unrelated lookup/format services are deliberately intercepted. The emulated object is a controlled allocation, not a fully initialized world hierarchy.
- The VCF constructor at `004AD6F0`, VLOC parsing at `004AE000`, class-`0x28` allocation/binding, camera mode and final scene renderer are **not** executed as one continuous original retail session in this run. The separately merged VLOC run validates the downstream parser/guard with isolated substitutes.
- Other possible writers to object status bits, alternate mission ODEF creation, remote multiplayer lifecycle and later flag changes require further analysis; the identification is of these **two exact constructors**, not an exhaustive global proof of all status-bit producers.

**Next original-code test:** execute the full `00451180` or `004513C0` path using retail-constructed VDF resources and native registered class dispatch, preserve the eligible status from allocation, and run class-`0x28` attachment construction/teardown and default `00406AB0` camera beyond its guard. Then validate camera transforms and x87 operations separately.
