/*
 * Program: i76.exe
 * Function: bind_texture_resource_to_object_slot
 * Entry: 00449680
 * Signature: undefined4 __cdecl bind_texture_resource_to_object_slot(uint param_1, byte * param_2, byte * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Creates/binds an object
   texture-slot record and resolves MAP/TMT/VQM-backed texture resources. */

undefined4 __cdecl bind_texture_resource_to_object_slot(uint param_1,byte *param_2,byte *param_3)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  uint *puVar7;
  byte *pbVar8;
  byte *pbVar9;
  uint *_Dest;
  code *pcVar10;
  
  if (param_1 == 0) {
    return 0;
  }
  if (param_2 == (byte *)0x0) {
    return 0;
  }
  if (param_3 == (byte *)0x0) {
    return 0;
  }
  uVar4 = 0;
  bVar2 = *param_2;
  pbVar8 = param_2;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar9 = pbVar8 + 1;
    pbVar8 = pbVar8 + 1;
    bVar2 = *pbVar9;
  }
  puVar7 = (uint *)(&g_texture_slot_binding_hash)[((uVar4 ^ param_1) * 0x6cd + 0xaab) % 0x7ed];
  pcVar10 = _stricmp_exref;
  while ((_stricmp_exref = pcVar10, puVar7 != (uint *)0x0 &&
         ((*puVar7 != param_1 ||
          (iVar5 = _stricmp((char *)(puVar7 + 5),(char *)param_2), iVar5 != 0))))) {
    puVar7 = (uint *)puVar7[0x10];
    pcVar10 = _stricmp_exref;
  }
  if (puVar7 != (uint *)0x0) {
    return 1;
  }
  uVar4 = 0;
  bVar2 = *param_3;
  pbVar8 = param_3;
  while (bVar2 != 0) {
    uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
    pbVar9 = pbVar8 + 1;
    pbVar8 = pbVar8 + 1;
    bVar2 = *pbVar9;
  }
  uVar4 = (&g_texture_set_cache_hash)[(uVar4 * 0x6cd + 0xaab) % 0x7ed];
  if (uVar4 != 0) {
    do {
      iVar5 = (*pcVar10)(uVar4,param_3);
      if (iVar5 == 0) break;
      uVar4 = *(uint *)(uVar4 + 0x30);
    } while (uVar4 != 0);
    if (uVar4 != 0) {
      *(int *)(uVar4 + 0x10) = *(int *)(uVar4 + 0x10) + 1;
      goto LAB_00449977;
    }
  }
  pcVar6 = strchr((char *)param_3,0x2e);
  if (pcVar6 == (char *)0x0) {
    iVar5 = 0;
  }
  else {
    iVar5 = (*pcVar10)(pcVar6,&DAT_004f25e8);
  }
  if (iVar5 == 0) {
    pbVar8 = HeapAlloc(g_texture_set_cache_heap,0,0x34);
    bVar3 = false;
    if (pbVar8 != (byte *)0x0) {
      strncpy((char *)pbVar8,(char *)param_3,0xf);
      pbVar8[0x10] = 1;
      pbVar8[0x11] = 0;
      pbVar8[0x12] = 0;
      pbVar8[0x13] = 0;
      pbVar8[0x1c] = 1;
      pbVar8[0x1d] = 0;
      pbVar8[0x1e] = 0;
      pbVar8[0x1f] = 0;
      pbVar8[0x20] = 1;
      pbVar8[0x21] = 0;
      pbVar8[0x22] = 0;
      pbVar8[0x23] = 0;
      pcVar6 = HeapAlloc(g_texture_name_array_heap,0,0x10);
      *(char **)(pbVar8 + 0x2c) = pcVar6;
      strncpy(pcVar6,(char *)param_3,0xf);
      uVar4 = 0;
      bVar2 = *pbVar8;
      pbVar9 = pbVar8;
      while (bVar2 != 0) {
        uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
        pbVar1 = pbVar9 + 1;
        pbVar9 = pbVar9 + 1;
        bVar2 = *pbVar1;
      }
      uVar4 = (uVar4 * 0x6cd + 0xaab) % 0x7ed;
      *(undefined4 *)(pbVar8 + 0x30) = (&g_texture_set_cache_hash)[uVar4];
      (&g_texture_set_cache_hash)[uVar4] = pbVar8;
      bVar3 = true;
      pcVar10 = _stricmp_exref;
    }
  }
  else {
    puVar7 = open_resource_file_into_memory((char *)param_3);
    bVar3 = false;
    if (puVar7 != (uint *)0x0) {
      _Dest = puVar7 + 1;
      strncpy((char *)_Dest,(char *)param_3,0xf);
      pcVar6 = HeapAlloc(g_texture_set_cache_heap,0,0x34);
      bVar3 = false;
      if (pcVar6 != (char *)0x0) {
        strncpy(pcVar6,(char *)_Dest,0xf);
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
          bVar2 = (byte)*_Dest;
          while (bVar2 != 0) {
            uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
            pbVar8 = (byte *)((int)_Dest + 1);
            _Dest = (uint *)((int)_Dest + 1);
            bVar2 = *pbVar8;
          }
          uVar4 = (uVar4 * 0x6cd + 0xaab) % 0x7ed;
          *(undefined4 *)(pcVar6 + 0x30) = (&g_texture_set_cache_hash)[uVar4];
          (&g_texture_set_cache_hash)[uVar4] = pcVar6;
          bVar3 = true;
        }
      }
      release_resource_file_reference((char *)param_3);
      pcVar10 = _stricmp_exref;
    }
  }
  if (bVar3) {
    uVar4 = 0;
    bVar2 = *param_3;
    pbVar8 = param_3;
    while (bVar2 != 0) {
      uVar4 = uVar4 * 2 ^ bVar2 & 0xdf;
      pbVar9 = pbVar8 + 1;
      pbVar8 = pbVar8 + 1;
      bVar2 = *pbVar9;
    }
    uVar4 = (&g_texture_set_cache_hash)[(uVar4 * 0x6cd + 0xaab) % 0x7ed];
    while ((uVar4 != 0 && (iVar5 = (*pcVar10)(uVar4,param_3), iVar5 != 0))) {
      uVar4 = *(uint *)(uVar4 + 0x30);
    }
  }
  else {
    uVar4 = 0;
  }
LAB_00449977:
  if ((uVar4 != 0) &&
     (puVar7 = create_texture_slot_binding_for_object(param_1,param_2,param_3,uVar4),
     puVar7 != (uint *)0x0)) {
    if ((*(uint *)(uVar4 + 0x18) & 1) != 0) {
      if ((*(uint *)(uVar4 + 0x18) & 2) != 0) {
        install_texture_animation_pingpong_timer
                  (param_1,param_2,_DAT_004bd3bc / *(float *)(uVar4 + 0x14),0.0,
                   *(float *)(uVar4 + 0x20),1);
        return 1;
      }
      install_texture_animation_linear_timer
                (param_1,param_2,_DAT_004bd3bc / *(float *)(uVar4 + 0x14),0.0,
                 *(float *)(uVar4 + 0x20),6.307143e-39);
    }
    return 1;
  }
  return 0;
}


