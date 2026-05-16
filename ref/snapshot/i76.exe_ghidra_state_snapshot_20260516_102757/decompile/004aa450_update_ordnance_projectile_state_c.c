/*
 * Program: i76.exe
 * Function: update_ordnance_projectile_state_c
 * Entry: 004aa450
 * Signature: undefined4 __cdecl update_ordnance_projectile_state_c(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

undefined4 __cdecl update_ordnance_projectile_state_c(int param_1)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  LPVOID pvVar5;
  int iVar6;
  undefined4 *puVar7;
  int local_30;
  int local_2c;
  LPVOID local_28;
  float local_24;
  int local_20;
  undefined4 *local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_18 = (float)*(double *)(param_1 + 0x40);
  local_14 = (float)*(double *)(param_1 + 0x48);
  puVar7 = (undefined4 *)(*(int *)(param_1 + 0x70) + 0x10);
  local_10 = (float)*(double *)(param_1 + 0x50);
  local_1c = puVar7;
  local_c = local_18;
  local_8 = local_14;
  local_4 = local_10;
  local_28 = release_world_object_tree_reference
                       (*(LPVOID *)(*(int *)(param_1 + 0x70) + 0xc),s_ordnc_004fe6f0);
  *(LPVOID *)(*(int *)(param_1 + 0x70) + 0xc) = local_28;
  iVar6 = *(int *)(param_1 + 0x70);
  bVar1 = false;
  local_30 = 0;
  if (0 < *(int *)(iVar6 + 0x3c)) {
    local_24 = *(float *)(iVar6 + 8) - *(float *)(iVar6 + 4);
    local_2c = *(int *)(iVar6 + 0x3c);
    do {
      fVar4 = local_10;
      fVar3 = local_14;
      fVar2 = local_18;
      local_14 = local_14 - _DAT_004bebf4;
      pvVar5 = local_28;
      if (_DAT_004bebf8 < local_24) {
        pvVar5 = (LPVOID)0x0;
      }
      iVar6 = scan_effect_targets_for_collision_response_b
                        (param_1,(int)pvVar5,&local_18,&local_30,&local_20);
      if (iVar6 != 0) {
        bVar1 = true;
      }
      local_18 = fVar2;
      local_14 = fVar3;
      local_10 = fVar4;
      if (bVar1) {
        spawn_mission_vehicle_effect_by_slot(param_1,&local_18,local_30,local_20);
      }
      local_2c = local_2c + -1;
    } while (local_2c != 0);
    local_2c = 0;
    puVar7 = local_1c;
  }
  if ((LPVOID)*puVar7 != (LPVOID)0x0) {
    finalize_released_world_object_after_damage((LPVOID)*puVar7,s_ordnc_004fe6f0);
    *puVar7 = 0;
  }
  return 1;
}


