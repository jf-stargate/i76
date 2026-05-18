/*
 * Program: i76.exe
 * Function: get_pending_active_player_ai_control_change_flag
 * Entry: 0040f890
 * Signature: undefined4 __stdcall get_pending_active_player_ai_control_change_flag(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Returns the pending active player/object AI
   control-change flag. */

undefined4 get_pending_active_player_ai_control_change_flag(void)

{
  return DAT_005244c4;
}


