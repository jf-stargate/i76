/*
 * Program: i76.exe
 * Function: preload_smoke_animation_textures
 * Entry: 00441150
 * Signature: undefined __stdcall preload_smoke_animation_textures(void)
 */


/* i76 second-pass rename
   old_name: FUN_00441150
   suggested_name: preload_smoke_animation_textures
   basis: References smoke animation texture maps and missing animation diagnostic. */

void preload_smoke_animation_textures(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  DAT_0052ba34 = 0;
  iVar4 = 0;
  puVar2 = &DAT_0052b960;
  for (iVar3 = 0x30; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  do {
    puVar1 = load_texture_resource_resolving_vqm_cbk_to_cache
                       (*(byte **)((int)&PTR_s_xwp1_101_map_004f1668 + iVar4));
    if (puVar1 == (uint *)0x0) {
      report_error();
      return;
    }
    *(uint **)((int)&DAT_0052b960 + iVar4) = puVar1;
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0xc0);
  DAT_0052ba30 = 0;
  DAT_0052ba20 = 0;
  DAT_0052ba28 = (undefined4 *)0x0;
  puVar2 = (undefined4 *)xalloc_global_heap(0x4800);
  iVar3 = 0x100;
  DAT_0052ba2c = puVar2;
  do {
    if (puVar2 != (undefined4 *)0x0) {
      puVar5 = puVar2;
      for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      puVar2[1] = 0x13;
      puVar2[0x10] = DAT_0052ba28;
      DAT_0052ba28 = puVar2;
    }
    puVar2 = puVar2 + 0x12;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DAT_0052ba24 = 0;
  DAT_0052b950 = 0;
  DAT_0052b958 = (undefined4 *)0x0;
  puVar2 = (undefined4 *)xalloc_global_heap(0x1200);
  iVar3 = 0x80;
  DAT_0052b954 = puVar2;
  do {
    if (puVar2 != (undefined4 *)0x0) {
      puVar5 = puVar2;
      for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      puVar2[7] = DAT_0052b958;
      DAT_0052b958 = puVar2;
    }
    puVar2 = puVar2 + 9;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DAT_0052ba34 = 1;
  return;
}


