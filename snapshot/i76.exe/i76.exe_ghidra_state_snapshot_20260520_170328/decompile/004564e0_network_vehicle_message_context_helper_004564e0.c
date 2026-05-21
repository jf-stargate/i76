/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004564e0
 * Entry: 004564e0
 * Signature: undefined __stdcall network_vehicle_message_context_helper_004564e0(void)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004564e0.
   Remove duplicated network wording. */

void network_vehicle_message_context_helper_004564e0(void)

{
  undefined2 uVar1;
  undefined2 extraout_var;
  float10 fVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  undefined2 local_14;
  undefined1 local_12;
  float local_10;
  
  fVar2 = get_network_or_session_runtime_seconds();
  local_10 = (float)fVar2;
  puVar4 = &local_14;
  uVar5 = 8;
  uVar3 = 0;
  local_14 = 0xcc43;
  local_12 = 0;
  uVar1 = get_multiplayer_mission_sync_player_id();
  dpSend(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),uVar1,uVar3,puVar4,uVar5);
  return;
}


