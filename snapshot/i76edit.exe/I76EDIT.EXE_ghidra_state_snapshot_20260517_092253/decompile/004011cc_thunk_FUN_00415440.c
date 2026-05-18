/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415440
 * Entry: 004011cc
 * Signature: undefined __cdecl thunk_FUN_00415440(undefined4 param_1, int * param_2, undefined2 param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00415440(undefined4 param_1,int *param_2,undefined2 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = _malloc(0x54);
  puVar3 = puVar1;
  for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[4] = (float)*param_2;
    puVar1[5] = (float)param_2[1];
    puVar1[0xd] = (float)param_2[2];
    puVar1[0xe] = (float)param_2[3];
    thunk_FUN_00415fa0((int)puVar1);
    *(undefined2 *)(puVar1 + 1) = param_3;
    *(short *)((int)puVar1 + 6) = (short)DAT_01641e8c;
    puVar1[2] = (float)_DAT_00434338;
    puVar1[3] = 0;
    puVar1[0x14] = 0;
    DAT_0043c544 = thunk_FUN_0041c430(DAT_0043c544,(undefined4 *)0x0,(int)puVar1);
  }
  return;
}


