/*
 * Program: i76.exe
 * Function: is_local_multiplayer_sync_player_current
 * Entry: 00454e40
 * Signature: bool __stdcall is_local_multiplayer_sync_player_current(void)
 */


/* cgpt rename v4: Compares the current multiplayer sync/player id against the local/session player
   id. */

bool is_local_multiplayer_sync_player_current(void)

{
  return DAT_00541064 == DAT_00541028;
}


