/*
 * Program: i76.exe
 * Function: force_feedback_runtime_helper_00445b10
 * Entry: 00445b10
 * Signature: undefined __stdcall force_feedback_runtime_helper_00445b10(void)
 */


/* cgpt label refinement v18: was player_force_feedback_force_feedback_helper_00445b10. Remove
   duplicated force_feedback wording. */

void force_feedback_runtime_helper_00445b10(void)

{
  if (g_runtime_parameter_heap_ready != 0) {
    shutdown_force_feedback_dll();
    HeapDestroy(g_runtime_parameter_heap);
    g_runtime_parameter_heap = (HANDLE)0x0;
  }
  return;
}


