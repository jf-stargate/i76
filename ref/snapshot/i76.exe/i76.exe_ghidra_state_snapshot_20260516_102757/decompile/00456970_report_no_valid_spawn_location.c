/*
 * Program: i76.exe
 * Function: report_no_valid_spawn_location
 * Entry: 00456970
 * Signature: undefined __cdecl report_no_valid_spawn_location(uint param_1, uint * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Cannot find a valid spawn location */

void __cdecl report_no_valid_spawn_location(uint param_1,uint *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  longlong lVar6;
  short sVar7;
  size_t local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  undefined1 local_200 [512];
  
  local_21c = 0x200;
  bVar5 = false;
  bVar1 = is_local_multiplayer_sync_player_current();
  if (CONCAT31(extraout_var,bVar1) != 0) {
    sVar7 = (short)param_1;
    lVar6 = multiplayer_player_table_context_helper_00454800(sVar7);
    if (lVar6 == 0) {
      network_vehicle_message_context_helper_00456760(param_1);
    }
    uVar2 = get_spawn_location_or_report_missing();
    if ((*param_2 & 0x80000000) != 0) {
      network_vehicle_message_context_helper_00456220(param_1,sVar7,0,0,uVar2,0);
      iVar3 = multiplayer_player_table_context_helper_004547c0(sVar7);
      if (iVar3 != 0) {
        multiplayer_respawn_timer_context_helper_00451540(iVar3,uVar2);
      }
    }
    iVar3 = multiplayer_player_table_context_helper_004547c0(sVar7);
    if ((iVar3 == 0) || ((*(byte *)(*(int *)(iVar3 + 0x70) + 0x454) & 0x20) != 0)) {
      if (uVar2 != 0xffffffff) {
        lVar6 = multiplayer_player_table_context_helper_00454800(sVar7);
        if (lVar6 == 0) {
          iVar3 = dpGetPlayerData(DAT_00541024,param_1,0,local_200,&local_21c,0);
          if (iVar3 == 0) {
            lVar6 = reject_hacked_vehicle_join(param_1,local_200,local_21c);
            if (lVar6 == 0) {
              return;
            }
          }
          else {
            bVar5 = true;
          }
        }
        if (!bVar5) {
          pcVar4 = load_or_create_player_vehicle_entity(param_1,uVar2,0,(void *)0x0,0);
          local_218 = (float)*(double *)(pcVar4 + 0x40);
          local_214 = (float)*(double *)(pcVar4 + 0x48);
          local_210 = (float)*(double *)(pcVar4 + 0x50);
          local_20c = local_218;
          local_208 = local_214;
          local_204 = local_210;
          chunk_manager_lookup_or_remove_entry(&local_20c,20.0);
          *(uint *)(*(int *)(pcVar4 + 0x70) + 0x454) =
               *(uint *)(*(int *)(pcVar4 + 0x70) + 0x454) | 0x100000;
        }
        network_vehicle_message_context_helper_00456220(param_1,sVar7,0,0,uVar2,0);
        return;
      }
      report_chunk_parse_error();
    }
  }
  return;
}


