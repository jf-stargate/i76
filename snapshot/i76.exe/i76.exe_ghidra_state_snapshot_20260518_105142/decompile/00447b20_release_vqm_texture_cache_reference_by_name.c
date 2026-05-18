/*
 * Program: i76.exe
 * Function: release_vqm_texture_cache_reference_by_name
 * Entry: 00447b20
 * Signature: undefined __cdecl release_vqm_texture_cache_reference_by_name(char * param_1)
 */


/* [cgpt i76.exe image payload renames v28; confidence=high] Releases a cached VQM/direct texture
   resource reference by normalized texture name and updates cache/LRU state. */

void __cdecl release_vqm_texture_cache_reference_by_name(char *param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  char *pcVar10;
  byte *pbVar11;
  byte local_10 [16];
  
  uVar5 = 0xffffffff;
  pcVar4 = param_1;
  do {
    pcVar10 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar10 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar10;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar4 = pcVar10 + -uVar5;
  pbVar9 = local_10;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar9 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pbVar9 = pbVar9 + 1;
  }
  pcVar4 = strchr((char *)local_10,0x2e);
  if (pcVar4 != (char *)0x0) {
    *pcVar4 = '\0';
  }
  uVar5 = 0xffffffff;
  pcVar4 = s__vqm_004f2698;
  do {
    pcVar10 = pcVar4;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar10 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar10;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  iVar7 = -1;
  pbVar9 = local_10;
  do {
    pbVar11 = pbVar9;
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    pbVar11 = pbVar9 + 1;
    bVar2 = *pbVar9;
    pbVar9 = pbVar11;
  } while (bVar2 != 0);
  pbVar9 = (byte *)(pcVar10 + -uVar5);
  pbVar11 = pbVar11 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar11 = *(undefined4 *)pbVar9;
    pbVar9 = pbVar9 + 4;
    pbVar11 = pbVar11 + 4;
  }
  pbVar8 = local_10;
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar11 = *pbVar9;
    pbVar9 = pbVar9 + 1;
    pbVar11 = pbVar11 + 1;
  }
  uVar5 = 0;
  while (local_10[0] != 0) {
    uVar5 = uVar5 * 2 ^ local_10[0] & 0xdf;
    pbVar9 = pbVar8 + 1;
    pbVar8 = pbVar8 + 1;
    local_10[0] = *pbVar9;
  }
  for (pcVar4 = (char *)(&g_vqm_texture_cache_hash)[(uVar5 * 0x6cd + 0xaab) % 0x6d];
      pcVar4 != (char *)0x0; pcVar4 = *(char **)(pcVar4 + 0x20)) {
    iVar7 = _stricmp(pcVar4,(char *)local_10);
    if (iVar7 == 0) goto LAB_00447bf6;
  }
  pcVar4 = (char *)0x0;
LAB_00447bf6:
  if (pcVar4 == (char *)0x0) {
    release_resource_file_reference(param_1);
  }
  else if (((*(short *)(pcVar4 + 0x14) != 0) &&
           (sVar3 = *(short *)(pcVar4 + 0x14) + -1, *(short *)(pcVar4 + 0x14) = sVar3, sVar3 == 0))
          && ((pcVar4[0x16] & 1U) == 0)) {
    pcVar4[0x18] = '\0';
    pcVar4[0x19] = '\0';
    pcVar4[0x1a] = '\0';
    pcVar4[0x1b] = '\0';
    *(int *)(pcVar4 + 0x18) = g_vqm_texture_lru_head;
    if (g_vqm_texture_lru_head != 0) {
      *(char **)(g_vqm_texture_lru_head + 0x1c) = pcVar4;
    }
    if (g_vqm_texture_lru_tail == 0) {
      g_vqm_texture_lru_tail = (int)pcVar4;
    }
    g_vqm_texture_lru_head = (int)pcVar4;
    *(ushort *)(pcVar4 + 0x16) = *(ushort *)(pcVar4 + 0x16) | 1;
    uVar5 = video_memory_texture_cache_record_exists(*(uint *)(pcVar4 + 0x10));
    if (uVar5 != 0) {
      pcVar4[0x16] = pcVar4[0x16] | 2;
      return;
    }
  }
  return;
}


