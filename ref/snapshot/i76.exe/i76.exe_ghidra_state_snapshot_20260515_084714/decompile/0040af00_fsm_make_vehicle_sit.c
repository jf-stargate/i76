/*
 * Program: i76.exe
 * Function: fsm_make_vehicle_sit
 * Entry: 0040af00
 * Signature: undefined __cdecl fsm_make_vehicle_sit(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: only vehicles can sit / dead car sit */

void __cdecl fsm_make_vehicle_sit(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar1 == 0) {
    report_chunk_parse_error();
    return;
  }
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = get_vehicle_damage_event_state_block(iVar1);
  if ((*(int *)(iVar2 + 4) == 0) && ((*(byte *)(iVar1 + 0x454) & 0x20) != 0)) {
    *(undefined4 *)(iVar2 + 4) = 1;
    report_chunk_parse_error();
  }
  *(undefined4 *)(iVar1 + 0xe0) = 0;
  *(undefined4 *)(iVar1 + 0xe4) = 0xbf800000;
  mark_active_player_object_control_changed(param_1);
  return;
}


