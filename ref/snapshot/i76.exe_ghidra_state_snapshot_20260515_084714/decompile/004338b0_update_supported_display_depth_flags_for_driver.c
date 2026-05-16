/*
 * Program: i76.exe
 * Function: update_supported_display_depth_flags_for_driver
 * Entry: 004338b0
 * Signature: undefined4 __cdecl update_supported_display_depth_flags_for_driver(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Maps a selected D3D driver's bit-depth caps into per-display-mode supported
   flags. */

undefined4 __cdecl update_supported_display_depth_flags_for_driver(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  uVar1 = (&DAT_005fdf44)[param_1 * 0x4f];
  if (0 < DAT_006080d8) {
    puVar3 = &DAT_006080ec;
    do {
      *puVar3 = 0;
      uVar2 = map_display_bit_depth_to_ddraw_caps_mask(puVar3[-1]);
      if ((uVar1 & uVar2) != 0) {
        *puVar3 = 1;
      }
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 4;
    } while (iVar4 < DAT_006080d8);
  }
  _DAT_0060840c = (&DAT_006080ec)[DAT_006080dc * 4];
  return 1;
}


