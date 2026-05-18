/*
 * Program: i76.exe
 * Function: update_ai_vehicle_alternating_side_attack_state
 * Entry: 0041e450
 * Signature: undefined __cdecl update_ai_vehicle_alternating_side_attack_state(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Alternates between combat behavior modes based on
   distance, timer, and line/visibility checks. */

void __cdecl update_ai_vehicle_alternating_side_attack_state(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  
  iVar1 = get_ai_vehicle_behavior_state_block((int)param_1);
  fVar3 = (float10)world_object_geometry_context_helper_004589f0((uint)param_1,(uint)param_2);
  if ((float10)_DAT_004bcb4c <= fVar3) {
    if ((float)fVar3 <= _DAT_004bcb50) {
      fVar3 = get_gameplay_runtime_seconds();
      if ((float10)*(float *)(iVar1 + 0xa82c) <= fVar3) {
        fVar4 = get_gameplay_runtime_seconds();
        fVar3 = (float10)_DAT_004bcb00;
        iVar2 = rand();
        *(float *)(iVar1 + 0xa82c) = (float)(iVar2 % 5) + (float)(fVar4 + fVar3);
        *(uint *)(iVar1 + 0xa9a0) = (uint)(*(int *)(iVar1 + 0xa9a0) == 0);
      }
    }
    else {
      *(undefined4 *)(iVar1 + 0xa9a0) = 1;
      fVar4 = get_gameplay_runtime_seconds();
      fVar3 = (float10)_DAT_004bcb00;
      iVar2 = rand();
      *(float *)(iVar1 + 0xa82c) = (float)(iVar2 % 5) + (float)(fVar4 + fVar3);
    }
  }
  else {
    *(undefined4 *)(iVar1 + 0xa9a0) = 0;
    fVar4 = get_gameplay_runtime_seconds();
    fVar3 = (float10)_DAT_004bcb00;
    iVar2 = rand();
    *(float *)(iVar1 + 0xa82c) = (float)(iVar2 % 5) + (float)(fVar4 + fVar3);
  }
  if (*(int *)(iVar1 + 0xa9a0) == 0) {
    iVar1 = is_ai_target_projected_to_same_route_segment((int)param_1,(int)param_2);
    if (iVar1 == 0) {
      run_ai_combat_behavior_mode_4((float)param_1,(float)param_2);
    }
    else {
      update_ai_roadwar_path_follow_drive_control((float)param_1,(uint)param_2);
    }
  }
  else if (*(int *)(iVar1 + 0xa9a0) == 1) {
    iVar1 = is_ai_target_projected_to_same_route_segment((int)param_1,(int)param_2);
    if (iVar1 == 0) {
      run_ai_combat_behavior_mode_2((float)param_1,(float)param_2);
    }
    else {
      roadwar_atomic_behavior_mode3_wrapper(param_1,param_2);
    }
  }
  return;
}


