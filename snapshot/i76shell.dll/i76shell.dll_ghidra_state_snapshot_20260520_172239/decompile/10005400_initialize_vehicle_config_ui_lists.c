/*
 * Program: i76shell.dll
 * Function: initialize_vehicle_config_ui_lists
 * Entry: 10005400
 * Signature: undefined __stdcall initialize_vehicle_config_ui_lists(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void initialize_vehicle_config_ui_lists(void)

{
  undefined *puVar1;
  int iVar2;
  undefined **ppuVar3;
  
  DAT_10051e60 = *(int *)(DAT_100cc52c + 0x40c) + 2;
  if (DAT_100520b8 != (int *)0x0) {
    update_vehicle_config_screen_layout_and_callbacks();
    redraw_vehicle_config_screen();
    return;
  }
  build_vehicle_hardpoint_slot_labels();
  DAT_10051e94 = DAT_10051f6c + DAT_10051fac + DAT_10051f70;
  DAT_100520b8 = create_pointer_list_default_16();
  puVar1 = &DAT_100433d8;
  do {
    insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,(int)puVar1,(undefined *)0x0);
    puVar1 = puVar1 + 0x20;
  } while ((int)puVar1 < 0x100434f9);
  if (DAT_10051dc0 == 0) {
    insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x10043538,(undefined *)0x0);
    remove_pointer_list_item((int)DAT_100520b8,0x100434d8);
  }
  else {
    insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x10043518,(undefined *)0x0);
  }
  DAT_1005209c = create_pointer_list_with_capacity(7);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x100433d8,(undefined *)0x0);
  _DAT_100433f4 = DAT_1005209c;
  DAT_100520a4 = create_pointer_list_with_capacity(6);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x100433f8,(undefined *)0x0);
  DAT_10043414 = DAT_100520a4;
  DAT_100520a8 = create_pointer_list_with_capacity(4);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x10043418,(undefined *)0x0);
  DAT_10043434 = DAT_100520a8;
  DAT_100520ac = create_pointer_list_with_capacity(3);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x10043438,(undefined *)0x0);
  DAT_10043454 = DAT_100520ac;
  if (DAT_10051dc0 == 0) {
    insert_pointer_list_item_sorted_or_append((int)DAT_100520b8,0x10043458,(undefined *)0x0);
    _DAT_10043474 = DAT_100520a0;
  }
  if (DAT_10051e1c != (code *)0x0) {
    (*DAT_10051e1c)(DAT_1005209c);
  }
  _DAT_1004340c = DAT_10051e94 * DAT_10051e60 + DAT_10043408;
  _DAT_1004342c = DAT_10051e64 * DAT_10051e60 + _DAT_1004340c;
  DAT_10043428 = _DAT_1004340c;
  DAT_100520b0 = create_pointer_list_with_capacity(0x40);
  DAT_100520b4 = create_pointer_list_default_16();
  if (DAT_10051fa8 != (code *)0x0) {
    (*DAT_10051fa8)(DAT_100520a4,DAT_100520a8,DAT_100520b0,DAT_100520b4);
  }
  if (DAT_10051e98 != (code *)0x0) {
    (*DAT_10051e98)(DAT_100520ac);
    redraw_vehicle_config_screen();
    return;
  }
  iVar2 = 0;
  do {
    if (iVar2 < DAT_100520ac[1]) {
      ppuVar3 = *(undefined ***)(*(int *)(DAT_100d1db0 + 8) + iVar2 * 4);
    }
    else {
      ppuVar3 = &PTR_DAT_100432c0;
    }
    insert_pointer_list_item_sorted_or_append((int)DAT_100520ac,(int)ppuVar3,(undefined *)0x0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 3);
  redraw_vehicle_config_screen();
  return;
}


