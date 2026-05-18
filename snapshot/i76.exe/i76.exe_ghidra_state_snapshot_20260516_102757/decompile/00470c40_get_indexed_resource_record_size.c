/*
 * Program: i76.exe
 * Function: get_indexed_resource_record_size
 * Entry: 00470c40
 * Signature: undefined4 __cdecl get_indexed_resource_record_size(void * param_1)
 */


/* [cgpt i76.exe texture/image/resource renames v21; confidence=high] Returns indexed-resource
   payload size from the 0x1c-byte PIX/PAK table record. */

undefined4 __cdecl get_indexed_resource_record_size(void *param_1)

{
  void *pvVar1;
  
  pvVar1 = bsearch(param_1,g_indexed_resource_records,g_indexed_resource_record_count,0x1c,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  if (pvVar1 == (void *)0x0) {
    return 0xffffffff;
  }
  return *(undefined4 *)((int)pvVar1 + 0x18);
}


