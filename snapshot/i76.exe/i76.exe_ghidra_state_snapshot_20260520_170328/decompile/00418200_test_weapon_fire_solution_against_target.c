/*
 * Program: i76.exe
 * Function: test_weapon_fire_solution_against_target
 * Entry: 00418200
 * Signature: undefined4 __cdecl test_weapon_fire_solution_against_target(uint param_1, uint param_2, float param_3, float param_4, undefined4 param_5, undefined4 param_6, int * param_7, int param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe weapon/projectile v27; confidence=high] Weapon fire-solution predicate using weapon
   type, target class, prediction, range/line geometry, spread, and friendly/near-target checks. */

undefined4 __cdecl
test_weapon_fire_solution_against_target
          (uint param_1,uint param_2,float param_3,float param_4,undefined4 param_5,
          undefined4 param_6,int *param_7,int param_8)

{
  float fVar1;
  double dVar2;
  uint uVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  float *pfVar9;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
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
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  undefined8 local_a0;
  float local_98;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  double local_58;
  float local_50 [3];
  float local_44 [3];
  float local_38 [3];
  undefined4 local_2c [3];
  undefined4 local_20 [3];
  undefined4 local_14 [4];
  
  switch(param_7[1]) {
  case 0:
    report_error();
    return 0;
  case 3:
    if (*param_7 == 3) {
      iVar10 = rand();
      iVar6 = rand();
      local_a0._0_4_ = (float)(iVar10 % 1000 + iVar6 % 1000);
      if (param_3 * _DAT_004bc9c0 < (float)(int)(float)local_a0) {
        return 0;
      }
      local_84 = *(float *)(param_8 + 0x1c);
      local_88 = *(float *)(param_1 + 0x30);
      local_cc = *(float *)(param_1 + 0x34);
      local_c8 = *(float *)(param_1 + 0x38);
      local_80 = *(float *)(param_8 + 0x20);
      local_b8 = (float)*(double *)(param_1 + 0x40);
      local_b4 = (float)*(double *)(param_1 + 0x48);
      local_b0 = (float)*(double *)(param_1 + 0x50);
      if (local_c8 * local_80 + local_cc * local_84 + local_88 * *(float *)(param_8 + 0x18) <=
          _DAT_004bc914) {
        local_c4 = local_88 * _DAT_004bc918;
        local_cc = local_cc * _DAT_004bc918;
        local_c8 = local_c8 * _DAT_004bc918;
        local_c0 = local_cc;
        local_bc = local_c8;
        local_88 = local_c4;
      }
      local_d0 = local_88 * _DAT_004bc9c4;
      local_cc = local_cc * _DAT_004bc9c4;
      local_c8 = local_c8 * _DAT_004bc9c4;
      local_dc = (float)*(double *)(param_2 + 0x40);
      local_d8 = (float)*(double *)(param_2 + 0x48);
      local_d4 = (float)*(double *)(param_2 + 0x50);
      local_ac = local_dc;
      local_a8 = local_d8;
      local_a4 = local_d4;
      get_world_object_damage_or_target_vectors(param_2,&local_70,&local_8c);
      local_dc = local_b8 - local_ac;
      local_d8 = local_b4 - local_a8;
      local_d4 = local_b0 - local_a4;
      local_88 = local_dc;
      local_84 = local_d8;
      local_80 = local_d4;
      pfVar9 = (float *)vec3_subtract_xyz(local_50,local_70,local_6c,local_68,local_d0,local_cc,
                                          local_c8);
      local_dc = *pfVar9;
      local_d8 = pfVar9[1];
      local_d4 = pfVar9[2];
      fVar13 = dot_product_vec3(&local_dc,&local_dc);
      local_a0 = (double)CONCAT44(local_a0._4_4_,(float)fVar13);
      if ((float10)_DAT_004bc924 <= ABS(fVar13)) {
        fVar13 = dot_product_vec3(&local_dc,&local_88);
        local_e4 = (float)(fVar13 / (float10)(float)local_a0);
      }
      else {
        local_e4 = 1e+07;
      }
      if (local_e4 < _DAT_004bc914) {
        return 0;
      }
      if (_DAT_004bc9c8 < local_e4) {
        return 0;
      }
      predict_world_object_position_at_time(param_2,local_e4,&local_ac);
      local_ac = local_ac - (local_d0 * local_e4 + local_b8);
      local_a4 = local_a4 - (local_c8 * local_e4 + local_b0);
      bVar4 = local_a4 * local_a4 + local_ac * local_ac < _DAT_004bc9b8;
      goto LAB_00419120;
    }
    break;
  case 4:
    switch(*param_7) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x65:
    case 0x66:
    case 0x67:
      iVar10 = rand();
      if (param_3 * param_3 * _DAT_004bc92c < (float)(iVar10 % 5000)) {
        return 0;
      }
      local_c4 = (float)*(double *)(param_8 + 0x28);
      local_c0 = (float)*(double *)(param_8 + 0x30);
      local_bc = (float)*(double *)(param_8 + 0x38);
      local_a0._0_4_ = *(float *)(param_8 + 0x18);
      local_a0._4_4_ = *(float *)(param_8 + 0x1c);
      local_98 = *(float *)(param_8 + 0x20);
      pfVar9 = (float *)get_cached_world_object_aim_position(local_20,param_2);
      local_ac = *pfVar9;
      local_a8 = pfVar9[1];
      local_a4 = pfVar9[2];
      local_b8 = *pfVar9;
      local_b4 = pfVar9[1];
      local_b0 = pfVar9[2];
      local_d0 = local_b8 - local_c4;
      local_cc = local_b4 - local_c0;
      local_c8 = local_b0 - local_bc;
      fVar1 = local_c8 * local_c8 + local_cc * local_cc + local_d0 * local_d0;
      if (_DAT_004bc930 < fVar1) {
        return 0;
      }
      if ((_DAT_004bc934 < fVar1) && (fVar1 < _DAT_004bc938)) {
        return 0;
      }
      local_c4 = local_d0;
      local_c0 = local_cc;
      local_bc = local_c8;
      fVar13 = zone_satellite_map_context_helper_00495000
                         (SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
      fVar11 = (float10)local_c0 * (float10)(float)fVar13;
      fVar12 = (float10)local_bc * (float10)(float)fVar13;
      local_c4 = (float)(fVar13 * (float10)local_d0);
      local_c0 = (float)fVar11;
      local_bc = (float)fVar12;
      fVar13 = fVar12 * (float10)local_98 +
               fVar11 * (float10)local_a0._4_4_ +
               fVar13 * (float10)local_d0 * (float10)(float)local_a0;
      if (_DAT_004bc93c <= fVar1) {
        if (fVar13 < (float10)_DAT_004bc950) {
          return 0;
        }
        if ((*param_7 != 1) && (*param_7 != 0x65)) {
          uVar5 = test_weapon_projectile_path_clear_to_target(param_1,param_2);
          return uVar5;
        }
        local_d8 = *(float *)(param_2 + 0x34);
        local_d4 = *(float *)(param_2 + 0x38);
        if ((float)_DAT_004bc958 <
            ABS(local_d4 * local_98 +
                local_d8 * local_a0._4_4_ + *(float *)(param_2 + 0x30) * (float)local_a0)) {
          uVar5 = test_weapon_projectile_path_clear_to_target(param_1,param_2);
          return uVar5;
        }
        return 0;
      }
      if (fVar13 < (float10)_DAT_004bc940) {
        return 0;
      }
      if ((*param_7 != 1) && (*param_7 != 0x65)) {
        uVar5 = test_weapon_projectile_path_clear_to_target(param_1,param_2);
        return uVar5;
      }
      local_d8 = *(float *)(param_2 + 0x34);
      local_d4 = *(float *)(param_2 + 0x38);
      if ((float)_DAT_004bc948 <
          ABS(local_d4 * local_98 +
              local_d8 * local_a0._4_4_ + *(float *)(param_2 + 0x30) * (float)local_a0)) {
        uVar5 = test_weapon_projectile_path_clear_to_target(param_1,param_2);
        return uVar5;
      }
      return 0;
    }
  case 1:
  case 2:
    iVar10 = rand();
    iVar6 = rand();
    iVar7 = rand();
    iVar10 = iVar10 % 1000 + iVar6 % 1000 + iVar7 % 1000;
    local_a0 = (double)CONCAT44(local_a0._4_4_,iVar10);
    if (param_3 * _DAT_004bc960 < (float)iVar10) {
      return 0;
    }
    local_d0 = (float)*(double *)(param_8 + 0x28);
    local_b8 = *(float *)(param_8 + 0x18);
    local_b4 = *(float *)(param_8 + 0x1c);
    local_cc = (float)*(double *)(param_8 + 0x30);
    local_b0 = *(float *)(param_8 + 0x20);
    local_c8 = (float)*(double *)(param_8 + 0x38);
    pfVar9 = (float *)get_cached_world_object_aim_position(local_2c,param_2);
    local_ac = *pfVar9;
    local_a8 = pfVar9[1];
    local_a4 = pfVar9[2];
    get_world_object_damage_or_target_vectors(param_1,&local_7c,(undefined4 *)&local_58);
    iVar10 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar10 == 0) {
      local_70 = 0.0;
      local_6c = 0.0;
      local_68 = 0.0;
      local_8c = 0.0;
    }
    else {
      get_world_object_damage_or_target_vectors(param_2,&local_70,&local_8c);
    }
    fVar1 = (float)param_7[5];
    local_c4 = fVar1 * local_b8 + local_7c;
    local_c0 = fVar1 * local_b4 + local_78;
    local_bc = fVar1 * local_b0 + local_74;
    local_dc = local_d0 - local_ac;
    local_d8 = local_cc - local_a8;
    local_d4 = local_c8 - local_a4;
    local_b8 = local_dc;
    local_b4 = local_d8;
    local_b0 = local_d4;
    local_7c = local_c4;
    local_78 = local_c0;
    local_74 = local_bc;
    pfVar9 = (float *)vec3_subtract_xyz(&local_88,local_70,local_6c,local_68,local_c4,local_c0,
                                        local_bc);
    local_b8 = *pfVar9;
    local_b4 = pfVar9[1];
    local_b0 = pfVar9[2];
    fVar13 = dot_product_vec3(&local_b8,&local_b8);
    if ((float10)_DAT_004bc924 <= ABS(fVar13)) {
      fVar11 = dot_product_vec3(&local_b8,&local_dc);
      local_e4 = (float)(fVar11 / (float10)(float)fVar13);
    }
    else {
      local_e4 = 1e+07;
    }
    iVar10 = rand();
    iVar10 = iVar10 % 1000 + -500;
    local_a0 = (double)CONCAT44(local_a0._4_4_,iVar10);
    local_e4 = local_e4 - (_DAT_004bc91c - param_4) * _DAT_004bc964 * (float)iVar10 * _DAT_004bc968;
    if (local_e4 < (float)_DAT_004bc970) {
      local_e4 = 0.0;
    }
    if (_DAT_004bc978 <= local_e4) {
      return 0;
    }
    local_b8 = local_e4 * local_7c + local_d0;
    local_b4 = local_e4 * local_78 + local_cc;
    local_b0 = local_e4 * local_74 + local_c8;
    pfVar9 = (float *)vec3_madd_xyz(&local_88,local_ac,local_a8,local_a4,local_e4,local_70,local_6c,
                                    local_68);
    pfVar9 = (float *)vec3_subtract_xyz(&local_88,local_b8,local_b4,local_b0,*pfVar9,pfVar9[1],
                                        pfVar9[2]);
    fVar13 = vec3_length(*pfVar9,pfVar9[1],pfVar9[2]);
    iVar10 = is_vehicle_or_actor_runtime_world_object(param_2);
    fVar1 = _DAT_004bc9a4;
    if (iVar10 != 0) {
      local_a0 = *(double *)(param_1 + 0x40) - *(double *)(param_2 + 0x40);
      dVar2 = *(double *)(param_1 + 0x50) - *(double *)(param_2 + 0x50);
      dVar2 = dVar2 * dVar2 + local_a0 * local_a0;
      fVar1 = _DAT_004bc988;
      if ((_DAT_004bc980 <= dVar2) && (fVar1 = _DAT_004bc99c, dVar2 < _DAT_004bc990)) {
        fVar1 = _DAT_004bc998;
      }
      if (param_7[1] == 4) {
        fVar1 = fVar1 * _DAT_004bc9a0;
      }
    }
    if (fVar1 <= (float)fVar13) {
      return 0;
    }
    iVar10 = test_weapon_projectile_path_clear_to_target(param_1,param_2);
    if (iVar10 == 0) {
      return 0;
    }
    puVar8 = (uint *)get_current_effect_target_scan_object();
    if (puVar8 != (uint *)0x0) {
      do {
        uVar3 = *puVar8;
        if (((uVar3 != param_1) && (uVar3 != param_2)) &&
           (iVar10 = is_vehicle_or_actor_runtime_world_object(uVar3), iVar10 != 0)) {
          fVar13 = (float10)*(double *)(param_1 + 0x40) - (float10)*(double *)(uVar3 + 0x40);
          fVar11 = (float10)*(double *)(param_1 + 0x50) - (float10)*(double *)(uVar3 + 0x50);
          dVar2 = (double)fVar13;
          fVar1 = (float)(fVar11 * fVar11 + fVar13 * (float10)dVar2);
          local_a0._4_4_ = (float)((ulonglong)dVar2 >> 0x20);
          local_a0 = (double)CONCAT44(local_a0._4_4_,fVar1);
          if ((fVar1 <= _DAT_004bc9a8) &&
             (((*(uint *)(param_1 + 0x10) ^ *(uint *)(uVar3 + 0x10)) & 0x70000) == 0)) {
            local_b8 = (float)*(double *)(uVar3 + 0x40);
            local_b4 = (float)*(double *)(uVar3 + 0x48);
            local_b0 = (float)*(double *)(uVar3 + 0x50);
            local_ac = local_b8;
            local_a8 = local_b4;
            local_a4 = local_b0;
            get_world_object_damage_or_target_vectors(uVar3,&local_70,&local_8c);
            local_c4 = local_d0 - local_ac;
            local_c0 = local_cc - local_a8;
            local_bc = local_c8 - local_a4;
            local_88 = local_c4;
            local_84 = local_c0;
            local_80 = local_bc;
            pfVar9 = (float *)vec3_subtract_xyz(local_44,local_70,local_6c,local_68,local_7c,
                                                local_78,local_74);
            local_64 = *pfVar9;
            local_60 = pfVar9[1];
            local_5c = pfVar9[2];
            fVar13 = dot_product_vec3(&local_64,&local_64);
            if ((float10)_DAT_004bc924 <= ABS(fVar13)) {
              fVar11 = dot_product_vec3(&local_64,&local_88);
              local_e4 = (float)(fVar11 / (float10)(float)fVar13);
            }
            else {
              local_e4 = 1e+07;
            }
            if (local_e4 < _DAT_004bc914) {
              local_e4 = 0.0;
            }
            if (local_e4 < _DAT_004bc978) {
              local_dc = local_e4 * local_7c + local_d0;
              local_d8 = local_e4 * local_78 + local_cc;
              local_d4 = local_e4 * local_74 + local_c8;
              pfVar9 = (float *)vec3_madd_xyz(local_38,local_ac,local_a8,local_a4,local_e4,local_70,
                                              local_6c,local_68);
              pfVar9 = (float *)vec3_subtract_xyz(local_50,local_dc,local_d8,local_d4,*pfVar9,
                                                  pfVar9[1],pfVar9[2]);
              fVar13 = vec3_length(*pfVar9,pfVar9[1],pfVar9[2]);
              iVar10 = get_active_player_or_camera_world_object_entry();
              if (iVar10 == 0) {
                return 0;
              }
              if ((float)fVar13 < _DAT_004bc9ac) {
                if (_DAT_004bc9b0 <= (float)local_a0) {
                  return 0;
                }
                if ((float)fVar13 < _DAT_004bc9b4) {
                  return 0;
                }
              }
            }
          }
        }
        puVar8 = (uint *)effect_target_scan_query_context_helper_00436790();
        if (puVar8 == (uint *)0x0) {
          return 1;
        }
      } while( true );
    }
    return 1;
  case 5:
    fVar13 = (float10)*(double *)(param_1 + 0x40) - (float10)*(double *)(param_2 + 0x40);
    fVar11 = (float10)*(double *)(param_1 + 0x48) - (float10)*(double *)(param_2 + 0x48);
    fVar12 = (float10)*(double *)(param_1 + 0x50) - (float10)*(double *)(param_2 + 0x50);
    local_58 = (double)fVar13;
    local_a0 = (double)fVar11;
    fVar13 = fVar12 * fVar12 + fVar11 * (float10)local_a0 + fVar13 * (float10)local_58;
    fVar1 = (float)fVar13;
    if ((float10)_DAT_004bc9b8 < fVar13) {
      return 0;
    }
    local_64 = (float)*(double *)(param_8 + 0x28);
    local_60 = (float)*(double *)(param_8 + 0x30);
    local_5c = (float)*(double *)(param_8 + 0x38);
    local_d0 = *(float *)(param_8 + 0x18);
    local_cc = *(float *)(param_8 + 0x1c);
    local_c8 = *(float *)(param_8 + 0x20);
    pfVar9 = (float *)get_cached_world_object_aim_position(local_14,param_2);
    local_ac = *pfVar9;
    local_a8 = pfVar9[1];
    local_a4 = pfVar9[2];
    local_dc = *pfVar9;
    local_d8 = pfVar9[1];
    local_d4 = pfVar9[2];
    local_c4 = local_dc - local_64;
    local_c0 = local_d8 - local_60;
    local_bc = local_d4 - local_5c;
    if ((_DAT_004bc934 < fVar1) && (fVar1 < _DAT_004bc938)) {
      return 1;
    }
    local_b8 = local_c4;
    local_b4 = local_c0;
    local_b0 = local_bc;
    fVar13 = zone_satellite_map_context_helper_00495000
                       (SUB84((double)fVar1,0),(uint)((ulonglong)(double)fVar1 >> 0x20));
    bVar4 = (float10)_DAT_004bc9bc <
            (float10)local_bc * (float10)(float)fVar13 * (float10)local_c8 +
            (float10)local_c0 * (float10)(float)fVar13 * (float10)local_cc +
            fVar13 * (float10)local_b8 * (float10)local_d0;
LAB_00419120:
    if (bVar4) {
      return 1;
    }
    return 0;
  case 6:
    iVar10 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar10 == 0) {
      return 0;
    }
    if (*(int *)(param_1 + 0x6c) == 8) {
      return 0;
    }
    iVar10 = get_vehicle_runtime_context(param_1);
    if (*(float *)(iVar10 + 0xe8) < _DAT_004bc91c) {
      return 0;
    }
    if ((*(int *)(param_1 + 0x6c) == 1) &&
       (iVar10 = get_vehicle_runtime_context(param_1), (*(byte *)(iVar10 + 0x454) & 4) != 0)) {
      return 0;
    }
    local_d0 = (float)*(double *)(param_1 + 0x40);
    local_cc = (float)*(double *)(param_1 + 0x48);
    local_c8 = (float)*(double *)(param_1 + 0x50);
    get_world_object_damage_or_target_vectors(param_1,&local_7c,(undefined4 *)&local_58);
    local_c4 = (float)*(double *)(param_2 + 0x40);
    local_c0 = (float)*(double *)(param_2 + 0x48);
    local_84 = (float)*(double *)(param_2 + 0x48) - local_cc;
    local_bc = (float)*(double *)(param_2 + 0x50);
    local_80 = (float)*(double *)(param_2 + 0x50) - local_c8;
    if (_DAT_004bc914 <
        local_80 * local_74 +
        local_84 * local_78 + ((float)*(double *)(param_2 + 0x40) - local_d0) * local_7c) {
      return 0;
    }
    local_ac = local_c4;
    local_a8 = local_c0;
    local_a4 = local_bc;
    get_world_object_damage_or_target_vectors(param_2,&local_70,&local_8c);
    if ((float)_DAT_004bc9e0 <= local_8c) {
      fVar13 = (float10)world_object_geometry_context_helper_004589f0(param_1,param_2);
      fVar13 = fVar13 / (float10)local_8c;
    }
    else {
      fVar13 = (float10)_DAT_004bc9e8;
    }
    local_e4 = (float)fVar13;
    if ((float10)_DAT_004bc914 <= fVar13) {
      if ((float10)_DAT_004bc9ec < fVar13) {
        return 0;
      }
    }
    else {
      if (fVar13 < (float10)_DAT_004bc918) {
        return 0;
      }
      local_e4 = 0.0;
    }
    predict_world_object_position_at_time(param_2,local_e4,&local_ac);
    bVar4 = (local_c8 - local_a4) * (local_c8 - local_a4) +
            (local_cc - local_a8) * (local_cc - local_a8) +
            (local_d0 - local_ac) * (local_d0 - local_ac) < _DAT_004bc9f0;
    goto LAB_00419476;
  default:
    report_error();
    return 0;
  }
  switch(*param_7) {
  case 0:
    local_e4 = 0.3;
    break;
  default:
    local_e4 = 0.25;
    break;
  case 2:
    local_e4 = 0.4;
    local_e0 = 150.0;
    goto LAB_0041916f;
  }
  local_e0 = 400.0;
LAB_0041916f:
  local_dc = (float)*(double *)(param_2 + 0x40);
  local_d8 = (float)*(double *)(param_2 + 0x48);
  local_d4 = (float)*(double *)(param_2 + 0x50);
  local_ac = local_dc;
  local_a8 = local_d8;
  local_a4 = local_d4;
  predict_world_object_position_at_time(param_2,local_e4,&local_ac);
  local_5c = (float)*(double *)(param_1 + 0x50);
  local_64 = (float)*(double *)(param_1 + 0x40);
  get_world_object_damage_or_target_vectors(param_1,&local_7c,(undefined4 *)&local_58);
  local_ac = local_ac -
             (local_e4 * local_7c + *(float *)(param_8 + 0x18) * _DAT_004bc9dc + local_64);
  local_a4 = local_a4 -
             (local_e4 * local_74 + *(float *)(param_8 + 0x20) * _DAT_004bc9dc + local_5c);
  bVar4 = local_a4 * local_a4 + local_ac * local_ac < local_e0;
LAB_00419476:
  if (!bVar4) {
    return 0;
  }
  return 1;
}


