/*
 * Program: i76.exe
 * Function: entity_instance_id_allocate_context_helper_00457270
 * Entry: 00457270
 * Signature: undefined __cdecl entity_instance_id_allocate_context_helper_00457270(undefined4 param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: entity instance id allocate context
   helper based on prior focused closure context. */

void __cdecl entity_instance_id_allocate_context_helper_00457270(undefined4 param_1)

{
  (&g_world_object_entry_callbacks)[g_world_object_entry_callback_count] = param_1;
  g_world_object_entry_callback_count = g_world_object_entry_callback_count + 1;
  return;
}


