/*
 * Program: i76.exe
 * Function: dispatch_force_feedback_effect
 * Entry: 00446110
 * Signature: bool __stdcall dispatch_force_feedback_effect(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: I7FF_SIM_Effect failed */

bool dispatch_force_feedback_effect(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (DAT_0052bbe4 != (code *)0x0) {
    _s_l_004f2328 = 0x16c;
    iVar1 = (*DAT_0052bbe4)(s_l_004f2328);
    if (iVar1 < 0) {
      wsprintfA(&stack0xffffff98,s_I7FF_SIM_Effect___failed__Return_004f2510,iVar1);
      OutputDebugStringA(&stack0xffffff98);
    }
  }
  return -1 < iVar1;
}


