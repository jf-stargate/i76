/*
 * Program: i76.exe
 * Function: weapon_ordnance_query_context_helper_004a8240
 * Entry: 004a8240
 * Signature: undefined __cdecl weapon_ordnance_query_context_helper_004a8240(uint param_1, int param_2, uint param_3)
 */


/* cgpt label refinement v20: was ordnance_weapon_query_context_helper_004a8240. Normalize query
   label ordering. */

void __cdecl weapon_ordnance_query_context_helper_004a8240(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 in_stack_00000020;
  
  if ((g_disable_radial_damage_for_optional_targets != 0) &&
     (iVar1 = world_object_has_optional_runtime_flag(param_1), iVar1 != 0)) {
    return;
  }
  dispatch_damage_context_to_world_object_class_handler(param_1,&param_2,in_stack_00000020);
  if ((param_2 != 0) && (iVar1 = is_vehicle_or_actor_runtime_world_object(param_1), iVar1 != 0)) {
    record_vehicle_damage_source_event(param_2,0x10,param_3 & 0xffff,param_1,0);
  }
  return;
}


