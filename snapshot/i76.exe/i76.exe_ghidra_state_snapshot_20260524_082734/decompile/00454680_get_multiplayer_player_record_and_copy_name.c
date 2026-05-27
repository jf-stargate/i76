/*
 * Program: i76.exe
 * Function: get_multiplayer_player_record_and_copy_name
 * Entry: 00454680
 * Signature: undefined2 __cdecl get_multiplayer_player_record_and_copy_name(int param_1, uchar * param_2)
 */


/* cgpt rename v4: Looks up a multiplayer player slot, optionally copies its player name, and
   returns the slot/player id. */

undefined2 __cdecl get_multiplayer_player_record_and_copy_name(int param_1,uchar *param_2)

{
  if ((&DAT_00541070)[param_1 * 0x24] == 0) {
    return 0;
  }
  if (param_2 != (uchar *)0x0) {
    _mbsnbcpy(param_2,&DAT_00541072 + param_1 * 0x48,0x18);
  }
  return (&DAT_00541070)[param_1 * 0x24];
}


