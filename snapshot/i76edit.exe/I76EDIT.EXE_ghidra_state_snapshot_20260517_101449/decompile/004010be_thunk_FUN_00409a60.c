/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409a60
 * Entry: 004010be
 * Signature: undefined __cdecl thunk_FUN_00409a60(int * param_1)
 */


void __cdecl thunk_FUN_00409a60(int *param_1)

{
  int *_Memory;
  
  _Memory = (int *)param_1[2];
  thunk_FUN_0041c480(&DAT_00439be8 + *_Memory,param_1);
  _free(_Memory);
  return;
}


