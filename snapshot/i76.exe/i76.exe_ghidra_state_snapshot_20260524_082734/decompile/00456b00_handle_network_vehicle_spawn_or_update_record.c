/*
 * Program: i76.exe
 * Function: handle_network_vehicle_spawn_or_update_record
 * Entry: 00456b00
 * Signature: undefined __cdecl handle_network_vehicle_spawn_or_update_record(short param_1, short * param_2)
 */


/* cgpt rename v2: Processes a network vehicle spawn/update record, writes missing vehicle data,
   creates vehicle entity, and updates chunk lookup. */

void __cdecl handle_network_vehicle_spawn_or_update_record(short param_1,short *param_2)

{
  size_t sVar1;
  short sVar2;
  int iVar3;
  char *pcVar4;
  short *psVar5;
  longlong lVar6;
  undefined8 uVar7;
  float local_c;
  float local_8;
  float local_4;
  
  psVar5 = (short *)0x0;
  multiplayer_player_count_context_helper_00454620(*param_2,(uchar *)0x0);
  if ((*param_2 == DAT_00541028) &&
     (sVar2 = get_multiplayer_message_source_player_id(), sVar2 != param_1)) {
    return;
  }
  lVar6 = multiplayer_player_table_context_helper_00454800(*param_2);
  if (lVar6 != 0) {
    if (*(int *)(param_2 + 4) == -1) {
      return;
    }
    param_2[2] = 0;
    param_2[3] = 0;
  }
  if (((*param_2 != DAT_00541028) &&
      (iVar3 = multiplayer_player_table_context_helper_004547c0(*param_2), iVar3 != 0)) &&
     ((*(byte *)(*(int *)(iVar3 + 0x70) + 0x454) & 0x20) == 0)) {
    return;
  }
  sVar1 = *(size_t *)(param_2 + 2);
  if ((sVar1 != 0) && (psVar5 = param_2 + 8, *(int *)(param_2 + 4) == -1)) {
    uVar7 = write_network_vehicle_file(psVar5,sVar1);
    multiplayer_player_vehicle_lookup_helper_00454750
              (*param_2,(int)uVar7,(int)((ulonglong)uVar7 >> 0x20),0);
    return;
  }
  pcVar4 = load_or_create_player_vehicle_entity
                     (CONCAT22((short)(sVar1 >> 0x10),*param_2),*(int *)(param_2 + 4),0,psVar5,sVar1
                     );
  local_c = (float)*(double *)(pcVar4 + 0x40);
  local_8 = (float)*(double *)(pcVar4 + 0x48);
  local_4 = (float)*(double *)(pcVar4 + 0x50);
  chunk_manager_lookup_or_remove_entry(&local_c,20.0);
  return;
}


