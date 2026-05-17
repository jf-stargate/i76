/*
 * Program: i76.exe
 * Function: apply_radial_damage_and_impulse_to_target
 * Entry: 004a7c80
 * Signature: bool __cdecl apply_radial_damage_and_impulse_to_target(LPVOID param_1, int param_2, float * param_3, float * param_4, float * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Root radial damage target handler;
   computes distance/direction, distribution, yaw, and dispatches class damage plus vehicle impulse.
    */

bool __cdecl
apply_radial_damage_and_impulse_to_target
          (LPVOID param_1,int param_2,float *param_3,float *param_4,float *param_5)

{
  int iVar1;
  int *piVar2;
  float *pfVar3;
  LPVOID pvVar4;
  int *piVar5;
  float10 fVar6;
  float local_d0;
  float fStack_cc;
  float local_c8;
  undefined4 local_c4;
  int local_c0;
  uint local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_90;
  float local_8c;
  float local_88;
  undefined4 local_78 [15];
  undefined4 local_3c [15];
  
  local_c4 = 0;
  if ((g_disable_radial_damage_for_optional_targets != 0) &&
     (iVar1 = world_object_has_optional_runtime_flag((int)param_1), iVar1 != 0)) {
    return false;
  }
  piVar2 = &local_c0;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  if (param_2 != 0) {
    if (*(int *)(param_2 + 0x6c) == 0x33) {
      piVar2 = (int *)build_vehicle_wheel_damage_distribution(&local_a8,param_2);
      piVar5 = &local_c0;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar5 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar5 = piVar5 + 1;
      }
      iVar1 = get_vehicle_damage_distribution_selector(param_2);
      if (iVar1 == 0x12) {
        local_bc = local_bc | 0x10000;
      }
      iVar1 = get_vehicle_damage_distribution_selector(param_2);
      if (iVar1 == 0x16) {
        local_bc = local_bc | 0x100000;
      }
      goto LAB_004a7d49;
    }
    if (*(int *)(param_2 + 0x6c) == 0x34) {
      piVar2 = (int *)build_explosion_damage_distribution(&local_90,param_2);
      piVar5 = &local_c0;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar5 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar5 = piVar5 + 1;
      }
      goto LAB_004a7d49;
    }
  }
  local_bc = CONCAT22(local_bc._2_2_,8);
LAB_004a7d49:
  if ((local_bc & 8) != 0) {
    local_d0 = -*param_4;
    fStack_cc = -param_4[1];
    local_c8 = -param_4[2];
    if ((param_2 == 0) || (iVar1 = is_vehicle_or_weapon_source_world_object(param_2), iVar1 == 0)) {
      local_d0 = local_d0 * *param_3 + param_3[2] * local_c8 + param_3[1] * fStack_cc;
      build_world_object_class_damage_transform(local_3c,(int)param_1);
    }
    else {
      local_d0 = local_d0 * *param_3 + param_3[2] * local_c8 + param_3[1] * fStack_cc;
      build_world_object_class_damage_transform(local_78,param_2);
    }
    local_ac = (float)ftol();
    iVar1 = world_object_has_optional_runtime_flag((int)param_1);
    if ((iVar1 != 0) && (0x14 < (uint)local_ac)) {
      local_d0 = local_ac;
      fStack_cc = 0.0;
      apply_vehicle_directional_impulse((int)param_1,param_4,(float)(uint)local_ac * _DAT_004beb70);
      notify_vehicle_runtime_after_impulse();
    }
  }
  local_c0 = 0;
  if (param_2 == 0) {
    local_c4 = 4;
  }
  else {
    iVar1 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar1 == 0) {
      iVar1 = is_transform_composed_world_object_class(param_2);
      if (iVar1 == 0) {
        if (*(int *)(param_2 + 0x6c) == 0x33) {
          local_c4 = 0x10;
          if ((local_bc & 8) != 0) {
            local_c4 = 0x18;
          }
          local_c0 = get_effect_source_parent_world_object(param_2);
        }
        else if (*(int *)(param_2 + 0x6c) == 0x34) {
          local_c0 = get_effect_source_parent_world_object(param_2);
          local_c4 = 0x10;
        }
      }
      else {
        local_c4 = 2;
      }
    }
    else {
      local_c4 = 1;
      local_c0 = param_2;
    }
  }
  iVar1 = world_object_has_optional_runtime_flag((int)param_1);
  if (iVar1 != 0) {
    if ((((local_b8 != 0.0) &&
         (pfVar3 = (float *)allocate_runtime_float_parameter_node
                                      (&g_damage_runtime_param_front_angle), pfVar3 != (float *)0x0)
         ) && (g_damage_runtime_param_front_angle != (float *)0x0)) &&
       (g_damage_runtime_param_front_angle == pfVar3)) {
      local_a8 = 0.0;
      local_a4 = 0.0;
      local_d0 = *param_5;
      local_a0 = 1.0;
      fStack_cc = param_5[1];
      local_c8 = param_5[2];
      fVar6 = compute_yaw_degrees_between_xz_vectors(&local_a8,&local_d0);
      *pfVar3 = (float)fVar6;
      fStack_cc = 0.0;
      local_d0 = local_b8;
      pfVar3[1] = (float)(uint)local_b8;
    }
    if (((local_b4 != 0.0) &&
        (pfVar3 = (float *)allocate_runtime_float_parameter_node(&g_damage_runtime_param_up_angle),
        pfVar3 != (float *)0x0)) &&
       ((g_damage_runtime_param_up_angle != (float *)0x0 &&
        (g_damage_runtime_param_up_angle == pfVar3)))) {
      local_d0 = 0.0;
      fStack_cc = 0.0;
      local_90 = 0.0;
      local_c8 = 1.0;
      local_8c = 0.0;
      local_a8 = *param_5;
      local_88 = 1.0;
      local_a4 = param_5[1];
      local_a0 = param_5[2];
      fVar6 = compute_yaw_degrees_between_xz_vectors(&local_90,&local_a8);
      *pfVar3 = (float)fVar6;
      fStack_cc = 0.0;
      local_d0 = local_b4;
      pfVar3[1] = (float)(uint)local_b4;
    }
    if (((local_b0 != 0.0) &&
        (pfVar3 = (float *)allocate_runtime_float_parameter_node(&g_damage_runtime_param_side_angle)
        , pfVar3 != (float *)0x0)) &&
       ((g_damage_runtime_param_side_angle != (float *)0x0 &&
        (g_damage_runtime_param_side_angle == pfVar3)))) {
      local_d0 = 0.0;
      fStack_cc = 0.0;
      local_a8 = 0.0;
      local_c8 = 1.0;
      local_a4 = 0.0;
      local_90 = *param_5;
      local_a0 = 1.0;
      local_8c = param_5[1];
      local_88 = param_5[2];
      fVar6 = compute_yaw_degrees_between_xz_vectors(&local_a8,&local_90);
      *pfVar3 = (float)fVar6;
      fStack_cc = 0.0;
      local_d0 = local_b0;
      pfVar3[1] = (float)(uint)local_b0;
    }
    if ((((local_ac != 0.0) &&
         (pfVar3 = (float *)allocate_runtime_float_parameter_node
                                      (&g_damage_runtime_param_impulse_angle),
         pfVar3 != (float *)0x0)) && (g_damage_runtime_param_impulse_angle != (float *)0x0)) &&
       (g_damage_runtime_param_impulse_angle == pfVar3)) {
      local_d0 = 0.0;
      fStack_cc = 0.0;
      local_a8 = 0.0;
      local_c8 = 1.0;
      local_a4 = 0.0;
      local_90 = *param_5;
      local_a0 = 1.0;
      local_8c = param_5[1];
      local_88 = param_5[2];
      fVar6 = compute_yaw_degrees_between_xz_vectors(&local_a8,&local_90);
      *pfVar3 = (float)fVar6;
      fStack_cc = 0.0;
      local_d0 = local_ac;
      pfVar3[1] = (float)(uint)local_ac;
    }
  }
  increment_refcount_recursive_for_object_tree((int)param_1,s_damage_004feed8);
  dispatch_damage_context_to_world_object_class_handler((int)param_1,&local_c0,param_5);
  pvVar4 = release_world_object_tree_reference(param_1,s_damage_004feed8);
  if (pvVar4 != (LPVOID)0x0) {
    finalize_released_world_object_after_damage(pvVar4,s_damage_004feed8);
  }
  if ((local_c0 != 0) && (pvVar4 != (LPVOID)0x0)) {
    record_vehicle_damage_source_event
              (local_c0,(byte)local_c4,local_bc & 0xffff,(uint)pvVar4,param_2);
  }
  return pvVar4 != (LPVOID)0x0;
}


