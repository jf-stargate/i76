/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409b80
 * Entry: 00401393
 * Signature: undefined4 __cdecl thunk_FUN_00409b80(int param_1, int param_2)
 */


undefined4 __cdecl thunk_FUN_00409b80(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(iVar1 + 0x1c);
  if ((((0x4f < iVar2) && (iVar2 < 0x54)) || (iVar2 == 0xc)) && (param_2 % 0x5a != 0)) {
    *(int *)(iVar1 + 0x18) = param_2 - param_2 % 0x5a;
    return 1;
  }
  *(int *)(iVar1 + 0x18) = param_2;
  return 1;
}


