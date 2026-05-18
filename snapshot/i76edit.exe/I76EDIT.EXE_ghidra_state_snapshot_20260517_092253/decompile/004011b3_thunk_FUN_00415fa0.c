/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415fa0
 * Entry: 004011b3
 * Signature: undefined __cdecl thunk_FUN_00415fa0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00415fa0(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x34) - *(float *)(param_1 + 0x10);
  *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x38) - *(float *)(param_1 + 0x14);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x10) - *(float *)(param_1 + 0x34);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x14) - *(float *)(param_1 + 0x38);
  fVar1 = SQRT(*(float *)(param_1 + 0x24) * *(float *)(param_1 + 0x24) +
               *(float *)(param_1 + 0x20) * *(float *)(param_1 + 0x20) +
               *(float *)(param_1 + 0x1c) * *(float *)(param_1 + 0x1c));
  if (_DAT_00432168 < fVar1) {
    *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) / fVar1;
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) / fVar1;
  }
  fVar1 = SQRT(*(float *)(param_1 + 0x30) * *(float *)(param_1 + 0x30) +
               *(float *)(param_1 + 0x2c) * *(float *)(param_1 + 0x2c) +
               *(float *)(param_1 + 0x28) * *(float *)(param_1 + 0x28));
  if (_DAT_00432168 < fVar1) {
    fVar2 = (*(float *)(param_1 + 0x2c) / fVar1) * _DAT_0043217c;
    *(float *)(param_1 + 0x28) = (*(float *)(param_1 + 0x28) / fVar1) * _DAT_0043217c;
    *(float *)(param_1 + 0x2c) = fVar2;
  }
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x10);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x20);
  *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x34);
  *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x2c);
  return;
}


