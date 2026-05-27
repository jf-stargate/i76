/*
 * Program: i76.exe
 * Function: i76_runtime_get_active_zone_page_ptr
 * Entry: 00493c00
 * Signature: undefined4 __cdecl i76_runtime_get_active_zone_page_ptr(int param_1)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493c00. Remove
   duplicated zone_satellite_map wording.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=i76_runtime_get_active_zone_page_ptr :: Returns
   runtime .TER active-zone page pointer from DAT_005a4628[index]. */

undefined4 __cdecl i76_runtime_get_active_zone_page_ptr(int param_1)

{
  return (&g_runtime_active_zone_page_ptrs)[param_1];
}


