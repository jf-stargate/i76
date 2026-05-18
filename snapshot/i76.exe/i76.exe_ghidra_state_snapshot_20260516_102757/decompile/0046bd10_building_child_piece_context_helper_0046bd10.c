/*
 * Program: i76.exe
 * Function: building_child_piece_context_helper_0046bd10
 * Entry: 0046bd10
 * Signature: undefined __cdecl building_child_piece_context_helper_0046bd10(int param_1, uint * param_2, float * param_3, float * param_4, float * param_5, float * param_6, float * param_7, float param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was building_world_object_building_child_piece_helper_0046bd10. Remove
   duplicated building wording. */

void __cdecl
building_child_piece_context_helper_0046bd10
          (int param_1,uint *param_2,float *param_3,float *param_4,float *param_5,float *param_6,
          float *param_7,float param_8)

{
  float fVar1;
  double dVar2;
  float fVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  float fVar12;
  float10 fVar13;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  undefined8 local_b8;
  float local_b0;
  float local_ac;
  uint local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80 [10];
  double local_58;
  double local_50;
  double local_48;
  float local_40 [16];
  
  local_a4 = (float)*(double *)(param_1 + 0x40);
  pfVar8 = (float *)(param_1 + 0x18);
  iVar10 = *(int *)(param_1 + 0x70);
  local_a0 = (float)*(double *)(param_1 + 0x48);
  local_e4 = *(float *)(iVar10 + 0x508);
  local_9c = (float)*(double *)(param_1 + 0x50);
  local_d0 = *(float *)(iVar10 + 0xbc);
  local_cc = *(float *)(iVar10 + 0xc0);
  local_c8 = *(float *)(iVar10 + 0xc4);
  fVar12 = *(float *)(iVar10 + 0xbc);
  local_c0 = *(float *)(iVar10 + 0xc0);
  local_bc = *(float *)(iVar10 + 0xc4);
  local_ac = *(float *)(iVar10 + 0xac);
  local_f0 = *(float *)(param_1 + 0x30);
  local_a8 = *(uint *)(iVar10 + 0x454);
  local_e8 = *(float *)(param_1 + 0x38);
  local_ec = *(float *)(param_1 + 0x34);
  local_94 = 0.0;
  dVar2 = (double)(local_e8 * local_e8 + local_f0 * local_f0);
  local_c4 = fVar12;
  local_98 = local_f0;
  local_90 = local_e8;
  fVar13 = zone_satellite_map_context_helper_00495000
                     (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  local_98 = (float)((float10)local_98 * fVar13);
  local_ec = (float)((float10)local_94 * fVar13);
  local_f0 = *pfVar8;
  local_e8 = *(float *)(param_1 + 0x20);
  local_90 = (float)((float10)local_90 * fVar13);
  dVar2 = (double)(local_e8 * local_e8 + local_f0 * local_f0);
  local_94 = local_ec;
  fVar13 = zone_satellite_map_context_helper_00495000
                     (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  fVar6 = local_e4;
  fVar5 = _DAT_004be330;
  local_f0 = local_f0 * (float)fVar13;
  local_e8 = local_e8 * (float)fVar13;
  local_b8 = (double)CONCAT44(_DAT_004be330,_DAT_004be330);
  local_b0 = _DAT_004be330;
  local_d8 = _DAT_004be330;
  local_ec = _DAT_004be330;
  local_dc = _DAT_004be330;
  local_d4 = _DAT_004be330;
  if ((local_a8 & 0x8000) == 0) {
    fVar1 = local_a0;
    if ((local_a8 & 0x80) == 0) {
      if (_DAT_004be33c <= local_a0) {
        fVar3 = *(float *)((int)local_e4 + 0xc);
        fVar1 = *(float *)(iVar10 + 0xe4);
        local_b8 = (double)CONCAT44(_DAT_004be330,fVar3);
        if (((_DAT_004be330 <= param_8) && (param_8 <= _DAT_004be340)) &&
           ((float)_DAT_004be348 <= ABS(fVar1 - fVar3))) {
          fVar1 = (fVar1 - fVar3) * param_8 + fVar3;
        }
        bVar4 = _DAT_004be330 <= param_8;
        *(float *)((int)local_e4 + 0xc) = fVar1;
        fVar1 = *(float *)(iVar10 + 0xe0);
        if ((bVar4) && (param_8 <= _DAT_004be340)) {
          fVar3 = fVar1 - *(float *)((int)local_e4 + 0x10);
          local_b8 = (double)CONCAT44(fVar5,fVar3);
          if ((float)_DAT_004be348 <= ABS(fVar3)) {
            fVar1 = fVar3 * param_8 + *(float *)((int)local_e4 + 0x10);
          }
        }
        *(float *)((int)local_e4 + 0x10) = fVar1;
      }
      else {
        *(undefined4 *)((int)local_e4 + 0xc) = 0;
        *(undefined4 *)((int)local_e4 + 0x10) = 0;
      }
      fVar5 = *(float *)((int)local_e4 + 0xc) * _DAT_004be350;
      local_e0 = *(float *)((int)local_e4 + 0x10) * _DAT_004be354;
      local_e4 = fVar5;
      if ((_DAT_004be330 < fVar5) ||
         (iVar10 = world_object_has_optional_runtime_flag(param_1), iVar10 != 0)) {
        local_dc = local_e4 * local_98 + local_f0 * local_e0;
        local_d8 = local_e4 * local_94 + local_ec * local_e0;
        local_d4 = local_e4 * local_90 + local_e8 * local_e0;
      }
      else if (local_ac <= -local_e4) {
        if (_DAT_004be328 < local_ac) {
          local_dc = local_f0 * local_e0 - local_c4;
          local_d8 = local_ec * local_e0 - local_c0;
          local_d4 = local_e8 * local_e0 - local_bc;
        }
        else if (local_ac <= _DAT_004be330) {
          fVar12 = 0.0;
          local_e8 = 0.0;
          local_ac = 0.0;
          local_c4 = 0.0;
          local_c0 = 0.0;
          local_bc = 0.0;
          local_dc = 0.0;
          local_d8 = 0.0;
          local_d4 = local_e8;
        }
        else {
          local_dc = local_c4 * _DAT_004be358;
          local_d8 = local_c0 * _DAT_004be358;
          local_d4 = local_bc * _DAT_004be358;
        }
      }
      else {
        fVar5 = local_e4 / local_ac;
        local_dc = local_f0 * local_e0 + fVar5 * local_c4;
        local_d8 = local_ec * local_e0 + fVar5 * local_c0;
        local_d4 = local_e8 * local_e0 + fVar5 * local_bc;
      }
      if (_DAT_004be328 < local_ac) {
        fVar5 = local_ac * _DAT_004be35c;
        local_dc = fVar5 * local_c4 + local_dc;
        local_d8 = fVar5 * local_c0 + local_d8;
        local_d4 = fVar5 * local_bc + local_d4;
      }
      local_cc = local_c0;
      local_c8 = local_bc;
      local_f0 = local_dc;
      local_ec = local_d8;
      local_e8 = local_d4;
      local_d0 = fVar12;
      effect_target_list_scan_context_helper_004383a0(&local_a4,&local_d0,&local_dc,param_8);
      iVar10 = world_object_has_optional_runtime_flag(param_1);
      if (((iVar10 == 0) && (*(float *)((int)fVar6 + 0xc) < _DAT_004be330)) &&
         (local_c8 * local_bc + local_cc * local_c0 + local_d0 * local_c4 < _DAT_004be330)) {
        local_f0 = 0.0;
        local_ec = 0.0;
        local_e8 = 0.0;
        local_d0 = 0.0;
        local_cc = 0.0;
        local_c8 = 0.0;
        local_dc = 0.0;
        local_d8 = 0.0;
        local_d4 = 0.0;
      }
      probe_effect_target_surface_height_at_position
                ((double)CONCAT44(local_a0,local_a4),local_9c,&local_e4,(undefined4 *)0x0);
      if (local_a0 < local_e4) {
        local_d0 = 0.0;
        local_dc = 0.0;
        local_a8 = local_a8 | 0x20;
        local_cc = 0.0;
        local_c8 = 0.0;
        local_d8 = 0.0;
        local_d4 = 0.0;
      }
      local_f0 = local_a4 - local_d0 * _DAT_004be360;
      local_ec = local_a0 - local_cc * _DAT_004be360;
      local_e8 = local_9c - local_c8 * _DAT_004be360;
      probe_effect_target_surface_height_at_position
                ((double)CONCAT44(local_ec,local_f0),local_e8,(float *)&local_b8,(undefined4 *)0x0);
      if (local_e4 < (float)local_b8) {
        local_e4 = (float)local_b8;
      }
      fVar1 = *(float *)((int)fVar6 + 0x14) + local_e4;
      local_e4 = param_8 * _DAT_004be364;
      if ((_DAT_004be330 <= local_e4) && (local_e4 <= _DAT_004be340)) {
        fVar12 = fVar1 - local_a0;
        local_b8 = (double)CONCAT44(local_b8._4_4_,fVar12);
        if ((float)_DAT_004be348 <= ABS(fVar12)) {
          fVar1 = local_e4 * fVar12 + local_a0;
        }
      }
    }
  }
  else {
    iVar10 = *(int *)(param_1 + 0x70);
    pfVar7 = param_7;
    pfVar11 = local_80;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar11 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar11 = pfVar11 + 1;
    }
    pfVar7 = (float *)copy_transform_position_vec3((float *)&local_b8,(int)pfVar8);
    local_f0 = *pfVar7;
    local_ec = pfVar7[1];
    local_e8 = pfVar7[2];
    local_c4 = *(float *)(iVar10 + 0xbc);
    local_c0 = *(float *)(iVar10 + 0xc0);
    local_bc = *(float *)(iVar10 + 0xc4);
    integrate_vertical_motion_with_gravity(&local_f0,&local_c4,-9.8,param_8);
    probe_effect_target_surface_height_at_position
              ((double)CONCAT44(local_ec,local_f0),local_e8,&local_e4,(undefined4 *)0x0);
    if (local_ec <= local_e4 - _DAT_004be334) {
      local_c0 = 0.0;
      local_ec = local_e4;
    }
    pfVar7 = local_80;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar7 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pfVar7 = pfVar7 + 1;
    }
    store_vec3_as_double_triplet((int)local_80,&local_f0);
    local_cc = local_c0;
    local_d0 = local_c4;
    local_c8 = local_bc;
    *param_6 = *(float *)(iVar10 + 200);
    param_6[1] = *(float *)(iVar10 + 0xcc);
    param_6[2] = *(float *)(iVar10 + 0xd0);
    pfVar8 = (float *)effect_target_list_scan_context_helper_004389f0
                                (local_40,local_80,*(float *)(iVar10 + 200),
                                 *(float *)(iVar10 + 0xcc),*(float *)(iVar10 + 0xd0),param_8);
    pfVar7 = local_80;
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar7 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pfVar7 = pfVar7 + 1;
    }
    local_f0 = (float)local_58;
    local_ec = (float)local_50;
    local_e8 = (float)local_48;
    local_a4 = local_f0;
    local_a0 = local_ec;
    local_9c = local_e8;
    probe_effect_target_surface_height_at_position
              ((double)CONCAT44(local_ec,local_f0),local_e8,(float *)&local_b8,(undefined4 *)0x0);
    fVar1 = local_a0;
    if (local_a0 == (float)local_b8) {
      local_a8 = local_a8 | 0x20;
    }
  }
  local_a0 = fVar1;
  fVar12 = _DAT_004be330;
  if ((local_a8 & 0x8000) == 0) {
    local_88 = local_d8 - _DAT_004be368;
    local_8c = local_dc;
    local_84 = local_d4;
    local_f0 = _DAT_004be330;
    local_ec = _DAT_004be330;
    local_e8 = _DAT_004be330;
    *param_6 = _DAT_004be330;
    param_6[1] = fVar12;
    param_6[2] = fVar12;
    dVar2 = (double)(local_d4 * local_d4 + local_88 * local_88 + local_dc * local_dc);
    fVar13 = zone_satellite_map_context_helper_00495000
                       (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
    local_b8 = (double)fVar13;
    local_f0 = local_8c * (float)fVar13;
    local_ec = local_88 * (float)fVar13;
    local_e8 = local_84 * (float)fVar13;
    if ((local_ac < _DAT_004be328) ||
       (local_90 * local_c8 + local_94 * local_cc + local_98 * local_d0 <= _DAT_004be330)) {
      pfVar8 = &local_98;
    }
    else {
      pfVar8 = &local_d0;
    }
    local_8c = local_f0;
    local_88 = local_ec;
    local_84 = local_e8;
    pfVar8 = (float *)zone_satellite_map_context_helper_00494710(&local_8c,pfVar8,local_40);
    pfVar7 = local_80;
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pfVar7 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pfVar7 = pfVar7 + 1;
    }
  }
  *param_5 = local_dc;
  param_5[1] = local_d8;
  param_5[2] = local_d4;
  *param_3 = local_d0;
  param_3[1] = local_cc;
  param_3[2] = local_c8;
  *param_4 = SQRT(local_c8 * local_c8 + local_cc * local_cc + local_d0 * local_d0);
  *param_2 = local_a8;
  local_58 = (double)local_a4;
  local_50 = (double)local_a0;
  local_48 = (double)local_9c;
  pfVar8 = local_80;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *param_7 = *pfVar8;
    pfVar8 = pfVar8 + 1;
    param_7 = param_7 + 1;
  }
  return;
}


