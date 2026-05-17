/*
 * Program: i76.exe
 * Function: commit_active_player_ai_control_change_state
 * Entry: 0040f870
 * Signature: undefined __stdcall commit_active_player_ai_control_change_state(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Commits the pending active player/object AI
   control-change flag into the previous-frame flag. */

void commit_active_player_ai_control_change_state(void)

{
  DAT_005244c0 = DAT_005244c4;
  DAT_005244c4 = 0;
  return;
}


