/*
 * Program: i76.exe
 * Function: set_weapon_runtime_state_field_04
 * Entry: 004a4bd0
 * Signature: undefined __cdecl set_weapon_runtime_state_field_04(undefined4 param_1, int param_2, undefined4 param_3)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium] Tiny setter for dword +0x04 in a
   weapon runtime slot record. Kept conservative until field meaning is pinned. */

void __cdecl set_weapon_runtime_state_field_04(undefined4 param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)((&DAT_005aab20)[param_2 * 0x13] + 4) = param_3;
  return;
}


