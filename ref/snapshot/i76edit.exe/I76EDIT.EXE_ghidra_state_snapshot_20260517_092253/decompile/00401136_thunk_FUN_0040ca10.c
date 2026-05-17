/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ca10
 * Entry: 00401136
 * Signature: undefined __stdcall thunk_FUN_0040ca10(void)
 */


void thunk_FUN_0040ca10(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_01641978;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    thunk_FUN_0040c990(piVar2);
    piVar2 = piVar1;
  }
  DAT_01641978 = (int *)0x0;
  return;
}


