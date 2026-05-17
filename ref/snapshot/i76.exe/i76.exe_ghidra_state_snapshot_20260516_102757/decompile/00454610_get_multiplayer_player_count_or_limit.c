/*
 * Program: i76.exe
 * Function: get_multiplayer_player_count_or_limit
 * Entry: 00454610
 * Signature: undefined4 __stdcall get_multiplayer_player_count_or_limit(void)
 */


/* cgpt rename v2: Returns a multiplayer player count/limit global used by scoreboard and DirectPlay
   message paths. */

undefined4 get_multiplayer_player_count_or_limit(void)

{
  return DAT_00541068;
}


