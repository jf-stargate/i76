/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00455cd0
 * Entry: 00455cd0
 * Signature: undefined __stdcall network_vehicle_message_context_helper_00455cd0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: network vehicle message context helper
   based on prior focused closure context. */

void network_vehicle_message_context_helper_00455cd0(void)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (DAT_005419b0 != DAT_00541828) {
    DAT_005419b0 = DAT_005419b0 + 1 & 0x1f;
    uVar1 = DAT_00541520;
    do {
      if (uVar1 == DAT_005419b4) {
        puVar2 = (undefined4 *)0x0;
        goto LAB_00455d35;
      }
      uVar1 = uVar1 + 1 & 0x3f;
    } while ((*(short *)(&DAT_00541528 + uVar1 * 3) != *(short *)(&DAT_00541830 + DAT_005419b0 * 3))
            || ((&DAT_0054152c)[uVar1 * 3] != (&DAT_00541834)[DAT_005419b0 * 3]));
    puVar2 = &DAT_00541528 + uVar1 * 3;
LAB_00455d35:
    if (puVar2 != (undefined4 *)0x0) {
      puVar2[2] = puVar2[2] & 0xfffffffa | 2;
    }
    network_vehicle_message_context_helper_004560a0
              (CONCAT22((short)(DAT_005419b0 * 0xc >> 0x10),
                        *(undefined2 *)(&DAT_00541830 + DAT_005419b0 * 3)),
               (&DAT_00541834)[DAT_005419b0 * 3],2);
  }
  return;
}


