/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408ac0
 * Entry: 00401140
 * Signature: undefined __cdecl thunk_FUN_00408ac0(int * param_1)
 */


void __cdecl thunk_FUN_00408ac0(int *param_1)

{
  void *_Memory;
  
  _Memory = (void *)param_1[2];
  thunk_FUN_0041c480(&DAT_00439be4,param_1);
  thunk_FUN_00408bc0(*(int *)((int)_Memory + 0x18),*(int *)((int)_Memory + 0x20),0,-1);
  thunk_FUN_00408bc0(*(int *)((int)_Memory + 0x1c),*(int *)((int)_Memory + 0x24),0,-1);
  _free(_Memory);
  return;
}


