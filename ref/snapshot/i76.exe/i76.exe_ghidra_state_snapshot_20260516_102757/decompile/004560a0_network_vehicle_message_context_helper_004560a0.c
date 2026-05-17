/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004560a0
 * Entry: 004560a0
 * Signature: undefined __cdecl network_vehicle_message_context_helper_004560a0(undefined4 param_1, undefined4 param_2, undefined4 param_3)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004560a0.
   Remove duplicated network wording. */

void __cdecl
network_vehicle_message_context_helper_004560a0
          (undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  float10 fVar1;
  undefined2 local_1c;
  undefined1 local_1a;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  fVar1 = get_gameplay_runtime_seconds();
  local_18 = (float)fVar1;
  local_14 = param_2;
  local_10 = param_3;
  local_1c = 0x444a;
  local_1a = 0;
  dpSend(DAT_00541024,DAT_00541028,param_1,0,&local_1c,0x10);
  return;
}


