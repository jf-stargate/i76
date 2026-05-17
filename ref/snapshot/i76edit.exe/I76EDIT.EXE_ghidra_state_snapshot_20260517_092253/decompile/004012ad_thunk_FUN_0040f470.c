/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f470
 * Entry: 004012ad
 * Signature: undefined __stdcall thunk_FUN_0040f470(void)
 */


void thunk_FUN_0040f470(void)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = DAT_0163ce60;
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    thunk_FUN_0040f3f0(piVar2);
    piVar2 = piVar1;
  }
  DAT_0163ce60 = (int *)0x0;
  return;
}


