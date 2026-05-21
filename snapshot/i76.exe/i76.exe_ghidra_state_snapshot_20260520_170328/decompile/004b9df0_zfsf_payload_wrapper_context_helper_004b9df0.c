/*
 * Program: i76.exe
 * Function: zfsf_payload_wrapper_context_helper_004b9df0
 * Entry: 004b9df0
 * Signature: undefined __stdcall zfsf_payload_wrapper_context_helper_004b9df0(void)
 */


/* cgpt label refinement v20: was zfsf_record_payload_wrapper_context_helper_004b9df0. Shorten
   readability label. */

void zfsf_payload_wrapper_context_helper_004b9df0(void)

{
  HeapDestroy(g_resource_key_table_heap_handle);
  g_resource_key_table_heap_handle = (HANDLE)0x0;
  return;
}


