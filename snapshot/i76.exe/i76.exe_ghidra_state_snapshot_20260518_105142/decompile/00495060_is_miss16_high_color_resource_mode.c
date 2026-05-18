/*
 * Program: i76.exe
 * Function: is_miss16_high_color_resource_mode
 * Entry: 00495060
 * Signature: bool __stdcall is_miss16_high_color_resource_mode(void)
 */


/* i76 second-pass rename
   old_name: FUN_00495060
   suggested_name: get_global_heap_handle
   basis: Tiny helper called before HeapAlloc/cache operations; likely returns global heap/context.
   
   [cgpt_i76exe_render_mode_v13] proposed=is_miss16_high_color_resource_mode :: Returns DAT_005dd2a8
   == 1. Used to select miss16 resources/high-color paths. Old name get_global_heap_handle was
   incorrect. */

bool is_miss16_high_color_resource_mode(void)

{
  return g_runtime_high_color_resource_mode == 1;
}


