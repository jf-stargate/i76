# Complete fresh reproduction

Requires licensed private retail `i76.exe`, `I76.ZFS` and annotated v97 GZF with hashes in `evidence/provenance.json`, Ghidra 12.1.4, compatible Java (measured OpenJDK 27-ea), Python 3 and liblzo2. Preserve original inputs; no proprietary inputs, project databases, source audits or full raw traces are published.

Check out base `b219f0f2edea9da7f6ea9f44b80de90d4ddecb49` plus this run. The checkout must retain the accepted resource extractor at `agent/runs/i76exe/i76exe-20261022T232710Z-96c58505/`. Define absolute paths; `WORK` must **not exist** and must be outside `SRC` and other workers' workspaces:

```bash
SRC=/absolute/path/to/checkout
RUN="$SRC/agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe"
WORK=/absolute/path/to/new-private-reproduction
HEADLESS=/absolute/path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
EXE=/private/path/i76.exe
ZFS=/private/path/I76.ZFS
GZF=/private/path/i76_mission_v97_verified_names.gzf
python3 "$RUN/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 "$RUN/scripts/verify_integration.py" --run "$RUN" --source-repo "$SRC" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 "$RUN/scripts/verify_integration.py" --run "$RUN"
PYTHONDONTWRITEBYTECODE=1 python3 -m unittest discover -s "$SRC/.github/tests" -v
python3 "$SRC/agent/protocol/tools/validate_protocol.py"
```

Driver checks private hashes before importing; uses the immutable accepted extractor for its 64 fixtures and independently extracts additional top-level `hdlv_msk.geo` through the same checked archive reader. All 65 digests are verified against public provenance and/or original ZFS records. It creates new XDG config/cache directories within WORK, preventing writes to another worker's configuration. Ghidra's own executable compilation cache stays there. No mutable baseline is opened.

The driver copies the GZF, imports a fresh project without analysis, and executes visible, repeat, behind, empty and camera_only as **five separate read-only processes**. Repeat uses a second copied/imported project. It rejects nonzero status, ERROR logs or absent `PRODUCER_COMPLETE`; a zero headless exit alone does not establish success. Each nonempty process builds the selected camera fixture; the three two-vehicle processes also build an unselected bus. Every individual case retains one emulator from initialization to consumption. Finally a read-only original source audit supplies disassembly/decompilation locally for sparse PE anchor checking. Full source audit stays private.

Expected full verifier: status passed, assertions 1402, cases 5. Public-only verification checks original-state chronology, ownership, derived invariants and repeat from bounded public events; full verification additionally checks private trace regeneration, resources, original PE/GZF/ZFS identities, all measured writer/entry opcodes and source vertex positions. Exact public artifact regeneration must agree; differing Ghidra/JDK behavior requires investigation, not silently changing hashes. The actual clip/draw output is supplied, so there is no framebuffer comparator.

`--emit` requires all private arguments and deliberately regenerates `events.json`, `provenance.json`, and `summary.json`; use only a disposable copy after acceptance. Normal verification performs no run mutation. Probe and verifier source are versioned in this run. No files from old private experiments or other workers' scratch are prerequisites.

The source-audit script's complete invocation is in the driver. For a single diagnostic case, use the same read-only project/absolute script path and `-postScript I76_IntegratedRenderProbe.java FIXTURES OUTPUT.tsv MODE`, where MODE is visible, behind, empty or camera_only. Do not reuse a partial trace as evidence. Final published events come only from complete runs.
