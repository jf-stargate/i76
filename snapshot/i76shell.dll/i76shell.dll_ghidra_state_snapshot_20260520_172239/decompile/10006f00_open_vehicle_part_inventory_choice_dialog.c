/*
 * Program: i76shell.dll
 * Function: open_vehicle_part_inventory_choice_dialog
 * Entry: 10006f00
 * Signature: undefined __cdecl open_vehicle_part_inventory_choice_dialog(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl open_vehicle_part_inventory_choice_dialog(int param_1)

{
  DAT_10051d08 = param_1;
  DAT_100520bc = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_100520bc,0x10043590,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520bc,0x100435a4,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520bc,0x100435b8,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100520bc,0x100435cc,(undefined *)0x0);
  _DAT_100435e0 = 0x140 - DAT_100435e8 / 2;
  _DAT_100435e4 = 0xf0 - DAT_100435ec / 2;
  _DAT_1004360c = DAT_100520bc;
  _DAT_100435f0 = 0x11;
  _DAT_100435f4 = 0x30;
  DAT_10043610 = 0xffffffff;
  _DAT_10043604 = &LAB_10006ca0;
  _DAT_10043608 = &LAB_10006dc0;
  if (DAT_10051dc0 == 0) {
    _DAT_10043600 = *(int *)(DAT_100d1db8 + 4);
  }
  else {
    DAT_100520c0 = FUN_1002d540((param_1 + -3) / 2);
    _DAT_10043600 = DAT_100520c0[1];
  }
  open_modal_scroll_list_dialog_with_selection((int *)&DAT_100435e0,10,DAT_10051e90);
  return;
}


