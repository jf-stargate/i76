/*
 * Program: i76.exe
 * Function: is_ai_target_blocked_or_not_in_state_range
 * Entry: 0041eea0
 * Signature: undefined4 __cdecl is_ai_target_blocked_or_not_in_state_range(int param_1, int param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Combines vehicle state range predicate with another
   paired-object predicate to reject blocked targets. */

undefined4 __cdecl is_ai_target_blocked_or_not_in_state_range(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = is_ai_target_not_in_vehicle_state_range_2_to_4(param_1,param_2);
  if ((iVar1 == 0) &&
     (iVar1 = is_ai_target_projected_to_same_route_segment(param_1,param_2), iVar1 != 0)) {
    return 0;
  }
  return 1;
}


