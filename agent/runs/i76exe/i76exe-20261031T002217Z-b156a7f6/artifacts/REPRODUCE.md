# Complete fresh reproduction

Requires licensed private EXE, ZFS and annotated v97 GZF with the hashes in manifest/provenance, Ghidra12.1.4 PUBLIC, measured compatible Java27-ea, Python3, liblzo2 and Python validator dependencies. Never publish payloads or project databases. Locate inputs independently and verify hashes; paths below are parameters, not assumed predecessor scratch locations.

From this checkout, set SRC to its absolute path and RUN to `agent/runs/i76exe/i76exe-20261031T002217Z-b156a7f6` beneath SRC. WORK must not exist and must be outside SRC. Then:

```bash
python3 "$RUN/scripts/reproduce.py" --source-repo "$SRC" --work "$WORK" --headless "$HEADLESS" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 "$RUN/scripts/verify_polygon.py" --source-repo "$SRC" --private "$WORK" --exe "$EXE" --gzf "$GZF" --zfs "$ZFS"
python3 "$RUN/scripts/verify_polygon.py" --source-repo "$SRC" --negative-controls
python3 "$RUN/scripts/verify_polygon.py" --source-repo "$SRC" --evidence "$RUN/evidence/corrupted_sample.json"
```

Last command must exit nonzero: `original stores reconstruct full output memory`. First command runs unchanged accepted PR70 extraction, fresh import, all five baseline cases and its 1,402-check private verifier before extension. Then it executes native visible/behind and a separate newly imported native repeat project. Audit verifies all instructions/table cells against retail PE; final standalone verifier recomputes geometry and projection and rejects four mutations. It compares regenerated evidence with immutable artifacts, never emits into the accepted run. XDG config/cache are local to WORK. All projects are read-only during probe execution. Logs, inputs and full audits remain private. Default public verifier requires no licensed assets; 293 checks. Full source verification passes 2,769 checks without mutation tests.

`audit_dispatch.py --source-repo "$SRC" --private "$WORK" --exe "$EXE" --out "$WORK/retail_dispatch.json"` regenerates the published instruction/table artifact. `verify_polygon.py --emit` is only for allocating unaccepted evidence; ordinary reproduction does not mutate run files. Two full fresh-driver executions and a separately imported native repeat are recorded in provenance/notes.

Trusted preflight uses a pristine checkout at pinned `3e10251444a117c8d9da053b6887245a2bc4dbcf`: run `python3 -m unittest discover -s .github/tests -v`, `python3 agent/protocol/tools/validate_protocol.py`, then that trusted checkout's `.github/scripts/pr_integrity.py --repo "$SRC" --trusted-root "$TRUSTED" --base-sha 3e10251444a117c8d9da053b6887245a2bc4dbcf --head-sha "$HEAD" --branch agent/i76exe/i76exe-20261031T002217Z-b156a7f6` on the proposed commit. Required GitHub integrity must pass on the exact published head. No merge is authorized.
