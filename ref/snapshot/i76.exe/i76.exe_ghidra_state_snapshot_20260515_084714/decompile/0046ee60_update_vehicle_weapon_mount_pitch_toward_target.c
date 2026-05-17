/*
 * Program: i76.exe
 * Function: update_vehicle_weapon_mount_pitch_toward_target
 * Entry: 0046ee60
 * Signature: undefined __cdecl update_vehicle_weapon_mount_pitch_toward_target(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Updates vehicle weapon mount
   pitch/aim toward target using targeting transforms. */

void __cdecl update_vehicle_weapon_mount_pitch_toward_target(int param_1,float param_2)

{
  float fVar1;
  double dVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 extraout_ST1;
  undefined8 local_a8;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [6];
  float local_68;
  float local_64;
  float local_60;
  double local_58;
  double local_50;
  double local_48;
  float afStack_40 [16];
  
  fVar13 = get_runtime_frame_delta_seconds();
  pfVar9 = *(float **)(param_1 + 0x70);
  pfVar12 = (float *)(param_1 + 0x18);
  pfVar8 = pfVar9;
  pfVar11 = pfVar12;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar11 = *pfVar8;
    pfVar8 = pfVar8 + 1;
    pfVar11 = pfVar11 + 1;
  }
  if (param_2 == 0.0) {
    local_9c = (float)fVar13 * _DAT_004be544;
    pfVar9[0x10] = 0.0;
    if (((local_9c < _DAT_004be538) || (_DAT_004be548 < local_9c)) ||
       (fVar13 = -(float10)pfVar9[0x11], ABS(fVar13) < (float10)_DAT_004be550)) {
      fVar14 = (float10)_DAT_004be538;
    }
    else {
      fVar14 = fVar13 * (float10)local_9c + (float10)pfVar9[0x11];
    }
  }
  else {
    pfVar8 = (float *)compute_transform_relative_to_ancestor(local_80,param_1,0);
    pfVar11 = local_80;
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar11 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pfVar11 = pfVar11 + 1;
    }
    local_8c = (float)local_58;
    local_88 = (float)local_50;
    local_84 = (float)local_48;
    local_98 = local_68;
    local_94 = local_64;
    local_90 = local_60;
    pfVar8 = (float *)get_world_object_position_vector((float *)&local_a8,param_2);
    local_a0 = pfVar8[2] - local_84;
    fVar1 = SQRT((*pfVar8 - local_8c) * (*pfVar8 - local_8c) + local_a0 * local_a0);
    fVar4 = pfVar8[1] - local_88;
    local_90 = SQRT(local_68 * local_68 + local_60 * local_60);
    dVar2 = (double)(fVar1 * fVar1 + fVar4 * fVar4);
    local_a8._4_4_ = (uint)((ulonglong)dVar2 >> 0x20);
    uVar6 = local_a8._4_4_;
    local_a8._0_4_ = SUB84(dVar2,0);
    fVar5 = (float)local_a8;
    local_a8 = dVar2;
    fVar14 = zone_satellite_map_context_helper_00495000(fVar5,uVar6);
    fVar5 = _DAT_004be538;
    dVar2 = (double)(local_90 * local_90 + local_94 * local_94);
    local_a8._4_4_ = (uint)((ulonglong)dVar2 >> 0x20);
    uVar6 = local_a8._4_4_;
    local_a8._0_4_ = SUB84(dVar2,0);
    fVar7 = (float)local_a8;
    local_a8 = dVar2;
    fVar15 = zone_satellite_map_context_helper_00495000(fVar7,uVar6);
    local_88 = local_94 * (float)fVar15;
    local_a8._4_4_ = (uint)((ulonglong)(double)fVar15 >> 0x20);
    local_a8 = (double)CONCAT44(local_a8._4_4_,
                                SQRT((float)((float10)fVar1 * fVar14) *
                                     (float)((float10)fVar1 * fVar14) +
                                     (float)((float10)fVar4 * fVar14) *
                                     (float)((float10)fVar4 * fVar14) + fVar5 * fVar5));
    _CIasin();
    fVar14 = (float10)_CIasin();
    fVar14 = extraout_ST1 - fVar14;
    if ((float10)_DAT_004be53c < fVar14) {
      fVar14 = (float10)_DAT_004be53c;
    }
    if (fVar14 < (float10)_DAT_004be540) {
      fVar14 = (float10)_DAT_004be540;
    }
    local_9c = (float)fVar13 * _DAT_004be544;
    fVar14 = -fVar14;
    bVar3 = _DAT_004be538 <= local_9c;
    pfVar9[0x10] = (float)fVar14;
    if ((bVar3) && (local_9c <= _DAT_004be548)) {
      fVar13 = fVar14 - (float10)pfVar9[0x11];
      fVar1 = (float)fVar13;
      local_a8 = (double)CONCAT44(local_a8._4_4_,fVar1);
      if ((float10)_DAT_004be550 <= ABS(fVar13)) {
        fVar14 = (float10)local_9c * (float10)fVar1 + (float10)pfVar9[0x11];
      }
    }
  }
  pfVar9[0x11] = (float)fVar14;
  pfVar9 = (float *)zone_satellite_map_context_helper_00493e00(local_80,pfVar9[0x11]);
  pfVar8 = afStack_40;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar8 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar8 = pfVar8 + 1;
  }
  pfVar9 = compose_matrix_or_transform_a(local_80,afStack_40,pfVar12);
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar12 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar12 = pfVar12 + 1;
  }
  return;
}


