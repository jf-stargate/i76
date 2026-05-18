/*
 * Program: i76.exe
 * Function: is_active_player_object_control_change_allowed
 * Entry: 0040f8a0
 * Signature: bool __cdecl is_active_player_object_control_change_allowed(int param_1)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Returns whether the active player/camera object can
   trigger a control-change event this frame. */

bool __cdecl is_active_player_object_control_change_allowed(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = is_damage_side_effects_suppressed();
  if (iVar1 == 0) {
    piVar2 = (int *)get_active_player_or_camera_world_object_entry();
    if ((piVar2 != (int *)0x0) && (param_1 == *piVar2)) {
      return DAT_005244c0 == 0;
    }
  }
  return false;
}


