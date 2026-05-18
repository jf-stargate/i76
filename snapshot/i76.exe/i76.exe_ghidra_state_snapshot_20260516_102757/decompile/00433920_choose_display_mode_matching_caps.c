/*
 * Program: i76.exe
 * Function: choose_display_mode_matching_caps
 * Entry: 00433920
 * Signature: undefined4 __cdecl choose_display_mode_matching_caps(int * param_1, uint param_2)
 */


/* cgpt rename v3: Finds the first display mode matching a capability mask, preferring 640x480x16
   when available. */

undefined4 __cdecl choose_display_mode_matching_caps(int *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int local_4;
  
  iVar2 = 0;
  if (0 < DAT_006080d8) {
    puVar4 = &DAT_006080e8;
    do {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask(*puVar4);
      if ((param_2 & uVar1) != 0) break;
      iVar2 = iVar2 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar2 < DAT_006080d8);
  }
  local_4 = iVar2;
  if (iVar2 < DAT_006080d8) {
    piVar5 = &DAT_006080e8 + iVar2 * 4;
    iVar3 = iVar2;
    do {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask(*piVar5);
      if (((((param_2 & uVar1) != 0) && (piVar5[-2] == 0x280)) && (piVar5[-1] == 0x1e0)) &&
         (local_4 = iVar3, *piVar5 == 0x10)) break;
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 4;
      local_4 = iVar2;
    } while (iVar3 < DAT_006080d8);
  }
  if (local_4 < DAT_006080d8) {
    *param_1 = local_4;
    return 1;
  }
  *param_1 = -100;
  return 1;
}


