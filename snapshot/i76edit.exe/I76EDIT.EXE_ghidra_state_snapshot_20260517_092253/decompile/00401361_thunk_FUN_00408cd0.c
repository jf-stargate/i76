/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408cd0
 * Entry: 00401361
 * Signature: undefined __stdcall thunk_FUN_00408cd0(void)
 */


void thunk_FUN_00408cd0(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_00439be4;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    thunk_FUN_00408ac0(piVar2);
    piVar2 = piVar1;
  }
  DAT_00439be4 = (int *)0x0;
  return;
}


