/*
 * Program: i76.exe
 * Function: evict_lru_vqm_texture_cache_record
 * Entry: 00447e10
 * Signature: undefined4 __stdcall evict_lru_vqm_texture_cache_record(void)
 */


/* [cgpt i76.exe image payload renames v28; confidence=high] Evicts a zero-refcount VQM/direct
   texture cache record from the LRU list to recover texture cache memory. */

undefined4 evict_lru_vqm_texture_cache_record(void)

{
  byte bVar1;
  int *lpMem;
  bool bVar2;
  undefined3 extraout_var;
  byte *lpMem_00;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = g_vqm_texture_lru_tail;
  if (g_vqm_texture_lru_tail == (byte *)0x0) {
    return 0;
  }
  bVar2 = is_miss16_high_color_resource_mode();
  lpMem_00 = pbVar6;
  if (CONCAT31(extraout_var,bVar2) != 0) {
    lpMem_00 = g_vqm_texture_lru_tail;
    if (g_vqm_texture_lru_tail != (byte *)0x0) {
      do {
        if ((lpMem_00[0x16] & 2) == 0) break;
        lpMem_00 = *(byte **)(lpMem_00 + 0x1c);
      } while (lpMem_00 != (byte *)0x0);
      if (lpMem_00 != (byte *)0x0) goto LAB_00447e54;
    }
    release_video_memory_texture_cache_record_by_id(*(uint *)(pbVar6 + 0x10));
    lpMem_00 = pbVar6;
  }
LAB_00447e54:
  if (g_vqm_texture_lru_tail == lpMem_00) {
    g_vqm_texture_lru_tail = *(byte **)(lpMem_00 + 0x1c);
  }
  if (g_vqm_texture_lru_head == lpMem_00) {
    g_vqm_texture_lru_head = *(byte **)(lpMem_00 + 0x18);
  }
  if (*(int *)(lpMem_00 + 0x18) != 0) {
    *(undefined4 *)(*(int *)(lpMem_00 + 0x18) + 0x1c) = *(undefined4 *)(lpMem_00 + 0x1c);
  }
  if (*(int *)(lpMem_00 + 0x1c) != 0) {
    *(undefined4 *)(*(int *)(lpMem_00 + 0x1c) + 0x18) = *(undefined4 *)(lpMem_00 + 0x18);
  }
  *(ushort *)(lpMem_00 + 0x16) = *(ushort *)(lpMem_00 + 0x16) & 0xfffc;
  lpMem_00[0x1c] = 0;
  lpMem_00[0x1d] = 0;
  lpMem_00[0x1e] = 0;
  lpMem_00[0x1f] = 0;
  lpMem_00[0x18] = 0;
  lpMem_00[0x19] = 0;
  lpMem_00[0x1a] = 0;
  lpMem_00[0x1b] = 0;
  uVar3 = 0;
  bVar1 = *lpMem_00;
  pbVar6 = lpMem_00;
  while (bVar1 != 0) {
    uVar3 = uVar3 * 2 ^ bVar1 & 0xdf;
    pbVar5 = pbVar6 + 1;
    pbVar6 = pbVar6 + 1;
    bVar1 = *pbVar5;
  }
  uVar3 = (uVar3 * 0x6cd + 0xaab) % 0x6d;
  pbVar6 = (byte *)(&g_vqm_texture_cache_hash)[uVar3];
  if (pbVar6 == lpMem_00) {
    (&g_vqm_texture_cache_hash)[uVar3] = *(undefined4 *)(lpMem_00 + 0x20);
  }
  else {
    pbVar5 = *(byte **)(pbVar6 + 0x20);
    if (*(byte **)(pbVar6 + 0x20) != (byte *)0x0) {
      do {
        pbVar4 = pbVar5;
        if (pbVar4 == lpMem_00) {
          *(undefined4 *)(pbVar6 + 0x20) = *(undefined4 *)(pbVar4 + 0x20);
          pbVar5 = pbVar4;
          break;
        }
        pbVar5 = *(byte **)(pbVar4 + 0x20);
        pbVar6 = pbVar4;
      } while (pbVar5 != (byte *)0x0);
      if (pbVar5 != (byte *)0x0) goto LAB_00447f22;
    }
    report_chunk_parse_error();
  }
LAB_00447f22:
  lpMem = *(int **)(lpMem_00 + 0x10);
  g_vqm_texture_cache_bytes_remaining =
       g_vqm_texture_cache_bytes_remaining + 8 + ((lpMem[1] << 3) >> 3) * *lpMem;
  HeapFree(g_vqm_texture_heap_handle,0,lpMem);
  HeapFree(DAT_00531cf4,0,lpMem_00);
  return 1;
}


