/*
 * Program: i76.exe
 * Function: ImmAssociateContext
 * Entry: 004ba368
 * Signature: HIMC __stdcall ImmAssociateContext(HWND param_1, HIMC param_2)
 */


HIMC ImmAssociateContext(HWND param_1,HIMC param_2)

{
  HIMC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004ba368. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = ImmAssociateContext(param_1,param_2);
  return pHVar1;
}


