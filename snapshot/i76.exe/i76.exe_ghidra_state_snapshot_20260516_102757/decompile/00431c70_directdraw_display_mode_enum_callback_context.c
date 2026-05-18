/*
 * Program: i76.exe
 * Function: directdraw_display_mode_enum_callback_context
 * Entry: 00431c70
 * Signature: undefined4 __stdcall directdraw_display_mode_enum_callback_context(void)
 */


/* cgpt label refinement v18: was display_mode_enum_callback_context_helper_00431c70. Refine generic
   display label to the DirectDraw display-mode enumeration callback neighborhood. */

undefined4 directdraw_display_mode_enum_callback_context(void)

{
  if (DAT_005280cc != 0) {
    DAT_005280cc = 0;
    (**(code **)(*DAT_006080c4 + 0x80))(DAT_006080c4,0);
  }
  return 1;
}


