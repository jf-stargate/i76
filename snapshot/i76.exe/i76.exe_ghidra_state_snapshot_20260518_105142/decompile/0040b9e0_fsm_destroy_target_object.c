/*
 * Program: i76.exe
 * Function: fsm_destroy_target_object
 * Entry: 0040b9e0
 * Signature: undefined __cdecl fsm_destroy_target_object(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: FSM destroy called for dead car/structure
    */

void __cdecl fsm_destroy_target_object(int param_1)

{
  int iVar1;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar1 == 0) {
    iVar1 = is_transform_composed_world_object_class(param_1);
    if (iVar1 != 0) {
      if ((*(uint *)(param_1 + 0x10) & 0x200) != 0) {
        report_chunk_parse_error();
        return;
      }
      create_building_world_object_default(param_1);
    }
    return;
  }
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((*(byte *)(iVar1 + 0x454) & 0x20) != 0) {
    report_chunk_parse_error();
    return;
  }
  trigger_vehicle_forced_damage_or_actor_cleanup(param_1);
  *(undefined4 *)(iVar1 + 0xe4) = 0xbf800000;
  return;
}


