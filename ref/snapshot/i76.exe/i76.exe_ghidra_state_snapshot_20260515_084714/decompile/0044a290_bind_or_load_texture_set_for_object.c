/*
 * Program: i76.exe
 * Function: bind_or_load_texture_set_for_object
 * Entry: 0044a290
 * Signature: uint __cdecl bind_or_load_texture_set_for_object(uint param_1, byte * param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Binds or loads a texture set for
   an object/texture-slot name during render submission. */

uint __cdecl bind_or_load_texture_set_for_object(uint param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint *puVar7;
  uint *puVar8;
  byte *pbVar9;
  byte *pbVar10;
  
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == (byte *)0x0) {
    return 0;
  }
  uVar4 = 0;
  bVar2 = *param_2;
  pbVar9 = param_2;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar10 = pbVar9 + 1;
    pbVar9 = pbVar9 + 1;
    bVar2 = *pbVar10;
  }
  puVar7 = (uint *)(&g_texture_slot_binding_hash)[((uVar4 ^ param_1) * 0x6cd + 0xaab) % 0x7ed];
  while ((puVar7 != (uint *)0x0 &&
         ((*puVar7 != param_1 ||
          (iVar5 = _stricmp((char *)(puVar7 + 5),(char *)param_2), iVar5 != 0))))) {
    puVar7 = (uint *)puVar7[0x10];
  }
  if (puVar7 != (uint *)0x0) goto LAB_0044a5d7;
  uVar4 = 0;
  bVar2 = *param_2;
  pbVar9 = param_2;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar10 = pbVar9 + 1;
    pbVar9 = pbVar9 + 1;
    bVar2 = *pbVar10;
  }
  pcVar6 = (char *)(&g_texture_set_cache_hash)[(uVar4 * 0x6cd + 0xaab) % 0x7ed];
  if (pcVar6 == (char *)0x0) {
LAB_0044a37b:
    pcVar6 = strchr((char *)param_2,0x2e);
    if (pcVar6 == (char *)0x0) {
      iVar5 = 0;
    }
    else {
      iVar5 = _stricmp(pcVar6,(char *)&DAT_004f25e8);
    }
    if (iVar5 == 0) {
      pbVar9 = HeapAlloc(g_texture_set_cache_heap,0,0x34);
      bVar3 = false;
      if (pbVar9 != (byte *)0x0) {
        strncpy((char *)pbVar9,(char *)param_2,0xf);
        pbVar9[0x10] = 1;
        pbVar9[0x11] = 0;
        pbVar9[0x12] = 0;
        pbVar9[0x13] = 0;
        pbVar9[0x1c] = 1;
        pbVar9[0x1d] = 0;
        pbVar9[0x1e] = 0;
        pbVar9[0x1f] = 0;
        pbVar9[0x20] = 1;
        pbVar9[0x21] = 0;
        pbVar9[0x22] = 0;
        pbVar9[0x23] = 0;
        pcVar6 = HeapAlloc(g_texture_name_array_heap,0,0x10);
        *(char **)(pbVar9 + 0x2c) = pcVar6;
        strncpy(pcVar6,(char *)param_2,0xf);
        uVar4 = 0;
        bVar2 = *pbVar9;
        pbVar10 = pbVar9;
        while (bVar2 != 0) {
          uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
          pbVar1 = pbVar10 + 1;
          pbVar10 = pbVar10 + 1;
          bVar2 = *pbVar1;
        }
        uVar4 = (uVar4 * 0x6cd + 0xaab) % 0x7ed;
        *(undefined4 *)(pbVar9 + 0x30) = (&g_texture_set_cache_hash)[uVar4];
        (&g_texture_set_cache_hash)[uVar4] = pbVar9;
        bVar3 = true;
      }
    }
    else {
      puVar7 = open_resource_file_into_memory((char *)param_2);
      bVar3 = false;
      if (puVar7 != (uint *)0x0) {
        puVar8 = puVar7 + 1;
        strncpy((char *)puVar8,(char *)param_2,0xf);
        pcVar6 = HeapAlloc(g_texture_set_cache_heap,0,0x34);
        bVar3 = false;
        if (pcVar6 != (char *)0x0) {
          strncpy(pcVar6,(char *)puVar8,0xf);
          pcVar6[0x10] = '\x01';
          pcVar6[0x11] = '\0';
          pcVar6[0x12] = '\0';
          pcVar6[0x13] = '\0';
          iVar5 = decode_tmt_texture_set_header_into_record((int)puVar7,(int)pcVar6);
          if (iVar5 == 0) {
            bVar3 = false;
          }
          else {
            uVar4 = 0;
            bVar2 = (byte)*puVar8;
            while (bVar2 != 0) {
              uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
              pbVar9 = (byte *)((int)puVar8 + 1);
              puVar8 = (uint *)((int)puVar8 + 1);
              bVar2 = *pbVar9;
            }
            uVar4 = (uVar4 * 0x6cd + 0xaab) % 0x7ed;
            *(undefined4 *)(pcVar6 + 0x30) = (&g_texture_set_cache_hash)[uVar4];
            (&g_texture_set_cache_hash)[uVar4] = pcVar6;
            bVar3 = true;
          }
        }
        release_resource_file_reference((char *)param_2);
      }
    }
    if (bVar3) {
      uVar4 = 0;
      bVar2 = *param_2;
      pbVar9 = param_2;
      while (bVar2 != 0) {
        uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
        pbVar10 = pbVar9 + 1;
        pbVar9 = pbVar9 + 1;
        bVar2 = *pbVar10;
      }
      pcVar6 = (char *)(&g_texture_set_cache_hash)[(uVar4 * 0x6cd + 0xaab) % 0x7ed];
      if (pcVar6 == (char *)0x0) {
        return 0;
      }
      do {
        iVar5 = _stricmp(pcVar6,(char *)param_2);
        if (iVar5 == 0) break;
        pcVar6 = *(char **)(pcVar6 + 0x30);
      } while (pcVar6 != (char *)0x0);
    }
    else {
      pcVar6 = (char *)0x0;
    }
  }
  else {
    do {
      iVar5 = _stricmp(pcVar6,(char *)param_2);
      if (iVar5 == 0) break;
      pcVar6 = *(char **)(pcVar6 + 0x30);
    } while (pcVar6 != (char *)0x0);
    if (pcVar6 == (char *)0x0) goto LAB_0044a37b;
    *(int *)(pcVar6 + 0x10) = *(int *)(pcVar6 + 0x10) + 1;
  }
  if ((pcVar6 == (char *)0x0) ||
     (puVar7 = create_texture_slot_binding_for_object(param_1,param_2,param_2,(uint)pcVar6),
     puVar7 == (uint *)0x0)) {
    return 0;
  }
  if ((*(uint *)(pcVar6 + 0x18) & 1) != 0) {
    if ((*(uint *)(pcVar6 + 0x18) & 2) == 0) {
      install_texture_animation_linear_timer
                (param_1,param_2,_DAT_004bd3bc / *(float *)(pcVar6 + 0x14),0.0,
                 *(float *)(pcVar6 + 0x20),6.307143e-39);
    }
    else {
      install_texture_animation_pingpong_timer
                (param_1,param_2,_DAT_004bd3bc / *(float *)(pcVar6 + 0x14),0.0,
                 *(float *)(pcVar6 + 0x20),1);
    }
  }
LAB_0044a5d7:
  if ((param_3 != 0) && (*(int *)(*(int *)(param_3 + 0x3c) + 8) == 1)) {
    iVar5 = ensure_m16_resource_loaded_and_mark_fullres((int *)(puVar7 + 0xe),(char *)(puVar7 + 1));
    if (iVar5 != 0) {
      return puVar7[0xe];
    }
  }
  if ((puVar7[0xf] & 2) != 0) {
    puVar8 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)(puVar7 + 1));
    puVar7[0xd] = (uint)puVar8;
    puVar7[0xf] = puVar7[0xf] & 0xfffffffd;
  }
  return puVar7[0xd];
}


