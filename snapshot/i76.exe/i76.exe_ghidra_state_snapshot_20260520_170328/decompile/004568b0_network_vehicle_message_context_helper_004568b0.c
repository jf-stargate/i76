/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004568b0
 * Entry: 004568b0
 * Signature: undefined __cdecl network_vehicle_message_context_helper_004568b0(uint param_1)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004568b0.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_004568b0(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1;
  multiplayer_chat_ui_context_helper_004541b0(param_1);
  lookup_multiplayer_player_vehicle_config_id((short)uVar1,&param_1);
  param_1 = param_1 & 0xfffffffe;
  multiplayer_player_record_lookup_helper_004546c0((short)uVar1,param_1);
  return;
}


