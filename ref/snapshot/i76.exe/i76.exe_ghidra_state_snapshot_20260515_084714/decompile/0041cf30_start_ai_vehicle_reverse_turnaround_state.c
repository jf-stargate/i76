/*
 * Program: i76.exe
 * Function: start_ai_vehicle_reverse_turnaround_state
 * Entry: 0041cf30
 * Signature: undefined __cdecl start_ai_vehicle_reverse_turnaround_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Captures steering/heading baseline, starts turnaround
   control, and sets a 4-second secondary timer. */

void __cdecl start_ai_vehicle_reverse_turnaround_state(float param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 extraout_ST0;
  float10 fVar4;
  
  iVar1 = get_vehicle_runtime_context((int)param_1);
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  iVar2 = get_ai_vehicle_behavior_state_block((int)param_1);
  iVar1 = get_vehicle_runtime_context((int)param_1);
  *(undefined4 *)(iVar2 + 0x9d20) = *(undefined4 *)(iVar1 + 0xe0);
  apply_world_object_transform_to_bounds_or_geometry
            (*(double *)((int)param_1 + 0x40),*(double *)((int)param_1 + 0x50));
  *(float *)(iVar2 + 0x9d3c) = (float)extraout_ST0;
  iVar1 = iVar2;
  iVar3 = get_vehicle_runtime_context((int)param_1);
  update_ai_vehicle_turnaround_brake_control(param_1,iVar3,iVar1);
  fVar4 = get_runtime_time_seconds();
  *(float *)(iVar2 + 0x9d34) = (float)(fVar4 + (float10)_DAT_004bcb00);
  fVar4 = compute_ai_vehicle_forward_heading_angle((int)param_1);
  *(float *)(iVar2 + 0x9d38) = (float)fVar4;
  return;
}


