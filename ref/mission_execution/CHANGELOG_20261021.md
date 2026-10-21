# 2026-10-21 repository research update — cumulative v79–v97/v0.6

**Against supplied checkout:** `remote1.tar`, branch main commit `73a1d411a8fd99f8dcac9aa54461cce9fe8fdfe6` (May 26, 2026). The extracted TAR also contained uncommitted October 19 material and widespread POSIX file-mode differences, which are deliberately **not** included as research changes. No remote GitHub access or push was performed.

## New evidence

- New fresh read-only Ghidra export from *cumulative v97 GZF*: 2100 functions and 55 native focused disassembly/decompilation files, complete symbol/reference inventories, plus 36 function-index delta rows against Oct 19.
- Updated standalone 96-opcode host ABI and 95-entry stock serialized command table, with per-command effects and caveats.
- BWD2/FSM mission format, loader revision/failure behavior, 80-mission resource census, object instance-key registration and binding, VM call frames, scheduler and global game-flow termination.
- Original-code emulation reports v0.5/v0.6 and reproducible Java harnesses. No full-game Windows mission execution is claimed.

## Intentionally excluded

- Retail `i76.exe`, `.MSN` game assets and the v97 GZF containing original program bytes, even though separately available in the private research handoff.
- Rewriting the May and October 19 historical snapshots; a new dated snapshot is added alongside them.
- Editing `i76edit.exe` or unrelated shell/terrain/model artifacts without corresponding new source evidence.
- Blanket chmod/file-mode changes introduced by extraction of the supplied TAR archive.

## Carry-forward

Next work: emulated world-object creation and actor binding; then full-engine repeat-load validation. Do not silently reclassify stubbed emulator services as verified retail behavior.
