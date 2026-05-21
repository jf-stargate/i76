/*
 * Program: i76shell.dll
 * Function: open_vehicle_part_category_screen
 * Entry: 1000a5e0
 * Signature: undefined __stdcall open_vehicle_part_category_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void open_vehicle_part_category_screen(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined *puVar11;
  undefined4 *puVar12;
  
  iVar10 = DAT_100cc500;
  DAT_100533b8 = (int *)allocate_shell_ui_object_0x20();
  *DAT_100533b8 = 0x10;
  DAT_100533b8[1] = 0x60;
  DAT_100533b8[2] = 0x260;
  DAT_100533b8[3] = 0x120;
  DAT_100533b8[4] = 0;
  DAT_100533b8[5] = 0;
  DAT_100533b8[7] = (int)redraw_vehicle_config_screen;
  piVar5 = create_pointer_list_default_16();
  puVar11 = &DAT_100440f0;
  DAT_100533b8[6] = (int)piVar5;
  do {
    insert_pointer_list_item_sorted_or_append(DAT_100533b8[6],(int)puVar11,(undefined *)0x0);
    puVar11 = puVar11 + 0x18;
  } while ((int)puVar11 < 0x10044199);
  bVar4 = false;
  while (((iVar10 != 0 && (iVar10 != DAT_100cc500)) || (!bVar4))) {
    *(undefined4 *)(iVar10 + 0x18) = 0;
    iVar10 = *(int *)(iVar10 + 4);
    bVar4 = true;
  }
  _DAT_10044104 = DAT_100d1dac;
  _DAT_1004411c = DAT_100d1db0;
  _DAT_10044134 = DAT_100d1db4;
  _DAT_1004414c = DAT_100d1db8;
  _DAT_10044164 = DAT_100d1dbc;
  _DAT_1004417c = DAT_100d1dc0;
  DAT_100533c4 = create_pointer_list_with_capacity(0x40);
  DAT_100533b0 = calculate_current_vehicle_config_weight();
  iVar10 = DAT_100533b8[2];
  iVar1 = DAT_100533b8[3];
  iVar2 = DAT_100533b8[1];
  iVar3 = *DAT_100533b8;
  puVar6 = HeapAlloc(DAT_10051c50,1,iVar10 * 0xc);
  if (puVar6 != (undefined4 *)0x0) {
    puVar12 = puVar6;
    for (uVar8 = iVar10 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
      *puVar12 = 0xf0f0f0f;
      puVar12 = puVar12 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar12 = 0xf;
      puVar12 = (undefined4 *)((int)puVar12 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar6,iVar3 + 0xc,iVar1 + iVar2,iVar10,0xc);
    HeapFree(DAT_10051c50,1,puVar6);
  }
  puVar6 = HeapAlloc(DAT_10051c50,1,iVar1 * 0xc);
  if (puVar6 != (undefined4 *)0x0) {
    puVar12 = puVar6;
    for (uVar8 = iVar1 * 3 & 0x3fffffff; uVar8 != 0; uVar8 = uVar8 - 1) {
      *puVar12 = 0xf0f0f0f;
      puVar12 = puVar12 + 1;
    }
    for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined1 *)puVar12 = 0xf;
      puVar12 = (undefined4 *)((int)puVar12 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar6,iVar10 + iVar3,iVar2 + 0xc,0xc,iVar1);
    HeapFree(DAT_10051c50,1,puVar6);
  }
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,6,*DAT_100533b8,DAT_100533b8[1],
             DAT_100533b8[2],DAT_100533b8[3]);
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
  uVar7 = lock_shell_surface_for_draw((int)DAT_100cc518);
  if ((char)uVar7 == '\0') {
    blit_or_fill_rect_clipped
              ((int *)((int)DAT_100cc518 + 0x6c),0,0,(int *)&DAT_10053380,0,0,0xffffffff);
    unlock_shell_surface_after_draw((int)DAT_100cc518);
  }
  puVar11 = &DAT_100440f0;
  do {
    redraw_vehicle_part_dialog_list_entries((int)puVar11);
    puVar11 = puVar11 + 0x18;
  } while ((int)puVar11 < 0x10044169);
  DAT_100d21a4 = &LAB_10009830;
  return;
}


