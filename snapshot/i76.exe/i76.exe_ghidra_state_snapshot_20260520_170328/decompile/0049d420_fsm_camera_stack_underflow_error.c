/*
 * Program: i76.exe
 * Function: fsm_camera_stack_underflow_error
 * Entry: 0049d420
 * Signature: undefined __stdcall fsm_camera_stack_underflow_error(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence Camera Stack Underfow */

void fsm_camera_stack_underflow_error(void)

{
  int iVar1;
  
  iVar1 = pop_runtime_camera_state_stack();
  if (iVar1 == 0) {
    report_error();
  }
  DAT_005a7ee0 = fsm_camera_stack_underflow_error;
  DAT_005a7ed8 = 0;
  DAT_005a7edc = 0;
  g_runtime_display_mode_state = 5;
  DAT_004c2724 = 0;
  g_runtime_display_mode_change_callback = &LAB_0048e190;
  return;
}


