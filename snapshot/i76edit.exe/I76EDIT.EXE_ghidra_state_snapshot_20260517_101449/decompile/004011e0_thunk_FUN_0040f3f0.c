/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f3f0
 * Entry: 004011e0
 * Signature: undefined __cdecl thunk_FUN_0040f3f0(int * param_1)
 */


void __cdecl thunk_FUN_0040f3f0(int *param_1)

{
  void *_Memory;
  
  _Memory = (void *)param_1[2];
  thunk_FUN_0041c480(&DAT_0163ce60,param_1);
  _free(_Memory);
  return;
}


