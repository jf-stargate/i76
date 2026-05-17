/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409dc0
 * Entry: 004013a7
 * Signature: undefined __cdecl thunk_FUN_00409dc0(int param_1)
 */


void __cdecl thunk_FUN_00409dc0(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = (int *)(&DAT_00439be8)[param_1];
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    thunk_FUN_00409a60(piVar2);
    piVar2 = piVar1;
  }
  (&DAT_00439be8)[param_1] = 0;
  return;
}


