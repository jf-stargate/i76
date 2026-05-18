/*
 * Program: i76.exe
 * Function: load_texture_resource_resolving_vqm_cbk_to_cache
 * Entry: 004474b0
 * Signature: uint * __cdecl load_texture_resource_resolving_vqm_cbk_to_cache(byte * param_1)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Loads texture resources into cache,
   resolving .vqm through the named .cbk codebook into indexed pixels where applicable. */

uint * __cdecl load_texture_resource_resolving_vqm_cbk_to_cache(byte *param_1)

{
  uint *puVar1;
  byte bVar2;
  char cVar3;
  bool bVar4;
  char *pcVar5;
  uint *puVar6;
  uint *puVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  byte *pbVar12;
  byte *pbVar13;
  uint *puVar14;
  SIZE_T dwBytes;
  char *pcVar15;
  byte *pbVar16;
  byte local_10 [16];
  
  uVar8 = 0xffffffff;
  puVar14 = (uint *)0x0;
  pbVar13 = param_1;
  do {
    pbVar16 = pbVar13;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pbVar16 = pbVar13 + 1;
    bVar2 = *pbVar13;
    pbVar13 = pbVar16;
  } while (bVar2 != 0);
  uVar8 = ~uVar8;
  pbVar13 = pbVar16 + -uVar8;
  pbVar16 = local_10;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
    pbVar13 = pbVar13 + 4;
    pbVar16 = pbVar16 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pbVar16 = *pbVar13;
    pbVar13 = pbVar13 + 1;
    pbVar16 = pbVar16 + 1;
  }
  pcVar5 = strchr((char *)local_10,0x2e);
  if (pcVar5 != (char *)0x0) {
    *pcVar5 = '\0';
  }
  uVar9 = 0xffffffff;
  uVar8 = 0;
  pcVar5 = s__vqm_004f2698;
  do {
    pcVar15 = pcVar5;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar15 = pcVar5 + 1;
    cVar3 = *pcVar5;
    pcVar5 = pcVar15;
  } while (cVar3 != '\0');
  uVar9 = ~uVar9;
  iVar10 = -1;
  pbVar13 = local_10;
  do {
    pbVar16 = pbVar13;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pbVar16 = pbVar13 + 1;
    bVar2 = *pbVar13;
    pbVar13 = pbVar16;
  } while (bVar2 != 0);
  pbVar13 = (byte *)(pcVar15 + -uVar9);
  pbVar16 = pbVar16 + -1;
  for (uVar11 = uVar9 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
    pbVar13 = pbVar13 + 4;
    pbVar16 = pbVar16 + 4;
  }
  pbVar12 = local_10;
  for (uVar9 = uVar9 & 3; bVar2 = local_10[0], uVar9 != 0; uVar9 = uVar9 - 1) {
    *pbVar16 = *pbVar13;
    pbVar13 = pbVar13 + 1;
    pbVar16 = pbVar16 + 1;
  }
  while (bVar2 != 0) {
    uVar8 = uVar8 * 2 ^ bVar2 & 0xdf;
    pbVar13 = pbVar12 + 1;
    pbVar12 = pbVar12 + 1;
    bVar2 = *pbVar13;
  }
  for (pcVar5 = (char *)(&g_vqm_texture_cache_hash)[(uVar8 * 0x6cd + 0xaab) % 0x6d];
      pcVar5 != (char *)0x0; pcVar5 = *(char **)(pcVar5 + 0x20)) {
    iVar10 = _stricmp(pcVar5,(char *)local_10);
    if (iVar10 == 0) goto LAB_00447587;
  }
  pcVar5 = (char *)0x0;
LAB_00447587:
  if (pcVar5 != (char *)0x0) {
    if (*(short *)(pcVar5 + 0x14) == 0) {
      if ((char *)g_vqm_texture_lru_tail == pcVar5) {
        g_vqm_texture_lru_tail = *(int *)(pcVar5 + 0x1c);
      }
      if ((char *)g_vqm_texture_lru_head == pcVar5) {
        g_vqm_texture_lru_head = *(int *)(pcVar5 + 0x18);
      }
      if (*(int *)(pcVar5 + 0x18) != 0) {
        *(undefined4 *)(*(int *)(pcVar5 + 0x18) + 0x1c) = *(undefined4 *)(pcVar5 + 0x1c);
      }
      if (*(int *)(pcVar5 + 0x1c) != 0) {
        *(undefined4 *)(*(int *)(pcVar5 + 0x1c) + 0x18) = *(undefined4 *)(pcVar5 + 0x18);
      }
      *(ushort *)(pcVar5 + 0x16) = *(ushort *)(pcVar5 + 0x16) & 0xfffc;
      pcVar5[0x1c] = '\0';
      pcVar5[0x1d] = '\0';
      pcVar5[0x1e] = '\0';
      pcVar5[0x1f] = '\0';
      pcVar5[0x18] = '\0';
      pcVar5[0x19] = '\0';
      pcVar5[0x1a] = '\0';
      pcVar5[0x1b] = '\0';
    }
    *(short *)(pcVar5 + 0x14) = *(short *)(pcVar5 + 0x14) + 1;
    return *(uint **)(pcVar5 + 0x10);
  }
  if (g_resource_cache_prefer_directory_first != 0) {
    puVar14 = open_resource_file_into_memory((char *)param_1);
  }
  if ((puVar14 == (uint *)0x0) &&
     (iVar10 = get_loaded_resource_file_size((char *)local_10), iVar10 != 0)) {
    g_resource_nested_load_depth = g_resource_nested_load_depth + 1;
    puVar6 = open_resource_file_into_memory((char *)local_10);
    puVar1 = puVar6 + 2;
    puVar7 = open_resource_file_into_memory((char *)puVar1);
    if (puVar7 == (uint *)0x0) {
      report_chunk_parse_error();
      release_resource_file_reference((char *)local_10);
      g_resource_nested_load_depth = g_resource_nested_load_depth + -1;
      return (uint *)0x0;
    }
    g_resource_nested_load_depth = g_resource_nested_load_depth + -1;
    if (g_resource_debug_log_file != 0) {
      debug_fprintf_wrapper('t');
      fprintf((FILE *)g_resource_debug_log_file,s__s__dx_d_004edf9c,local_10,*puVar6,puVar6[1]);
    }
    uVar8 = *puVar6;
    uVar9 = puVar6[1];
    while( true ) {
      dwBytes = *puVar6 * puVar6[1] + 8;
      puVar14 = HeapAlloc(g_vqm_texture_heap_handle,0,dwBytes);
      if ((puVar14 != (uint *)0x0) &&
         (g_vqm_texture_cache_bytes_remaining = g_vqm_texture_cache_bytes_remaining - dwBytes,
         puVar14 != (uint *)0x0)) break;
      iVar10 = evict_lru_vqm_texture_cache_record();
      if (iVar10 == 0) {
        report_chunk_parse_error();
        release_resource_file_reference((char *)puVar1);
        release_resource_file_reference((char *)local_10);
        return (uint *)0x0;
      }
    }
    iVar10 = decode_vqm_cbk_4x4_blocks_to_indexed_pixels
                       (puVar6,(int)puVar7,puVar14,uVar8 * uVar9 + 0x18);
    if (iVar10 == 0) {
      report_chunk_parse_error();
      release_resource_file_reference((char *)puVar1);
      release_resource_file_reference((char *)local_10);
      return (uint *)0x0;
    }
    pcVar5 = HeapAlloc(DAT_00531cf4,0,0x24);
    if (pcVar5 == (char *)0x0) {
      pcVar5 = (char *)0x0;
    }
    else {
      pcVar5[0x20] = '\0';
      pcVar5[0x21] = '\0';
      pcVar5[0x22] = '\0';
      pcVar5[0x23] = '\0';
      pcVar5[0x1c] = '\0';
      pcVar5[0x1d] = '\0';
      pcVar5[0x1e] = '\0';
      pcVar5[0x1f] = '\0';
      pcVar5[0x18] = '\0';
      pcVar5[0x19] = '\0';
      pcVar5[0x1a] = '\0';
      pcVar5[0x1b] = '\0';
      strncpy(pcVar5,(char *)local_10,0x10);
      uVar8 = 0;
      pbVar13 = local_10;
      while (local_10[0] != 0) {
        uVar8 = uVar8 * 2 ^ local_10[0] & 0xdf;
        pbVar16 = pbVar13 + 1;
        pbVar13 = pbVar13 + 1;
        local_10[0] = *pbVar16;
      }
      uVar8 = (uVar8 * 0x6cd + 0xaab) % 0x6d;
      *(undefined4 *)(pcVar5 + 0x20) = (&g_vqm_texture_cache_hash)[uVar8];
      (&g_vqm_texture_cache_hash)[uVar8] = pcVar5;
    }
    if (pcVar5 == (char *)0x0) {
      report_chunk_parse_error();
      release_resource_file_reference((char *)puVar1);
      release_resource_file_reference((char *)local_10);
      return (uint *)0x0;
    }
    *(uint **)(pcVar5 + 0x10) = puVar14;
    pcVar5[0x14] = '\x01';
    pcVar5[0x15] = '\0';
    release_resource_file_reference((char *)puVar1);
    release_resource_file_reference((char *)local_10);
    bVar4 = is_miss16_high_color_resource_mode();
    if (CONCAT31(extraout_var,bVar4) != 0) {
      mark_asset_fullres_flag_from_fullres_list((int)puVar14,local_10);
      return puVar14;
    }
  }
  else {
    if (g_resource_cache_prefer_directory_first == 0) {
      puVar14 = open_resource_file_into_memory((char *)param_1);
    }
    bVar4 = is_miss16_high_color_resource_mode();
    if (CONCAT31(extraout_var_00,bVar4) != 0) {
      mark_asset_fullres_flag_from_fullres_list((int)puVar14,param_1);
    }
  }
  return puVar14;
}


