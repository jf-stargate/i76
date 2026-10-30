# Fresh-project reproduction

Use a checkout containing this run and its exact accepted base history. Required tools: Ghidra **12.1.4**, Java >=21 (measured OpenJDK 27-ea), Python 3, GNU C on x86_64 with x87 support; protocol checks additionally need PyYAML/jsonschema. Use licensed private retail PE, v97 GZF, I76.ZFS, miss8/M06.MSN and miss8/M06.TER matching `manifest.json`. No resource extraction or other worker's private project/trace is required. ZFS is an authenticated provenance input; this run supplies already hash-verified M06 sidecars and intentionally does not acquire renderer palettes/textures from the archive.

Set absolute paths HEADLESS, EXE, GZF, ZFS, MSN, TER, WORK, SRC and RUN. WORK must not already exist; RUN is this run directory in SRC. Set JAVA_HOME to a compatible JDK if needed. The script places Ghidra configuration/cache and all proprietary/derived private output in WORK. It copies the GZF before import so the original licensed input remains read-only.

```bash
bash "$RUN/scripts/reproduce.sh" "$HEADLESS" "$EXE" "$GZF" "$ZFS" "$MSN" "$TER" "$WORK" "$SRC"
```

The script compiles the host instruction service, imports a fresh annotated program with `-noanalysis`, runs a read-only original-code/PE section audit, executes primary/contrast/below/raw/poison in five fresh emulator states, imports another **new project** for primary repeat, independently verifies every trace/buffer, compares regenerated public results, and validates protocol schemas/hashes. Inspect WORK/verification.json and protocol.log. Ghidra can exit zero after a script error: the verifier requires all expected complete outputs and will reject missing/malformed sidecars. The raw scenario intentionally records Ghidra's FPATAN failure; it must still finish capture and produce empty binary sidecars. Do not interpret that expected diagnostic as positive primitive output.

To rerun the standalone independent verifier or regenerate bounded derived evidence:

```bash
python3 "$RUN/scripts/verify_visible_terrain.py" --run "$RUN" --private "$WORK" --repeat "$WORK/repeat" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --service "$WORK/x87_terrain_service"
# Add --emit "$WORK/derived" to regenerate results.json and verification.json.
```

The verifier reads private `.tsv`, `.grid.bin`, `.vertices.bin`, `.arena.bin` and retail_audit.txt. It does not import the Java harness or reuse its sampler/graph code. It independently reconstructs typed grid/source associations and checks graph invariants; this is a verifier, not a renderer. Public `results.json` has only two small selected source primitives plus counts/digests/service ledger. Public selected events are a bounded review aid, not the full private trace. Full audit/decompilation, PE/GZF/ZFS/MSN/TER, mapped resource bytes and bulk private traces/buffers must remain private.

Scientific repeat expectations: with these exact tool/input identities, primary trace/grid/vertex/arena hashes should be byte-identical; A5-poison vertices/arena must equal primary; contrast must differ and below/raw must have no primitives. This does not promise equivalence across Ghidra/JDK versions or to all retail hardware arithmetic. No rendered-image metric is defined or scored.

Lineage: terrain-load calls and local mapping/CRT service patterns were reduced from the accepted `i76exe-20261028T174609Z-3f1f83f8/scripts/I76_AuthenticTerrainPhysicsProbe.java` (SHA-256 `ca1ad48b130ccf4a4227639104325362c7b90dab949cd03f333502260c8b55b7`). Vehicle constructors, suspension, camera and queue work were removed. The current owned scripts are standalone. Historical terrain LOD annotations guided address selection; this run rechecks original PE instructions and memory outputs independently.
