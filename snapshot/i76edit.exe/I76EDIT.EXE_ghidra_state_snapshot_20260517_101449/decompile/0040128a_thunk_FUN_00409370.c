/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409370
 * Entry: 0040128a
 * Signature: undefined __cdecl thunk_FUN_00409370(int param_1, int param_2)
 */


void __cdecl thunk_FUN_00409370(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = _malloc(param_2 * param_1 * 8 + 8);
  *piVar1 = param_1;
  piVar1[1] = param_2;
  return;
}


