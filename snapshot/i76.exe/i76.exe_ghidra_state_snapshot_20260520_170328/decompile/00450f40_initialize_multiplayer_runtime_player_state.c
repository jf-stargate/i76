/*
 * Program: i76.exe
 * Function: initialize_multiplayer_runtime_player_state
 * Entry: 00450f40
 * Signature: undefined __stdcall initialize_multiplayer_runtime_player_state(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Pre-runtime multiplayer/trip
   setup. Clears player/session runtime buffers and registers camera/world-object callbacks. */

void initialize_multiplayer_runtime_player_state(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0053fcb0;
  for (iVar1 = 0x32; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_odef_spawn_transform_count = 0;
  g_odef_regen_transform_count = 0;
  DAT_00540d8c = 0;
  DAT_0053fd78 = 0;
  entity_instance_id_allocate_context_helper_00457270(fsm_camera_stack_operation);
  register_world_object_tree_callback(multiplayer_network_scoreboard_table_helper_00451a70);
  return;
}


