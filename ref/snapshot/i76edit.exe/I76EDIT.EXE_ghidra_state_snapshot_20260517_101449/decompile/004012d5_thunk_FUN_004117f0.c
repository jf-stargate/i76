/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004117f0
 * Entry: 004012d5
 * Signature: undefined __cdecl thunk_FUN_004117f0(undefined4 * param_1, undefined4 param_2, uint param_3)
 */


void __cdecl thunk_FUN_004117f0(undefined4 *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = param_2;
    param_1 = param_1 + 1;
  }
  return;
}


