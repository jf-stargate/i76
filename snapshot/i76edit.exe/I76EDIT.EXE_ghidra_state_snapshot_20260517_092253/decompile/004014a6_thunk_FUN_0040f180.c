/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f180
 * Entry: 004014a6
 * Signature: undefined __cdecl thunk_FUN_0040f180(undefined4 param_1, int * param_2, undefined2 param_3)
 */


void __cdecl thunk_FUN_0040f180(undefined4 param_1,int *param_2,undefined2 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = _malloc(0xd0);
  puVar3 = puVar1;
  for (iVar2 = 0x34; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = puVar1 + 0x1e;
    puVar4 = puVar3;
    for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    *puVar3 = param_1;
    puVar1[0x22] = (float)*param_2;
    puVar1[0x23] = (float)param_2[1];
    puVar1[0x2b] = (float)param_2[2];
    puVar1[0x2c] = (float)param_2[3];
    thunk_FUN_00415fa0((int)puVar3);
    *(undefined2 *)(puVar1 + 0x1f) = param_3;
    *(undefined2 *)((int)puVar1 + 0x7e) = 0;
    puVar1[0x20] = 0;
    puVar1[0x21] = 0;
    puVar1[0x32] = 0;
    DAT_0163ce60 = thunk_FUN_0041c430(DAT_0163ce60,(undefined4 *)0x0,(int)puVar1);
  }
  return;
}


