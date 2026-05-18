/*
 * Program: i76.exe
 * Function: scan_effect_targets_for_collision_response_b
 * Entry: 00435830
 * Signature: undefined4 __cdecl scan_effect_targets_for_collision_response_b(int param_1, int param_2, float * param_3, int * param_4, undefined4 * param_5)
 */


/* cgpt readability rename v13 set A: Variant effect-target scan that evaluates collision candidates
   and output contact/target response data. */

undefined4 __cdecl
scan_effect_targets_for_collision_response_b
          (int param_1,int param_2,float *param_3,int *param_4,undefined4 *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  undefined4 *puVar5;
  float *pfVar6;
  undefined3 extraout_var;
  int iVar7;
  int *piVar8;
  int *piVar9;
  float *pfVar10;
  undefined4 *puVar11;
  float *pfVar12;
  float *pfVar13;
  float10 fVar14;
  float in_stack_fffffeac;
  float in_stack_fffffeb0;
  float in_stack_fffffeb4;
  float in_stack_fffffeb8;
  float in_stack_fffffebc;
  float in_stack_fffffec0;
  float in_stack_fffffec4;
  float in_stack_fffffec8;
  float in_stack_fffffecc;
  float fVar15;
  float fVar16;
  float fVar17;
  float *pfVar18;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_ac;
  float local_a8 [4];
  float local_98;
  float local_94;
  float local_90;
  float local_8c [3];
  float local_80 [16];
  float local_40 [16];
  
  fVar14 = get_runtime_update_delta_seconds();
  local_90 = (float)fVar14;
  fVar14 = mission_flow_map_context_helper_0049c7b0();
  local_d4 = (float)*(double *)(param_1 + 0x48);
  local_d0 = (float)*(double *)(param_1 + 0x50);
  local_d8 = (float)*(double *)(param_1 + 0x40);
  local_dc = (float)fVar14;
  local_f8 = *param_3 - local_d8;
  local_f4 = param_3[1] - local_d4;
  local_f0 = param_3[2] - local_d0;
  fVar2 = local_f4 * local_dc;
  fVar3 = local_f0 * local_dc;
  fVar1 = local_f8 * local_dc;
  if (local_d8 <= *param_3) {
    local_b4 = *param_3;
    local_c0 = local_d8;
  }
  else {
    local_b4 = local_d8;
    local_c0 = *param_3;
  }
  if (param_3[2] <= local_d0) {
    local_b8 = param_3[2];
    local_ac = local_d0;
  }
  else {
    local_b8 = local_d0;
    local_ac = param_3[2];
  }
  if (g_effect_target_primary_list == (int *)0x0) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  else {
    g_effect_target_scan_current_list_head = &g_effect_target_primary_list;
    g_effect_target_scan_current_node = g_effect_target_primary_list;
  }
  piVar8 = g_effect_target_scan_current_node;
  local_a8[3] = fVar1;
  local_a8[0] = local_d8;
  local_a8[1] = local_d4;
  local_a8[2] = local_d0;
  local_98 = fVar2;
  local_94 = fVar3;
  fVar17 = local_90;
  if (g_effect_target_scan_current_node == (int *)0x0) {
    piVar9 = (int *)0x0;
  }
  else {
    piVar9 = (int *)g_effect_target_scan_current_node[2];
  }
joined_r0x004359b4:
  do {
    if (piVar9 == (int *)0x0) {
      *param_4 = 0;
      *param_5 = 0xffffffff;
      return 0;
    }
    local_90 = fVar17;
    if ((((*piVar9 != param_2) && (local_c0 <= (float)piVar9[0x17])) &&
        ((float)piVar9[0x14] <= local_b4)) &&
       ((local_b8 <= (float)piVar9[0x19] && ((float)piVar9[0x16] <= local_ac)))) {
      pfVar18 = local_8c;
      pfVar6 = &local_e0;
      fVar16 = (float)piVar9[4];
      pfVar13 = &local_f8;
      fVar15 = 6.185341e-39;
      piVar8 = piVar9;
      puVar5 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(pfVar13,piVar9);
      puVar11 = (undefined4 *)&stack0xfffffec4;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar11 = puVar11 + 1;
      }
      pfVar10 = local_a8;
      pfVar12 = (float *)&stack0xfffffeac;
      for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar12 = *pfVar10;
        pfVar10 = pfVar10 + 1;
        pfVar12 = pfVar12 + 1;
      }
      iVar7 = test_effect_target_swept_interval_candidate
                        (in_stack_fffffeac,in_stack_fffffeb0,in_stack_fffffeb4,in_stack_fffffeb8,
                         in_stack_fffffebc,in_stack_fffffec0,in_stack_fffffec4,in_stack_fffffec8,
                         in_stack_fffffecc,fVar15,(float)pfVar13,(float)piVar8,fVar16,fVar17,pfVar6,
                         pfVar18);
      piVar8 = g_effect_target_scan_current_node;
      if (iVar7 != 0) {
        pfVar6 = local_a8;
        pfVar13 = (float *)&stack0xfffffebc;
        for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar13 = *pfVar6;
          pfVar6 = pfVar6 + 1;
          pfVar13 = pfVar13 + 1;
        }
        in_stack_fffffeb8 = 6.185465e-39;
        iVar7 = query_vehicle_effect_collision_response_state();
        piVar8 = g_effect_target_scan_current_node;
        if (iVar7 != 0) {
          local_f8 = fVar1 * local_e0 + local_d8;
          *param_3 = local_f8;
          local_f4 = fVar2 * local_e0 + local_d4;
          param_3[1] = local_f4;
          local_f0 = fVar3 * local_e0 + local_d0;
          param_3[2] = local_f0;
          iVar7 = effect_target_list_scan_context_helper_004387b0(&local_d8,piVar9);
          local_f8 = *(float *)(iVar7 + 0xc);
          local_d8 = fVar1 - local_f8;
          local_f4 = *(float *)(iVar7 + 0x10);
          local_f0 = *(float *)(iVar7 + 0x14);
          local_d4 = fVar2 - local_f4;
          local_d0 = fVar3 - local_f0;
          if (*(int *)(*piVar9 + 0x6c) == 8) {
            *param_4 = *piVar9;
          }
          local_c0 = local_d8;
          local_bc = local_d4;
          local_b8 = local_d0;
          if (*param_4 == 0) {
            local_f8 = 0.0;
            local_f4 = 0.0;
            *param_5 = 0xffffffff;
            local_f0 = 0.0;
            local_a8[0] = 0.0;
            local_a8[1] = 0.0;
            local_a8[2] = 0.0;
          }
          else {
            pfVar6 = (float *)compute_transform_relative_to_ancestor(local_40,*param_4,0);
            pfVar13 = local_80;
            for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar13 = *pfVar6;
              pfVar6 = pfVar6 + 1;
              pfVar13 = pfVar13 + 1;
            }
            pfVar6 = (float *)compose_matrix_or_transform_b(local_80,local_40);
            pfVar13 = local_80;
            for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar13 = *pfVar6;
              pfVar6 = pfVar6 + 1;
              pfVar13 = pfVar13 + 1;
            }
            transform_vec3_array_by_matrix(local_a8,param_3,1,local_80);
            *param_5 = *(undefined4 *)(*param_4 + 0x6c);
          }
          bVar4 = apply_radial_damage_and_impulse_to_target
                            ((LPVOID)*param_4,param_1,&local_c0,local_8c,local_a8);
          if (CONCAT31(extraout_var,bVar4) == 0) {
            *param_4 = 0;
          }
          return 1;
        }
      }
    }
    piVar9 = (int *)0x0;
    fVar17 = local_90;
  } while (piVar8 == (int *)0x0);
  g_effect_target_scan_current_node = (int *)*piVar8;
  if (g_effect_target_scan_current_node == (int *)0x0) goto code_r0x00435aae;
  goto LAB_00435ad4;
code_r0x00435aae:
  if ((int **)g_effect_target_scan_current_list_head == &g_effect_target_primary_list) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  piVar8 = g_effect_target_scan_current_node;
  if (g_effect_target_scan_current_node != (int *)0x0) {
LAB_00435ad4:
    piVar9 = (int *)g_effect_target_scan_current_node[2];
    piVar8 = g_effect_target_scan_current_node;
  }
  goto joined_r0x004359b4;
}


