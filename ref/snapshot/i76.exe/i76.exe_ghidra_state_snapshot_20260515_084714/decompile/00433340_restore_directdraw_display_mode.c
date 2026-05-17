/*
 * Program: i76.exe
 * Function: restore_directdraw_display_mode
 * Entry: 00433340
 * Signature: undefined4 __stdcall restore_directdraw_display_mode(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: calls RestoreDisplayMode and reports failure */

undefined4 restore_directdraw_display_mode(void)

{
  _DAT_005fd500 = 1;
  DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x4c))(DAT_006080b8);
  if (DAT_005fdc0c != 0) {
    directdraw_error_to_string(DAT_005fdc0c);
    set_directdraw_error_message(s_RestoreDisplayMode_failed___s_004f1200);
    return 0;
  }
  _DAT_005fd500 = 0;
  return 1;
}


