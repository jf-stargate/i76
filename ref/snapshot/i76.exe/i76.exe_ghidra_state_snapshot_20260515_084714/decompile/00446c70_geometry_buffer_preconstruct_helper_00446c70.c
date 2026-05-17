/*
 * Program: i76.exe
 * Function: geometry_buffer_preconstruct_helper_00446c70
 * Entry: 00446c70
 * Signature: undefined4 __stdcall geometry_buffer_preconstruct_helper_00446c70(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: geometry buffer preconstruct helper
   based on prior focused closure context. */

undefined4 geometry_buffer_preconstruct_helper_00446c70(void)

{
  HeapDestroy(g_geometry_heap);
  HeapDestroy(g_geometry_cache_entry_heap);
  return 1;
}


