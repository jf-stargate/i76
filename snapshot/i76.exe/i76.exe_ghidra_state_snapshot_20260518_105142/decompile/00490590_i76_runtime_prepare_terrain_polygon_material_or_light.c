/*
 * Program: i76.exe
 * Function: i76_runtime_prepare_terrain_polygon_material_or_light
 * Entry: 00490590
 * Signature: undefined4 * __stdcall i76_runtime_prepare_terrain_polygon_material_or_light(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490590. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_prepare_terrain_polygon_material_or_light :: Common helper called by both
   terrain polygon render callbacks before polygon submission.
   
   [cgpt_i76exe_terrain_runtime_structs_v11]
   proposed=i76_runtime_alloc_prepare_terrain_polygon_work_record :: Returns current terrain polygon
   work record from DAT_006543c0 and clears header/list fields.
   
   [cgpt_i76exe_terrain_runtime_structs_v12]
   proposed=i76_runtime_alloc_prepare_terrain_polygon_work_record :: Returns current polygon work
   cursor, sets active pointer, clears vertex_count and linked-list next pointer. */

undefined4 * i76_runtime_prepare_terrain_polygon_material_or_light(void)

{
  g_runtime_terrain_polygon_work_record_active = g_runtime_terrain_polygon_work_record_cursor;
  g_runtime_terrain_polygon_work_record_cursor[5] = 0;
  *g_runtime_terrain_polygon_work_record_active = 0;
  return g_runtime_terrain_polygon_work_record_active;
}


