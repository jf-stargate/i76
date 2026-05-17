/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f850
 * Entry: 004010c3
 * Signature: undefined4 __cdecl thunk_FUN_0040f850(int param_1, undefined4 param_2, char * param_3)
 */


undefined4 __cdecl thunk_FUN_0040f850(int param_1,undefined4 param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  _strncpy((char *)(iVar1 + 0x20),param_3,8);
  *(undefined1 *)(iVar1 + 0x28) = 0;
  *(undefined4 *)(iVar1 + 0x1c) = param_2;
  return 1;
}


