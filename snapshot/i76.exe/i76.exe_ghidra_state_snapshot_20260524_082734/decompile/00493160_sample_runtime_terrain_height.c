/*
 * Program: i76.exe
 * Function: sample_runtime_terrain_height
 * Entry: 00493160
 * Signature: ushort __cdecl sample_runtime_terrain_height(int param_1, int param_2)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00493160. Remove
   duplicated terrain wording.
   
   I76 rename v43: sample_runtime_terrain_height
   Samples terrain height through runtime page grid and TER page data. */

ushort __cdecl sample_runtime_terrain_height(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = (param_2 + 0xc00U & 0xffffff80) + ((int)(param_1 + 0xc00U) >> 7);
  uVar2 = (param_2 + 0xc00U & 0x7f) * 0x80 + (param_1 + 0xc00U & 0x7f);
  if ((iVar1 < 0x4000) && (uVar2 < 0x4000)) {
    return *(ushort *)((&g_runtime_terrain_page_pointer_grid)[iVar1] + uVar2 * 2) & 0xfff;
  }
  return 0;
}


