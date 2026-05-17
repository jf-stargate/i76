/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f8c0
 * Entry: 00401294
 * Signature: undefined4 __cdecl thunk_FUN_0040f8c0(int param_1, char * param_2, char * param_3)
 */


undefined4 __cdecl thunk_FUN_0040f8c0(int param_1,char *param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  _strncpy((char *)(iVar1 + 0x6d),param_2,8);
  *(undefined1 *)(iVar1 + 0x75) = 0;
  _strncpy((char *)(iVar1 + 100),param_3,8);
  *(undefined1 *)(iVar1 + 0x6c) = 0;
  return 1;
}


