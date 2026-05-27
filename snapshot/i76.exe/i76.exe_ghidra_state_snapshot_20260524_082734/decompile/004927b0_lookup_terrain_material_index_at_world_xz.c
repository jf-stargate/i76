/*
 * Program: i76.exe
 * Function: lookup_terrain_material_index_at_world_xz
 * Entry: 004927b0
 * Signature: ushort __cdecl lookup_terrain_material_index_at_world_xz(double param_1, double param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Maps world X/Z coordinates
   into the terrain material map and returns the upper material-index bits from the terrain cell.
   
   I76 rename v43: lookup_runtime_terrain_surface_class
   Terrain surface-class lookup using packed TER word bits. */

ushort __cdecl lookup_terrain_material_index_at_world_xz(double param_1,double param_2)

{
  int iVar1;
  uint uVar2;
  uint local_10;
  uint local_8;
  
                    /* I76 semantic baseline: lookup_terrain_material_index_at_world_xz
                       Looks up terrain material index at world X/Z. */
  local_10 = SUB84((double)(_DAT_006442c4 * (float)param_1 + (float)_DAT_004faf18),0);
  local_8 = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  if (((0x2800 - local_10 | 0x2800 - local_8 | local_8 | local_10) & 0x80000000) != 0) {
    return 5;
  }
  param_1._0_4_ = SUB84((double)(_DAT_006442c4 * (float)param_1 + (float)_DAT_004faf18),0);
  param_2._0_4_ = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  iVar1 = (param_2._0_4_ + 0xc00U & 0xffffff80) + ((int)(param_1._0_4_ + 0xc00U) >> 7);
  uVar2 = (param_2._0_4_ + 0xc00U & 0x7f) * 0x80 + (param_1._0_4_ + 0xc00U & 0x7f);
  if (((iVar1 < 0x4000) && (-1 < iVar1)) && (uVar2 < 0x4000)) {
    return *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar1] + uVar2 * 2) >> 0xd;
  }
  return 0;
}


