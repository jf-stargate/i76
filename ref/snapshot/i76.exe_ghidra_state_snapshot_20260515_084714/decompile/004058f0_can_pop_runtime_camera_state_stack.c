/*
 * Program: i76.exe
 * Function: can_pop_runtime_camera_state_stack
 * Entry: 004058f0
 * Signature: undefined4 __stdcall can_pop_runtime_camera_state_stack(void)
 */


/* cgpt readability rename v13 set A: Predicate used before popping runtime camera/view state; also
   checks active-player control-change gating. */

undefined4 can_pop_runtime_camera_state_stack(void)

{
  int iVar1;
  
  if (0 < DAT_004c2988) {
    iVar1 = get_pending_active_player_ai_control_change_flag();
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}


