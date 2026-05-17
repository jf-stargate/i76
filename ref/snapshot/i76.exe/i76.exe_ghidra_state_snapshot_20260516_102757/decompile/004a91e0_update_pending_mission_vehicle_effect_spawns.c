/*
 * Program: i76.exe
 * Function: update_pending_mission_vehicle_effect_spawns
 * Entry: 004a91e0
 * Signature: undefined __stdcall update_pending_mission_vehicle_effect_spawns(void)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Walks pending effect/spawn
   records, countdown timers, places objects, and dispatches mission vehicle effects by slot. */

void update_pending_mission_vehicle_effect_spawns(void)

{
  int iVar1;
  int *piVar2;
  int *lpMem;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  int local_10;
  int local_c [2];
  
  lpMem = g_pending_mission_vehicle_effect_spawn_list;
  while (lpMem != (int *)0x0) {
    find_selected_mission_runtime_index(**(int **)(*lpMem + 0x70));
    pfVar4 = (float *)(lpMem + 3);
    iVar3 = 0xe;
    do {
      if (pfVar4[-1] == 1.4013e-45) {
        local_c[0] = 0;
        local_10 = -1;
        fVar5 = get_network_or_session_runtime_seconds();
        if (fVar5 <= (float10)pfVar4[3]) {
          fVar5 = get_runtime_frame_delta_seconds();
          pfVar4[3] = (float)((float10)pfVar4[3] - fVar5);
        }
        else {
          iVar1 = *lpMem;
          *(double *)(iVar1 + 0x40) = (double)*pfVar4;
          *(double *)(iVar1 + 0x48) = (double)pfVar4[1];
          *(double *)(iVar1 + 0x50) = (double)pfVar4[2];
          scan_effect_targets_for_collision_response_b(*lpMem,0,pfVar4,local_c,&local_10);
          spawn_mission_vehicle_effect_by_slot(*lpMem,pfVar4,local_c[0],local_10);
          lpMem[1] = lpMem[1] + -1;
          pfVar4[-1] = 0.0;
        }
      }
      pfVar4 = pfVar4 + 5;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (lpMem[1] == 0) {
      piVar2 = (int *)lpMem[0x48];
      g_pending_mission_vehicle_effect_spawn_list = piVar2;
      HeapFree(DAT_005da7b0,0,lpMem);
      lpMem = piVar2;
    }
    else {
      lpMem = (int *)lpMem[0x48];
    }
  }
  return;
}


