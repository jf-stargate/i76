/*
 * Program: i76.exe
 * Function: entity_instance_id_table_context_helper_004574e0
 * Entry: 004574e0
 * Signature: uint __stdcall entity_instance_id_table_context_helper_004574e0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: entity instance id table context
   helper based on prior focused closure context. */

uint entity_instance_id_table_context_helper_004574e0(void)

{
  if (g_active_world_object_entry_count == 0) {
    return 0;
  }
  do {
    DAT_0054a260 = (&DAT_00542428)[DAT_0054a260];
    if ((&g_active_world_object_entries)[DAT_0054a260 * 0x1e] != 0) break;
  } while (DAT_0054a260 < g_active_world_object_entry_count);
  return (g_active_world_object_entry_count <= DAT_0054a260) - 1 &
         (uint)(&g_active_world_object_entries + DAT_0054a260 * 0x1e);
}


