/*
 * Program: i76.exe
 * Function: register_world_object_tree_callback
 * Entry: 00457290
 * Signature: undefined __cdecl register_world_object_tree_callback(undefined4 param_1)
 */


/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Appends a world/object tree
   callback pointer to the global callback list. */

void __cdecl register_world_object_tree_callback(undefined4 param_1)

{
  (&g_world_object_tree_callbacks)[g_world_object_tree_callback_count] = param_1;
  g_world_object_tree_callback_count = g_world_object_tree_callback_count + 1;
  return;
}


