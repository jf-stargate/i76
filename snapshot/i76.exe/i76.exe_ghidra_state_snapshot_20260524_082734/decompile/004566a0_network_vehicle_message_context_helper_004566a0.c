/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_004566a0
 * Entry: 004566a0
 * Signature: undefined __stdcall network_vehicle_message_context_helper_004566a0(void)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_004566a0.
   Remove duplicated network wording. */

void network_vehicle_message_context_helper_004566a0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005419d0;
  for (iVar1 = 0x280; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_005423d0;
  for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_00542420 = 0;
  DAT_005419c8 = 0;
  return;
}


