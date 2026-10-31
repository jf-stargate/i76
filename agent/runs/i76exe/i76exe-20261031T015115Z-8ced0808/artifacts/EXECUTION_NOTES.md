# Execution notes

Model identifier exposed to this session: **GPT-6** (Codex). Thinking configuration and actual token usage were not exposed; no value is inferred. Runtime clock at run allocation was 2026-10-31 01:51:15 UTC. End time is recorded in the manifest when finalized; no invented wall-time measurement is used.

| Checkpoint | Measured outcome |
| --- | --- |
| A | Current protected main authenticated as `f2bcfbf40db8873bc4a787c9a3ceb3f305fbb019`; policy 1.0.4 read there. One run/branch allocated. Unchanged #75 reproduction passed, including predecessor/native checks, exact traces and accepted corruption controls. |
| B | Retail disassembly and 459 read-only GZF instruction rows matched retail PE. Original destination fields, `00474C60` constructor, `004791E0` table producer and pixel writer identified. |
| C | Original `00474C10` stopped at imported `HeapCreate` `000C0FE2`; original `00474C60` returned with a valid descriptor using one explicit allocation service. Original `004791E0` stopped at imported float-to-integer `000C0BFC`; diagnostic table declared separately. |
| D | Both original `0047CB00` callbacks returned at `0047CE38`; 210 actual original `0047CC62` byte stores changed a guarded framebuffer. |
| E | Standalone source/span/address/table/writer/full-buffer/guard verification passed 3,593 positive assertions. Three corruptions rejected after 81 further executed checks. |
| F | Behind camera and absent surface yielded zero pixel writes; X offset shifted all 210 destinations; fresh GZF import repeated complete trace and framebuffer exactly. |

Recoverable execution failures/corrections: the initial unchanged #75 command failed because the parent private scratch directory did not exist; the directory was created and the same run's unchanged driver reran successfully. An initial direct Ghidra launch lacked writable `XDG_CONFIG_HOME`; the next launch used run-private config/cache, as the accepted driver does. The first multi-hunk probe patch failed an exact-context check and made no file change; smaller patches were applied. **Three recoverable retries** were needed for those three issues; no new run or branch was allocated. The first standalone diagnostic launched successfully. The raw heap and original palette failures above are expected scientific blockers, not concealed tool retries. A preliminary verifier output counted mutation-attempt assertions together; its final output separates 3,593 positive and 81 mutation-attempt checks. No human intervention occurred beyond the user's original assignment and later “continue” instruction. The 38 trusted pinned-base GitHub/protocol unit tests passed separately.

The exact commands and private output identity are in `artifacts/REPRODUCE.md` and `evidence/raster_results.json`. GitHub publication, exact-head trusted preflight and CI result are recorded after they complete; this note does not predeclare them. No accepted run, canonical reference, shared tool or other worker workspace was changed.
