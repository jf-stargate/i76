/*
 * Program: i76.exe
 * Function: find_vqm_texture_cache_record_by_bitmap_id
 * Entry: 00447dd0
 * Signature: int __cdecl find_vqm_texture_cache_record_by_bitmap_id(int param_1)
 */


/* cgpt rename v4: Searches VQM texture cache hash buckets and LRU list for a cache record matching
   a bitmap/resource id. */

int __cdecl find_vqm_texture_cache_record_by_bitmap_id(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = &g_vqm_texture_cache_hash;
  do {
    for (iVar1 = *piVar2; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x20)) {
      if (*(int *)(iVar1 + 0x10) == param_1) {
        return iVar1;
      }
    }
    piVar2 = piVar2 + 1;
    iVar1 = g_vqm_texture_lru_tail;
  } while ((int)piVar2 < 0x531cf4);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x10) == param_1) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
  }
  return iVar1;
}


