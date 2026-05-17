/*
 * Program: i76.exe
 * Function: is_ai_behavior_secondary_timer_expired
 * Entry: 0041cc40
 * Signature: bool __cdecl is_ai_behavior_secondary_timer_expired(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Returns whether AI behavior timer at state +0x9d34
   has expired. */

bool __cdecl is_ai_behavior_secondary_timer_expired(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  fVar2 = get_runtime_time_seconds();
  return (float10)*(float *)(iVar1 + 0x9d34) < fVar2;
}


