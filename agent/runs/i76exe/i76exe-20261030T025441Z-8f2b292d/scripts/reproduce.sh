#!/usr/bin/env bash
# Full new-project replay. All arguments absolute; WORK must not exist.
set -euo pipefail
if [ "$#" -ne 8 ]; then
  echo 'usage: reproduce.sh HEADLESS EXE GZF ZFS MSN TER WORK SOURCE_REPO' >&2
  exit 2
fi
headless=$1;exe=$2;gzf=$3;zfs=$4;msn=$5;ter=$6;work=$7;repo=$8
run=$(cd -- "$(dirname -- "$0")/.." && pwd)
if [ -e "$work" ]; then echo 'WORK must be new' >&2; exit 2; fi
mkdir -p "$work/project" "$work/repeat" "$work/config" "$work/cache"
export XDG_CONFIG_HOME="$work/config" XDG_CACHE_HOME="$work/cache"
cp -- "$gzf" "$work/i76_mission_v97_verified_names.gzf"
cp -- "$gzf" "$work/repeat/i76_mission_v97_verified_names.gzf"
cc -O2 "$run/scripts/x87_terrain_service.c" -o "$work/x87_terrain_service"
"$headless" "$work/project" terrain -import "$work/i76_mission_v97_verified_names.gzf" -noanalysis > "$work/import.log" 2>&1
"$headless" "$work/project" terrain -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainAudit.java "$exe" "$work/retail_audit.txt" > "$work/audit.log" 2>&1
for scenario in primary contrast below raw poison; do
  "$headless" "$work/project" terrain -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainProbe.java "$msn" "$ter" "$work/$scenario.tsv" "$scenario" "$work/x87_terrain_service" > "$work/$scenario.log" 2>&1
done
"$headless" "$work/repeat" terrain -import "$work/repeat/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_VisibleTerrainProbe.java "$msn" "$ter" "$work/repeat/primary.tsv" primary "$work/x87_terrain_service" > "$work/repeat/repeat.log" 2>&1
python3 "$run/scripts/verify_visible_terrain.py" --run "$run" --private "$work" --repeat "$work/repeat" --exe "$exe" --gzf "$gzf" --zfs "$zfs" --msn "$msn" --ter "$ter" --service "$work/x87_terrain_service" > "$work/verification.json"
python3 "$repo/agent/protocol/tools/validate_protocol.py" "$run" > "$work/protocol.log"
