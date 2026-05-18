/*
 * Program: i76.exe
 * Function: load_target_reticle_textures
 * Entry: 00459550
 * Signature: undefined __stdcall load_target_reticle_textures(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: references ztarg201/202 maps */

void load_target_reticle_textures(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int local_38;
  int local_34 [13];
  
  _DAT_0054abf0 = 0xc3fa0000;
  DAT_00609504 = 0;
  DAT_00609500 = 0;
  DAT_00609508 = 0;
  DAT_0054a3c8 = 0;
  DAT_0054ab90 = 0;
  DAT_0054a2e4 = 0;
  DAT_004f67ec = 0xffffffff;
  DAT_0054a3c4 = 0xffffffff;
  DAT_0054a414 = 0;
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar6 = &DAT_0054ab98;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar6 = &DAT_0054a3d0;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar6 = &DAT_0054ac30;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar6 = &DAT_0054a340;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,0,0,0,0);
  puVar6 = &DAT_0054a2f0;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  DAT_0054ac64 = 0;
  DAT_004f67f0 = 0xffffffff;
  DAT_0054a3c0 = (undefined4 *)xalloc_global_heap(0x9e);
  *DAT_0054a3c0 = 0x1e;
  DAT_0054a3c0[1] = DAT_0054a3c0[1] & 0xe0000005 | 5;
  if (DAT_0054a3c0 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
    uVar8 = 0;
    iVar4 = 0;
  }
  else {
    puVar1 = DAT_0054a3c0 + 2;
    uVar8 = 5;
    iVar4 = 0x1e;
  }
  puVar1 = (undefined4 *)construct_bitmap_surface_context(local_34,iVar4,uVar8,(int)puVar1,0);
  puVar6 = &DAT_0054a378;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar6 = puVar6 + 1;
  }
  DAT_0054a450 = 0xfe;
  fill_bitmap_surface_context(&DAT_0054a378,0xfe);
  pcVar5 = s_ztarg201_map_004f6528;
  puVar6 = &DAT_0054aad8;
  puVar1 = &DAT_0054a458;
  do {
    local_38 = 4;
    do {
      puVar2 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)pcVar5);
      *puVar6 = puVar2;
      if (puVar2 != (uint *)0x0) {
        puVar3 = (undefined4 *)
                 construct_bitmap_surface_context
                           (local_34,*puVar2,(int)(puVar2[1] << 3) >> 3,(int)(puVar2 + 2),0);
        puVar7 = puVar1;
        for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar7 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar7 = puVar7 + 1;
        }
      }
      pcVar5 = pcVar5 + 0xd;
      puVar6 = puVar6 + 1;
      puVar1 = puVar1 + 0xd;
      local_38 = local_38 + -1;
    } while (local_38 != 0);
  } while ((int)puVar1 < 0x54aad8);
  DAT_0054a40c = 0;
  DAT_0054a2e8 = 0;
  DAT_0054a438 = 0;
  return;
}


