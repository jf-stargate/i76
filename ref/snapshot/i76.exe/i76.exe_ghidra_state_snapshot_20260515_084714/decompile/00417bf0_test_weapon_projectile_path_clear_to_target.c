/*
 * Program: i76.exe
 * Function: test_weapon_projectile_path_clear_to_target
 * Entry: 00417bf0
 * Signature: undefined4 __cdecl test_weapon_projectile_path_clear_to_target(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Tests whether a weapon/projectile path from source to
   target is clear, checking moving effect targets and collision candidates. */

undefined4 __cdecl test_weapon_projectile_path_clear_to_target(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  float *pfVar7;
  undefined4 *puVar8;
  float *pfVar9;
  float *pfVar10;
  float10 fVar11;
  float in_stack_fffffdf0;
  float in_stack_fffffdf4;
  float in_stack_fffffdf8;
  float in_stack_fffffdfc;
  float in_stack_fffffe00;
  float in_stack_fffffe04;
  float in_stack_fffffe08;
  float in_stack_fffffe0c;
  float in_stack_fffffe10;
  float fVar12;
  float *pfVar13;
  float fVar14;
  float fVar15;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  undefined1 *local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_184 [4];
  float local_174;
  float local_170;
  float local_16c [3];
  undefined1 local_160 [24];
  undefined4 local_148 [12];
  double local_118;
  undefined1 local_b0 [176];
  
  local_1a4 = local_b0;
  fVar11 = get_runtime_update_delta_seconds();
  local_1a0 = (float)fVar11;
  pfVar3 = (float *)get_cached_world_object_aim_position(&local_19c,param_1);
  fVar1 = *pfVar3;
  fVar14 = pfVar3[2];
  fVar2 = pfVar3[1] - _DAT_004bc8e0;
  pfVar3 = (float *)get_cached_world_object_aim_position(&local_19c,param_2);
  local_1b4 = *pfVar3;
  local_1b0 = pfVar3[1] - _DAT_004bc8e0;
  local_1ac = pfVar3[2];
  local_19c = local_1b4 - fVar1;
  fVar15 = local_1b0 - fVar2;
  fVar12 = local_1ac - fVar14;
  local_198 = fVar15;
  local_194 = fVar12;
  local_184[0] = fVar1;
  local_184[1] = fVar2;
  local_184[2] = fVar14;
  fVar11 = mission_flow_map_context_helper_0049c7b0();
  local_184[3] = (float)(fVar11 * (float10)local_19c);
  puVar5 = (undefined4 *)(param_1 + 0x18);
  puVar8 = local_148;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar8 = puVar8 + 1;
  }
  local_174 = (float)((float10)fVar15 * fVar11);
  local_170 = (float)((float10)fVar12 * fVar11);
  local_118 = local_118 - _DAT_004bc8e8;
  iVar6 = weapon_ordnance_query_context_helper_004a7800((int)local_160,&local_1b4);
  if (iVar6 != 0) {
    return 0;
  }
  piVar4 = (int *)get_current_effect_target_scan_object();
  fVar1 = local_1a0;
  if (piVar4 == (int *)0x0) {
    return 1;
  }
  do {
    iVar6 = is_vehicle_or_actor_runtime_world_object(*piVar4);
    if ((iVar6 == 0) && (*piVar4 != param_2)) {
      fVar14 = (float)piVar4[4] - _DAT_004bc8f0;
      pfVar3 = local_16c;
      pfVar10 = &local_1a8;
      pfVar13 = &local_19c;
      fVar12 = 6.014383e-39;
      fVar15 = fVar1;
      puVar5 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(pfVar13,piVar4);
      puVar8 = (undefined4 *)&stack0xfffffe08;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
      }
      pfVar7 = local_184;
      pfVar9 = (float *)&stack0xfffffdf0;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar9 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar9 = pfVar9 + 1;
      }
      iVar6 = test_effect_target_swept_interval_candidate
                        (in_stack_fffffdf0,in_stack_fffffdf4,in_stack_fffffdf8,in_stack_fffffdfc,
                         in_stack_fffffe00,in_stack_fffffe04,in_stack_fffffe08,in_stack_fffffe0c,
                         in_stack_fffffe10,fVar12,(float)pfVar13,(float)piVar4,fVar14,fVar15,pfVar10
                         ,pfVar3);
      if (iVar6 != 0) {
        pfVar3 = local_184;
        pfVar10 = (float *)&stack0xfffffe00;
        for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
          *pfVar10 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar10 = pfVar10 + 1;
        }
        in_stack_fffffdfc = 6.014508e-39;
        iVar6 = query_vehicle_effect_collision_response_state();
        if (iVar6 != 0) {
          return 0;
        }
      }
    }
    piVar4 = (int *)effect_target_scan_query_context_helper_00436790();
    if (piVar4 == (int *)0x0) {
      return 1;
    }
  } while( true );
}


