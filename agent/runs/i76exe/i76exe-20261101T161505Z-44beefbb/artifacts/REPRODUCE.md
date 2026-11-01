# Reproduce the terrain semantic audit

Private licensed inputs are required: retail `i76.exe` SHA-256 `bc073a930da5b03793c086f22eeeff6f2cc7d9c81ce650c6656d0d0c49af13f3` and the supplied GZF SHA-256 `d48df73dc331b87c2bae23f4f481be102aa0a77c6baceb01687de8a6e0e57fbd`. No mission or TER payload is needed for this **static/readability** run. No new retail/runtime execution is claimed. The earlier M06 emulator remains separately reproducible through its own run's `artifacts/REPRODUCE.md`; do not count its old tests as this run's execution.

Tested tools: Ghidra 12.1.4, OpenJDK 27-ea in this workspace, Python 3 (standard library for capture audit), objdump for independent PE disassembly. Repository protocol validation additionally requires jsonschema and PyYAML. The original private GZF contains program name `i76.exe`, imported domain file `i76_mission_v98_verified_names`; filename/version labels alone do not establish applied annotations.

Create a **new private directory and project name**. Do not open/save over an existing user project. Set task-specific shell variables, for example:

```sh
terrain_run=agent/runs/i76exe/i76exe-20261101T161505Z-44beefbb
terrain_private=/path/to/new/private-directory
terrain_ghidra=/path/to/ghidra_12.1.4_PUBLIC/support/analyzeHeadless
terrain_gzf=/path/to/private/i76_mission_v98_verified_names.gzf
terrain_exe=/path/to/private/i76.exe
```

From the repository root, after creating `$terrain_private/project`, run the final sequence. `TerrainSemantic.java` defaults to **dry-run**; only literal argument `apply` commits annotations to the opened disposable program. It creates no GZF export and never updates shared scripts.

```sh
"$terrain_ghidra" "$terrain_private/project" terrain_final \
  -import "$terrain_gzf" -noanalysis -scriptPath "$PWD/$terrain_run/scripts" \
  -postScript TerrainInspect.java "$terrain_private/final_before.txt" \
  -postScript TerrainSemantic.java \
  -postScript TerrainInspect.java "$terrain_private/after_dry.txt" \
  -postScript TerrainSemantic.java apply \
  -postScript TerrainSemantic.java apply \
  -postScript TerrainInspect.java "$terrain_private/final_after.txt"
```

Expected console summaries: dry **19 planned / 0 already / 0 skipped / not committed**; apply **19 / 0 / 0 / committed**; repeat **0 / 19 / 0 / committed**. Unexpected state is preserved or rejected; inspect it instead of forcing changes. Function count in the supplied baseline is **2337**, not the count in earlier shared-tool trials.

The inspection output is bounded to the terrain cluster, direct helpers and one caller, but remains **private**. Do not commit those captures, the project, GZF or PE. Derive only safe metrics/checks in another private directory first:

```sh
python3 "$terrain_run/scripts/audit_captures.py" \
  --private "$terrain_private" --exe "$terrain_exe" --gzf "$terrain_gzf" \
  --out "$terrain_private/safe-evidence"
```

Expected **23/23** checks, covering private identities, unchanged dry-run capture/function count/instructions, all five original PE code-range hashes, height ST0/two-argument ABI/full calculation, correct normal stack packing/named fields, page/grid sizes and inventoried analyst labels. Metrics are specific to this Ghidra build and input; another baseline may require separate review rather than exact text comparison. Unrelated caller output is inspected as context, not counted in the five-function regression claim.

Check the interior-load claim independently with `objdump -d -M intel --start-address=0x493160 --stop-address=0x4931b3 "$terrain_exe"`. Inspect the normal selector at `00493286..00493297` and signed page tests before changing any formula. Program range hashes in `TerrainSemantic.java` were measured from the PE sections and are checked against actual Ghidra memory before any annotations.

Validate the published run with the trusted base protocol:

```sh
python3 agent/protocol/tools/validate_protocol.py "$terrain_run"
```

The PR additionally runs trusted `.github/scripts/pr_integrity.py` with exact base/head SHA and owned branch. Protocol validation certifies scope/hashes/schema, not recovered semantics. Hardware FISTP correction, all-mission parity, bit12 and full collision behavior remain outside these checks.
