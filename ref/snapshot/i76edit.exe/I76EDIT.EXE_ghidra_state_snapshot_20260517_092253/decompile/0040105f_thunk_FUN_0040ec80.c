/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ec80
 * Entry: 0040105f
 * Signature: undefined __cdecl thunk_FUN_0040ec80(int param_1)
 */


void __cdecl thunk_FUN_0040ec80(int param_1)

{
  int *piVar1;
  
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  piVar1 = FUN_0040ee80(param_1);
  if (piVar1 == (int *)0x0) {
    DAT_00434964 = thunk_FUN_0041c430(DAT_00434964,(undefined4 *)0x0,param_1);
    return;
  }
  thunk_FUN_0041c430(*piVar1,piVar1,param_1);
  return;
}


