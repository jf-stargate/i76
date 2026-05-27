/*
 * Program: i76.exe
 * Function: open_resource_file_into_memory
 * Entry: 0046ffc0
 * Signature: uint * __cdecl open_resource_file_into_memory(char * param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Canonicalized resource open
   helper that chooses directory-backed loaded cache versus indexed archive record depending on
   preference/global state.
   
   I76 rename v43: open_resource_file_into_memory
   Main resource open path below BWD2 parser; lowercases name and checks indexed/cache paths. */

uint * __cdecl open_resource_file_into_memory(char *param_1)

{
  int iVar1;
  uint *puVar2;
  char local_10 [16];
  
  strncpy(local_10,param_1,0x10);
  _strlwr(local_10);
  if ((&stack0x00000000 != (undefined1 *)0x10) && (local_10[0] != '\0')) {
    iVar1 = strncmp(local_10,s_null_004c3280,4);
    if (iVar1 != 0) {
      if (g_resource_cache_prefer_directory_first != 0) {
        puVar2 = load_resource_stream_into_loaded_cache(local_10);
        if (puVar2 != (uint *)0x0) {
          return puVar2;
        }
        puVar2 = (uint *)load_indexed_resource_record_payload(local_10);
        return puVar2;
      }
      puVar2 = (uint *)load_indexed_resource_record_payload(local_10);
      if (puVar2 != (uint *)0x0) {
        return puVar2;
      }
      puVar2 = load_resource_stream_into_loaded_cache(local_10);
      return puVar2;
    }
  }
  return (uint *)0x0;
}


