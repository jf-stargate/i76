/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040c990
 * Entry: 00401488
 * Signature: undefined __cdecl thunk_FUN_0040c990(int * param_1)
 */


void __cdecl thunk_FUN_0040c990(int *param_1)

{
  void *_Memory;
  
  _Memory = (void *)param_1[2];
  thunk_FUN_0041c480(&DAT_01641978,param_1);
  _free(_Memory);
  return;
}


