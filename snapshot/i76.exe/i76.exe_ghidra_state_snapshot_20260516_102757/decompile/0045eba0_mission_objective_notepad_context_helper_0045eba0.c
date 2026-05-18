/*
 * Program: i76.exe
 * Function: mission_objective_notepad_context_helper_0045eba0
 * Entry: 0045eba0
 * Signature: undefined __stdcall mission_objective_notepad_context_helper_0045eba0(void)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_mission_objective_notepad_helper_0045eba0. Shorten
   readability label. */

void mission_objective_notepad_context_helper_0045eba0(void)

{
  if (g_world_object_node_heap != (HANDLE)0x0) {
    HeapDestroy(g_world_object_node_heap);
  }
  if (DAT_0054ad38 != (HANDLE)0x0) {
    HeapDestroy(DAT_0054ad38);
  }
  return;
}


