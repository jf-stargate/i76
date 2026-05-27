/*
 * Program: i76.exe
 * Function: is_miss16_high_color_resource_mode
 * Entry: 00495060
 * Signature: bool __stdcall is_miss16_high_color_resource_mode(void)
 */


/* [i76 level/static/material baseline v48]
   name: is_miss16_high_color_resource_mode
   confidence: high
   module: mission_color_depth
   High-color/miss16 resource-mode predicate. Prior name corrected from heap/global guess. Relevant
   to miss8 direct MAP vs miss16 M16/VQM resource differences.
   note: Name already matches baseline. */

bool is_miss16_high_color_resource_mode(void)

{
  return g_runtime_high_color_resource_mode == 1;
}


