/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004565b0
 * Entry: 004565b0
 * Signature: undefined __cdecl network_vehicle_message_context_helper_004565b0(short param_1, char * param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004565b0.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_004565b0(short param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined2 local_20c [4];
  uint local_204;
  char local_200 [512];
  
  get_runtime_time_seconds();
  if (param_1 == 0) {
    param_1 = get_multiplayer_mission_sync_player_id();
  }
  local_204 = 0xffffffff;
  pcVar3 = param_2;
  do {
    if (local_204 == 0) break;
    local_204 = local_204 - 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_204 = ~local_204;
  local_20c[0] = 0x4843;
  pcVar3 = local_200;
  for (uVar2 = local_204 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)param_2;
    param_2 = param_2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar2 = local_204 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar3 = *param_2;
    param_2 = param_2 + 1;
    pcVar3 = pcVar3 + 1;
  }
  dpSend(DAT_00541024,CONCAT22((short)(local_204 + 0xc >> 0x10),DAT_00541028),param_1,1,local_20c,
         local_204 + 0xc);
  return;
}


