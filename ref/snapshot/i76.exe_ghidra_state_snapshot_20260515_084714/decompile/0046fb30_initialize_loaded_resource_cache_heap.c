/*
 * Program: i76.exe
 * Function: initialize_loaded_resource_cache_heap
 * Entry: 0046fb30
 * Signature: undefined __stdcall initialize_loaded_resource_cache_heap(void)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Initializes loaded-resource cache
   heap, hash table, purge lists, and cache budget based on system memory profile. */

void initialize_loaded_resource_cache_heap(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int local_20 [8];
  
  piVar1 = (int *)system_cutscene_memory_context_helper_00499ae0(local_20);
  piVar3 = local_20;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = *piVar1;
    piVar1 = piVar1 + 1;
    piVar3 = piVar3 + 1;
  }
  g_loaded_resource_cache_used_bytes = 0;
  g_loaded_resource_cache_low_watermark = 2000;
  g_loaded_resource_purge_list_tail = 0;
  g_loaded_resource_purge_list_head = 0;
  if (local_20[2] < 32000000) {
    g_loaded_resource_cache_budget_bytes = 0x600000;
  }
  else {
    g_loaded_resource_cache_budget_bytes = ((63999999 < local_20[2]) - 1 & 0xffc00000) + 0xb00000;
  }
  g_loaded_resource_heap = HeapCreate(0,0,g_loaded_resource_cache_budget_bytes);
  g_loaded_resource_cache_hash = HeapAlloc(g_loaded_resource_heap,8,0x1f64);
  g_loaded_resource_cache_budget_bytes = g_loaded_resource_cache_budget_bytes - 0x1f64;
  return;
}


