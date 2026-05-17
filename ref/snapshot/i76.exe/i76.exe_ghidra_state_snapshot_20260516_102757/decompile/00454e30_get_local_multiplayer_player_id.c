/*
 * Program: i76.exe
 * Function: get_local_multiplayer_player_id
 * Entry: 00454e30
 * Signature: undefined2 __stdcall get_local_multiplayer_player_id(void)
 */


/* cgpt rename v2: Returns the local multiplayer player id used by scoreboard, respawn,
   kill-message, and vehicle update paths. */

undefined2 get_local_multiplayer_player_id(void)

{
  return DAT_00541028;
}


