/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041ce60
 * Entry: 00401037
 * Signature: undefined4 * __cdecl thunk_FUN_0041ce60(undefined4 * param_1, float param_2, float param_3, float param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __cdecl
thunk_FUN_0041ce60(undefined4 *param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  float afStack_30 [12];
  
  uVar4 = thunk_FUN_0040f140(param_2 * _DAT_00432200);
  uStack_34 = (undefined4)((ulonglong)uVar4 >> 0x20);
  afStack_30[0] = (float)uVar4;
  fStack_40 = afStack_30[0] * param_3;
  fStack_3c = afStack_30[0] * param_4;
  fStack_38 = afStack_30[0] * param_5;
  puVar1 = (undefined4 *)thunk_FUN_0041cb50(&fStack_40,afStack_30);
  puVar3 = param_1;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  return param_1;
}


