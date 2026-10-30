# Reproduction

Requires the licensed private retail `i76.exe`, `I76.ZFS`, annotated v97 GZF, Ghidra 12.1.4, Java 27, Python 3 and the accepted resource extraction code. Measured identities are recorded in `manifest.json`; the EXE/ZFS/GZF and projects are not published.

1. Follow PR #70's `artifacts/REPRODUCE.md` exactly in a new private directory. Its driver imports a fresh GZF project, runs five separate processes, and its full verifier must report `passed`, 1402 assertions, source verification true, five cases. The accepted source run is `agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe`.
2. For the native clip probe, create a **different fresh project** and run the original probe script. Supply absolute paths and new private config/cache folders (all outside the checkout):

```bash
SRC=/absolute/path/to/i76-checkout
RUN="$SRC/agent/runs/i76exe/i76exe-20261030T125716Z-1011d511"
PRIVATE=/absolute/path/to/private-rnd04-work
HEADLESS=/absolute/path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
GZF=/private/path/i76_mission_v97_verified_names.gzf
FIXTURES="$PRIVATE/pr70-repro/fixtures"
mkdir -p "$PRIVATE/native-project" "$PRIVATE/native-config" "$PRIVATE/native-cache"
XDG_CONFIG_HOME="$PRIVATE/native-config" XDG_CACHE_HOME="$PRIVATE/native-cache" \
  "$HEADLESS" "$PRIVATE/native-project" research \
  -import "$GZF" -noanalysis \
  -scriptPath "$RUN/scripts" -postScript I76_IntegratedClipProbe.java \
  "$FIXTURES" "$PRIVATE/native-positive.tsv" visible
```

3. Repeat step 2 with new `repeat-project`, `repeat-config`, `repeat-cache` directories and output path, to establish a fresh-project repeat. The negative control is a separate process/project with the final script and last mode argument `behind`. It keeps the visible run's selected camera owner but places the unselected target behind the view; no polygon wrapper or original clip call should occur.
4. Run the standalone verifier against the committed bounded event evidence:

```bash
python3 "$RUN/scripts/verify_clipping.py" --run "$RUN"
```

It checks the continuous ownership chain, exact entry/return and stack arguments, 4-vertex source/destination sizes, native output mutation and numeric validity, source preservation, fresh-project repeat identity, preserved kind-10/draw substitutes, negative control and retail instruction anchors. The expected result is `passed: 18 assertions`.

For local independent re-capture, use `-postScript I76_ClipSourceAudit.java OUTPUT 471fd0 47bf00 47c2f0 47c8d0 487ea0` on the imported GZF read-only. The output is diagnostic; the published exact instruction excerpt is `evidence/retail_instructions.tsv`.

Do not pass `--emit`, alter the accepted run, or publish licensed payloads or private project/cache files. Reproduction was executed in this workspace with the measured private assets and an independently imported GZF project. Full licensed-resource re-extraction is the PR #70 driver's responsibility; the standalone verifier only consumes the bounded events committed here.
