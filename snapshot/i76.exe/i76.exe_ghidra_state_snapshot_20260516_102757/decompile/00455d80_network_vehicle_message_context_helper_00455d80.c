/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00455d80
 * Entry: 00455d80
 * Signature: undefined __stdcall network_vehicle_message_context_helper_00455d80(void)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00455d80.
   Remove duplicated network wording. */

void network_vehicle_message_context_helper_00455d80(void)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_005419b0 != DAT_00541828) {
    uVar1 = DAT_005419b0 + 1 & 0x1f;
    uVar2 = DAT_00541828 + 1 & 0x1f;
    DAT_00541828 = uVar2;
    DAT_005419b0 = uVar1;
    (&DAT_00541830)[uVar2 * 3] = (&DAT_00541830)[uVar1 * 3];
    (&DAT_00541834)[uVar2 * 3] = (&DAT_00541834)[uVar1 * 3];
    *(undefined4 *)(&DAT_00541838 + uVar2 * 0xc) = *(undefined4 *)(&DAT_00541838 + uVar1 * 0xc);
  }
  return;
}


