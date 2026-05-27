/*
 * Program: i76.exe
 * Function: destroy_loaded_resource_cache_heap
 * Entry: 0046fab0
 * Signature: undefined __stdcall destroy_loaded_resource_cache_heap(void)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Evicts all loaded-resource cache
   records, frees hash table, resets purge lists/counters, and destroys the resource heap.
   
   I76 rename v43: loaded_resource_cache_lookup
   Loaded resource cache lookup helper. */

void destroy_loaded_resource_cache_heap(void)

{
  char *pcVar1;
  char *pcVar2;
  LPVOID lpMem;
  int iVar3;
  
  if (g_loaded_resource_cache_hash != (LPVOID)0x0) {
    iVar3 = 0;
    lpMem = g_loaded_resource_cache_hash;
    do {
      pcVar2 = *(char **)((int)lpMem + iVar3);
      while (pcVar2 != (char *)0x0) {
        pcVar1 = *(char **)(pcVar2 + 0x18);
        evict_loaded_resource_cache_record(pcVar2);
        pcVar2 = pcVar1;
        lpMem = g_loaded_resource_cache_hash;
      }
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x1f64);
    g_loaded_resource_cache_used_bytes = 0;
    g_loaded_resource_purge_list_tail = 0;
    g_loaded_resource_purge_list_head = 0;
    HeapFree(g_loaded_resource_heap,0,lpMem);
    HeapDestroy(g_loaded_resource_heap);
  }
  return;
}


