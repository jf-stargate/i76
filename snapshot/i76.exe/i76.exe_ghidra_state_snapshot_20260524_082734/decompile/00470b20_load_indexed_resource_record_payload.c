/*
 * Program: i76.exe
 * Function: load_indexed_resource_record_payload
 * Entry: 00470b20
 * Signature: int __cdecl load_indexed_resource_record_payload(void * param_1)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Loads or reuses the owning
   .pak stream and returns base + indexed-resource payload offset.
   
   I76 rename v43: load_indexed_pix_pak_resource_payload
   Loads payload from indexed PIX/PAK resource record. */

int __cdecl load_indexed_resource_record_payload(void *param_1)

{
  void *pvVar1;
  uint *puVar2;
  int iVar3;
  
  pvVar1 = bsearch(param_1,g_indexed_resource_records,g_indexed_resource_record_count,0x1c,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  if (pvVar1 == (void *)0x0) {
    return 0;
  }
  iVar3 = *(int *)((int)pvVar1 + 0x10) * 0x18;
  if (*(int *)(g_pix_pak_file_table + 0x10 + iVar3) == 0) {
    puVar2 = load_resource_stream_into_loaded_cache((char *)(g_pix_pak_file_table + iVar3));
    *(uint **)(g_pix_pak_file_table + 0x10 + iVar3) = puVar2;
    if (*(int *)(g_pix_pak_file_table + 0x10 + iVar3) == 0) {
      report_error();
    }
  }
  *(int *)(g_pix_pak_file_table + 0x14 + iVar3) = *(int *)(g_pix_pak_file_table + 0x14 + iVar3) + 1;
  return *(int *)(g_pix_pak_file_table + 0x10 + iVar3) + *(int *)((int)pvVar1 + 0x14);
}


