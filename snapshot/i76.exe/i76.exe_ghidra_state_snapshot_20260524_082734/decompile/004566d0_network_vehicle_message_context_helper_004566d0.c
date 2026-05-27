/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004566d0
 * Entry: 004566d0
 * Signature: int __cdecl network_vehicle_message_context_helper_004566d0(undefined4 param_1)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004566d0.
   Remove duplicated network wording. */

int __cdecl network_vehicle_message_context_helper_004566d0(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_00542420 == 0x280) {
    return -1;
  }
  (&DAT_005419d0)[DAT_00542420] = param_1;
  iVar1 = DAT_00542420;
  DAT_00542420 = DAT_00542420 + 1;
  return iVar1;
}


