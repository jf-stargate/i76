/*
 * Program: i76shell.dll
 * Function: handle_modal_dialog_escape_or_cancel
 * Entry: 1000bdd0
 * Signature: int __cdecl handle_modal_dialog_escape_or_cancel(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl handle_modal_dialog_escape_or_cancel(int param_1)

{
  undefined4 *lpMem;
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined4 *puStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,0x13,0xbf,0x53,0x103,0x13a);
  lpMem = HeapAlloc(DAT_10051c50,1,0x612);
  if (lpMem != (undefined4 *)0x0) {
    puVar5 = lpMem;
    for (iVar3 = 0x184; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0xf0f0f0f;
      puVar5 = puVar5 + 1;
    }
    *(undefined2 *)puVar5 = 0xf0f;
    fill_shell_surface_rect_from_buffer(DAT_100cc518,lpMem,0xc5,0x18d,0x103,6);
    HeapFree(DAT_10051c50,1,lpMem);
  }
  FUN_100090e0(0x1c2,0x59,6,0x13a);
  _DAT_10053380 = (undefined4 *)0x0;
  DAT_10053398 = (LPVOID)0x0;
  _DAT_10053384 = 0;
  _DAT_1005339c = 0;
  _DAT_10053388 = 0;
  _DAT_100533a0 = 0;
  _DAT_1005338c = 0;
  _DAT_100533a4 = 0;
  _DAT_10053390 = 0;
  _DAT_100533a8 = 0;
  DAT_10053398 = HeapAlloc(DAT_10051c50,9,
                           *(int *)((int)DAT_100cc518 + 0x3c0) * *(int *)((int)DAT_100cc518 + 0x3bc)
                          );
  _DAT_1005339c = *(undefined4 *)((int)DAT_100cc518 + 0x48);
  _DAT_100533a0 = *(undefined4 *)((int)DAT_100cc518 + 0x4c);
  _DAT_10053384 = 0;
  _DAT_10053388 = 0;
  _DAT_1005338c = 0x27f;
  _DAT_10053390 = 0x1df;
  _DAT_10053380 = &DAT_10053398;
  uVar1 = lock_shell_surface_for_draw((int)DAT_100cc518);
  if ((char)uVar1 == '\0') {
    blit_or_fill_rect_clipped
              ((int *)((int)DAT_100cc518 + 0x6c),0,0,(int *)&DAT_10053380,0,0,0xffffffff);
    unlock_shell_surface_after_draw((int)DAT_100cc518);
  }
  measure_and_draw_string_from_glyph_sheet
            (DAT_100cc518,0xe4,*(int *)(&DAT_100441bc + param_1 * 0x14) + 0x53,
             *(int *)(DAT_100cc52c + 0x408),&DAT_100442bc,(undefined *)0x0);
  piVar2 = create_pointer_list_default_16();
  puVar4 = &DAT_100441b0;
  do {
    insert_pointer_list_item_sorted_or_append((int)piVar2,(int)puVar4,(undefined *)0x0);
    puVar4 = puVar4 + 0x14;
  } while ((int)puVar4 < 0x10044278);
  do {
    while( true ) {
      do {
        flush_or_repaint_shell_surface_context((int)DAT_100cc518);
        update_debug_mouse_coordinate_overlay(DAT_100cc514);
        (**(code **)(DAT_10058198 + 0x28))(0);
        iVar3 = FUN_1001fb10(DAT_100cc514);
      } while (iVar3 != 1);
      iVar3 = hit_test_ui_object_list_by_point
                        ((int)piVar2,*(int *)(DAT_100cc514 + 0x2c) + -0xbf,
                         *(int *)(DAT_100cc514 + 0x30) + -0x53);
      if ((7 < iVar3) || (iVar3 < 0)) break;
      uStack_10 = 0xbf;
      uStack_c = 0x53;
      uStack_8 = 0x186;
      uStack_4 = 0x17e;
      puStack_14 = &DAT_10053398;
      uVar1 = lock_shell_surface_for_draw((int)DAT_100cc518);
      if ((char)uVar1 == '\0') {
        blit_or_fill_rect_clipped
                  ((int *)&puStack_14,0,0,(int *)((int)DAT_100cc518 + 0x6c),0xbf,0x53,0xffffffff);
        blit_or_fill_rect_clipped
                  ((int *)&puStack_14,0,0,(int *)((int)DAT_100cc518 + 0xa8),0xbf,0x53,0xffffffff);
        unlock_shell_surface_after_draw((int)DAT_100cc518);
      }
      mark_shell_surface_dirty_rect(DAT_100cc518,0xbf,0x53,200,300);
      measure_and_draw_string_from_glyph_sheet
                (DAT_100cc518,0xe4,*(int *)(&DAT_100441bc + iVar3 * 0x14) + 0x53,
                 *(int *)(DAT_100cc52c + 0x408),&DAT_100442c0,(undefined *)0x0);
      param_1 = iVar3;
    }
    if (iVar3 == 8) goto LAB_1000c0f0;
  } while (iVar3 != 9);
  param_1 = -1;
LAB_1000c0f0:
  if (DAT_10053398 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10053398);
    DAT_10053398 = (LPVOID)0x0;
  }
  clear_pointer_list(piVar2);
  destroy_pointer_list_with_optional_item_destructor(piVar2,(undefined *)0x0);
  clear_text_rect(DAT_100cc518,0xbf,0x53,0x120,0x170);
  if (DAT_100d21a8 != (code *)0x0) {
    (*DAT_100d21a8)();
  }
  return param_1;
}


