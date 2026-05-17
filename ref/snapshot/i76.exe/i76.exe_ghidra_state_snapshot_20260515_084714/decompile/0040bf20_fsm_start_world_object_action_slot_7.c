/*
 * Program: i76.exe
 * Function: fsm_start_world_object_action_slot_7
 * Entry: 0040bf20
 * Signature: undefined4 __cdecl fsm_start_world_object_action_slot_7(int param_1)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM action/predicate: resolves object action
   slot/type 7 and starts it when present. */

undefined4 __cdecl fsm_start_world_object_action_slot_7(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = target_reticle_context_helper_00458f40(param_1,7);
    if (iVar1 != 0) {
      world_object_texture_animation_state_getter_0046d740(iVar1);
      return 1;
    }
  }
  return 0;
}


