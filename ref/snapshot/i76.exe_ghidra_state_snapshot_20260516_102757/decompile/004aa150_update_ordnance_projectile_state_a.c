/*
 * Program: i76.exe
 * Function: update_ordnance_projectile_state_a
 * Entry: 004aa150
 * Signature: undefined4 __cdecl update_ordnance_projectile_state_a(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

undefined4 __cdecl update_ordnance_projectile_state_a(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  LPVOID pvVar8;
  LPVOID pvVar9;
  int iVar10;
  undefined4 *puVar11;
  int local_2c;
  int local_20;
  undefined4 *local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar4 = param_1;
  local_18 = (float)*(double *)(param_1 + 0x40);
  local_14 = (float)*(double *)(param_1 + 0x48);
  puVar11 = (undefined4 *)(*(int *)(param_1 + 0x70) + 0x10);
  local_10 = (float)*(double *)(param_1 + 0x50);
  local_1c = puVar11;
  local_c = local_18;
  local_8 = local_14;
  local_4 = local_10;
  pvVar8 = release_world_object_tree_reference
                     (*(LPVOID *)(*(int *)(param_1 + 0x70) + 0xc),s_ordnc_004fe6f0);
  *(LPVOID *)(*(int *)(iVar4 + 0x70) + 0xc) = pvVar8;
  iVar10 = *(int *)(iVar4 + 0x70);
  fVar1 = *(float *)(iVar10 + 4);
  local_2c = *(int *)(iVar10 + 0x3c);
  fVar2 = *(float *)(iVar10 + 8);
  bVar3 = false;
  param_1 = 0;
  if (0 < local_2c) {
    do {
      fVar7 = local_10;
      fVar6 = local_14;
      fVar5 = local_18;
      local_14 = local_14 - _DAT_004bebf4;
      pvVar9 = pvVar8;
      if (_DAT_004bebf8 < fVar2 - fVar1) {
        pvVar9 = (LPVOID)0x0;
      }
      iVar10 = scan_effect_targets_for_collision_response_b
                         (iVar4,(int)pvVar9,&local_18,&param_1,&local_20);
      if (iVar10 != 0) {
        bVar3 = true;
      }
      local_18 = fVar5;
      local_14 = fVar6;
      local_10 = fVar7;
      if (bVar3) {
        iVar10 = is_vehicle_or_actor_runtime_world_object(param_1);
        if (iVar10 != 0) {
          mark_vehicle_runtime_state_dirty(param_1);
        }
        spawn_mission_vehicle_effect_by_slot(iVar4,&local_18,param_1,local_20);
      }
      local_2c = local_2c + -1;
      puVar11 = local_1c;
    } while (local_2c != 0);
  }
  if ((LPVOID)*puVar11 != (LPVOID)0x0) {
    finalize_released_world_object_after_damage((LPVOID)*puVar11,s_ordnc_004fe6f0);
    *puVar11 = 0;
  }
  return 1;
}


