/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004926f0
 * Entry: 004926f0
 * Signature: uint __cdecl terrain_map_context_helper_004926f0(double param_1, double param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004926f0. Remove
   duplicated terrain wording. */

uint __cdecl terrain_map_context_helper_004926f0(double param_1,double param_2)

{
  int iVar1;
  uint uVar2;
  
  param_1._0_4_ = SUB84((double)(_DAT_006442c4 * (float)param_1 + (float)_DAT_004faf18),0);
  param_2._0_4_ = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  iVar1 = (param_2._0_4_ + 0xc00U & 0xffffff80) + ((int)(param_1._0_4_ + 0xc00U) >> 7);
  uVar2 = (param_2._0_4_ + 0xc00U & 0x7f) * 0x80 + (param_1._0_4_ + 0xc00U & 0x7f);
  if (((iVar1 < 0x4000) && (-1 < iVar1)) && (uVar2 < 0x4000)) {
    return (*(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar1] + uVar2 * 2) & 0x1000) >> 0xc;
  }
  return 0;
}


