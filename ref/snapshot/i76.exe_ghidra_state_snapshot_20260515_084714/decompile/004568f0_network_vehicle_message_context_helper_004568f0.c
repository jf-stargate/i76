/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004568f0
 * Entry: 004568f0
 * Signature: undefined __cdecl network_vehicle_message_context_helper_004568f0(undefined4 param_1, int * param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004568f0.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_004568f0(undefined4 param_1,int *param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  
  bVar1 = is_local_multiplayer_sync_player_current();
  if ((CONCAT31(extraout_var,bVar1) != 0) && (*param_2 == 0)) {
    iVar2 = multiplayer_chat_ui_context_helper_00452e00();
    if (iVar2 != 0) {
      send_mission_file_timestamp_over_network(param_1,param_2[1]);
      multiplayer_chat_ui_context_helper_004541b0(param_1);
      return;
    }
    uVar3 = multiplayer_join_prompt_context_helper_004558c0((short)param_1,param_2[1]);
    if (uVar3 != 0) {
      if (uVar3 == 3) {
        send_mission_file_timestamp_over_network(param_1,param_2[1]);
        return;
      }
      network_vehicle_message_context_helper_004560a0(param_1,param_2[1],uVar3);
    }
  }
  return;
}


