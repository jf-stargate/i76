/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456710
 * Entry: 00456710
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456710(uint param_1)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456710.
   Remove duplicated network wording. */

void __cdecl network_vehicle_message_context_helper_00456710(uint param_1)

{
  if ((param_1 != 0xffffffff) && ((&DAT_005419d0)[param_1] != 0)) {
    (&DAT_005419d0)[param_1] = 0;
    DAT_005419c8 = 1;
    (&DAT_005423d0)[param_1 >> 5] = (&DAT_005423d0)[param_1 >> 5] | 1 << ((byte)param_1 & 0x1f);
  }
  return;
}


