/*
 * Program: i76.exe
 * Function: set_weapon_runtime_fire_request_flag
 * Entry: 004a3560
 * Signature: undefined4 __cdecl set_weapon_runtime_fire_request_flag(int param_1, undefined4 param_2)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Writes the weapon runtime
   fire-request/armed flag in a weapon slot record. */

undefined4 __cdecl set_weapon_runtime_fire_request_flag(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_005aab44 + param_1 * 0x4c) = param_2;
  return 1;
}


