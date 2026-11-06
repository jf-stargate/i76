# Reproduction

Requires licensed inputs matching manifest.json, Ghidra 12.1.4, JDK27 (measured 27-ea+34), Python3, cc/x86-64 x87, liblzo2, and protocol validation dependencies. Source data, GZF projects and complete raw traces remain private. The available v100 archive is measured and its entire executable section is retail-identical; the older v97 archive is unavailable locally.

From the pinned isolated checkout, use absolute paths:

```
python3 "$RUN/scripts/reproduce.py" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF_V100" --zfs "$ZFS" --msn "$MSN" --ter "$TER" --work "$RUN/private/new-replay" --repo "$REPO"
```

WORK must not exist. The driver authenticates inputs, extracts the unchanged accepted stock fixtures, compiles the inherited narrow x87 helper, imports an isolated project, compares retail code, executes the ten primary/contrast/below/X/Z cases, runs the independent graph/predicate verifier and compares scenario summaries with publication. Ghidra zero exit alone is not success: the independent verifier requires completion, exact original source graph/loops and source/work writes.

For asset-free review:

```
python3 "$RUN/scripts/check_public.py"
python3 agent/protocol/tools/validate_protocol.py "$RUN"
```

A separate measured fresh import repeats the complete primary trace and ten geometry sidecars bit-for-bit. Unchanged #76 I76_CameraTerrainProbe.java produces the same eight common sidecars on the same retail-identical v100 import. The inherited independent source/camera/transform/clip/bin checker is run as verify_context_v100.py with --private CASES --repeat FRESH_PRIMARY --fixtures FIXTURES --msn MSN --ter TER --exe EXE --gzf GZF_V100 --zfs ZFS --corruptions --emit PRIVATE_DERIVED. Its only code change is the GZF digest; 89159 checks pass, including source, camera and work-record corruption rejection. Full command argument names match accepted #76.

For the alternate blocked probe, replay.py accepts --cases alternate on the owned private imported project. This intentionally stops at null descriptor header setup and is excluded from the complete source-to-emission scenario oracle. Reproduction.json and private_output_hashes.json retain measured hashes without publishing proprietary bytes. No game assets or databases are committed.

The complete packaged driver was measured for primary/contrast/below using --cases primary contrast below in a third isolated project. All ten default scenarios were separately measured and verified with the same owned observer/model; the full default driver sequence itself was not repeated after packaging.
