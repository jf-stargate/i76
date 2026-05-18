/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004905c0
 * Entry: 004905c0
 * Signature: undefined __stdcall terrain_map_context_helper_004905c0(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004905c0. Remove
   duplicated terrain wording. */

void terrain_map_context_helper_004905c0(void)

{
  g_runtime_terrain_polygon_work_record_cursor =
       g_runtime_terrain_polygon_work_record_cursor + 0x1c +
       *(int *)(&g_runtime_polygon_record_fixed_size_table +
               *(int *)(g_runtime_terrain_polygon_work_record_cursor + 0xc) * 4);
  return;
}


