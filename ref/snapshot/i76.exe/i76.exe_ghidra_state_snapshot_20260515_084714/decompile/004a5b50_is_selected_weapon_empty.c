/*
 * Program: i76.exe
 * Function: is_selected_weapon_empty
 * Entry: 004a5b50
 * Signature: undefined4 __cdecl is_selected_weapon_empty(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Returns true when the selected
   weapon has no remaining ammo/fraction. */

undefined4 __cdecl is_selected_weapon_empty(int param_1)

{
  int iVar1;
  float fVar2;
  
  if ((*(int *)(param_1 + 4) != -1) &&
     (iVar1 = *(int *)(param_1 + 0xa8 + *(int *)(param_1 + 4) * 0x58), iVar1 != -1)) {
    fVar2 = _DAT_004beab8;
    if (iVar1 * 0x4c != -0x5aab08) {
      fVar2 = (float)(uint)(&DAT_005aab14)[iVar1 * 0x13] /
              (float)*(int *)(&DAT_005d893c + (&DAT_005aab38)[iVar1 * 0x13] * 0xd8);
    }
    if (fVar2 == _DAT_004beab8) {
      return 1;
    }
  }
  return 0;
}


