/*
 * Program: i76shell.dll
 * Function: restore_previous_shell_dialog_state
 * Entry: 1000c160
 * Signature: undefined __cdecl restore_previous_shell_dialog_state(int param_1)
 */


void __cdecl restore_previous_shell_dialog_state(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = HeapAlloc(DAT_10051c50,1,0x468);
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = puVar1;
    for (iVar2 = 0x11a; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0xf0f0f0f;
      puVar3 = puVar3 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0xe8,0x11d,0xbc,6);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  puVar1 = HeapAlloc(DAT_10051c50,1,0x222);
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = puVar1;
    for (iVar2 = 0x88; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0xf0f0f0f;
      puVar3 = puVar3 + 1;
    }
    *(undefined2 *)puVar3 = 0xf0f;
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0x19e,200,6,0x5b);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,(-(uint)(param_1 != 1) & 0xd) + 0x12,
             0xe2,0xc2,0xbc,0x5c);
  flush_or_repaint_shell_surface_context((int)DAT_100cc518);
  return;
}


