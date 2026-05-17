/*
 * Program: i76.exe
 * Function: initialize_effect_target_system
 * Entry: 004346d0
 * Signature: undefined __stdcall initialize_effect_target_system(void)
 */


/* cgpt readability rename v13 set A: Initializes effect-target lists, registers world-object
   callbacks, creates collision heap, and clears probe lists. */

void initialize_effect_target_system(void)

{
  g_effect_target_primary_list = 0;
  g_effect_target_secondary_list = 0;
  g_effect_target_scan_current_list_head = 0;
  g_effect_target_scan_current_node = 0;
  entity_instance_id_allocate_context_helper_00457270(&LAB_00434710);
  register_world_object_tree_callback(unregister_effect_target_record);
  initialize_effect_target_collision_heap();
  clear_effect_target_surface_probe_list();
  return;
}


