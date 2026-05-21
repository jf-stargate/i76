/*
 * Program: i76shell.dll
 * Function: destroy_vehicle_config_ui_lists
 * Entry: 10005680
 * Signature: undefined __stdcall destroy_vehicle_config_ui_lists(void)
 */


void destroy_vehicle_config_ui_lists(void)

{
  void *pvVar1;
  
  if (DAT_100520b8 != (int *)0x0) {
    clear_pointer_list(DAT_100520b8);
    destroy_pointer_list_with_optional_item_destructor(DAT_100520b8,(undefined *)0x0);
    DAT_100520b8 = (int *)0x0;
  }
  if (DAT_100520b0 != (int *)0x0) {
    clear_pointer_list(DAT_100520b0);
    destroy_pointer_list_with_optional_item_destructor(DAT_100520b0,(undefined *)0x0);
    DAT_100520b0 = (int *)0x0;
  }
  if (DAT_100520b4 != (int *)0x0) {
    clear_pointer_list(DAT_100520b4);
    destroy_pointer_list_with_optional_item_destructor(DAT_100520b4,(undefined *)0x0);
    DAT_100520b4 = (int *)0x0;
  }
  if (DAT_10051dc0 == 0) {
    FUN_10019440();
  }
  else {
    FUN_1002a900();
  }
  if (DAT_10051d04 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10051d04);
    DAT_10051d04 = (LPVOID)0x0;
  }
  if (DAT_10051cf8 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10051cf8);
    DAT_10051cf8 = (LPVOID)0x0;
  }
  if (DAT_10051d00 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10051d00);
    DAT_10051d00 = (LPVOID)0x0;
  }
  if (DAT_10051cfc != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,DAT_10051cfc);
    DAT_10051cfc = (LPVOID)0x0;
  }
  pvVar1 = DAT_10051fbc;
  if (DAT_10051fbc != (void *)0x0) {
    FUN_10036620();
    operator_delete(pvVar1);
    DAT_10051fbc = (void *)0x0;
  }
  pvVar1 = DAT_10051fb8;
  if (DAT_10051fb8 != (void *)0x0) {
    FUN_10036620();
    operator_delete(pvVar1);
    DAT_10051fb8 = (void *)0x0;
  }
  pvVar1 = DAT_10051fb4;
  if (DAT_10051fb4 != (void *)0x0) {
    FUN_10036620();
    operator_delete(pvVar1);
    DAT_10051fb4 = (void *)0x0;
  }
  pvVar1 = DAT_10051fb0;
  if (DAT_10051fb0 != (void *)0x0) {
    FUN_10036620();
    operator_delete(pvVar1);
    DAT_10051fb0 = (void *)0x0;
  }
  FUN_10019750();
  FUN_100318d0();
  return;
}


