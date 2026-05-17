/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409d00
 * Entry: 0040153c
 * Signature: undefined4 __cdecl thunk_FUN_00409d00(int param_1, undefined4 param_2)
 */


undefined4 __cdecl thunk_FUN_00409d00(int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)(param_1 + 8) + 0x60) = param_2;
  return 1;
}


