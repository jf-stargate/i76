/*
 * Program: i76.exe
 * Function: mark_active_player_object_control_changed
 * Entry: 0040f8d0
 * Signature: undefined __cdecl mark_active_player_object_control_changed(int param_1)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Marks the tracked active player/camera object as
   having changed control state this frame. */

void __cdecl mark_active_player_object_control_changed(int param_1)

{
  if (param_1 == DAT_005244c8) {
    DAT_005244c4 = 1;
  }
  return;
}


