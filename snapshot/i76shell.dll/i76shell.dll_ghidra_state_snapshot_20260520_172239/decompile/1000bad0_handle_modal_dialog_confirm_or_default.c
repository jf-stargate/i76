/*
 * Program: i76shell.dll
 * Function: handle_modal_dialog_confirm_or_default
 * Entry: 1000bad0
 * Signature: undefined4 __stdcall handle_modal_dialog_confirm_or_default(void)
 */


/* i76shell first-pass rename
   old_name: FUN_1000bad0
   suggested_name: shell_screen_state_handler_a
   basis: Shell screen/state candidate; name intentionally cautious. */

undefined4 handle_modal_dialog_confirm_or_default(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,0x14,0xb3,0xc2,0x11a,0x5d);
  puVar1 = HeapAlloc(DAT_10051c50,1,0x69c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar5 = puVar1;
    for (iVar2 = 0x1a7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0xb9,0x11e,0x11a,6);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  puVar1 = HeapAlloc(DAT_10051c50,1,0x228);
  if (puVar1 != (undefined4 *)0x0) {
    puVar5 = puVar1;
    for (iVar2 = 0x8a; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0x1cd,200,6,0x5c);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  flush_or_repaint_shell_surface_context((int)DAT_100cc518);
  while( true ) {
    do {
      update_debug_mouse_coordinate_overlay(DAT_100cc514);
      iVar2 = FUN_1001fb10(DAT_100cc514);
    } while (iVar2 != 1);
    iVar2 = *(int *)(DAT_100cc514 + 0x2c) + -0xb3;
    iVar3 = *(int *)(DAT_100cc514 + 0x30) + -0xc2;
    if ((((0x4b < iVar2) && (iVar2 < 0x83)) && (0x37 < iVar3)) && (iVar3 < 0x4a)) break;
    if (((0x96 < iVar2) && (iVar2 < 0xd1)) && ((0x37 < iVar3 && (iVar3 < 0x4a)))) {
      uVar4 = 0;
LAB_1000bc10:
      clear_text_rect(DAT_100cc518,0xb3,0xc2,0x122,0x6e);
      if (DAT_100d21a8 != (code *)0x0) {
        (*DAT_100d21a8)();
      }
      return uVar4;
    }
  }
  uVar4 = 1;
  goto LAB_1000bc10;
}


