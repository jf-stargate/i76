/*
 * Program: i76.exe
 * Function: texture_cache_lru_helper_00447c80
 * Entry: 00447c80
 * Signature: undefined __stdcall texture_cache_lru_helper_00447c80(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: texture cache lru helper based on
   prior focused closure context. */

void texture_cache_lru_helper_00447c80(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = &g_vqm_texture_cache_hash;
  do {
    iVar3 = *piVar4;
    while (iVar1 = iVar3, iVar1 != 0) {
      iVar3 = *(int *)(iVar1 + 0x20);
      if ((*(byte *)(iVar1 + 0x16) & 1) == 0) {
        *(undefined4 *)(iVar1 + 0x18) = 0;
        *(int *)(iVar1 + 0x18) = g_vqm_texture_lru_head;
        if (g_vqm_texture_lru_head != 0) {
          *(int *)(g_vqm_texture_lru_head + 0x1c) = iVar1;
        }
        if (g_vqm_texture_lru_tail == 0) {
          g_vqm_texture_lru_tail = iVar1;
        }
        g_vqm_texture_lru_head = iVar1;
        *(byte *)(iVar1 + 0x16) = *(byte *)(iVar1 + 0x16) | 1;
        uVar2 = video_memory_texture_cache_record_exists(*(uint *)(iVar1 + 0x10));
        if (uVar2 != 0) {
          *(byte *)(iVar1 + 0x16) = *(byte *)(iVar1 + 0x16) | 2;
        }
      }
    }
    piVar4 = piVar4 + 1;
  } while ((int)piVar4 < 0x531cf4);
  iVar3 = evict_lru_vqm_texture_cache_record();
  while (iVar3 != 0) {
    iVar3 = evict_lru_vqm_texture_cache_record();
  }
  HeapDestroy(DAT_00531cf4);
  HeapDestroy(g_vqm_texture_heap_handle);
  return;
}


