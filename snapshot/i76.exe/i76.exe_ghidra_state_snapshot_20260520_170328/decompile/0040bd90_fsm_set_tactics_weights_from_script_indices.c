/*
 * Program: i76.exe
 * Function: fsm_set_tactics_weights_from_script_indices
 * Entry: 0040bd90
 * Signature: undefined __cdecl fsm_set_tactics_weights_from_script_indices(int param_1, int * param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action: maps two script indices into four AI/FSM
   tactic weight fields +0xa81c..+0xa828. */

void __cdecl fsm_set_tactics_weights_from_script_indices(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar1 = get_vehicle_damage_event_state_block(iVar1);
  *(undefined4 *)(iVar1 + 0xa820) = *(undefined4 *)(&DAT_005fcb7c + *param_2 * 4);
  *(undefined4 *)(iVar1 + 0xa81c) = *(undefined4 *)(&DAT_005fcb9c + *param_2 * 4);
  *(undefined4 *)(iVar1 + 0xa824) = *(undefined4 *)(&DAT_005fcbdc + *param_3 * 4);
  *(undefined4 *)(iVar1 + 0xa828) = *(undefined4 *)(&DAT_005fcbbc + *param_3 * 4);
  return;
}


