/*
 * Program: i76.exe
 * Function: lookup_zfsf_record_logical_size
 * Entry: 004b9b40
 * Signature: int __cdecl lookup_zfsf_record_logical_size(int param_1, char * param_2)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Looks up a live ZFSF record by name and
   returns decompressed/logical size. For compressed records this is flags_size >> 8; for
   uncompressed records this is stored_size. */

int __cdecl lookup_zfsf_record_logical_size(int param_1,char *param_2)

{
  void *pvVar1;
  char local_24 [36];
  
  strncpy(local_24,param_2,0x10);
  pvVar1 = bsearch(local_24,*(void **)(param_1 + 0x28),*(size_t *)(param_1 + 0x18),0x24,
                   compare_zfsf_record_name_cstring);
  if (pvVar1 == (void *)0x0) {
    return -1;
  }
  if ((*(uint *)((int)pvVar1 + 0x20) & 6) != 0) {
    return (int)*(uint *)((int)pvVar1 + 0x20) >> 8;
  }
  return *(int *)((int)pvVar1 + 0x18);
}


