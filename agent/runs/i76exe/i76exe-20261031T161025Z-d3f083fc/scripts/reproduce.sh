#!/usr/bin/env bash
set -euo pipefail
if [ "$#" -ne 8 ]; then echo 'usage: reproduce.sh HEADLESS EXE GZF ZFS MSN TER WORK REPO' >&2; exit 2; fi
headless=$1; exe=$2; gzf=$3; zfs=$4; msn=$5; ter=$6; work=$7; repo=$8
run=$(cd -- "$(dirname -- "$0")/.." && pwd)
test ! -e "$work"
mkdir -p "$work"
bash "$repo/agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/scripts/reproduce.sh" "$headless" "$exe" "$gzf" "$zfs" "$msn" "$ter" "$work/terrain-baseline" "$repo"
vehicle="$repo/agent/runs/i76exe/i76exe-20261030T025421Z-351de3fe"
python3 "$vehicle/scripts/reproduce.py" --source-repo "$repo" --work "$work/vehicle-baseline" --headless "$headless" --exe "$exe" --gzf "$gzf" --zfs "$zfs"
python3 "$vehicle/scripts/verify_integration.py" --run "$vehicle" --source-repo "$repo" --private "$work/vehicle-baseline" --exe "$exe" --gzf "$gzf" --zfs "$zfs" > "$work/vehicle-verification.json"
export XDG_CONFIG_HOME="$work/config" XDG_CACHE_HOME="$work/cache"
mkdir -p "$work/project" "$work/repeat"
cp "$gzf" "$work/project/i76_mission_v97_verified_names.gzf"
cp "$gzf" "$work/repeat/i76_mission_v97_verified_names.gzf"
cc -O2 "$repo/agent/runs/i76exe/i76exe-20261031T011728Z-b887fccd/scripts/x87_terrain_service.c" -o "$work/x87_terrain_service"
"$headless" "$work/project" research -import "$work/project/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_UnifiedAudit.java "$exe" "$work/ownership-audit.txt" > "$work/audit.log" 2>&1
for mode in visible camera_only behind contrast below; do
 "$headless" "$work/project" research -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_UnifiedProbe.java "$work/vehicle-baseline/fixtures" "$work/control-$mode.tsv" "$mode" "$msn" "$ter" "$work/x87_terrain_service" > "$work/control-$mode.log" 2>&1
done
"$headless" "$work/repeat" research -import "$work/repeat/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_UnifiedProbe.java "$work/vehicle-baseline/fixtures" "$work/fresh-visible.tsv" visible "$msn" "$ter" "$work/x87_terrain_service" > "$work/fresh-visible.log" 2>&1
python3 "$run/scripts/verify_all.py" --work "$work" --exe "$exe" --gzf "$gzf" --zfs "$zfs" --msn "$msn" --ter "$ter" --emit "$work/derived"
