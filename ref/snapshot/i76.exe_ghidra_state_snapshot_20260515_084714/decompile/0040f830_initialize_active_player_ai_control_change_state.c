/*
 * Program: i76.exe
 * Function: initialize_active_player_ai_control_change_state
 * Entry: 0040f830
 * Signature: undefined __stdcall initialize_active_player_ai_control_change_state(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Initializes per-frame active player/object AI
   control-change tracking globals. */

void initialize_active_player_ai_control_change_state(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)get_active_player_or_camera_world_object_entry();
  if (puVar1 != (undefined4 *)0x0) {
    DAT_005244c4 = 0;
    DAT_005244c8 = *puVar1;
    DAT_005244c0 = 0;
    return;
  }
  DAT_005244c8 = 0;
  DAT_005244c4 = 0;
  DAT_005244c0 = 0;
  return;
}


