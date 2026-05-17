/*
 * Program: i76.exe
 * Function: get_weapon_ammo_fraction_remaining
 * Entry: 004a4bf0
 * Signature: float10 __cdecl get_weapon_ammo_fraction_remaining(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Returns current ammo divided by
   weapon-definition ammo capacity. */

float10 __cdecl get_weapon_ammo_fraction_remaining(int param_1)

{
  if (param_1 * 0x4c == -0x5aab08) {
    return (float10)_DAT_004beab8;
  }
  return (float10)(uint)(&DAT_005aab14)[param_1 * 0x13] /
         (float10)*(int *)(&DAT_005d893c + (&DAT_005aab38)[param_1 * 0x13] * 0xd8);
}


