/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041f2b0
 * Entry: 004013c0
 * Signature: uint __cdecl thunk_FUN_0041f2b0(uint param_1, uint param_2, int param_3)
 */


uint __cdecl thunk_FUN_0041f2b0(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int aiStack_c [3];
  
  if ((-1 < (int)param_1) && (-1 < (int)param_2)) {
    if (param_3 < 99) {
      thunk_FUN_00411ba0(param_1,param_2,1);
    }
    else {
      iVar2 = thunk_FUN_00411ba0(param_1,param_2,0);
      if (iVar2 < 0) {
        return 0xffffffff;
      }
      if (param_3 == 99) {
        param_3 = 0;
      }
      if (param_3 == 100) {
        param_3 = 1;
      }
    }
    piVar3 = (int *)thunk_FUN_00412300(aiStack_c,param_1,param_2);
    iVar2 = piVar3[1];
    iVar1 = piVar3[2];
    puVar4 = thunk_FUN_00412120(*piVar3,param_3);
    return (uint)*(ushort *)((int)puVar4 + (iVar1 * 0x80 + iVar2) * 2);
  }
  return 0xffffffff;
}


