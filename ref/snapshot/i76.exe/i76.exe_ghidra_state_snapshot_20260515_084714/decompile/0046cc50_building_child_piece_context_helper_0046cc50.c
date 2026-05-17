/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046cc50
 * Entry: 0046cc50
 * Signature: undefined __cdecl building_child_piece_context_helper_0046cc50(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046cc50. Remove
   duplicated building wording. */

void __cdecl building_child_piece_context_helper_0046cc50(int param_1,float *param_2)

{
  int iVar1;
  bool bVar2;
  float *pfVar3;
  undefined3 extraout_var;
  float fVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float *pfVar9;
  float10 fVar10;
  undefined4 auStack_8c [11];
  undefined4 uStack_60;
  undefined4 local_3c [15];
  
  iVar1 = *(int *)(param_1 + 0x70);
  fVar10 = get_runtime_time_seconds();
  *param_2 = (float)fVar10;
  puVar7 = (undefined4 *)(param_1 + 0x18);
  puVar8 = auStack_8c;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  pfVar3 = (float *)runtime_library_memory_copy_helper_004bb010(local_3c);
  pfVar9 = param_2;
  for (iVar6 = 9; pfVar9 = pfVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar9 = *pfVar3;
    pfVar3 = pfVar3 + 1;
  }
  iVar6 = copy_vehicle_runtime_transform_matrix(local_3c,param_1);
  param_2[10] = *(float *)(iVar6 + 0x18);
  param_2[0xb] = *(float *)(iVar6 + 0x1c);
  param_2[0xc] = *(float *)(iVar6 + 0x20);
  iVar6 = copy_vehicle_runtime_transform_matrix(local_3c,param_1);
  param_2[0xd] = *(float *)(iVar6 + 0x24);
  param_2[0xe] = *(float *)(iVar6 + 0x28);
  param_2[0xf] = *(float *)(iVar6 + 0x2c);
  param_2[0x10] = *(float *)(iVar1 + 0xe4);
  param_2[0x11] = *(float *)(iVar1 + 0xe0);
  param_2[0x12] = 0.0;
  if ((*(byte *)(iVar1 + 0x454) & 0x20) != 0) {
    param_2[0x12] = 1.12104e-44;
  }
  if ((*(byte *)(iVar1 + 0x454) & 1) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x20);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x8000) == 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x200);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x40000) != 0) {
    bVar2 = radar_render_context_helper_00461680(param_1);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      param_2[0x12] = (float)((uint)param_2[0x12] | 0x400);
    }
  }
  fVar10 = compute_world_object_damage_integrity_percent(param_1);
  if (fVar10 <= (float10)_DAT_004be36c) {
    if (fVar10 <= (float10)_DAT_004be370) {
      fVar4 = (float)((uint)param_2[0x12] | 0x40000000);
    }
    else {
      fVar4 = (float)((uint)param_2[0x12] | 0x80000000);
    }
  }
  else {
    fVar4 = (float)((uint)param_2[0x12] | 0xc0000000);
  }
  param_2[0x12] = fVar4;
  uVar5 = get_primary_vehicle_weapon_target_object(param_1);
  if (uVar5 == 0) {
    *(undefined2 *)(param_2 + 0x15) = 0;
  }
  else {
    iVar6 = is_vehicle_or_actor_runtime_world_object(uVar5);
    if (iVar6 == 0) {
      *(short *)(param_2 + 0x15) = *(short *)(*(int *)(uVar5 + 0x70) + 8) + 1;
      param_2[0x12] = (float)((uint)param_2[0x12] | 0x40);
    }
    else {
      *(undefined2 *)(param_2 + 0x15) = *(undefined2 *)(*(int *)(uVar5 + 0x70) + 0x480);
    }
  }
  if ((*(byte *)(iVar1 + 0x454) & 0x20) == 0) {
    param_2[0x16] = 0.0;
  }
  else {
    *(undefined2 *)(param_2 + 0x16) = *(undefined2 *)(iVar1 + 0x482);
  }
  *(undefined1 *)((int)param_2 + 0x5d) = 0;
  *(undefined1 *)(param_2 + 0x17) = 0;
  uStack_60 = 0x46ce16;
  get_multiplayer_player_spawn_score_fields
            (*(short *)(iVar1 + 0x480),param_2 + 0x13,(undefined2 *)(param_2 + 0x14),
             (undefined2 *)((int)param_2 + 0x52));
  return;
}


