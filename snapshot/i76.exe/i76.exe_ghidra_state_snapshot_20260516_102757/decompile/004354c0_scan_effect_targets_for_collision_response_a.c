/*
 * Program: i76.exe
 * Function: scan_effect_targets_for_collision_response_a
 * Entry: 004354c0
 * Signature: undefined4 __cdecl scan_effect_targets_for_collision_response_a(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, undefined4 param_8, uint param_9)
 */


/* cgpt readability rename v13 set A: Scans effect-target lists for a matching collision/response
   candidate using transformed positions and runtime filters. */

undefined4 __cdecl
scan_effect_targets_for_collision_response_a
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,undefined4 param_8,uint param_9)

{
  float fVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int *piVar6;
  int iVar7;
  uint *puVar8;
  float *pfVar9;
  uint *puVar10;
  float10 fVar11;
  uint *in_stack_0000003c;
  float afStackY_18c [4];
  uint in_stack_fffffe88;
  uint *puVar12;
  float local_134;
  undefined4 local_12c;
  float local_10c;
  undefined4 local_108;
  undefined4 local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4 [4];
  float local_e4;
  float local_e0;
  float local_d0 [16];
  float local_90 [4];
  float local_80 [16];
  float local_40 [16];
  
  fVar11 = mission_flow_map_context_helper_0049c7b0();
  fVar3 = (param_2 - param_6) * (float)fVar11;
  fVar4 = (param_3 - param_7) * (float)fVar11;
  fVar1 = (float)(fVar11 * (float10)(param_1 - param_5));
  local_12c = 0;
  if (g_effect_target_primary_list == (int *)0x0) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  else {
    g_effect_target_scan_current_list_head = &g_effect_target_primary_list;
    g_effect_target_scan_current_node = g_effect_target_primary_list;
  }
  piVar6 = g_effect_target_scan_current_node;
  if (g_effect_target_scan_current_node == (int *)0x0) {
    puVar8 = (uint *)0x0;
  }
  else {
    puVar8 = (uint *)g_effect_target_scan_current_node[2];
  }
joined_r0x00435593:
  do {
    if (puVar8 == (uint *)0x0) {
      return local_12c;
    }
    if (*puVar8 != param_9) {
      pfVar5 = (float *)get_effect_target_transformed_position_radius(local_90,(int *)puVar8);
      local_f4[0] = param_1;
      local_f4[3] = fVar1;
      local_f4[1] = param_2;
      local_f4[2] = param_3;
      local_e4 = fVar3;
      local_e0 = fVar4;
      piVar6 = g_effect_target_scan_current_node;
      if ((param_3 - pfVar5[2]) * (param_3 - pfVar5[2]) +
          (param_2 - pfVar5[1]) * (param_2 - pfVar5[1]) + (param_1 - *pfVar5) * (param_1 - *pfVar5)
          < (pfVar5[3] + param_4) * (pfVar5[3] + param_4)) {
        pfVar5 = local_f4;
        pfVar9 = afStackY_18c;
        puVar12 = puVar8;
        for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar9 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar9 = pfVar9 + 1;
        }
        iVar7 = query_vehicle_effect_collision_response_state();
        piVar6 = g_effect_target_scan_current_node;
        if (iVar7 != 0) {
          local_100 = fVar1 * local_134 + param_1;
          local_fc = fVar3 * local_134 + param_2;
          local_f8 = fVar4 * local_134 + param_3;
          if (*(int *)(*puVar8 + 0x6c) == 8) {
            *in_stack_0000003c = *puVar8;
          }
          if (*in_stack_0000003c == 0) {
            local_10c = 0.0;
            local_108 = 0;
            local_104 = 0;
          }
          else {
            pfVar5 = (float *)compute_transform_relative_to_ancestor(local_80,*in_stack_0000003c,0);
            pfVar9 = local_d0;
            for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar9 = *pfVar5;
              pfVar5 = pfVar5 + 1;
              pfVar9 = pfVar9 + 1;
            }
            pfVar5 = (float *)compose_matrix_or_transform_b(local_d0,local_40);
            pfVar9 = local_d0;
            for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
              *pfVar9 = *pfVar5;
              pfVar5 = pfVar5 + 1;
              pfVar9 = pfVar9 + 1;
            }
            transform_vec3_array_by_matrix(&local_10c,&local_100,1,local_d0);
          }
          uVar2 = *in_stack_0000003c;
          puVar8 = &param_9;
          puVar10 = (uint *)&stack0xfffffe88;
          for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar10 = *puVar8;
            puVar8 = puVar8 + 1;
            puVar10 = puVar10 + 1;
          }
          afStackY_18c[3] = 6.184468e-39;
          weapon_ordnance_query_context_helper_004a8240(uVar2,in_stack_fffffe88,(uint)puVar12);
          local_12c = 1;
          piVar6 = g_effect_target_scan_current_node;
        }
      }
    }
    puVar8 = (uint *)0x0;
  } while (piVar6 == (int *)0x0);
  g_effect_target_scan_current_node = (int *)*piVar6;
  if (g_effect_target_scan_current_node == (int *)0x0) goto code_r0x004357e9;
  goto LAB_0043580d;
code_r0x004357e9:
  if ((int **)g_effect_target_scan_current_list_head == &g_effect_target_primary_list) {
    g_effect_target_scan_current_list_head = &g_effect_target_secondary_list;
    g_effect_target_scan_current_node = g_effect_target_secondary_list;
  }
  piVar6 = g_effect_target_scan_current_node;
  if (g_effect_target_scan_current_node != (int *)0x0) {
LAB_0043580d:
    puVar8 = (uint *)g_effect_target_scan_current_node[2];
    piVar6 = g_effect_target_scan_current_node;
  }
  goto joined_r0x00435593;
}


