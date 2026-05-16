/*
 * Program: i76.exe
 * Function: vehicle_damage_network_context_helper_004644d0
 * Entry: 004644d0
 * Signature: undefined __cdecl vehicle_damage_network_context_helper_004644d0(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: vehicle damage network context helper
   based on prior focused closure context. */

void __cdecl vehicle_damage_network_context_helper_004644d0(int param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  float fVar4;
  bool bVar5;
  byte bVar6;
  undefined1 uVar7;
  float *pfVar8;
  undefined3 extraout_var;
  float fVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  float *pfVar14;
  undefined4 *puVar15;
  int *piVar16;
  float10 fVar17;
  undefined4 auStack_9c [11];
  undefined4 uStack_70;
  int local_44;
  int local_40;
  undefined4 local_3c [6];
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  iVar1 = *(int *)(param_1 + 0x70);
  fVar17 = get_runtime_time_seconds();
  *param_2 = (float)fVar17;
  puVar13 = (undefined4 *)(param_1 + 0x18);
  puVar15 = auStack_9c;
  for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar15 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar15 = puVar15 + 1;
  }
  pfVar8 = (float *)runtime_library_memory_copy_helper_004bb010(local_3c);
  pfVar14 = param_2;
  for (iVar12 = 9; pfVar14 = pfVar14 + 1, iVar12 != 0; iVar12 = iVar12 + -1) {
    *pfVar14 = *pfVar8;
    pfVar8 = pfVar8 + 1;
  }
  puVar13 = (undefined4 *)(*(int *)(param_1 + 0x70) + 0xa4);
  puVar15 = local_3c;
  for (iVar12 = 0xf; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar15 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar15 = puVar15 + 1;
  }
  param_2[10] = local_24;
  param_2[0xb] = local_20;
  param_2[0xc] = local_1c;
  puVar13 = (undefined4 *)(*(int *)(param_1 + 0x70) + 0xa4);
  puVar15 = local_3c;
  for (iVar12 = 0xf; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar15 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar15 = puVar15 + 1;
  }
  param_2[0xd] = local_18;
  param_2[0xe] = local_14;
  param_2[0xf] = local_10;
  param_2[0x10] = *(float *)(iVar1 + 0xe4);
  param_2[0x11] = *(float *)(iVar1 + 0xe0);
  param_2[0x12] = 0.0;
  if (*(int *)(iVar1 + 0xe8) == -0x40800000) {
    param_2[0x12] = 5.60519e-45;
  }
  if (*(int *)(iVar1 + 0xf0) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 2);
  }
  if ((*(byte *)(iVar1 + 0x454) & 0x20) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 8);
  }
  if ((*(byte *)(iVar1 + 0x454) & 0x40) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x10);
  }
  if ((*(byte *)(iVar1 + 0x454) & 2) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 1);
  }
  if ((*(byte *)(iVar1 + 0x454) & 1) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x20);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x200000) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x800);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x4000) != 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x80);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x8000) == 0) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x200);
  }
  iVar12 = *(int *)(*(int *)(param_1 + 0x70) + 0x104);
  if ((iVar12 == 0) || (iVar12 == 2)) {
    param_2[0x12] = (float)((uint)param_2[0x12] | 0x100);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x40000) != 0) {
    bVar5 = radar_render_context_helper_00461680(param_1);
    if (CONCAT31(extraout_var,bVar5) != 0) {
      param_2[0x12] = (float)((uint)param_2[0x12] | 0x400);
    }
  }
  fVar17 = compute_world_object_damage_integrity_percent(param_1);
  if (fVar17 <= (float10)_DAT_004be1f0) {
    if (fVar17 <= (float10)_DAT_004be1f4) {
      fVar9 = (float)((uint)param_2[0x12] | 0x40000000);
    }
    else {
      fVar9 = (float)((uint)param_2[0x12] | 0x80000000);
    }
  }
  else {
    fVar9 = (float)((uint)param_2[0x12] | 0xc0000000);
  }
  param_2[0x12] = fVar9;
  uVar10 = get_primary_vehicle_weapon_target_object(param_1);
  if (uVar10 == 0) {
    *(undefined2 *)(param_2 + 0x15) = 0;
  }
  else {
    iVar12 = is_vehicle_or_actor_runtime_world_object(uVar10);
    if (iVar12 == 0) {
      *(short *)(param_2 + 0x15) = *(short *)(*(int *)(uVar10 + 0x70) + 8) + 1;
      param_2[0x12] = (float)((uint)param_2[0x12] | 0x40);
    }
    else {
      *(undefined2 *)(param_2 + 0x15) = *(undefined2 *)(*(int *)(uVar10 + 0x70) + 0x480);
    }
  }
  if ((*(byte *)(iVar1 + 0x454) & 0x20) == 0) {
    bVar6 = 0;
    iVar12 = 0x178;
    param_2[0x16] = 0.0;
    do {
      iVar11 = *(int *)(param_1 + 0x70);
      iVar2 = *(int *)(iVar11 + -0x20 + iVar12);
      if ((iVar2 == 0) || (iVar12 == 0x188)) {
        fVar9 = (float)*(int *)(iVar11 + iVar12) * _DAT_004be1d4;
      }
      else {
        fVar9 = (float)*(int *)(iVar11 + iVar12) / (float)iVar2;
      }
      iVar2 = *(int *)(iVar11 + -0x10 + iVar12);
      if ((iVar2 == 0) || (iVar12 == 0x188)) {
        fVar4 = (float)*(int *)(iVar11 + 0x14 + iVar12) * _DAT_004be1d4;
      }
      else {
        fVar4 = (float)*(int *)(iVar11 + 0x14 + iVar12) / (float)iVar2;
      }
      if (fVar9 <= fVar4) {
        fVar4 = fVar9;
      }
      if (fVar4 <= _DAT_004be1e8) {
        if (fVar4 <= _DAT_004be1dc) {
          iVar11 = 2;
          if (fVar4 <= _DAT_004be1ec) {
            iVar11 = 3;
          }
        }
        else {
          iVar11 = 1;
        }
      }
      else {
        iVar11 = 0;
      }
      bVar3 = bVar6 & 0x1f;
      iVar12 = iVar12 + 4;
      bVar6 = bVar6 + 2;
      param_2[0x16] = (float)((uint)param_2[0x16] | iVar11 << bVar3);
    } while (iVar12 < 0x18c);
  }
  else {
    *(undefined2 *)(param_2 + 0x16) = *(undefined2 *)(iVar1 + 0x482);
  }
  *(undefined1 *)((int)param_2 + 0x5d) = 0;
  iVar12 = 0;
  piVar16 = (int *)(iVar1 + 0x3a8);
  do {
    if (*piVar16 != 0) {
      extract_part_damage_state_pair(*piVar16,&local_44,&local_40);
      if (_DAT_004be1ec < (float)local_44 / (float)local_40) {
        bVar6 = 0;
      }
      else {
        bVar6 = (byte)(1 << ((byte)iVar12 & 0x1f));
      }
      *(byte *)((int)param_2 + 0x5d) = *(byte *)((int)param_2 + 0x5d) | bVar6;
    }
    iVar12 = iVar12 + 1;
    piVar16 = piVar16 + 1;
  } while (iVar12 < 6);
  compute_world_object_damage_integrity_percent(param_1);
  uVar7 = ftol();
  *(undefined1 *)(param_2 + 0x17) = uVar7;
  uStack_70 = 0x464879;
  get_multiplayer_player_spawn_score_fields
            (*(short *)(iVar1 + 0x480),param_2 + 0x13,(undefined2 *)(param_2 + 0x14),
             (undefined2 *)((int)param_2 + 0x52));
  return;
}


