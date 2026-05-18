/*
 * Program: i76.exe
 * Function: fsm_set_ai_behavior_state_field_9d14
 * Entry: 0040c080
 * Signature: undefined __cdecl fsm_set_ai_behavior_state_field_9d14(int param_1, undefined4 * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: writes script value directly to AI/FSM
   behavior-state field +0x9d14. */

void __cdecl fsm_set_ai_behavior_state_field_9d14(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0x9d14) = *param_2;
  return;
}


