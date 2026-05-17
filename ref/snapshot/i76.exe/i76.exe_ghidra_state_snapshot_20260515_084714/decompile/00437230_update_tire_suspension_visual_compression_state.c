/*
 * Program: i76.exe
 * Function: update_tire_suspension_visual_compression_state
 * Entry: 00437230
 * Signature: undefined __cdecl update_tire_suspension_visual_compression_state(int param_1, float * param_2, int param_3, int param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Applies tire/suspension
   visual compression state to tire child objects using contact height and compression values. */

void __cdecl
update_tire_suspension_visual_compression_state
          (int param_1,float *param_2,int param_3,int param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  double *pdVar9;
  float fVar10;
  uint uVar11;
  double *pdVar12;
  float *pfVar13;
  float10 fVar14;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  undefined8 local_f0;
  double local_e8;
  double local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  double local_b8;
  double local_b0;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  undefined8 local_88;
  double local_80;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  double local_18;
  double local_10;
  double local_8;
  
  iVar8 = *(int *)(param_1 + 0x70);
  pdVar9 = (double *)(param_1 + 0x18);
  local_9c = *(float *)(iVar8 + 0x3ac);
  local_88 = *pdVar9;
  local_f0 = *pdVar9;
  local_e8 = (double)CONCAT44(local_e8._4_4_,*(undefined4 *)(param_1 + 0x20));
  local_a0 = *(float *)(iVar8 + 0x3a8);
  local_80 = (double)CONCAT44(local_80._4_4_,*(undefined4 *)(param_1 + 0x20));
  local_a8 = *(float *)(iVar8 + 0x3bc);
  local_a4 = *(float *)(iVar8 + 0x3b8);
  local_100 = *(float *)(iVar8 + 0x3b4);
  local_10c = *(float *)(param_1 + 0x30);
  local_f4 = *(float *)(iVar8 + 0x3b0);
  local_108 = *(float *)(param_1 + 0x34);
  local_104 = *(float *)(param_1 + 0x38);
  fVar10 = *(float *)(iVar8 + 0x45c);
  local_70 = local_10c;
  local_6c = local_108;
  local_68 = local_104;
  zone_satellite_map_context_helper_00493ca0
            (*param_2,param_2[1],param_2[2],local_10c,local_108,local_104,(float *)&local_d8,
             (float *)&local_f0);
  local_fc = ((float)local_d8 * local_10c + (float)local_d0 * local_104 + local_d8._4_4_ * local_108
             ) * _DAT_004bd040;
  fVar14 = dot_product_vec3((float *)&local_f0,(float *)&local_88);
  local_f8 = (float)(fVar14 * (float10)_DAT_004bd040);
  update_tire_contact_height_and_compression_state(local_9c,0,local_fc - local_f8,param_5,fVar10);
  update_tire_contact_height_and_compression_state(local_a0,0,local_f8 + local_fc,param_5,fVar10);
  update_tire_contact_height_and_compression_state(local_a8,0,-local_fc - local_f8,param_5,fVar10);
  update_tire_contact_height_and_compression_state(local_a4,0,local_f8 - local_fc,param_5,fVar10);
  if (local_100 != 0.0) {
    update_tire_contact_height_and_compression_state(local_100,0,0.0,param_5,fVar10);
  }
  if (local_f4 != 0.0) {
    update_tire_contact_height_and_compression_state(local_f4,0,0.0,param_5,fVar10);
  }
  fVar10 = local_9c;
  if (*(float *)(param_1 + 0x28) <= *(float *)(iVar8 + 0x478)) {
    local_10c = *(float *)(iVar8 + 4);
    local_108 = *(float *)(iVar8 + 0x34);
    local_104 = *(float *)(iVar8 + 0xc);
    transform_vec3_array_by_matrix(&local_10c,&local_10c,1,(float *)pdVar9);
    local_f4 = local_108;
    local_10c = *(float *)(iVar8 + 0x10);
    local_108 = *(float *)(iVar8 + 0x34);
    local_104 = *(float *)(iVar8 + 0x18);
    transform_vec3_array_by_matrix(&local_10c,&local_10c,1,(float *)pdVar9);
    local_100 = local_108;
    local_10c = *(float *)(iVar8 + 0x1c);
    local_108 = *(float *)(iVar8 + 0x34);
    local_104 = *(float *)(iVar8 + 0x24);
    transform_vec3_array_by_matrix(&local_10c,&local_10c,1,(float *)pdVar9);
    local_8c = local_108;
    local_10c = *(float *)(iVar8 + 0x28);
    local_108 = *(float *)(iVar8 + 0x34);
    local_104 = *(float *)(iVar8 + 0x30);
    transform_vec3_array_by_matrix(&local_10c,&local_10c,1,(float *)pdVar9);
    local_f8 = local_108;
    fVar10 = local_9c;
  }
  else {
    iVar4 = get_tire_world_position_minus_contact_offset((undefined4 *)&local_d8,(int)local_9c);
    local_f8 = *(float *)(iVar4 + 4);
    iVar4 = get_tire_world_position_minus_contact_offset((undefined4 *)&local_d8,(int)local_a0);
    local_8c = *(float *)(iVar4 + 4);
    iVar4 = get_tire_world_position_minus_contact_offset((undefined4 *)&local_d8,(int)local_a8);
    local_f4 = *(float *)(iVar4 + 4);
    iVar4 = get_tire_world_position_minus_contact_offset((undefined4 *)&local_d8,(int)local_a4);
    local_100 = *(float *)(iVar4 + 4);
  }
  fVar14 = get_tire_contact_surface_height((int)fVar10);
  local_fc = (float)(fVar14 - (float10)local_f8);
  fVar14 = get_tire_contact_surface_height((int)local_a0);
  if ((float10)local_fc < fVar14 - (float10)local_8c) {
    local_fc = (float)(fVar14 - (float10)local_8c);
  }
  fVar14 = get_tire_contact_surface_height((int)local_a8);
  if ((float10)local_fc < fVar14 - (float10)local_f4) {
    local_fc = (float)(fVar14 - (float10)local_f4);
  }
  fVar14 = get_tire_contact_surface_height((int)local_a4);
  if ((float10)local_fc < fVar14 - (float10)local_100) {
    local_fc = (float)(fVar14 - (float10)local_100);
  }
  local_c0._0_4_ = local_f8 + local_fc;
  local_e8 = (double)CONCAT44(local_e8._4_4_,_DAT_004bd03c);
  local_f0 = 0.0;
  uVar11 = 0;
  local_10c = 0.0;
  local_108 = 0.0;
  local_104 = _DAT_004bd03c;
  local_f8 = 0.0;
  fVar14 = get_tire_contact_surface_height((int)fVar10);
  if ((float10)_DAT_004bd044 < (float10)(float)local_c0 - fVar14) {
    local_104 = local_104 - (float)DWORD_004bd04c;
    local_f8 = 1.12104e-44;
    local_10c = -3.1415927;
    uVar11 = 8;
  }
  local_c0._0_4_ = local_8c + local_fc;
  fVar14 = get_tire_contact_surface_height((int)local_a0);
  if ((float10)_DAT_004bd044 < (float10)(float)local_c0 - fVar14) {
    local_10c = local_10c - (float)DWORD_004bd050;
    local_104 = local_104 - (float)DWORD_004bd054;
    uVar11 = uVar11 | 4;
    local_f8 = (float)uVar11;
  }
  local_c0._0_4_ = local_f4 + local_fc;
  fVar14 = get_tire_contact_surface_height((int)local_a8);
  if ((float10)_DAT_004bd044 < (float10)(float)local_c0 - fVar14) {
    local_10c = local_10c - _DAT_004bd048;
    local_104 = local_104 - (float)DWORD_004bd04c;
    uVar11 = uVar11 | 2;
    local_f8 = (float)uVar11;
  }
  local_c0 = (double)CONCAT44(local_c0._4_4_,local_100 + local_fc);
  fVar14 = get_tire_contact_surface_height((int)local_a4);
  if ((float10)_DAT_004bd044 < (float10)(float)local_c0 - fVar14) {
    local_10c = local_10c - _DAT_004bd048;
    local_104 = local_104 - (float)DWORD_004bd054;
    uVar11 = uVar11 | 1;
    local_f8 = (float)uVar11;
  }
  if (*(float *)(param_1 + 0x28) <= *(float *)(iVar8 + 0x478)) {
    local_10c = -local_10c;
    local_104 = -local_104;
  }
  local_100 = param_5 + param_5;
  if (((_DAT_004bd03c <= local_100) && (local_100 <= (float)DWORD_004bd05c)) &&
     (fVar10 = local_10c - *(float *)(iVar8 + 200), (float)_DWORD_004bd060 <= ABS(fVar10))) {
    local_10c = local_100 * fVar10 + *(float *)(iVar8 + 200);
  }
  local_f4 = *(float *)(iVar8 + 0xd0);
  if (((_DAT_004bd03c <= local_100) && (local_100 <= (float)DWORD_004bd05c)) &&
     ((float)_DWORD_004bd060 <= ABS(local_104 - local_f4))) {
    local_104 = local_100 * (local_104 - local_f4) + local_f4;
  }
  local_c0 = (double)local_fc;
  local_d8 = *(double *)(param_1 + 0x40);
  local_d0 = *(double *)(param_1 + 0x48);
  fVar10 = local_fc * *(float *)(iVar8 + 0x464) + (float)local_d0;
  local_c8 = *(double *)(param_1 + 0x50);
  local_f0 = (double)(local_fc * *(float *)(iVar8 + 0x460) + (float)local_d8);
  local_e0 = local_c0 * (double)*(float *)(iVar8 + 0x468) + local_c8;
  local_e8 = (double)fVar10;
  *(double *)(param_1 + 0x40) = local_f0;
  *(double *)(param_1 + 0x48) = (double)fVar10;
  *(double *)(param_1 + 0x50) = local_e0;
  if (((_DAT_004bd068 <= local_10c * local_10c) || (_DAT_004bd068 <= local_108 * local_108)) ||
     (_DAT_004bd068 <= local_104 * local_104)) {
    fVar10 = *(float *)(iVar8 + 0x488 + uVar11 * 8);
    local_100 = *(float *)(iVar8 + 0x48c + uVar11 * 8);
    local_80 = (double)CONCAT44(local_80._4_4_,*(float *)(param_1 + 0x38));
    local_88 = *(double *)(param_1 + 0x30);
    local_f0 = *(double *)(param_1 + 0x40);
    local_c0 = (double)(local_100 * *(float *)(param_1 + 0x30) + fVar10 * *(float *)pdVar9);
    local_b8 = (double)(local_100 * *(float *)(param_1 + 0x34) + fVar10 * *(float *)(param_1 + 0x1c)
                       );
    local_d8 = local_f0 + local_c0;
    local_e8 = *(double *)(param_1 + 0x48);
    local_b0 = (double)(local_100 * *(float *)(param_1 + 0x38) + fVar10 * *(float *)(param_1 + 0x20)
                       );
    local_d0 = local_e8 + local_b8;
    local_e0 = *(double *)(param_1 + 0x50);
    local_c8 = local_e0 + local_b0;
    pfVar5 = (float *)effect_target_list_scan_context_helper_004389f0
                                (local_40,(float *)pdVar9,local_10c,local_108,local_104,param_5);
    fVar10 = -*(float *)(iVar8 + 0x488 + uVar11 * 8);
    fVar1 = -*(float *)(iVar8 + 0x48c + (int)local_f8 * 8);
    pfVar13 = local_40;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar13 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar13 = pfVar13 + 1;
    }
    fVar3 = fVar1 * local_28 + fVar10 * local_40[0];
    local_88 = (double)fVar3;
    fVar2 = fVar1 * local_24 + fVar10 * local_40[1];
    local_f0 = (double)CONCAT44(fVar2,fVar3);
    local_c0 = (double)(fVar3 + (float)local_d8);
    local_80 = (double)fVar2;
    local_b8 = (double)(fVar2 + (float)local_d0);
    fVar10 = fVar1 * local_20 + fVar10 * local_40[2];
    local_e8 = (double)CONCAT44(local_e8._4_4_,fVar10);
    local_8 = (double)(fVar10 + (float)local_c8);
    local_18 = local_c0;
    local_10 = local_b8;
  }
  else {
    pdVar12 = pdVar9;
    pfVar5 = local_40;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = *(float *)pdVar12;
      pdVar12 = (double *)((int)pdVar12 + 4);
      pfVar5 = pfVar5 + 1;
    }
  }
  fVar1 = local_9c;
  pfVar5 = (float *)compose_world_object_runtime_transform((float *)&local_d8,(int)local_9c);
  fVar10 = local_a0;
  local_64 = *pfVar5;
  local_60 = pfVar5[1];
  local_5c = pfVar5[2];
  pfVar5 = (float *)compose_world_object_runtime_transform((float *)&local_d8,(int)local_a0);
  local_58 = *pfVar5;
  local_54 = pfVar5[1];
  local_50 = pfVar5[2];
  puVar6 = (undefined8 *)compose_world_object_runtime_transform((float *)&local_d8,(int)local_a8);
  local_88 = (double)*puVar6;
  local_80 = (double)CONCAT44(local_80._4_4_,*(undefined4 *)(puVar6 + 1));
  puVar6 = (undefined8 *)compose_world_object_runtime_transform((float *)&local_f0,(int)local_a4);
  local_d8 = (double)*puVar6;
  local_d0 = (double)CONCAT44(local_d0._4_4_,*(undefined4 *)(puVar6 + 1));
  fVar14 = get_tire_contact_surface_height((int)fVar1);
  local_c0._0_4_ = (float)fVar14;
  fVar14 = get_tire_compression_visual_offset((int)fVar1);
  local_60 = (float)((float10)(float)local_c0 - fVar14);
  fVar14 = get_tire_contact_surface_height((int)fVar10);
  local_c0._0_4_ = (float)fVar14;
  fVar14 = get_tire_compression_visual_offset((int)fVar10);
  fVar10 = local_a8;
  local_54 = (float)((float10)(float)local_c0 - fVar14);
  fVar14 = get_tire_contact_surface_height((int)local_a8);
  local_c0._0_4_ = (float)fVar14;
  fVar14 = get_tire_compression_visual_offset((int)fVar10);
  fVar10 = local_a4;
  local_88._4_4_ = (float)((float10)(float)local_c0 - fVar14);
  fVar14 = get_tire_contact_surface_height((int)local_a4);
  local_c0 = (double)CONCAT44(local_c0._4_4_,(float)fVar14);
  fVar14 = get_tire_compression_visual_offset((int)fVar10);
  local_48 = (float)((float10)local_88._4_4_ + ((float10)(float)local_c0 - fVar14));
  local_f0 = (double)CONCAT44(local_48,(float)local_88 + (float)local_d8);
  local_e8 = (double)CONCAT44(local_e8._4_4_,local_80._0_4_ + (float)local_d0);
  local_4c = ((float)local_88 + (float)local_d8) * _DAT_004bd06c;
  local_48 = local_48 * _DAT_004bd06c;
  local_c0 = (double)CONCAT44(local_48,local_4c);
  local_44 = (local_80._0_4_ + (float)local_d0) * _DAT_004bd06c;
  local_b8._0_4_ = local_44;
  pfVar5 = (float *)zone_satellite_map_context_helper_00494c80
                              ((float *)&local_d8,&local_58,&local_4c,&local_64);
  local_98 = *pfVar5;
  local_94 = pfVar5[1];
  fVar10 = *(float *)(param_1 + 0x24);
  local_90 = pfVar5[2];
  fVar1 = *(float *)(param_1 + 0x2c);
  local_c0 = *(double *)(param_1 + 0x24);
  local_b8 = (double)CONCAT44(local_b8._4_4_,fVar1);
  if (param_4 == 0) {
    if ((param_3 != 0) ||
       (fVar1 * local_90 + *(float *)(param_1 + 0x28) * local_94 + fVar10 * local_98 <=
        fVar1 * local_2c + *(float *)(param_1 + 0x28) * local_30 + fVar10 * local_40[3])) {
      *(float *)(iVar8 + 200) = local_10c;
      *(float *)(iVar8 + 0xd0) = local_104;
      pfVar5 = local_40;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(float *)pdVar9 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        pdVar9 = (double *)((int)pdVar9 + 4);
      }
      return;
    }
  }
  else if (local_94 < _DAT_004bd03c) {
    local_10c = -*pfVar5;
    local_108 = -pfVar5[1];
    local_104 = -pfVar5[2];
    local_98 = local_10c;
    local_94 = local_108;
    local_90 = local_104;
  }
  if (_DAT_004bd044 < local_94) {
    local_6c = -((local_90 * local_68 + local_98 * local_70) / local_94);
  }
  local_d0._0_4_ = *(float *)(param_1 + 0x48);
  local_d8._0_4_ = *(float *)(param_1 + 0x40);
  local_d8._4_4_ = *(float *)(param_1 + 0x44);
  local_c8._4_4_ = *(undefined4 *)(param_1 + 0x54);
  local_d0._4_4_ = *(undefined4 *)(param_1 + 0x4c);
  local_c8._0_4_ = *(undefined4 *)(param_1 + 0x50);
  puVar7 = (undefined4 *)zone_satellite_map_context_helper_00494710(&local_98,&local_70,local_40);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pdVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    pdVar9 = (double *)((int)pdVar9 + 4);
  }
  *(float *)(param_1 + 0x48) = (float)local_d0;
  *(float *)(param_1 + 0x40) = (float)local_d8;
  *(float *)(param_1 + 0x44) = local_d8._4_4_;
  *(undefined4 *)(param_1 + 0x4c) = local_d0._4_4_;
  *(undefined4 *)(param_1 + 0x50) = (undefined4)local_c8;
  *(undefined4 *)(param_1 + 0x54) = local_c8._4_4_;
  *(undefined4 *)(iVar8 + 0xd0) = 0;
  *(undefined4 *)(iVar8 + 200) = 0;
  return;
}


