/*
 * Program: i76.exe
 * Function: vehicle_system_log_tag
 * Entry: 00465310
 * Signature: undefined __cdecl vehicle_system_log_tag(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: vhcl */

void __cdecl vehicle_system_log_tag(int *param_1)

{
  LPVOID pvVar1;
  
  pvVar1 = (LPVOID)*param_1;
  stop_vehicle_engine_loop_sound((int)pvVar1);
  stop_vehicle_secondary_runtime_sounds((int)pvVar1);
  entity_instance_id_lookup_or_update(param_1);
  remove_loaded_vehicle_runtime_and_weapon_slots((int)pvVar1);
  unlink_and_release_world_object_node_refcounted(pvVar1,s_vhcl_004f8124);
  return;
}


