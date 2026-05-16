/*
 * Program: i76.exe
 * Function: set_ai_behavior_target_object
 * Entry: 0041e660
 * Signature: undefined __cdecl set_ai_behavior_target_object(int param_1, undefined4 param_2)
 */


/* cgpt rename v6 ai vehicle behavior cluster: Stores a target object/id into the AI behavior state
   block at +0xa998. */

void __cdecl set_ai_behavior_target_object(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = get_ai_vehicle_behavior_state_block(param_1);
  *(undefined4 *)(iVar1 + 0xa998) = param_2;
  return;
}


