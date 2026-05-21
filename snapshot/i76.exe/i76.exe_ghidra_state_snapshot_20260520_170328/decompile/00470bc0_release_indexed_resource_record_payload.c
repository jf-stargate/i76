/*
 * Program: i76.exe
 * Function: release_indexed_resource_record_payload
 * Entry: 00470bc0
 * Signature: undefined4 __cdecl release_indexed_resource_record_payload(void * param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Binary-searches indexed
   resource records, decrements backing-file record refcount, and releases backing loaded-resource
   cache record when it reaches zero. */

undefined4 __cdecl release_indexed_resource_record_payload(void *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  
  pvVar2 = bsearch(param_1,g_indexed_resource_records,g_indexed_resource_record_count,0x1c,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  if (pvVar2 == (void *)0x0) {
    return 0;
  }
  iVar3 = *(int *)((int)pvVar2 + 0x10) * 0x18;
  iVar1 = *(int *)(g_pix_pak_file_table + 0x14 + iVar3);
  if (iVar1 != 0) {
    *(int *)(g_pix_pak_file_table + 0x14 + iVar3) = iVar1 + -1;
    if (*(int *)((char *)(g_pix_pak_file_table + iVar3) + 0x14) == 0) {
      release_loaded_resource_cache_record_by_name((char *)(g_pix_pak_file_table + iVar3));
      *(undefined4 *)(g_pix_pak_file_table + 0x10 + iVar3) = 0;
    }
  }
  return 1;
}


