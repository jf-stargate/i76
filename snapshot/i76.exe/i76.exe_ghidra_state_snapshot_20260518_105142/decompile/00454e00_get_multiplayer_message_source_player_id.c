/*
 * Program: i76.exe
 * Function: get_multiplayer_message_source_player_id
 * Entry: 00454e00
 * Signature: undefined2 __stdcall get_multiplayer_message_source_player_id(void)
 */


/* cgpt rename v2: Returns a multiplayer message/source player id used by DirectPlay message
   handling and anti-cheat kick paths. */

undefined2 get_multiplayer_message_source_player_id(void)

{
  return DAT_00541064;
}


