#!/usr/bin/env bash
# Full isolated i76.exe M06 transform/walker/polygon-candidate replay.
set -euo pipefail
if [ "$#" -ne 6 ]; then
  echo 'usage: reproduce.sh HEADLESS GZF EXE MSN TER NEW_PRIVATE_WORK_DIR' >&2
  exit 2
fi
headless=$1; gzf=$2; exe=$3; msn=$4; ter=$5; work=$6
run=$(cd -- "$(dirname -- "$0")/.." && pwd)
repo=$(cd -- "$run/../../../.." && pwd)
if [ -e "$work" ]; then echo 'NEW_PRIVATE_WORK_DIR must not exist' >&2; exit 2; fi
mkdir -p "$work/project" "$work/reimport/project" "$work/config" "$work/cache"
export XDG_CONFIG_HOME="$work/config" XDG_CACHE_HOME="$work/cache"
cp -- "$gzf" "$work/i76_mission_v97_verified_names.gzf"
cp -- "$gzf" "$work/reimport/i76_mission_v97_verified_names.gzf"
cc -O2 "$run/scripts/x87_terrain_service.c" -o "$work/x87_terrain_service"
"$headless" "$work/project" terrain -import "$work/i76_mission_v97_verified_names.gzf" -noanalysis > "$work/import.log" 2>&1
"$headless" "$work/project" terrain -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainAudit.java "$exe" "$work/retail_audit.txt" > "$work/audit.log" 2>&1
for scenario in primary contrast below pool; do
  output=$scenario
  if [ "$scenario" = primary ]; then output=final; fi
  "$headless" "$work/project" terrain -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainProbe.java "$msn" "$ter" "$work/$output.tsv" "$scenario" "$work/x87_terrain_service" > "$work/$scenario.log" 2>&1
done
"$headless" "$work/reimport" terrain -import "$work/reimport/i76_mission_v97_verified_names.gzf" -noanalysis > "$work/reimport/import.log" 2>&1
"$headless" "$work/reimport" terrain -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainProbe.java "$msn" "$ter" "$work/reimport.tsv" primary "$work/x87_terrain_service" > "$work/reimport/replay.log" 2>&1
python3 "$run/scripts/verify_transform_emission.py" "$msn" "$ter" "$work" > "$work/verification.json"
python3 "$repo/agent/protocol/tools/validate_protocol.py" "$run" > "$work/protocol.log"
