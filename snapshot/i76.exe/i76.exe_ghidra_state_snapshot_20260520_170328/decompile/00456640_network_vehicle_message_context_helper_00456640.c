/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456640
 * Entry: 00456640
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456640(undefined4 param_1, undefined4 param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456640.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_00456640(undefined4 param_1,undefined4 param_2)

{
  float10 fVar1;
  undefined2 local_18;
  undefined1 local_16;
  float local_14;
  undefined4 local_10;
  
  fVar1 = get_gameplay_runtime_seconds();
  local_14 = (float)fVar1;
  local_10 = param_2;
  local_18 = 0x4f42;
  local_16 = 0;
  dpSend(DAT_00541024,DAT_00541028,param_1,0,&local_18,0xc);
  return;
}


