/*
 * Program: i76shell.dll
 * Function: show_vehicle_weight_limit_warning
 * Entry: 100076d0
 * Signature: undefined __stdcall show_vehicle_weight_limit_warning(void)
 */


void show_vehicle_weight_limit_warning(void)

{
  if (DAT_10051fb8 != (undefined4 *)0x0) {
    FUN_100366b0(DAT_10051fb8);
  }
  if (DAT_10051fb4 != (undefined4 *)0x0) {
    FUN_10036640(DAT_10051fb4);
    return;
  }
  return;
}


