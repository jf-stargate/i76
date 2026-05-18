/*
 * Program: i76.exe
 * Function: cache_nearest_palette_cube_index
 * Entry: 004796a0
 * Signature: undefined __cdecl cache_nearest_palette_cube_index(int param_1, int param_2, int param_3)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Maps GEO section RGB bytes
   to nearest game palette index used as a runtime section color/material field. */

void __cdecl cache_nearest_palette_cube_index(int param_1,int param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  byte *pbVar3;
  char cVar4;
  int iVar5;
  char local_4;
  
  pcVar1 = (char *)((int)&g_palette_cube_nearest_index_cache +
                   (param_3 >> 3) + ((param_1 >> 3) * 0x20 + (param_2 >> 3)) * 0x20);
  if (*pcVar1 == -1) {
    iVar5 = 0x7fffffff;
    cVar4 = '\0';
    pbVar3 = (byte *)&g_palette_cube_sample_points;
    do {
      iVar2 = *(int *)(g_palette_cube_distance_table + (param_3 - (uint)pbVar3[2]) * 4) +
              *(int *)(g_palette_cube_distance_table + (param_2 - (uint)pbVar3[1]) * 4) +
              *(int *)(g_palette_cube_distance_table + (param_1 - (uint)*pbVar3) * 4);
      if (iVar2 < iVar5) {
        iVar5 = iVar2;
        local_4 = cVar4;
      }
      pbVar3 = pbVar3 + 3;
      cVar4 = cVar4 + '\x01';
    } while ((int)pbVar3 < 0x6435dd);
    *pcVar1 = local_4;
  }
  return;
}


