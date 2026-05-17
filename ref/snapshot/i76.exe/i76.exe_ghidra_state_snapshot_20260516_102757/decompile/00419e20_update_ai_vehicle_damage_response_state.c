/*
 * Program: i76.exe
 * Function: update_ai_vehicle_damage_response_state
 * Entry: 00419e20
 * Signature: undefined4 __cdecl update_ai_vehicle_damage_response_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Large AI behavior helper using vehicle runtime/damage
   event state, frame delta, and steering/target vectors to update damage-response behavior. */

undefined4 __cdecl update_ai_vehicle_damage_response_state(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  float *pfVar5;
  float *pfVar6;
  undefined4 *puVar7;
  float *pfVar8;
  float *pfVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float in_stack_fffffe9c;
  float in_stack_fffffea0;
  float in_stack_fffffea4;
  float in_stack_fffffea8;
  float in_stack_fffffeac;
  float in_stack_fffffeb0;
  float in_stack_fffffeb4;
  float fVar13;
  float *pfVar14;
  float fVar15;
  float *pfVar16;
  float fVar17;
  float fVar18;
  float local_108;
  float local_104;
  float local_100;
  float local_f0;
  undefined1 *local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8 [4];
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc [3];
  undefined1 local_b0 [176];
  
  local_108 = *(float *)(param_1 + 0x30);
  fVar17 = *(float *)(param_1 + 0x34);
  fVar18 = *(float *)(param_1 + 0x38);
  pfVar14 = (float *)(param_1 + 0x18);
  local_104 = fVar17;
  local_100 = fVar18;
  fVar10 = mission_flow_map_context_helper_0049c7b0();
  fVar11 = fVar10 * (float10)*(float *)(param_2 + 0xe8) * (float10)_DAT_004bc9ec;
  fVar10 = (float10)local_108;
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = get_vehicle_damage_event_state_block(iVar1);
  local_108 = (float)*(double *)(param_1 + 0x40);
  local_104 = (float)*(double *)(param_1 + 0x48);
  local_100 = (float)*(double *)(param_1 + 0x50);
  fVar13 = 6.026339e-39;
  local_e4 = local_108;
  local_e0 = local_104;
  local_dc = local_100;
  iVar1 = probe_ai_vehicle_path_clearance_along_heading
                    (pfVar14,&local_e4,iVar1 + 0xbc,*(float *)(iVar1 + 0xac),&local_c0,
                     *(float *)(iVar1 + 0xe8),1,(float *)(iVar2 + 0x9d28));
  if (iVar1 != 0) {
    return 1;
  }
  local_ec = local_b0;
  fVar12 = get_runtime_update_delta_seconds();
  local_e8 = (float)fVar12;
  local_108 = (float)*(double *)(param_1 + 0x40);
  local_104 = (float)*(double *)(param_1 + 0x48);
  local_100 = (float)*(double *)(param_1 + 0x50);
  local_d8[0] = local_108;
  local_d8[1] = local_104;
  local_d8[2] = local_100;
  local_d8[3] = (float)(fVar11 * fVar10);
  local_c8 = (float)((float10)fVar17 * fVar11);
  local_c4 = (float)((float10)fVar18 * fVar11);
  piVar3 = (int *)get_current_effect_target_scan_object();
  if (piVar3 != (int *)0x0) {
    do {
      if (*piVar3 != param_1) {
        pfVar6 = local_bc;
        fVar17 = (float)piVar3[4] - _DAT_004bc8f0;
        pfVar9 = &local_f0;
        pfVar16 = &local_108;
        fVar15 = 6.026578e-39;
        fVar18 = local_e8;
        puVar4 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(pfVar16,piVar3);
        puVar7 = (undefined4 *)&stack0xfffffeb4;
        for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar7 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar7 = puVar7 + 1;
        }
        pfVar5 = local_d8;
        pfVar8 = (float *)&stack0xfffffe9c;
        for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
          *pfVar8 = *pfVar5;
          pfVar5 = pfVar5 + 1;
          pfVar8 = pfVar8 + 1;
        }
        iVar1 = test_effect_target_swept_interval_candidate
                          (in_stack_fffffe9c,in_stack_fffffea0,in_stack_fffffea4,in_stack_fffffea8,
                           in_stack_fffffeac,in_stack_fffffeb0,in_stack_fffffeb4,fVar13,
                           (float)pfVar14,fVar15,(float)pfVar16,(float)piVar3,fVar17,fVar18,pfVar9,
                           pfVar6);
        if (iVar1 != 0) {
          pfVar6 = local_d8;
          pfVar9 = (float *)&stack0xfffffeac;
          for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
            *pfVar9 = *pfVar6;
            pfVar6 = pfVar6 + 1;
            pfVar9 = pfVar9 + 1;
          }
          in_stack_fffffea8 = 6.026699e-39;
          iVar1 = query_vehicle_effect_collision_response_state();
          if (iVar1 != 0) {
            return 1;
          }
        }
      }
      piVar3 = (int *)effect_target_scan_query_context_helper_00436790();
      if (piVar3 == (int *)0x0) {
        return 0;
      }
    } while( true );
  }
  return 0;
}


