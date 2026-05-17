/*
 * Program: i76.exe
 * Function: loaded_resource_cache_cleanup_context_helper_0046fa80
 * Entry: 0046fa80
 * Signature: undefined __stdcall loaded_resource_cache_cleanup_context_helper_0046fa80(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache cleanup context
   helper based on adjacent named subsystem context. */

void loaded_resource_cache_cleanup_context_helper_0046fa80(void)

{
  while (g_loaded_resource_purge_list_tail != (char *)0x0) {
    evict_loaded_resource_cache_record(g_loaded_resource_purge_list_tail);
  }
  HeapCompact(g_loaded_resource_heap,0);
  return;
}


