/*
 * Program: i76.exe
 * Function: fsm_set_ai_behavior_state_field_a948
 * Entry: 0040c0a0
 * Signature: undefined __cdecl fsm_set_ai_behavior_state_field_a948(int param_1, undefined4 * param_2)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: writes script value directly to AI/FSM
   behavior-state field +0xa948. */

void __cdecl fsm_set_ai_behavior_state_field_a948(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0xa948) = *param_2;
  return;
}


