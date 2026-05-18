/*
 * Program: i76.exe
 * Function: vec3_interpolate_context_helper_004795a0
 * Entry: 004795a0
 * Signature: undefined __cdecl vec3_interpolate_context_helper_004795a0(undefined4 * param_1)
 */


/* cgpt readability rename set D v16: Readability pass set D: vec3 interpolate context helper based
   on adjacent named subsystem context. */

void __cdecl vec3_interpolate_context_helper_004795a0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  bool bVar3;
  
  bVar3 = g_palette_cube_distance_table == (undefined *)0x0;
  puVar2 = &g_palette_cube_sample_points;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  if (bVar3) {
    g_palette_cube_distance_table = &DAT_0059b788;
    iVar1 = -0x100;
    do {
      *(int *)(g_palette_cube_distance_table + iVar1 * 4) = iVar1 * iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x100);
  }
  puVar2 = &g_palette_cube_nearest_index_cache;
  for (iVar1 = 0x2000; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  return;
}


