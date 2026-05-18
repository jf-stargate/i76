/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456410
 * Entry: 00456410
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456410(undefined4 param_1)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456410.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_00456410(undefined4 param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar2;
  float10 fVar3;
  undefined2 local_18;
  char local_16;
  float local_14;
  float local_10;
  
  fVar3 = get_network_or_session_runtime_seconds();
  local_18 = 0x5858;
  bVar1 = is_local_multiplayer_sync_player_current();
  uVar2 = 8;
  local_16 = (CONCAT31(extraout_var,bVar1) != 0) + '\x03';
  local_14 = (float)fVar3;
  bVar1 = is_local_multiplayer_sync_player_current();
  if (CONCAT31(extraout_var_00,bVar1) != 0) {
    fVar3 = get_gameplay_runtime_seconds();
    local_10 = (float)fVar3;
    uVar2 = 0xc;
  }
  dpSend(DAT_00541024,DAT_00541028,param_1,0,&local_18,uVar2);
  return;
}


