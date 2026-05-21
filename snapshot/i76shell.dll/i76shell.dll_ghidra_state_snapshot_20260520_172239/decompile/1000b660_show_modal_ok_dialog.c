/*
 * Program: i76shell.dll
 * Function: show_modal_ok_dialog
 * Entry: 1000b660
 * Signature: undefined __cdecl show_modal_ok_dialog(undefined * param_1)
 */


void __cdecl show_modal_ok_dialog(undefined *param_1)

{
  byte *pbVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,0x11,0xb3,0xc2,0x11a,0x5c);
  if (param_1 != (undefined *)0x0) {
    (*(code *)param_1)(0xb3,0xc2,0,0);
  }
  pbVar1 = (byte *)resolve_localized_shell_string_cached(DAT_100f5360,s_OK_100442b8);
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0x136,0x126,*(int *)(DAT_100cc52c + 0x408),pbVar1,(undefined *)0x0);
  puVar2 = HeapAlloc(DAT_10051c50,1,0x69c);
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar3 = 0x1a7; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar2,0xb9,0x11e,0x11a,6);
    HeapFree(DAT_10051c50,1,puVar2);
  }
  puVar2 = HeapAlloc(DAT_10051c50,1,0x228);
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar3 = 0x8a; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar2,0x1cd,200,6,0x5c);
    HeapFree(DAT_10051c50,1,puVar2);
  }
  flush_or_repaint_shell_surface_context((int)DAT_100cc518);
  do {
    do {
      update_debug_mouse_coordinate_overlay(DAT_100cc514);
      iVar3 = FUN_1001fb10(DAT_100cc514);
    } while (iVar3 != 1);
    iVar3 = *(int *)(DAT_100cc514 + 0x2c) + -0xb3;
    iVar4 = *(int *)(DAT_100cc514 + 0x30) + -0xc2;
  } while ((((iVar3 < 0x77) || (0xa0 < iVar3)) || (iVar4 < 0x3d)) || (0x4a < iVar4));
  clear_text_rect(DAT_100cc518,0xb3,0xc2,0x13e,0x76);
  if (DAT_100d21a8 != (code *)0x0) {
    (*DAT_100d21a8)();
  }
  return;
}


