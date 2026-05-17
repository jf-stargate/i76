/*
 * Program: i76.exe
 * Function: solve_vehicle_wheel_contact_suspension_solver
 * Entry: 0043a5d0
 * Signature: undefined __cdecl solve_vehicle_wheel_contact_suspension_solver(float * param_1, uint * param_2, float * param_3, float * param_4, float * param_5, float * param_6, float * param_7, float param_8)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Large wheel-ground contact
   and suspension solver: computes contact masks, grounded/airborne state, suspension response
   vectors, and output transform/velocity state. */

void __cdecl
solve_vehicle_wheel_contact_suspension_solver
          (float *param_1,uint *param_2,float *param_3,float *param_4,float *param_5,float *param_6,
          float *param_7,float param_8)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  undefined8 *puVar5;
  int iVar6;
  float fVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  double *pdVar13;
  double *pdVar14;
  float *pfVar15;
  float10 fVar16;
  double in_stack_fffffe34;
  double in_stack_fffffe3c;
  undefined4 in_stack_fffffe44;
  undefined4 uVar17;
  double dVar18;
  float *pfVar19;
  undefined4 uVar20;
  float *pfVar21;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  undefined8 local_140;
  float local_138;
  float local_134;
  int local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  uint local_118;
  int local_114;
  float local_110;
  float local_10c;
  float local_108;
  float *local_104;
  double local_100;
  double local_f8;
  double local_f0;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  double local_cc;
  double local_c4;
  double local_bc;
  double local_b4;
  double local_ac;
  double local_a4;
  float local_9c;
  float local_98;
  float local_94;
  undefined4 local_8c [3];
  float local_80 [6];
  float local_68;
  float local_64;
  float local_60;
  float local_40 [16];
  
  pfVar4 = param_1 + 6;
  local_114 = get_vehicle_runtime_context((int)param_1);
  fVar16 = get_vehicle_throttle_input_scalar(local_114);
  local_178 = 0.0;
  local_174 = 0.0;
  *param_5 = 0.0;
  local_148 = (float)fVar16;
  local_170 = 0.0;
  param_5[1] = 0.0;
  param_5[2] = 0.0;
  iVar3 = get_vehicle_runtime_context((int)param_1);
  if (((*(uint *)(iVar3 + 0x454) & 4) != 0) || ((*(uint *)(iVar3 + 0x454) & 0x200) == 0)) {
    local_178 = (float)*(double *)(param_1 + 0x10);
    local_174 = (float)*(double *)(param_1 + 0x12);
    local_170 = (float)*(double *)(param_1 + 0x14);
    local_184 = *(float *)(iVar3 + 0xbc);
    local_180 = *(float *)(iVar3 + 0xc0);
    local_17c = *(float *)(iVar3 + 0xc4);
    local_16c = local_178;
    local_168 = local_174;
    local_164 = local_170;
    integrate_vertical_motion_with_gravity(&local_16c,&local_184,-9.8,param_8);
    probe_effect_target_surface_height_at_position
              ((double)CONCAT44(local_168,local_16c),local_164,&local_144,(undefined4 *)0x0);
    fVar7 = local_168;
    if (param_1[10] <= _DAT_004bd148) {
      pfVar19 = (float *)copy_transform_forward_vector(local_8c,(int)pfVar4);
      pfVar19 = (float *)vec3_madd_xyz((float *)&local_b4,local_16c,local_168,local_164,
                                       *(float *)(iVar3 + 0x34),*pfVar19,pfVar19[1],pfVar19[2]);
      local_178 = *pfVar19;
      local_174 = pfVar19[1];
      local_170 = pfVar19[2];
      fVar7 = local_174;
    }
    fVar7 = fVar7 - local_144;
    if ((((*(byte *)(iVar3 + 0x454) & 4) != 0) && (*(float *)(iVar3 + 0x470) < fVar7)) ||
       (_DAT_004bd138 < fVar7)) {
      *(float *)(iVar3 + 0x470) = fVar7;
      pfVar19 = param_7;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        *pfVar19 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar19 = pfVar19 + 1;
      }
      store_vec3_as_double_triplet((int)param_7,&local_16c);
      *param_3 = local_184;
      param_3[1] = local_180;
      param_3[2] = local_17c;
      fVar16 = vec3_length(local_184,local_180,local_17c);
      *param_4 = (float)fVar16;
      *param_6 = *(float *)(iVar3 + 200);
      param_6[1] = *(float *)(iVar3 + 0xcc);
      param_6[2] = *(float *)(iVar3 + 0xd0);
      local_104 = (float *)*param_6;
      if (_DAT_004bd1a4 < (float)local_104) {
        fVar16 = approach_float_with_rate_limit((float)local_104,-0.15707964,param_8);
        *param_6 = (float)fVar16;
      }
      *param_2 = *(uint *)(iVar3 + 0x454) & 0xffffddfd | 4;
      pfVar4 = (float *)effect_target_list_scan_context_helper_004389f0
                                  (local_40,param_7,*param_6,param_6[1],param_6[2],param_8);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *param_7 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        param_7 = param_7 + 1;
      }
      return;
    }
    *(float *)(iVar3 + 0x470) = fVar7;
    local_168 = local_144;
    if ((*(byte *)(iVar3 + 0x454) & 4) != 0) {
      pfVar19 = param_7;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        *pfVar19 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar19 = pfVar19 + 1;
      }
      store_vec3_as_double_triplet((int)param_7,&local_16c);
      *param_3 = local_184;
      param_3[1] = local_180;
      param_3[2] = local_17c;
      fVar16 = vec3_length(local_184,local_180,local_17c);
      *param_4 = (float)fVar16;
      *param_6 = *(float *)(iVar3 + 200);
      param_6[1] = *(float *)(iVar3 + 0xcc);
      param_6[2] = *(float *)(iVar3 + 0xd0);
      *param_2 = *(uint *)(iVar3 + 0x454) & 0xfffffffb | 0x200;
      puVar5 = (undefined8 *)copy_vec3(&local_178,param_7);
      local_140 = (double)*puVar5;
      local_138 = *(float *)(puVar5 + 1);
      fVar16 = dot_product_vec3((float *)&local_140,param_3);
      local_160 = (float)fVar16;
      iVar3 = world_object_has_optional_runtime_flag((int)param_1);
      if (iVar3 == 0) {
        return;
      }
      if ((_DAT_004bd1a8 <= local_160) && (local_160 <= _DAT_004bd134)) {
        return;
      }
      *param_2 = *param_2 | 2;
      return;
    }
  }
  local_104 = (float *)(local_114 + 0x460);
  *param_2 = *(uint *)(local_114 + 0x454);
  fVar1 = param_1[0xb];
  local_184 = param_1[0xc];
  local_180 = param_1[0xd];
  local_17c = param_1[0xe];
  local_178 = *pfVar4;
  local_174 = param_1[7];
  local_170 = param_1[8];
  fVar7 = param_1[9];
  fVar2 = param_1[10];
  local_100 = *(double *)(param_1 + 0x10);
  local_f8 = (double)*(undefined8 *)(param_1 + 0x12);
  local_d8 = local_178;
  local_f0 = (double)*(undefined8 *)(param_1 + 0x14);
  local_d0 = local_170;
  local_d4 = local_174;
  pdVar13 = &local_100;
  pdVar14 = &local_cc;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
    pdVar13 = (double *)((int)pdVar13 + 4);
    pdVar14 = (double *)((int)pdVar14 + 4);
  }
  if (_DAT_004bd16c <=
      *local_104 * fVar7 +
      *(float *)(local_114 + 0x464) * fVar2 + *(float *)(local_114 + 0x468) * fVar1) {
    local_144 = 0.0;
    if ((*(int *)(local_114 + 0xf0) == 0) && (*(int *)(local_114 + 0x104) != 0)) goto LAB_0043ab13;
  }
  else {
    local_144 = 1.4013e-45;
  }
  local_148 = -1.0;
LAB_0043ab13:
  if ((_DAT_004bd1ac < local_148) && (*(int *)(local_114 + 0x104) == 2)) {
    local_148 = 0.0;
  }
  if ((local_148 < _DAT_004bd148) && (*(int *)(local_114 + 0xf4) != 0)) {
    local_148 = local_148 + local_148;
  }
  local_16c = *(float *)(local_114 + 0xbc);
  local_168 = *(float *)(local_114 + 0xc0);
  local_164 = *(float *)(local_114 + 0xc4);
  local_134 = *(float *)(local_114 + 0xac);
  if (local_17c * local_164 + local_180 * local_168 + local_184 * local_16c < _DAT_004bd148) {
    local_134 = -local_134;
  }
  local_9c = 1.0;
  if ((_DAT_004bd1a8 <= local_134 * *(float *)(local_114 + 0xe8)) || (local_148 <= _DAT_004bd150)) {
    if ((*(int *)(local_114 + 0xf0) == 0) || (*(float *)(local_114 + 0xac) <= _DAT_004bd130)) {
      local_130 = 0;
      local_118 = *param_2 & 2;
    }
    else {
      local_130 = 1;
      local_118 = 1;
      if ((*param_2 & 2) == 0) {
        local_9c = local_134 * _DAT_004bd16c;
      }
    }
  }
  else {
    local_118 = 1;
    local_130 = 1;
    *param_2 = *param_2 | 2;
  }
  local_110 = local_184;
  local_10c = local_180;
  local_108 = local_17c;
  compute_vehicle_longitudinal_drive_brake_force
            ((float)param_1,local_148,(int)local_144,&local_110,*param_2,&local_12c,&local_130);
  if (local_130 != 0) {
    local_118 = 1;
  }
  uVar12 = local_118;
  local_e8 = 1.0;
  local_14c = 0.0;
  *param_2 = *param_2 & 0xffffdfff;
  if (((local_118 == 0) && (local_144 == 0.0)) &&
     (compute_vehicle_suspension_traction_limit
                ((int)param_1,local_134,&local_14c,&local_130,&local_e8), local_130 != 0)) {
    uVar12 = 1;
    local_118 = 1;
  }
  local_140 = (double)CONCAT44(local_140._4_4_,uVar12);
  iVar3 = get_vehicle_runtime_context((int)param_1);
  local_124 = 0.0;
  local_120 = 0.0;
  local_11c = 0.0;
  local_184 = 0.0;
  local_180 = 0.0;
  local_17c = 0.0;
  local_e4 = 0.0;
  local_e0 = 0.0;
  local_dc = 0.0;
  local_150 = *(float *)(iVar3 + 0x46c) * _DAT_004bd158;
  if (_DAT_004bd134 <= *(float *)(iVar3 + 0xac)) {
    local_160 = *(float *)(iVar3 + 0x120) * *(float *)(iVar3 + 0xac) * *(float *)(iVar3 + 0xac) *
                _DAT_004bd1b0;
    iVar11 = get_vehicle_rear_right_tire_runtime_component(iVar3);
    iVar6 = get_vehicle_rear_left_tire_runtime_component(iVar3);
    local_128 = *(float *)(iVar11 + 0x14) + *(float *)(iVar6 + 0x14);
    iVar11 = get_vehicle_front_right_tire_runtime_component(iVar3);
    local_128 = local_128 + *(float *)(iVar11 + 0x14);
    iVar11 = get_vehicle_front_left_tire_runtime_component(iVar3);
    local_128 = local_128 + *(float *)(iVar11 + 0x14);
    fVar16 = get_terrain_material_primary_scalar(*(int *)(iVar3 + 0x45c));
    local_160 = *(float *)(iVar3 + 0xb0) *
                (float)((float10)local_160 - fVar16 * (float10)local_128 * (float10)local_150);
    local_124 = *(float *)(iVar3 + 0xbc) * local_160;
    local_120 = *(float *)(iVar3 + 0xc0) * local_160;
    local_11c = *(float *)(iVar3 + 0xc4) * local_160;
  }
  uVar17 = 0x43aed3;
  pfVar19 = DAT_004bd088;
  local_184 = local_124;
  local_180 = local_120;
  local_17c = local_11c;
  zone_satellite_map_context_helper_00493ca0
            (DAT_004bd080,DAT_004bd084,(float)DAT_004bd088,*(float *)(iVar3 + 0x460),
             *(float *)(iVar3 + 0x464),*(float *)(iVar3 + 0x468),(float *)&local_b4,&local_178);
  fVar16 = get_vehicle_effective_terrain_friction_scalar(iVar3);
  local_150 = (float)(fVar16 * (float10)local_150);
  iVar11 = get_vehicle_front_right_tire_runtime_component(iVar3);
  iVar6 = get_vehicle_front_left_tire_runtime_component(iVar3);
  local_128 = *(float *)(iVar11 + 0xc) + *(float *)(iVar6 + 0xc);
  iVar11 = get_vehicle_rear_right_tire_runtime_component(iVar3);
  local_128 = local_128 + *(float *)(iVar11 + 0xc);
  iVar11 = get_vehicle_rear_left_tire_runtime_component(iVar3);
  local_160 = (local_128 + *(float *)(iVar11 + 0xc)) * local_150;
  fVar16 = dot_product_vec3(&local_178,&local_178);
  if (fVar16 <= (float10)local_160 * (float10)local_160) {
    fVar7 = (float)local_140;
  }
  else {
    local_130 = 1;
    fVar7 = 1.4013e-45;
  }
  if ((local_144 != 0.0) || ((fVar7 != 0.0 && (_DAT_004bd134 <= *(float *)(iVar3 + 0xac))))) {
    local_140._0_4_ = local_178;
    local_140._4_4_ = local_174;
    local_138 = local_170;
    if ((local_144 != 0.0) ||
       ((*(float *)(iVar3 + 0xe4) < _DAT_004bd13c || (*(int *)(iVar3 + 0xf0) != 0)))) {
      iVar11 = 1;
    }
    else {
      iVar11 = 0;
    }
    if ((*(uint *)(iVar3 + 0x454) & 0x1000) == 0) {
      apply_wheel_contact_impulse_between_vehicles
                ((int)param_1,*(int *)(iVar3 + 0x3ac),local_150,iVar11,&local_124,&local_e4);
      apply_wheel_contact_impulse_between_vehicles
                ((int)param_1,*(int *)(iVar3 + 0x3a8),local_150,iVar11,&local_124,&local_e4);
      apply_wheel_contact_impulse_between_vehicles
                ((int)param_1,*(int *)(iVar3 + 0x3bc),local_150,iVar11,&local_124,&local_e4);
      apply_wheel_contact_impulse_between_vehicles
                ((int)param_1,*(int *)(iVar3 + 0x3b8),local_150,iVar11,&local_124,&local_e4);
    }
    else {
      apply_longitudinal_drag_force_to_velocity((int)param_1,local_160,iVar11,&local_124);
      param_1 = pfVar19;
    }
  }
  else {
    pfVar8 = (float *)copy_object_local_translation_vec3(local_8c,(int)pfVar4);
    local_140 = *(double *)pfVar8;
    local_138 = pfVar8[2];
    local_184 = *pfVar8;
    local_180 = pfVar8[1];
    local_17c = pfVar8[2];
    fVar16 = dot_product_vec3(&local_178,(float *)&local_140);
    local_184 = (float)((float10)local_184 * fVar16);
    local_180 = (float)((float10)local_180 * fVar16);
    local_17c = (float)((float10)local_17c * fVar16);
    param_1 = pfVar19;
    local_138 = local_17c;
    local_140._0_4_ = local_184;
    local_140._4_4_ = local_180;
  }
  if (local_130 != 0) {
    local_118 = 1;
  }
  if (local_118 == 0) {
    if (_DAT_004bd134 <= local_e8) {
      local_15c = local_110 * local_134;
      local_158 = local_10c * local_134;
      local_154 = local_108 * local_134;
      fVar7 = local_14c;
    }
    else {
      local_154 = local_164;
      local_15c = local_16c;
      local_158 = local_168;
      *param_2 = *param_2 | 0x2000;
      fVar7 = local_e8 * local_14c;
    }
    fVar7 = -(fVar7 * local_134);
    local_184 = fVar7 * local_d8 + local_124;
    local_180 = fVar7 * local_d4 + local_120;
    local_17c = fVar7 * local_d0 + local_11c;
    local_124 = local_184;
    local_120 = local_180;
    local_11c = local_17c;
    if (local_148 < _DAT_004bd148) {
      local_178 = local_110 * local_12c + local_184;
      local_174 = local_10c * local_12c + local_180;
      local_170 = local_108 * local_12c + local_17c;
      local_124 = local_178;
      local_120 = local_174;
      local_11c = local_170;
    }
    pfVar19 = (float *)0x43b674;
    effect_target_list_scan_context_helper_004384f0(&local_cc,&local_15c,&local_124,param_8);
    if (local_154 * local_164 + local_158 * local_168 + local_15c * local_16c < _DAT_004bd148) {
      local_158 = 0.0;
      local_15c = 0.0;
      local_154 = 0.0;
      pdVar13 = &local_100;
      pdVar14 = &local_cc;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
        pdVar13 = (double *)((int)pdVar13 + 4);
        pdVar14 = (double *)((int)pdVar14 + 4);
      }
    }
    if (local_148 <= _DAT_004bd148) {
      local_16c = (float)local_140;
      local_168 = local_140._4_4_;
      local_170 = local_138;
    }
    else {
      local_16c = local_110 * local_12c + (float)local_140;
      local_168 = local_10c * local_12c + local_140._4_4_;
      local_170 = local_108 * local_12c + local_138;
    }
    fVar7 = param_8 * param_8 * (float)_DAT_004bd1b8;
    local_100 = (double)local_16c;
    local_f8 = (double)local_168;
    local_140 = (double)fVar7;
    local_f0 = (double)local_170;
    local_b4 = (double)(fVar7 * local_16c + (float)local_cc);
    local_ac = local_140 * (double)local_168 + local_c4;
    local_a4 = local_140 * (double)local_170 + local_bc;
    local_15c = local_16c * param_8 + local_15c;
    pdVar13 = &local_b4;
    pdVar14 = &local_cc;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
      pdVar13 = (double *)((int)pdVar13 + 4);
      pdVar14 = (double *)((int)pdVar14 + 4);
    }
    local_158 = local_168 * param_8 + local_158;
    local_154 = local_170 * param_8 + local_154;
    local_178 = local_16c + local_124;
    local_174 = local_168 + local_120;
    local_170 = local_170 + local_11c;
    local_16c = local_178;
    local_168 = local_174;
    local_164 = local_170;
  }
  else {
    *param_2 = *param_2 | 2;
    local_15c = local_16c;
    local_158 = local_168;
    local_154 = local_164;
    pfVar19 = (float *)0x43b184;
    effect_target_list_scan_context_helper_004384f0(&local_cc,&local_15c,&local_124,param_8);
    if (local_154 * local_164 + local_158 * local_168 + local_15c * local_16c < _DAT_004bd148) {
      local_158 = 0.0;
      local_15c = 0.0;
      local_154 = 0.0;
      pdVar13 = &local_100;
      pdVar14 = &local_cc;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
        pdVar13 = (double *)((int)pdVar13 + 4);
        pdVar14 = (double *)((int)pdVar14 + 4);
      }
    }
    local_184 = local_110 * local_12c + (float)local_140;
    local_180 = local_10c * local_12c + local_140._4_4_;
    local_17c = local_108 * local_12c + local_138;
    fVar7 = param_8 * param_8 * (float)_DAT_004bd1b8;
    local_b4 = (double)local_184;
    local_ac = (double)local_180;
    local_140 = (double)fVar7;
    local_a4 = (double)local_17c;
    local_100 = (double)(fVar7 * local_184 + (float)local_cc);
    local_15c = local_184 * param_8 + local_15c;
    local_158 = local_180 * param_8 + local_158;
    local_154 = local_17c * param_8 + local_154;
    local_f8 = local_140 * (double)local_180 + local_c4;
    local_f0 = local_140 * (double)local_17c + local_bc;
    pdVar13 = &local_100;
    pdVar14 = &local_cc;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
      pdVar13 = (double *)((int)pdVar13 + 4);
      pdVar14 = (double *)((int)pdVar14 + 4);
    }
    local_184 = local_184 + local_124;
    local_180 = local_180 + local_120;
    local_17c = local_17c + local_11c;
    local_16c = local_184;
    local_168 = local_180;
    local_164 = local_17c;
    if ((*(uint *)(local_114 + 0x454) & 0x1000) == 0) {
      local_178 = *(float *)(local_114 + 200);
      local_174 = *(float *)(local_114 + 0xcc);
      local_170 = *(float *)(local_114 + 0xd0);
      pfVar19 = &local_178;
      param_1 = &local_98;
      integrate_vec3_motion_with_acceleration(param_1,pfVar19,local_e4,local_e0,local_dc,param_8);
      if (_DAT_004bd150 < param_8) {
        local_14c = local_94 / param_8;
      }
      else {
        local_14c = local_94 * _DAT_004bd188;
      }
    }
    else {
      local_14c = *(float *)(local_114 + 0xe0) * *(float *)(local_114 + 0xe8) * _DAT_004bd178;
      if (*(float *)(local_114 + 0xac) < _DAT_004bd134) {
        local_14c = local_14c * *(float *)(local_114 + 0xac);
      }
      local_160 = *(float *)(local_114 + 0xb4) * param_8;
      if (((_DAT_004bd148 <= local_160) && (local_160 <= _DAT_004bd1c0)) &&
         (local_144 = local_14c - *(float *)(local_114 + 0xcc),
         (float)_DAT_004bd1c8 <= ABS(local_144))) {
        local_14c = local_160 * local_144 + *(float *)(local_114 + 0xcc);
      }
      local_14c = local_14c * local_9c;
      local_178 = local_15c;
      local_174 = local_158;
      local_170 = local_154;
    }
  }
  local_ac = (double)local_10c;
  fVar7 = *(float *)(local_114 + 0x11c);
  local_100 = (double)(fVar7 * local_110 + (float)local_cc);
  local_f8 = (double)(fVar7 * local_10c + (float)local_c4);
  local_f0 = (double)(fVar7 * local_108 + (float)local_bc);
  pdVar13 = &local_100;
  pdVar14 = &local_cc;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pdVar14 = *(undefined4 *)pdVar13;
    pdVar13 = (double *)((int)pdVar13 + 4);
    pdVar14 = (double *)((int)pdVar14 + 4);
  }
  pfVar9 = (float *)zone_satellite_map_context_helper_00493da0(local_40,-(local_14c * param_8));
  pfVar8 = local_80;
  pfVar21 = local_40;
  pfVar15 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar15 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar15 = pfVar15 + 1;
  }
  uVar20 = 0x43b974;
  pfVar9 = compose_matrix_or_transform_a(pfVar21,pfVar8,pfVar4);
  pfVar15 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar15 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar15 = pfVar15 + 1;
  }
  local_100 = (double)local_68;
  local_f8 = (double)local_64;
  local_f0 = (double)local_60;
  pdVar13 = &local_100;
  puVar10 = (undefined4 *)&stack0xfffffe54;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = *(undefined4 *)pdVar13;
    pdVar13 = (double *)((int)pdVar13 + 4);
    puVar10 = puVar10 + 1;
  }
  dVar18 = (double)-*(float *)(local_114 + 0x11c);
  pdVar13 = &local_cc;
  puVar10 = (undefined4 *)&stack0xfffffe34;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = *(undefined4 *)pdVar13;
    pdVar13 = (double *)((int)pdVar13 + 4);
    puVar10 = puVar10 + 1;
  }
  puVar10 = (undefined4 *)
            vehicle_contact_physics_scalar_helper_0043bc90
                      ((undefined4 *)&local_100,in_stack_fffffe34,in_stack_fffffe3c,
                       (double)CONCAT44(uVar17,in_stack_fffffe44),dVar18,
                       (double)CONCAT44(pfVar19,param_1),(double)CONCAT44(pfVar21,uVar20),
                       (double)CONCAT44(pfVar4,pfVar8));
  pdVar13 = &local_cc;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pdVar13 = *puVar10;
    puVar10 = puVar10 + 1;
    pdVar13 = (double *)((int)pdVar13 + 4);
  }
  vehicle_contact_physics_response_helper_0043bd70((int)local_80,(undefined4 *)&local_cc);
  pfVar4 = local_104;
  pfVar19 = (float *)vec3_cross_product((float *)&local_b4,local_104,&local_15c);
  local_15c = *pfVar19;
  local_158 = pfVar19[1];
  local_154 = pfVar19[2];
  pfVar4 = (float *)vec3_cross_product((float *)&local_b4,&local_15c,pfVar4);
  local_15c = *pfVar4;
  local_158 = pfVar4[1];
  local_154 = pfVar4[2];
  fVar16 = vec3_length(*pfVar4,pfVar4[1],pfVar4[2]);
  local_150 = (float)fVar16;
  pfVar4 = (float *)copy_object_local_translation_vec3((undefined4 *)&local_b4,(int)local_80);
  local_110 = *pfVar4;
  local_10c = pfVar4[1];
  local_108 = pfVar4[2];
  fVar16 = dot_product_vec3(&local_110,&local_15c);
  if (fVar16 < (float10)_DAT_004bd148) {
    local_150 = -local_150;
  }
  uVar12 = local_118;
  if (((local_148 < _DAT_004bd148) && (_DAT_004bd1a8 < local_150)) && (local_150 < _DAT_004bd134)) {
    local_174 = 0.0;
    local_178 = 0.0;
    local_158 = 0.0;
    local_15c = 0.0;
    local_170 = 0.0;
    local_150 = 0.0;
    local_154 = 0.0;
    *param_2 = *param_2 & 0xffffdffd;
    uVar12 = 0;
  }
  if ((uVar12 != 0) && (local_130 == 0)) {
    pfVar4 = (float *)copy_vec3((undefined4 *)&local_b4,local_80);
    local_d8 = *pfVar4;
    local_d4 = pfVar4[1];
    local_d0 = pfVar4[2];
    fVar16 = dot_product_vec3(&local_d8,&local_15c);
    if (((float10)_DAT_004bd1d0 < fVar16) && (fVar16 < (float10)_DAT_004bd1d4)) {
      *param_2 = *param_2 & 0xffffdffd;
    }
  }
  *param_3 = local_15c;
  param_3[1] = local_158;
  param_3[2] = local_154;
  *param_4 = local_150;
  *param_5 = local_16c;
  param_5[1] = local_168;
  param_5[2] = local_164;
  *param_6 = *(float *)(local_114 + 200);
  param_6[1] = *(float *)(local_114 + 0xcc);
  param_6[2] = *(float *)(local_114 + 0xd0);
  param_6[1] = local_14c;
  pfVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_7 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    param_7 = param_7 + 1;
  }
  return;
}


