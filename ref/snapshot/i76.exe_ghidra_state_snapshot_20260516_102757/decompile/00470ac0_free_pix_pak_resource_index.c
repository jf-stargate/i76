/*
 * Program: i76.exe
 * Function: free_pix_pak_resource_index
 * Entry: 00470ac0
 * Signature: undefined __stdcall free_pix_pak_resource_index(void)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Releases per-PAK resource handles,
   frees PIX/PAK file table and sorted indexed-resource record table. */

void free_pix_pak_resource_index(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (g_pix_pak_file_count != 0) {
    iVar1 = 0;
    do {
      if (*(int *)((char *)((int)g_pix_pak_file_table + iVar1) + 0x10) != 0) {
        release_loaded_resource_cache_record_by_name((char *)((int)g_pix_pak_file_table + iVar1));
      }
      uVar2 = uVar2 + 1;
      iVar1 = iVar1 + 0x18;
    } while (uVar2 < g_pix_pak_file_count);
  }
  xfree_global_heap(g_pix_pak_file_table);
  xfree_global_heap(g_indexed_resource_records);
  return;
}


