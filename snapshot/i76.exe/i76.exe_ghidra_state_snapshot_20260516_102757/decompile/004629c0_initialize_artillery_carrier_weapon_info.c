/*
 * Program: i76.exe
 * Function: initialize_artillery_carrier_weapon_info
 * Entry: 004629c0
 * Signature: undefined __stdcall initialize_artillery_carrier_weapon_info(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: artillery weapon info */

void initialize_artillery_carrier_weapon_info(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  undefined3 extraout_var;
  undefined4 *puVar5;
  int iVar6;
  
  iVar6 = 0;
  if (0 < g_network_weapon_runtime_actor_count) {
    puVar5 = &g_network_weapon_runtime_actor_entries;
    do {
      iVar1 = *(int *)*puVar5;
      iVar2 = *(int *)(*(int *)(iVar1 + 0x70) + 0x508);
      iVar4 = collect_vehicle_weapon_runtime_slots(iVar1,(int *)(iVar2 + 0xc));
      if (iVar4 != 1) {
        report_chunk_parse_error();
      }
      iVar4 = copy_weapon_runtime_state_summary(*(int *)(iVar2 + 0x10),(undefined4 *)(iVar2 + 0x2c))
      ;
      if (iVar4 != 1) {
        report_chunk_parse_error();
      }
      set_weapon_runtime_state_field_04(iVar1,*(int *)(iVar2 + 0x10),0);
      bVar3 = weapon_runtime_slot_belongs_to_world_object(*(int *)(iVar2 + 0x10),iVar1);
      if (CONCAT31(extraout_var,bVar3) == 0) {
        report_chunk_parse_error();
      }
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar6 < g_network_weapon_runtime_actor_count);
  }
  g_network_weapon_runtime_actor_table_dirty = 0;
  return;
}


