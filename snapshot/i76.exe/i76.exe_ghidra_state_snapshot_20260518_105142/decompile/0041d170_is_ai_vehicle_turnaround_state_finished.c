/*
 * Program: i76.exe
 * Function: is_ai_vehicle_turnaround_state_finished
 * Entry: 0041d170
 * Signature: undefined4 __cdecl is_ai_vehicle_turnaround_state_finished(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Checks heading/position/speed deltas to determine
   whether a turnaround state has completed. */

undefined4 __cdecl is_ai_vehicle_turnaround_state_finished(int param_1)

{
  int iVar1;
  float10 fVar2;
  float10 extraout_ST0;
  undefined4 local_1c;
  
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  fVar2 = compute_ai_vehicle_forward_heading_angle(param_1);
  fVar2 = normalize_angle_delta_signed_pi((float)fVar2,*(float *)(iVar1 + 0x9d38));
  apply_world_object_transform_to_bounds_or_geometry
            (*(double *)(param_1 + 0x40),*(double *)(param_1 + 0x50));
  if ((float10)_DAT_004bcb18 < ABS((float10)*(float *)(iVar1 + 0x9d3c) - extraout_ST0)) {
LAB_0041d227:
    local_1c = 1;
  }
  else {
    if (_DAT_004bcb04 <= (float)ABS(fVar2)) {
      iVar1 = get_vehicle_runtime_context(param_1);
      if (*(float *)(iVar1 + 0xac) < _DAT_004bcae4) goto LAB_0041d227;
    }
    local_1c = 0;
  }
  return local_1c;
}


