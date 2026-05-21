/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493c50
 * Entry: 00493c50
 * Signature: undefined __stdcall zone_satellite_map_context_helper_00493c50(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493c50. Remove
   duplicated zone_satellite_map wording. */

void zone_satellite_map_context_helper_00493c50(void)

{
  uint uVar1;
  int iStack_4;
  
  uVar1 = 0;
  do {
    iStack_4 = (int)((ulonglong)
                     (_DAT_004be8c0 / SQRT((double)((ulonglong)((uVar1 | 0x1ff00) << 0xd) << 0x20)))
                    >> 0x20);
    (&DAT_00655180)[uVar1] = (char)(iStack_4 + 0x400 >> 0xc);
    uVar1 = uVar1 + 1;
  } while ((int)uVar1 < 0x100);
  DAT_00655200 = 0xff;
  return;
}


