/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409b60
 * Entry: 0040150a
 * Signature: undefined4 __cdecl thunk_FUN_00409b60(int param_1, undefined4 param_2)
 */


undefined4 __cdecl thunk_FUN_00409b60(int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)(param_1 + 8) + 0xc) = param_2;
  return 1;
}


