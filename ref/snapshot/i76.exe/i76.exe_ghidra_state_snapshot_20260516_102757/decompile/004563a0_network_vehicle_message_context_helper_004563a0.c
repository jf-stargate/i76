/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004563a0
 * Entry: 004563a0
 * Signature: undefined __cdecl network_vehicle_message_context_helper_004563a0(undefined4 param_1, undefined4 * param_2, undefined2 param_3)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004563a0.
   Remove duplicated network wording. */

void __cdecl
network_vehicle_message_context_helper_004563a0
          (undefined4 param_1,undefined4 *param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined2 extraout_var;
  float10 fVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  undefined2 local_20;
  undefined1 local_1e;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined2 local_10;
  undefined2 local_e;
  
  fVar2 = get_gameplay_runtime_seconds();
  local_1c = (float)fVar2;
  local_14 = *param_2;
  local_18 = param_1;
  puVar4 = &local_20;
  local_10 = *(undefined2 *)(param_2 + 1);
  uVar5 = 0x14;
  uVar3 = 0;
  local_20 = 0x4853;
  local_1e = 0;
  local_e = param_3;
  uVar1 = get_multiplayer_mission_sync_player_id();
  dpSend(DAT_00541024,CONCAT22(extraout_var,DAT_00541028),uVar1,uVar3,puVar4,uVar5);
  return;
}


