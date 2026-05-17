/*
 * Program: i76.exe
 * Function: update_ordnance_projectile_state_b
 * Entry: 004aa2d0
 * Signature: undefined4 __cdecl update_ordnance_projectile_state_b(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

undefined4 __cdecl update_ordnance_projectile_state_b(int *param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  int *piVar4;
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
  
  piVar4 = param_1;
  local_18 = (float)*(double *)(param_1 + 0x10);
  local_14 = (float)*(double *)(param_1 + 0x12);
  puVar11 = (undefined4 *)(param_1[0x1c] + 0x10);
  local_10 = (float)*(double *)(param_1 + 0x14);
  local_1c = puVar11;
  local_c = local_18;
  local_8 = local_14;
  local_4 = local_10;
  pvVar8 = release_world_object_tree_reference(*(LPVOID *)(param_1[0x1c] + 0xc),s_ordnc_004fe6f0);
  *(LPVOID *)(piVar4[0x1c] + 0xc) = pvVar8;
  iVar10 = piVar4[0x1c];
  fVar1 = *(float *)(iVar10 + 4);
  local_2c = *(int *)(iVar10 + 0x3c);
  fVar2 = *(float *)(iVar10 + 8);
  bVar3 = false;
  param_1 = (int *)0x0;
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
                         ((int)piVar4,(int)pvVar9,&local_18,(int *)&param_1,&local_20);
      if (iVar10 != 0) {
        bVar3 = true;
      }
      local_18 = fVar5;
      local_14 = fVar6;
      local_10 = fVar7;
      if (bVar3) {
        iVar10 = is_vehicle_or_actor_runtime_world_object((int)param_1);
        if (iVar10 != 0) {
          apply_flat_tire_damage_from_hazard_collision((float)param_1,piVar4);
        }
        spawn_mission_vehicle_effect_by_slot((int)piVar4,&local_18,(int)param_1,local_20);
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


