/*
 * Program: i76.exe
 * Function: initialize_fsm_vehicle_runtime_system
 * Entry: 00409bd0
 * Signature: undefined __stdcall initialize_fsm_vehicle_runtime_system(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: Initializes FSM/vehicle runtime globals, team
   vehicle buckets, bridge validation, world-object callbacks, FSM helper subsystems, and default
   runtime state. */

void initialize_fsm_vehicle_runtime_system(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  initialize_bridge_validation_node_pool();
  puVar2 = &DAT_00507da0;
  for (iVar1 = 0x200; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00508da8;
  for (iVar1 = 0x200; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  DAT_0051f5c4 = 0;
  puVar2 = &DAT_0051f5d0;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  entity_instance_id_allocate_context_helper_00457270(initialize_fsm_runtime_heap_and_tables);
  register_world_object_tree_callback(&LAB_00409980);
  _DAT_0051f5f4 = 0;
  DAT_0051f608 = 0;
  DAT_0051f60c = 0;
  DAT_0051f610 = 0;
  DAT_0051f614 = 0;
  DAT_0051f618 = 0;
  DAT_0051f61c = 0;
  DAT_0051f620 = 0;
  DAT_0051f624 = 0;
  DAT_0051f628 = 0;
  DAT_0051f62c = 0;
  DAT_0051f630 = 0;
  DAT_0051f634 = 0;
  DAT_0051f638 = 0;
  DAT_0051f63c = 0;
  reset_vehicle_damage_source_event_state();
  initialize_fsm_runtime_progress_counters();
  reset_fsm_instruction_minmax_state();
  reset_serialized_fsm_table_reader_state();
  initialize_fsm_tactics_weight_tables();
  DAT_0051f5c8 = 0;
  DAT_0051f5cc = 0;
  DAT_0051f5bc = 0;
  DAT_0051f5b8 = 0;
  DAT_0051f604 = 0;
  DAT_0051f5b0 = 0;
  DAT_00508da0 = 0;
  DAT_0051f5c0 = 0;
  _DAT_0051f600 = 1;
  DAT_0051f5fc = 0xffffffff;
  _DAT_005095a8 = 0x7f7fffff;
  return;
}


