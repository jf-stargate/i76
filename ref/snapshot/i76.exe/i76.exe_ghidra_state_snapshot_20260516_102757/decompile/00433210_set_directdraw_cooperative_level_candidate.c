/*
 * Program: i76.exe
 * Function: set_directdraw_cooperative_level_candidate
 * Entry: 00433210
 * Signature: undefined4 __cdecl set_directdraw_cooperative_level_candidate(undefined4 param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl set_directdraw_cooperative_level_candidate(undefined4 param_1,int param_2)

{
  _DAT_005fd500 = 1;
  if (param_2 == 0) {
    DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x50))(DAT_006080b8,param_1,8);
    _DAT_005fd500 = 0;
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_SetCooperativeLevel_to_normal_fa_004f117c);
      return 0;
    }
    DAT_00608410 = 0;
    return 1;
  }
  DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x50))(DAT_006080b8,param_1,0x11);
  _DAT_005fd500 = 0;
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_SetCooperativeLevel_to_fullscree_004f11a8);
    return 0;
  }
  DAT_00608410 = 1;
  return 1;
}


