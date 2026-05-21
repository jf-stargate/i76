/*
 * Program: i76shell.dll
 * Function: open_network_provider_choice_dialog
 * Entry: 1002c1c0
 * Signature: undefined __stdcall open_network_provider_choice_dialog(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void open_network_provider_choice_dialog(void)

{
  DAT_100f21bc = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_100f21bc,0x1004b360,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f21bc,0x1004b374,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f21bc,0x1004b388,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100f21bc,0x1004b39c,(undefined *)0x0);
  _DAT_1004b410 = 0xf;
  _DAT_1004b414 = 0x32;
  _DAT_1004b408 = 0xab;
  _DAT_1004b40c = 0xec;
  DAT_1004b430 = 0xffffffff;
  _DAT_1004b420 = *(undefined4 *)(DAT_100f21a8 + 4 + DAT_100f1d5c * 0x1c);
  _DAT_1004b400 = 0xeb;
  _DAT_1004b404 = 0x7a;
  _DAT_1004b424 = &LAB_1002bf90;
  _DAT_1004b428 = &LAB_1002c080;
  _DAT_1004b42c = DAT_100f21bc;
  open_modal_scroll_list_dialog((int *)&DAT_1004b400,9);
  return;
}


