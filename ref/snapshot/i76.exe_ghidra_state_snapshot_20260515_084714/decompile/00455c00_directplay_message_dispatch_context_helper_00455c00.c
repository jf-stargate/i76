/*
 * Program: i76.exe
 * Function: directplay_message_dispatch_context_helper_00455c00
 * Entry: 00455c00
 * Signature: undefined __stdcall directplay_message_dispatch_context_helper_00455c00(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: directplay message dispatch context
   helper based on prior focused closure context. */

void directplay_message_dispatch_context_helper_00455c00(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined2 extraout_var;
  
  if (DAT_005419b0 != DAT_00541828) {
    DAT_005419b0 = DAT_005419b0 + 1 & 0x1f;
    uVar1 = DAT_00541520;
    do {
      if (uVar1 == DAT_005419b4) {
        puVar2 = (undefined4 *)0x0;
        goto LAB_00455c65;
      }
      uVar1 = uVar1 + 1 & 0x3f;
    } while ((*(short *)(&DAT_00541528 + uVar1 * 3) != *(short *)(&DAT_00541830 + DAT_005419b0 * 3))
            || ((&DAT_0054152c)[uVar1 * 3] != (&DAT_00541834)[DAT_005419b0 * 3]));
    puVar2 = &DAT_00541528 + uVar1 * 3;
LAB_00455c65:
    if (puVar2 != (undefined4 *)0x0) {
      puVar2[2] = puVar2[2] & 0xfffffffb | 3;
    }
    send_mission_file_timestamp_over_network
              (CONCAT22((short)(DAT_005419b0 * 0xc >> 0x10),
                        *(undefined2 *)(&DAT_00541830 + DAT_005419b0 * 3)),
               (&DAT_00541834)[DAT_005419b0 * 3]);
    multiplayer_chat_ui_context_helper_004541b0
              (CONCAT22(extraout_var,*(undefined2 *)(&DAT_00541830 + DAT_005419b0 * 3)));
  }
  return;
}


