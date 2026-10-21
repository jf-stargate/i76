/*
 * Program: i76.exe
 * Function: FUN_004a2070
 * Entry: 004a2070
 * Signature: undefined __cdecl FUN_004a2070(LPVOID param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl FUN_004a2070(LPVOID param_1)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  ulonglong uVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float10 fVar8;
  float local_90;
  float local_8c;
  float local_88;
  double local_84;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined8 local_60;
  float local_54;
  int local_50;
  float local_4c;
  float *local_48;
  float local_44;
  float local_40 [16];
  
  fVar8 = get_runtime_frame_delta_seconds();
  local_4c = (float)fVar8;
  iVar6 = *(int *)((int)param_1 + 0x70);
  local_50 = iVar6;
  fVar8 = get_network_or_session_runtime_seconds();
  if ((float10)*(float *)(iVar6 + 0x3c) < fVar8) {
    draw_classifier_display(param_1);
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    return;
  }
  pfVar1 = (float *)((int)param_1 + 0x18);
  pfVar2 = (float *)((int)param_1 + 0x84);
  transform_vec3_array_by_matrix(&local_6c,pfVar2,1,pfVar1);
  local_48 = (float *)(iVar6 + 0x18);
  local_90 = *local_48;
  local_8c = *(float *)(iVar6 + 0x1c);
  local_88 = *(float *)(iVar6 + 0x20);
  local_44 = local_8c;
  integrate_vertical_motion_with_gravity(&local_6c,&local_90,-9.8,local_4c);
  local_60 = (double)(local_6c * _DAT_006442c4 + (float)_fpu_double_to_integer_magic_bias);
  local_84 = (double)(local_64 * _DAT_006442c4 + (float)_fpu_double_to_integer_magic_bias);
  if (((0x2800 - local_84._0_4_ | 0x2800U - (int)(undefined4 *)local_60 | local_84._0_4_ |
       (uint)(undefined4 *)local_60) & 0x80000000) != 0) {
    draw_classifier_display(param_1);
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    return;
  }
  uVar4 = (ulonglong)local_60 >> 0x20;
  local_60 = (double)CONCAT44((int)uVar4,(float *)(iVar6 + 0x24));
  pfVar5 = (float *)effect_target_list_scan_context_helper_004389f0
                              (local_40,pfVar1,*(float *)(iVar6 + 0x24),*(float *)(iVar6 + 0x28),
                               *(float *)(iVar6 + 0x2c),local_4c);
  pfVar7 = pfVar1;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  probe_effect_target_surface_height_at_position
            ((double)CONCAT44(local_68,local_6c),local_64,&local_54,&local_78);
  if (local_68 <= local_54) {
    local_8c = (local_8c + local_44) * _DAT_004bea98;
    if (_DAT_004bea80 < local_8c) {
      draw_classifier_display(param_1);
      unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
      return;
    }
    local_68 = local_54;
    fVar3 = (local_78 * local_90 + local_70 * local_88 + local_74 * local_8c) * _DAT_004beaa4;
    local_8c = (fVar3 * local_74 + local_8c) * _DAT_004beaa8;
    local_90 = (fVar3 * local_78 + local_90) * _DAT_004beaa8;
    local_88 = (fVar3 * local_70 + local_88) * _DAT_004beaa8;
    if (ABS(local_8c) < (float)_DAT_004beab0) {
      local_88 = 0.0;
      local_8c = 0.0;
      local_90 = 0.0;
      *(undefined4 *)(local_50 + 0x2c) = 0;
      *(undefined4 *)(local_50 + 0x28) = 0;
      *(undefined4 *)local_60 = 0;
    }
  }
  *(double *)((int)param_1 + 0x40) =
       (double)(local_6c -
               (*pfVar1 * *pfVar2 +
               *(float *)((int)param_1 + 0x30) * *(float *)((int)param_1 + 0x8c) +
               *(float *)((int)param_1 + 0x24) * *(float *)((int)param_1 + 0x88)));
  *(double *)((int)param_1 + 0x48) =
       (double)(local_68 -
               (*(float *)((int)param_1 + 0x1c) * *pfVar2 +
               *(float *)((int)param_1 + 0x34) * *(float *)((int)param_1 + 0x8c) +
               *(float *)((int)param_1 + 0x28) * *(float *)((int)param_1 + 0x88)));
  *(double *)((int)param_1 + 0x50) =
       (double)(local_64 -
               (*(float *)((int)param_1 + 0x20) * *pfVar2 +
               *(float *)((int)param_1 + 0x38) * *(float *)((int)param_1 + 0x8c) +
               *(float *)((int)param_1 + 0x2c) * *(float *)((int)param_1 + 0x88)));
  *local_48 = local_90;
  local_48[1] = local_8c;
  local_48[2] = local_88;
  *(float *)(local_50 + 8) = SQRT(local_88 * local_88 + local_8c * local_8c + local_90 * local_90);
  return;
}


