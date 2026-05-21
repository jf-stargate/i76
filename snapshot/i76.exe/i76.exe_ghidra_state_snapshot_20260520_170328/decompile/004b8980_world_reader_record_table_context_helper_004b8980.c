/*
 * Program: i76.exe
 * Function: world_reader_record_table_context_helper_004b8980
 * Entry: 004b8980
 * Signature: undefined __stdcall world_reader_record_table_context_helper_004b8980(void)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context. */

void world_reader_record_table_context_helper_004b8980(void)

{
  LPVOID pvVar1;
  
  while (g_runtime_rseg_node_list_head != (LPVOID)0x0) {
    pvVar1 = *(LPVOID *)((int)g_runtime_rseg_node_list_head + 4);
    xfree_global_heap(g_runtime_rseg_node_list_head);
    g_runtime_rseg_node_list_head = pvVar1;
  }
  g_runtime_rseg_node_list_head = (LPVOID)0x0;
  return;
}


