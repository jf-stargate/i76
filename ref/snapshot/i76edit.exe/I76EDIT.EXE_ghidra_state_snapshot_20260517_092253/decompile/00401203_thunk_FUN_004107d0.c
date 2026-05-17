/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004107d0
 * Entry: 00401203
 * Signature: undefined __cdecl thunk_FUN_004107d0(uint param_1, uint param_2)
 */


void __cdecl thunk_FUN_004107d0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = thunk_FUN_0041f2b0(param_1,param_2,1);
  if (uVar1 == 0x8000) {
    uVar2 = thunk_FUN_0041f2b0(param_1 - 1,param_2,1);
    uVar1 = 0;
    if (uVar2 != 0x8000) {
      uVar1 = uVar2;
    }
    uVar3 = (uint)(uVar2 != 0x8000);
    uVar2 = thunk_FUN_0041f2b0(param_1 + 1,param_2,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1,param_2 - 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1,param_2 + 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1 - 1,param_2 - 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1 + 1,param_2 + 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1 + 1,param_2 - 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    uVar2 = thunk_FUN_0041f2b0(param_1 - 1,param_2 + 1,1);
    if (uVar2 != 0x8000) {
      uVar3 = uVar3 + 1;
      uVar1 = uVar1 + uVar2;
    }
    if (uVar3 != 0) {
      thunk_FUN_0041f3a0(param_1,param_2,(short)((int)uVar1 / (int)uVar3),1);
      return;
    }
    if (uVar1 != 0) {
      thunk_FUN_0041f3a0(param_1,param_2,(short)uVar1,1);
    }
  }
  return;
}


