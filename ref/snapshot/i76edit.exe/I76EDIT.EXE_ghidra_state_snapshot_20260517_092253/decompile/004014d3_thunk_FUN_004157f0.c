/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004157f0
 * Entry: 004014d3
 * Signature: undefined __cdecl thunk_FUN_004157f0(int * param_1)
 */


void __cdecl thunk_FUN_004157f0(int *param_1)

{
  void *_Memory;
  
  _Memory = (void *)param_1[2];
  thunk_FUN_0041c480(&DAT_0043c544,param_1);
  thunk_FUN_00415980(*(int *)((int)_Memory + 0x40),*(int *)((int)_Memory + 0x48),0,-1);
  thunk_FUN_00415980(*(int *)((int)_Memory + 0x44),*(int *)((int)_Memory + 0x4c),0,-1);
  _free(_Memory);
  return;
}


