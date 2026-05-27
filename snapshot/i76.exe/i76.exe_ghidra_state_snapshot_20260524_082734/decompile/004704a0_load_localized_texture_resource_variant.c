/*
 * Program: i76.exe
 * Function: load_localized_texture_resource_variant
 * Entry: 004704a0
 * Signature: undefined __cdecl load_localized_texture_resource_variant(byte * param_1, int param_2, size_t param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe image payload renames v28; confidence=medium] Loads a localized/resource variant of
   a texture/image resource. */

void __cdecl load_localized_texture_resource_variant(byte *param_1,int param_2,size_t param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  
  uVar2 = (&DAT_004f8aaf)[_g_display_mode_variant_index & 0xff];
  if (param_1 == (byte *)0x0) {
    pbVar3 = (byte *)0x0;
    goto LAB_0047055f;
  }
  if (param_2 == 0) {
    strncpy((char *)&g_localized_texture_variant_name_scratch,(char *)param_1,param_3);
    uVar4 = 0xffffffff;
    *(undefined1 *)((int)&g_localized_texture_variant_name_scratch + param_3) = uVar2;
    pbVar3 = param_1 + param_3;
    do {
      pbVar6 = pbVar3;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pbVar6 = pbVar3 + 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar6;
    } while (bVar1 != 0);
    uVar4 = ~uVar4;
    pbVar3 = pbVar6 + -uVar4;
    pbVar6 = (byte *)((int)&g_localized_texture_variant_name_scratch + param_3 + 1);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pbVar6 = *(undefined4 *)pbVar3;
      pbVar3 = pbVar3 + 4;
      pbVar6 = pbVar6 + 4;
    }
LAB_00470555:
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar6 = *pbVar3;
      pbVar3 = pbVar3 + 1;
      pbVar6 = pbVar6 + 1;
    }
  }
  else {
    if (param_2 != 1) {
      uVar4 = 0xffffffff;
      pbVar3 = param_1;
      do {
        pbVar6 = pbVar3;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pbVar6 = pbVar3 + 1;
        bVar1 = *pbVar3;
        pbVar3 = pbVar6;
      } while (bVar1 != 0);
      uVar4 = ~uVar4;
      pbVar3 = pbVar6 + -uVar4;
      pbVar6 = (byte *)&g_localized_texture_variant_name_scratch;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pbVar6 = *(undefined4 *)pbVar3;
        pbVar3 = pbVar3 + 4;
        pbVar6 = pbVar6 + 4;
      }
      goto LAB_00470555;
    }
    uVar4 = 0xffffffff;
    pbVar3 = param_1;
    do {
      pbVar6 = pbVar3;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pbVar6 = pbVar3 + 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar6;
    } while (bVar1 != 0);
    uVar4 = ~uVar4;
    pbVar3 = pbVar6 + -uVar4;
    pbVar6 = (byte *)&g_localized_texture_variant_name_scratch;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pbVar6 = *(undefined4 *)pbVar3;
      pbVar3 = pbVar3 + 4;
      pbVar6 = pbVar6 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pbVar6 = *pbVar3;
      pbVar3 = pbVar3 + 1;
      pbVar6 = pbVar6 + 1;
    }
    *(undefined1 *)((int)&g_localized_texture_variant_name_scratch + param_3) = uVar2;
  }
  pbVar3 = (byte *)&g_localized_texture_variant_name_scratch;
LAB_0047055f:
  if (pbVar3 == (byte *)0x0) {
    load_texture_resource_resolving_vqm_cbk_to_cache(param_1);
    return;
  }
  load_texture_resource_resolving_vqm_cbk_to_cache(pbVar3);
  return;
}


