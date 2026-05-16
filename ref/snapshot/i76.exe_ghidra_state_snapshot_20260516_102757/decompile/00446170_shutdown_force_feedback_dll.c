/*
 * Program: i76.exe
 * Function: shutdown_force_feedback_dll
 * Entry: 00446170
 * Signature: bool __stdcall shutdown_force_feedback_dll(void)
 */


/* i76 second-pass rename
   old_name: FUN_00446170
   suggested_name: shutdown_force_feedback_dll
   basis: OutputDebugString diagnostic: Unable to Exit from SWForce object. */

bool shutdown_force_feedback_dll(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (DAT_0052bbe0 != (code *)0x0) {
    iVar1 = (*DAT_0052bbe0)();
    if (iVar1 < 0) {
      OutputDebugStringA(s_Unable_to_Exit_from_SWForce_obje_004f253c);
    }
  }
  return -1 < iVar1;
}


