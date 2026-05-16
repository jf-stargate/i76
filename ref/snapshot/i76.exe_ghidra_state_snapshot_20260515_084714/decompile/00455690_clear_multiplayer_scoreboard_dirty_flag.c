/*
 * Program: i76.exe
 * Function: clear_multiplayer_scoreboard_dirty_flag
 * Entry: 00455690
 * Signature: undefined __stdcall clear_multiplayer_scoreboard_dirty_flag(void)
 */


/* cgpt rename v2: Clears a scoreboard/UI dirty flag used by scoreboard report and overlay paths. */

void clear_multiplayer_scoreboard_dirty_flag(void)

{
  DAT_005414f8 = 0;
  return;
}


