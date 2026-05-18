/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00421be0
 * Entry: 004010eb
 * Signature: undefined __cdecl thunk_FUN_00421be0(uint param_1, uint param_2)
 */


void __cdecl thunk_FUN_00421be0(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = thunk_FUN_0041f150(param_1,param_2);
  uVar2 = thunk_FUN_0041f2b0(param_1,param_2,1);
  if (uVar2 == 0x8000) {
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
      if (DAT_0043c12c == 3) {
        thunk_FUN_0041f3a0(param_1,param_2,(short)((int)uVar1 / (int)uVar3),1);
        thunk_FUN_0041f4a0(param_1,param_2,0,0);
        return;
      }
      thunk_FUN_0041f4a0(param_1,param_2,0,0);
      return;
    }
  }
  else if ((-1 < (int)uVar1) && ((int)uVar1 < 6)) {
    if (DAT_0043c12c == 3) {
      thunk_FUN_0041f4a0(param_1,param_2,0,0);
      return;
    }
    thunk_FUN_0041f4a0(param_1,param_2,(short)DAT_004379fc,0);
  }
  return;
}


