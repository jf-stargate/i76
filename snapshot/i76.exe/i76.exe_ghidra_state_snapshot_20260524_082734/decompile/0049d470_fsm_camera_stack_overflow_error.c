/*
 * Program: i76.exe
 * Function: fsm_camera_stack_overflow_error
 * Entry: 0049d470
 * Signature: undefined __stdcall fsm_camera_stack_overflow_error(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence Camera Stack 0verfow */

void fsm_camera_stack_overflow_error(void)

{
  int iVar1;
  
  iVar1 = push_runtime_camera_state_stack();
  if (iVar1 == 0) {
    report_error();
  }
  DAT_005a7ee0 = fsm_camera_stack_overflow_error;
  DAT_005a7ed8 = 0;
  DAT_005a7edc = 0;
  return;
}


