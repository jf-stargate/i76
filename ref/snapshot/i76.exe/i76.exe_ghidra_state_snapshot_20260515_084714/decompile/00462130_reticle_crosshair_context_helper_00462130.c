/*
 * Program: i76.exe
 * Function: reticle_crosshair_context_helper_00462130
 * Entry: 00462130
 * Signature: uint __stdcall reticle_crosshair_context_helper_00462130(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: reticle crosshair context helper based
   on prior focused closure context. */

uint reticle_crosshair_context_helper_00462130(void)

{
  if (g_runtime_display_input_mode == 1) {
    DAT_0054b67c = (uint)(DAT_0054b67c == 0);
    if (DAT_0054b67c != 0) {
      get_world_object_class_id(DAT_0054b684,1);
      world_object_geometry_context_helper_00458860(DAT_0054b680,1);
      return DAT_0054b67c;
    }
    world_object_geometry_context_helper_00458860(DAT_0054b684,1);
    get_world_object_class_id(DAT_0054b680,1);
  }
  return DAT_0054b67c;
}


