/*
 * Program: i76.exe
 * Function: show_init_graphics_error_dialog
 * Entry: 00471580
 * Signature: undefined __cdecl show_init_graphics_error_dialog(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: strings Init_Graphic_System / Gold Edition */

void __cdecl show_init_graphics_error_dialog(char *param_1)

{
  int iVar1;
  undefined4 local_404;
  char local_400 [1024];
  
  _vsnprintf(local_400,0x400,param_1,&stack0x00000008);
  if (DAT_0058d934 != 0) {
    release_and_show_mouse_cursor();
    local_404 = DAT_005dd360;
    DAT_005dd360 = 0;
    iVar1 = (*DAT_005dd2cc)(&DAT_005dcec0,0);
    if (iVar1 == 0) {
      report_error();
    }
    (*DAT_005dd2e4)(&DAT_005dcec0,0);
    (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_00643620);
    (*DAT_005dd2e0)(&DAT_005dcec0);
  }
  iVar1 = MessageBoxA(DAT_005dcf7c,local_400,s_Interstate__76_Gold_Edition_004c2680,0x31);
  if (iVar1 != 2) {
    if (DAT_0058d934 != 0) {
      DAT_005dd360 = local_404;
      iVar1 = (*DAT_005dd2cc)(&DAT_005dcec0,local_404);
      if (iVar1 == 0) {
        report_error();
      }
      (*DAT_005dd2c8)(&DAT_005dcec0,&DAT_005dcfa8);
      (*DAT_005dd2e0)(&DAT_005dcec0);
      capture_and_hide_mouse_cursor();
    }
    return;
  }
  update_or_clear_input_binding_state_after_poll();
                    /* WARNING: Subroutine does not return */
  exit(1);
}


