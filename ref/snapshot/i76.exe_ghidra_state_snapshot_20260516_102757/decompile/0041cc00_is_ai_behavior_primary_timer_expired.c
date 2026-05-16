/*
 * Program: i76.exe
 * Function: is_ai_behavior_primary_timer_expired
 * Entry: 0041cc00
 * Signature: bool __cdecl is_ai_behavior_primary_timer_expired(int param_1)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Returns whether AI behavior timer at state +0xa82c
   has expired. */

bool __cdecl is_ai_behavior_primary_timer_expired(int param_1)

{
  int iVar1;
  float10 fVar2;
  
                    /* I76 semantic baseline: is_ai_behavior_primary_timer_expired
                       Compares gameplay time against AI behavior primary expiry at state+0xa82c. */
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  fVar2 = get_gameplay_runtime_seconds();
  return (float10)*(float *)(iVar1 + 0xa82c) < fVar2;
}


