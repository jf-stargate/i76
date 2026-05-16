/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004905e0
 * Entry: 004905e0
 * Signature: undefined __stdcall terrain_map_context_helper_004905e0(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004905e0. Remove
   duplicated terrain wording. */

void terrain_map_context_helper_004905e0(void)

{
  if (DAT_00654398 != (LPVOID)0x0) {
    system_cutscene_memory_context_helper_00498a00(DAT_00654398);
  }
  if (DAT_006543b0 != (LPVOID)0x0) {
    system_cutscene_memory_context_helper_00498a00(DAT_006543b0);
  }
  if (DAT_006543bc != (LPVOID)0x0) {
    system_cutscene_memory_context_helper_00498a00(DAT_006543bc);
  }
  if (DAT_00654388 != (LPVOID)0x0) {
    system_cutscene_memory_context_helper_00498a00(DAT_00654388);
  }
  if (DAT_006543b4 != (LPVOID)0x0) {
    xfree_global_heap(DAT_006543b4);
  }
  return;
}


