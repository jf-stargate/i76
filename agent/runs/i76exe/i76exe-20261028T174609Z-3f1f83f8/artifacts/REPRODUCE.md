# Reproduce the terrain/contact evidence

Required private inputs: retail i76.exe/I76.ZFS, miss8/M06.MSN/M06.TER, and the annotated v97 GZF identified in manifest.json. Required tools: Ghidra 12.1.4, Java >=21, Python 3, liblzo2, gcc on x86_64 with x87 support. Measured environment used OpenJDK 27-ea and `gcc -O2`. Do not commit extracted resources, generated executables, mapped PE images, Ghidra projects, full decompilation or raw proprietary data.

Let SRC be the accepted repository checkout, RUN this owned run directory, WORK private writable scratch, HEADLESS Ghidra's support/analyzeHeadless, EXE/GZF/ZFS/MSN/TER the authenticated inputs. Use absolute paths. The shared /media checkout was read-only, so the measured run used `/home/z/i76-terrain/` and reused a private Ghidra import from `/home/z/i76-research/ghidra/`; no source database was mutated.

## Prepare inputs and instruction service

```bash
python3 "$RUN/scripts/prepare_private_inputs.py" --source-repo "$SRC" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --out "$WORK/fixtures"
gcc -O2 "$RUN/scripts/x87_fistp_service.c" -o "$WORK/x87_fistp_service"
```

The preparer reuses the accepted vehicle extractor in run `i76exe-20261022T232710Z-96c58505` and adds ACT/LUM/TBL and engsnd.dat directly from the verified ZFS. Raw ACT has zero in its compressed logical-size field; raw stored length is authoritative. The service protocol is ten little-endian ST0 bytes and a two-byte CW; normal requests return int64 FISTP, while bit 15 requests FCOS and returns ten x87 bytes. This is only a numerical instruction boundary, not game reconstruction.

For a fresh project, copy GZF to WORK first (import requires an adjacent lock), then:

```bash
"$HEADLESS" "$WORK" research -import "$WORK/i76_mission_v97_verified_names.gzf" -noanalysis
```

Use the imported program name `i76_mission_v97_verified_names`. Do not run two headless processes against the same project concurrently; even read-only processing takes a project lock.

## Replay scenarios

Each script invocation starts a fresh emulator; its frames retain state. Argument order is fixture-directory, output, vehicle, selected, native-root, native-registry, mode, MSN, TER, hardware-service, frame-count.

```bash
"$HEADLESS" "$WORK" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$RUN/scripts" -postScript I76_AuthenticTerrainPhysicsProbe.java "$WORK/fixtures" "$WORK/publish_bus.tsv" bus 1 1 1 math-clock-pop-terrain-host-filter-registry "$MSN" "$TER" "$WORK/x87_fistp_service" 32
```

Generate these additional outputs with the same command pattern:

| Output | Vehicle | Mode | Frames |
|---|---|---|---:|
| publish_bus_repeat.tsv | bus | math-clock-pop-terrain-host-filter-registry | 32 |
| publish_gtsi.tsv | gtsi | math-clock-pop-terrain-host-filter-registry | 32 |
| publish_slow.tsv | gtsi | math-clock-pop-terrain-host-filter-registry-slow | 4 |
| publish_raw.tsv | bus | math-clock-pop-terrain-filter-registry | 2 |

The raw control leaves Ghidra FISTP uncorrected while retaining the original filter initializer; its physics heights are diagnostic, not positive evidence. Slow mode supplies 100-ms GetTickCount increments; ordinary mode supplies 16-ms increments. The original clock and timer produce the actual deltas/substeps. Other modes in the lineage are diagnostic controls only. The `.grid.bin` sidecar contains private initialized pointer data for independent validation; it is not published.

```bash
python3 "$RUN/scripts/verify_authentic_terrain.py" --run "$RUN" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --x87-service "$WORK/x87_fistp_service"
```

The verifier checks identities, sparse original instructions, the entire initialized grid, material properties, engine-registry/CDF selection, source-to-public records, every logged TER read, every logged height, typed frame numerics, original callback/solver completion, compression bounds and independent hardware requests. Published private trace hashes are reproduction anchors for this environment, not cross-version promises.

## Static audit

The audit script accepts extra retail VAs after its private output path. Useful targets: 00493910 00493960 004939D0 00493BD0 00493080 00493550 004931C0 004927B0 00471400 004B8A10 00440740 0043A5D0 0046DC10 0049E0F0 0049E1B0 00469B00 00469F10. Write its full output privately; only the reviewed sparse anchors are published. All processing uses `-readOnly -noanalysis` and preserves annotations.

Harness lineage is pinned in evidence/provenance.json to PR #50 commit 41ab143afe0d9d1536cc1d4ec62c31fdb6138ec4. The owned standalone copy executes original routines and supplies explicit services; it does not modify PR #49/#50 or implement an engine.
