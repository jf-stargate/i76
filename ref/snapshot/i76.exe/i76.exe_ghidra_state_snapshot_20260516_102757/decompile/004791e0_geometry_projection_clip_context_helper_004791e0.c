/*
 * Program: i76.exe
 * Function: geometry_projection_clip_context_helper_004791e0
 * Entry: 004791e0
 * Signature: undefined __cdecl geometry_projection_clip_context_helper_004791e0(int param_1, undefined4 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: geometry projection clip context
   helper based on adjacent named subsystem context. */

void __cdecl geometry_projection_clip_context_helper_004791e0(int param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  bool bVar10;
  uint local_18;
  
  bVar10 = g_palette_cube_distance_table == (undefined *)0x0;
  puVar8 = (undefined4 *)(param_1 + 0xe8);
  puVar9 = &g_palette_cube_sample_points;
  for (iVar5 = 0xc0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  if (bVar10) {
    g_palette_cube_distance_table = &DAT_0059b788;
    iVar5 = -0x100;
    do {
      *(int *)(g_palette_cube_distance_table + iVar5 * 4) = iVar5 * iVar5;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x100);
  }
  puVar8 = &g_palette_cube_nearest_index_cache;
  for (iVar5 = 0x2000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0xffffffff;
    puVar8 = puVar8 + 1;
  }
  if (param_2 == (undefined4 *)0x0) {
    local_18 = 0;
    do {
      iVar5 = 0x18;
      puVar6 = &DAT_0061d1a0 + local_18;
      puVar7 = puVar6;
      do {
        iVar2 = ftol();
        iVar3 = ftol();
        iVar4 = ftol();
        if (iVar2 < 0) {
          iVar2 = 0;
        }
        else if (0xff < iVar2) {
          iVar2 = 0xff;
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else if (0xff < iVar3) {
          iVar3 = 0xff;
        }
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        else if (0xff < iVar4) {
          iVar4 = 0xff;
        }
        uVar1 = cache_nearest_palette_cube_index(iVar2,iVar3,iVar4);
        *puVar7 = uVar1;
        puVar7 = puVar7 + -0x100;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar5 = 8;
      puVar7 = &DAT_0061b9a0 + local_18;
      do {
        iVar2 = ftol();
        iVar3 = ftol();
        iVar4 = ftol();
        if (iVar2 < 0) {
          iVar2 = 0;
        }
        else if (0xff < iVar2) {
          iVar2 = 0xff;
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else if (0xff < iVar3) {
          iVar3 = 0xff;
        }
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        else if (0xff < iVar4) {
          iVar4 = 0xff;
        }
        uVar1 = cache_nearest_palette_cube_index(iVar2,iVar3,iVar4);
        *puVar7 = uVar1;
        puVar7 = puVar7 + -0x100;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar5 = 0x70;
      uVar1 = *puVar6;
      do {
        puVar6 = puVar6 + 0x100;
        *puVar6 = uVar1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      puVar6 = &DAT_0062b1a0 + local_18;
      uVar1 = (&DAT_0061b2a0)[local_18];
      iVar5 = 0x70;
      do {
        *puVar6 = uVar1;
        puVar6 = puVar6 + -0x100;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      local_18 = local_18 + 1;
    } while (local_18 < 0x100);
    return;
  }
  puVar8 = (undefined4 *)&DAT_0061b2a0;
  for (iVar5 = 0x4000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *param_2;
    param_2 = param_2 + 1;
    puVar8 = puVar8 + 1;
  }
  return;
}


