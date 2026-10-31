#!/usr/bin/env bash
# Licensed source data remain private. WORK must not exist; use absolute paths.
set -euo pipefail
if [ "$#" -ne 8 ]; then echo 'usage: reproduce.sh HEADLESS EXE GZF ZFS MSN TER WORK SOURCE_REPO' >&2; exit 2; fi
headless=$1; exe=$2; gzf=$3; zfs=$4; msn=$5; ter=$6; work=$7; repo=$8
run=$(cd -- "$(dirname -- "$0")/.." && pwd)
if [ -e "$work" ]; then echo 'WORK must not exist' >&2; exit 2; fi
mkdir -p "$work"
old="$repo/agent/runs/i76exe/i76exe-20261031T002156Z-133da9a8"
# Checkpoint 1: unchanged accepted M-RND-06, including accepted M-RND-05.
bash "$old/scripts/reproduce.sh" "$headless" "$exe" "$gzf" "$zfs" "$msn" "$ter" "$work/baseline" "$repo"
export XDG_CONFIG_HOME="$work/baseline/baseline/config" XDG_CACHE_HOME="$work/baseline/baseline/cache"
extract="$repo/agent/runs/i76exe/i76exe-20261022T232710Z-96c58505"
python3 "$extract/scripts/extract_private_fixtures.py" --zfs "$zfs" --out "$work/fixtures" --metadata "$extract/evidence/retail_resource_digests.json" > "$work/extract.log"
mkdir -p "$work/project" "$work/repeat" "$work/cases"
cp -- "$gzf" "$work/project/i76_mission_v97_verified_names.gzf"
cp -- "$gzf" "$work/repeat/i76_mission_v97_verified_names.gzf"
cc -O2 "$run/scripts/x87_terrain_service.c" -o "$work/x87_terrain_service"
"$headless" "$work/project" context -import "$work/project/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_ContextAudit.java "$exe" "$work/context_audit.txt" > "$work/audit.log" 2>&1
for case in primary contrast below; do
 "$headless" "$work/project" context -process i76_mission_v97_verified_names -readOnly -noanalysis -scriptPath "$run/scripts" -postScript I76_CameraTerrainProbe.java "$work/fixtures" "$work/cases/$case.tsv" bus "$msn" "$ter" "$work/x87_terrain_service" "$case" > "$work/$case.log" 2>&1
done
"$headless" "$work/repeat" context -import "$work/repeat/i76_mission_v97_verified_names.gzf" -noanalysis -scriptPath "$run/scripts" -postScript I76_CameraTerrainProbe.java "$work/fixtures" "$work/repeat/primary.tsv" bus "$msn" "$ter" "$work/x87_terrain_service" primary > "$work/repeat.log" 2>&1
python3 "$run/scripts/verify_context.py" --private "$work/cases" --repeat "$work/repeat/primary.tsv" --fixtures "$work/fixtures" --msn "$msn" --ter "$ter" --exe "$exe" --gzf "$gzf" --zfs "$zfs" --corruptions --emit "$work/derived" > "$work/verification.json"
python3 "$run/scripts/check_publication.py" "$run" "$work/derived" > "$work/publication.log"
python3 "$repo/agent/protocol/tools/validate_protocol.py" "$run" > "$work/protocol.log"
