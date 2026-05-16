/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00495000
 * Entry: 00495000
 * Signature: float10 __cdecl zone_satellite_map_context_helper_00495000(undefined4 param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00495000. Remove
   duplicated zone_satellite_map wording. */

float10 __cdecl zone_satellite_map_context_helper_00495000(undefined4 param_1,uint param_2)

{
  uint uVar1;
  float10 fVar2;
  
  uVar1 = (0xbfc - (param_2 >> 0x14) >> 1) << 0x14 |
          (uint)(byte)(&DAT_00655180)[param_2 >> 0xd & 0xff] << 0xc;
  fVar2 = (float10)(double)((ulonglong)uVar1 << 0x20);
  return ((float10)_DAT_004faf20 - fVar2 * fVar2 * (float10)(double)CONCAT44(param_2,param_1)) *
         (float10)(double)((ulonglong)uVar1 << 0x20) * (float10)_DAT_004faf28 *
         (float10)_DAT_004faf30;
}


