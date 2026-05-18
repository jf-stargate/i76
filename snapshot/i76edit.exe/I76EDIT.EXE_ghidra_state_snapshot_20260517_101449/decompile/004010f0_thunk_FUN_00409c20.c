/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409c20
 * Entry: 004010f0
 * Signature: undefined4 __cdecl thunk_FUN_00409c20(int param_1, char * param_2)
 */


undefined4 __cdecl thunk_FUN_00409c20(int param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  _strncpy((char *)(iVar1 + 0x29),param_2,0x27);
  *(undefined1 *)(iVar1 + 0x50) = 0;
  return 1;
}


