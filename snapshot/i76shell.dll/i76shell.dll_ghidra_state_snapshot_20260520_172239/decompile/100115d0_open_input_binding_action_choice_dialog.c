/*
 * Program: i76shell.dll
 * Function: open_input_binding_action_choice_dialog
 * Entry: 100115d0
 * Signature: undefined __cdecl open_input_binding_action_choice_dialog(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl open_input_binding_action_choice_dialog(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_1 < 0x136) && (param_2 < 0x87)) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  populate_input_binding_device_action_list(iVar1);
  if (*(int *)(DAT_10056c38 + 4) <= DAT_10056c24) {
    DAT_10056c24 = *(int *)(DAT_10056c38 + 4) + -1;
  }
  DAT_10056c30 = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c30,0x100462c8,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c30,0x100462dc,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c30,0x100462f0,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_10056c30,0x10046304,(undefined *)0x0);
  _DAT_10046280 = 0x16;
  _DAT_10046284 = 0x30;
  DAT_100462a0 = 0xffffffff;
  _DAT_10046290 = *(undefined4 *)(DAT_10056c38 + 4);
  _DAT_10046270 = 0x140 - DAT_10046278 / 2;
  _DAT_10046274 = 0xf0 - DAT_1004627c / 2;
  _DAT_10046294 = &LAB_10010ad0;
  _DAT_10046298 = &LAB_10011520;
  _DAT_1004629c = DAT_10056c30;
  set_modal_list_previous_callback(&LAB_100115a0);
  open_modal_scroll_list_dialog_with_selection((int *)&DAT_10046270,0x10,DAT_10056c24);
  return;
}


