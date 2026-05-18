/*
 * Program: i76.exe
 * Function: multiplayer_game_state_context_helper_00452db0
 * Entry: 00452db0
 * Signature: undefined __cdecl multiplayer_game_state_context_helper_00452db0(uint * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: multiplayer game state context helper
   based on prior focused closure context. */

void __cdecl multiplayer_game_state_context_helper_00452db0(uint *param_1)

{
  _DAT_00540ff4 = param_1[0x24];
  DAT_00540ff8 = param_1[0x25];
  DAT_00541018 = *param_1 >> 2 & 1;
  DAT_00541010 = *param_1 >> 3 & 1;
  return;
}


