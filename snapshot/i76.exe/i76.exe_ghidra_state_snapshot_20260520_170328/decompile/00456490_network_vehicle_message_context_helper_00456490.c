/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456490
 * Entry: 00456490
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456490(undefined4 param_1, undefined4 param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456490.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_00456490(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined2 local_14;
  char local_12;
  undefined4 local_10;
  
  local_14 = 0x5959;
  bVar1 = is_local_multiplayer_sync_player_current();
  local_12 = (CONCAT31(extraout_var,bVar1) != 0) + '\x03';
  local_10 = param_2;
  dpSend(DAT_00541024,DAT_00541028,param_1,0,&local_14,8);
  return;
}


