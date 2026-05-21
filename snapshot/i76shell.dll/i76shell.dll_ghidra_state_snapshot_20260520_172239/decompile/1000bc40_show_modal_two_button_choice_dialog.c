/*
 * Program: i76shell.dll
 * Function: show_modal_two_button_choice_dialog
 * Entry: 1000bc40
 * Signature: undefined4 __cdecl show_modal_two_button_choice_dialog(undefined * param_1)
 */


undefined4 __cdecl show_modal_two_button_choice_dialog(undefined *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,0xb,0x73,0x82,0x19a,0xdc);
  if (param_1 != (undefined *)0x0) {
    (*(code *)param_1)(0x73,0x82,0,0);
  }
  puVar1 = HeapAlloc(DAT_10051c50,1,0x99c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar5 = puVar1;
    for (iVar2 = 0x267; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0x79,0x15e,0x19a,6);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  puVar1 = HeapAlloc(DAT_10051c50,1,0x528);
  if (puVar1 != (undefined4 *)0x0) {
    puVar5 = puVar1;
    for (iVar2 = 0x14a; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar1,0x20d,0x88,6,0xdc);
    HeapFree(DAT_10051c50,1,puVar1);
  }
  flush_or_repaint_shell_surface_context((int)DAT_100cc518);
  while( true ) {
    do {
      update_debug_mouse_coordinate_overlay(DAT_100cc514);
      (**(code **)(DAT_10058198 + 0x28))(0);
      iVar2 = FUN_1001fb10(DAT_100cc514);
    } while (iVar2 != 1);
    iVar6 = *(int *)(DAT_100cc514 + 0x30) + -0x82;
    iVar3 = *(int *)(DAT_100cc514 + 0x2c) + -0x73;
    iVar2 = point_in_ui_object_bounds(iVar3,iVar6,0x100440c8);
    if (iVar2 != 0) break;
    iVar2 = point_in_ui_object_bounds(iVar3,iVar6,0x100440dc);
    if (iVar2 != 0) {
      uVar4 = 0;
LAB_1000bd9b:
      clear_text_rect(DAT_100cc518,0x73,0x82,0x1ac,0xee);
      if (DAT_100d21a8 != (code *)0x0) {
        (*DAT_100d21a8)();
      }
      return uVar4;
    }
  }
  uVar4 = 1;
  goto LAB_1000bd9b;
}


