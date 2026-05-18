/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415aa0
 * Entry: 0040107d
 * Signature: undefined __stdcall thunk_FUN_00415aa0(void)
 */


void thunk_FUN_00415aa0(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_0043c544;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    thunk_FUN_004157f0(piVar2);
    piVar2 = piVar1;
  }
  DAT_0043c544 = (int *)0x0;
  return;
}


