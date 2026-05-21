/*
 * Program: i76shell.dll
 * Function: destroy_vehicle_part_category_lists
 * Entry: 10034e60
 * Signature: undefined __stdcall destroy_vehicle_part_category_lists(void)
 */


void destroy_vehicle_part_category_lists(void)

{
  if (DAT_100d1dac != (int *)0x0) {
    clear_pointer_list(DAT_100d1dac);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1dac,(undefined *)0x0);
    DAT_100d1dac = (int *)0x0;
  }
  if (DAT_100d1dc0 != (int *)0x0) {
    clear_pointer_list(DAT_100d1dc0);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1dc0,(undefined *)0x0);
    DAT_100d1dc0 = (int *)0x0;
  }
  if (DAT_100d1dbc != (int *)0x0) {
    clear_pointer_list(DAT_100d1dbc);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1dbc,(undefined *)0x0);
    DAT_100d1dbc = (int *)0x0;
  }
  if (DAT_100d1db8 != (int *)0x0) {
    clear_pointer_list(DAT_100d1db8);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1db8,(undefined *)0x0);
    DAT_100d1db8 = (int *)0x0;
  }
  if (DAT_100d1db4 != (int *)0x0) {
    clear_pointer_list(DAT_100d1db4);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1db4,(undefined *)0x0);
    DAT_100d1db4 = (int *)0x0;
  }
  if (DAT_100d1db0 != (int *)0x0) {
    clear_pointer_list(DAT_100d1db0);
    destroy_pointer_list_with_optional_item_destructor(DAT_100d1db0,(undefined *)0x0);
    DAT_100d1db0 = (int *)0x0;
  }
  if (DAT_100f5308 != (LPVOID)0x0) {
    destroy_pointer_list_with_optional_item_destructor(DAT_100f5308,(undefined *)0x0);
    DAT_100f5308 = (LPVOID)0x0;
  }
  return;
}


