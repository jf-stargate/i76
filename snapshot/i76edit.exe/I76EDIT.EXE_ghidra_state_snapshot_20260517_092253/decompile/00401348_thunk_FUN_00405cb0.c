/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00405cb0
 * Entry: 00401348
 * Signature: undefined4 __cdecl thunk_FUN_00405cb0(undefined4 param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00405cb0(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  
  puVar2 = &DAT_00439a50;
  for (iVar1 = 0x50; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  DAT_00439b90 = 0xffffffff;
  DAT_00439b98 = 0xffffffff;
  DAT_00439b94 = 0xffffffff;
  DAT_00439b9c = 0xffffffff;
  uVar4 = CONCAT44(param_3 >> 0x10,param_3) & 0xffffffff0000ffff;
  uVar3 = thunk_FUN_0040c580((int)uVar4,(int)(uVar4 >> 0x20));
  iVar1 = (int)((ulonglong)uVar3 >> 0x20);
  DAT_00434438 = 1;
  if (DAT_00434434 != 5) {
    thunk_FUN_00406950((int)uVar3,iVar1);
    return 1;
  }
  DAT_00439b90 = (int)uVar3;
  DAT_00439b94 = iVar1;
  return 1;
}


