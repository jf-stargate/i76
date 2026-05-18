/*
 * Program: i76.exe
 * Function: indexed_resource_record_exists
 * Entry: 00470c70
 * Signature: bool __cdecl indexed_resource_record_exists(void * param_1)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Checks existence of a key in
   the sorted 0x1c-byte PIX/PAK indexed-resource table. */

bool __cdecl indexed_resource_record_exists(void *param_1)

{
  void *pvVar1;
  
  pvVar1 = bsearch(param_1,g_indexed_resource_records,g_indexed_resource_record_count,0x1c,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  return pvVar1 != (void *)0x0;
}


