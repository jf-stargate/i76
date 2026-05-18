/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d940
 * Entry: 0040115e
 * Signature: undefined __cdecl thunk_FUN_0040d940(int param_1, int * param_2, int * param_3)
 */


void __cdecl thunk_FUN_0040d940(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = thunk_FUN_004121d0(param_1,0,0);
  iVar2 = (int)((ulonglong)uVar3 >> 0x20);
  iVar1 = (int)uVar3;
  if (iVar1 == -1) {
    *param_2 = -1;
    *param_3 = -1;
    return;
  }
  *param_2 = (int)(iVar1 + (iVar1 >> 0x1f & 0x7fU)) >> 7;
  *param_3 = (int)(iVar2 + (iVar2 >> 0x1f & 0x7fU)) >> 7;
  return;
}


