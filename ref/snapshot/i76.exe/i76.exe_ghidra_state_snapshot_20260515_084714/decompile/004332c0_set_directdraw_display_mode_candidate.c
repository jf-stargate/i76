/*
 * Program: i76.exe
 * Function: set_directdraw_display_mode_candidate
 * Entry: 004332c0
 * Signature: undefined4 __cdecl set_directdraw_display_mode_candidate(undefined4 param_1, undefined4 param_2, undefined4 param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
set_directdraw_display_mode_candidate(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  DAT_00608400 = param_1;
  DAT_00608404 = param_2;
  DAT_00608408 = param_3;
  _DAT_005fd500 = 1;
  DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x54))(DAT_006080b8,param_1,param_2,param_3);
  _DAT_005fd500 = 0;
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_SetDisplayMode_to__dx_dx_d_faile_004f11d8);
    return 0;
  }
  return 1;
}


