/*
 * Program: i76shell.dll
 * Function: update_vehicle_config_screen_layout_and_callbacks
 * Entry: 10005310
 * Signature: undefined __stdcall update_vehicle_config_screen_layout_and_callbacks(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void update_vehicle_config_screen_layout_and_callbacks(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_10051dc0 != 0) {
    build_vehicle_hardpoint_slot_labels();
    DAT_10051e94 = DAT_10051fac + DAT_10051f6c + DAT_10051f70;
    _DAT_1004340c = DAT_10051e94 * DAT_10051e60 + DAT_10043408;
    _DAT_1004342c = DAT_10051e64 * DAT_10051e60 + _DAT_1004340c;
    DAT_10043428 = _DAT_1004340c;
  }
  if (DAT_10051dbc != (code *)0x0) {
    (*DAT_10051dbc)(DAT_1005209c);
  }
  if (DAT_10051e9c != (code *)0x0) {
    (*DAT_10051e9c)(DAT_100520a4,DAT_100520a8,DAT_100520b0,DAT_100520b4);
  }
  if (DAT_10051f20 != (code *)0x0) {
    (*DAT_10051f20)(DAT_100520ac);
    return;
  }
  iVar2 = 0;
  do {
    iVar1 = find_pointer_list_item_index(DAT_100d1db0,*(int *)(*(int *)(DAT_100520ac + 8) + iVar2));
    if (iVar1 == -1) {
      *(undefined ***)(*(int *)(DAT_100520ac + 8) + iVar2) = &PTR_DAT_100432c0;
    }
    iVar2 = iVar2 + 4;
  } while (iVar2 < 0xc);
  return;
}


