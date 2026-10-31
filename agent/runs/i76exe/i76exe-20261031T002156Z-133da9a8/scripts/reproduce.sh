#!/usr/bin/env bash
# Licensed inputs stay private. WORK must be new; all paths absolute.
set -euo pipefail
if [ "$#" -ne 8 ]; then echo 'usage: reproduce.sh HEADLESS EXE GZF ZFS MSN TER WORK SOURCE_REPO' >&2; exit 2; fi
headless=$1; exe=$2; gzf=$3; zfs=$4; msn=$5; ter=$6; work=$7; repo=$8
run=$(cd -- "$(dirname -- "$0")/.." && pwd)
if [ -e "$work" ]; then echo 'WORK must not exist' >&2; exit 2; fi
mkdir -p "$work"
accepted="$repo/agent/runs/i76exe/i76exe-20261030T025441Z-8f2b292d"
# Checkpoint A precedes the extension. Accepted scripts are immutable inputs.
bash "$accepted/scripts/reproduce.sh" "$headless" "$exe" "$gzf" "$zfs" "$msn" "$ter" "$work/baseline" "$repo"
mkdir -p "$work/research/project" "$work/repeat"
export XDG_CONFIG_HOME="$work/baseline/config" XDG_CACHE_HOME="$work/baseline/cache"
cp -- "$gzf" "$work/research/i76_mission_v97_verified_names.gzf"
cp -- "$gzf" "$work/repeat/i76_mission_v97_verified_names.gzf"
cc -O2 "$run/scripts/x87_terrain_service.c" -o "$work/x87_terrain_service"
"$headless" "$work/research/project" handoff -import "$work/research/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_TerrainHandoffAudit.java "$exe" "$work/research/retail_audit.txt" > "$work/research/audit.log" 2>&1
for case in primary contrast below baseline diagnostic projected alternate; do
  scenario=primary; mode=transform
  if [ "$case" = contrast ] || [ "$case" = below ]; then scenario=$case; fi
  if [ "$case" = baseline ] || [ "$case" = diagnostic ] || [ "$case" = projected ] || [ "$case" = alternate ]; then mode=$case; fi
  "$headless" "$work/research/project" handoff -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_TerrainHandoffProbe.java "$msn" "$ter" "$work/research/$case.tsv" "$scenario" "$work/x87_terrain_service" "$mode" > "$work/research/$case.log" 2>&1
  # B/C are independently checked before baseline walker D or diagnostics E.
  if [ "$case" = primary ]; then python3 "$run/scripts/verify_handoff.py" --private "$work/research" --msn "$msn" --ter "$ter" --exe "$exe" --cases primary > "$work/checkpoint-C.json"; fi
done
"$headless" "$work/repeat" handoff -import "$work/repeat/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_TerrainHandoffProbe.java "$msn" "$ter" "$work/repeat/projected.tsv" primary "$work/x87_terrain_service" projected > "$work/repeat/repeat.log" 2>&1
python3 "$run/scripts/verify_handoff.py" --private "$work/research" --repeat "$work/repeat" --msn "$msn" --ter "$ter" --exe "$exe" --negative-controls --emit "$work/derived" > "$work/verification.json"
python3 "$run/scripts/check_publication.py" "$run" "$work/derived" > "$work/publication.log"
python3 "$repo/agent/protocol/tools/validate_protocol.py" "$run" > "$work/protocol.log"
