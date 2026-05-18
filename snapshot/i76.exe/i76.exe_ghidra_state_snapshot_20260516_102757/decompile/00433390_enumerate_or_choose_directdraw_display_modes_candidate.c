/*
 * Program: i76.exe
 * Function: enumerate_or_choose_directdraw_display_modes_candidate
 * Entry: 00433390
 * Signature: undefined4 __stdcall enumerate_or_choose_directdraw_display_modes_candidate(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 enumerate_or_choose_directdraw_display_modes_candidate(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 local_6c [19];
  undefined4 uStack_20;
  
  puVar1 = local_6c;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  local_6c[0] = 0x6c;
  DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x30))(DAT_006080b8,local_6c);
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_Getting_the_current_display_mode_004f1220);
    return 0;
  }
  _DAT_00608414 = local_6c[1];
  _DAT_00608418 = local_6c[0];
  DAT_0060841c = uStack_20;
  return 1;
}


