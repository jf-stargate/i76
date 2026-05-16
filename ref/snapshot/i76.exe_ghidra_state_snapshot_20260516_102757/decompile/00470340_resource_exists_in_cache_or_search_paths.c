/*
 * Program: i76.exe
 * Function: resource_exists_in_cache_or_search_paths
 * Entry: 00470340
 * Signature: bool __cdecl resource_exists_in_cache_or_search_paths(char * param_1)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=high] Tests whether a resource exists in
   cache/registered paths; used by GEO texture slot .tmt versus .map fallback. */

bool __cdecl resource_exists_in_cache_or_search_paths(char *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  char local_10 [16];
  
  strncpy(local_10,param_1,0x10);
  _strlwr(local_10);
  bVar1 = indexed_resource_record_exists(local_10);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    return true;
  }
  bVar1 = registered_resource_key_exists((undefined4 *)local_10);
  return bVar1;
}


