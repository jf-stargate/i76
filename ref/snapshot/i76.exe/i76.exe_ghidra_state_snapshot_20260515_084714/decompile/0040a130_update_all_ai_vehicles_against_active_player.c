/*
 * Program: i76.exe
 * Function: update_all_ai_vehicles_against_active_player
 * Entry: 0040a130
 * Signature: undefined __stdcall update_all_ai_vehicles_against_active_player(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: Updates all registered AI vehicles against the
   active player/camera object or brakes them when no active object exists. */

void update_all_ai_vehicles_against_active_player(void)

{
  float *pfVar1;
  LPVOID pvVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  float10 fVar9;
  int *local_c;
  
  fVar9 = get_runtime_time_seconds();
  if ((float10)_DAT_005095a8 < fVar9) {
    set_game_flow_state(DAT_0051f5fc);
  }
  piVar4 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar4 != (int *)0x0) {
    pvVar2 = (LPVOID)*piVar4;
    if ((DAT_0051f5fc == -1) && ((*(uint *)((int)pvVar2 + 0x10) & 0x200) != 0)) {
      fVar9 = get_runtime_time_seconds();
      DAT_0051f5fc = 1;
      _DAT_005095a8 = (float)(fVar9 - (float10)_DAT_004bc5fc);
    }
    piVar7 = &DAT_0051f5d0;
    local_c = &DAT_00507da0;
    do {
      iVar6 = *piVar7;
      piVar8 = local_c;
      if (0 < iVar6) {
        do {
          piVar3 = (int *)*piVar8;
          if (((piVar3 != (int *)0x0) && (piVar4 != piVar3)) &&
             (iVar5 = fsm_query_world_object_flag_0x200_set(*piVar3), iVar5 == 0)) {
            update_vehicle_ai_target_and_attack_state((LPVOID)*piVar3,pvVar2,0);
          }
          iVar6 = iVar6 + -1;
          piVar8 = piVar8 + 1;
        } while (iVar6 != 0);
      }
      piVar7 = piVar7 + 1;
      local_c = local_c + 0x40;
    } while ((int)piVar7 < 0x51f5f0);
    return;
  }
  piVar4 = &DAT_0051f5d0;
  local_c = &DAT_00507da0;
  do {
    iVar6 = *piVar4;
    piVar7 = local_c;
    if (0 < iVar6) {
      do {
        pfVar1 = (float *)*piVar7;
        if ((pfVar1 != (float *)0x0) &&
           (iVar5 = fsm_query_world_object_flag_0x200_set((int)*pfVar1), iVar5 == 0)) {
          set_vehicle_brake_to_max_safe_value(*pfVar1);
        }
        iVar6 = iVar6 + -1;
        piVar7 = piVar7 + 1;
      } while (iVar6 != 0);
    }
    piVar4 = piVar4 + 1;
    local_c = local_c + 0x40;
  } while ((int)piVar4 < 0x51f5f0);
  return;
}


