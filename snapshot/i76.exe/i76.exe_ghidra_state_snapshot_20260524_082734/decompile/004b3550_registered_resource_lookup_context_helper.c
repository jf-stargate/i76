/*
 * Program: i76.exe
 * Function: registered_resource_lookup_context_helper
 * Entry: 004b3550
 * Signature: undefined __cdecl registered_resource_lookup_context_helper(LPVOID param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: registered resource lookup context
   helper based on adjacent named subsystem context.
   
   I76 rename v43: registered_resource_lookup_context_helper
   Registered resource lookup context helper. */

void __cdecl registered_resource_lookup_context_helper(LPVOID param_1)

{
  HeapFree(g_resource_key_table_heap_handle,0,param_1);
  return;
}


