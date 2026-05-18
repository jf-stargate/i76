/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00402f40
 * Entry: 004012c6
 * Signature: float10 __cdecl thunk_FUN_00402f40(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl thunk_FUN_00402f40(float param_1)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float fStack_10;
  float fStack_8;
  float fStack_4;
  
  fStack_8 = 1.0;
  iVar2 = 0;
  fStack_4 = 0.0;
  do {
    if (0x1f < iVar2) break;
    fStack_10 = (fStack_4 + fStack_8) * _DAT_00432020;
    fVar3 = thunk_FUN_00403020(fStack_10);
    fVar5 = (float10)_DAT_01641ecc;
    fVar4 = thunk_FUN_00403070(fStack_10);
    fVar5 = (float10)param_1 -
            SQRT((fVar4 - (float10)_DAT_01641eac) * (fVar4 - (float10)_DAT_01641eac) +
                 (float10)(float)(fVar3 - fVar5) * (float10)(float)(fVar3 - fVar5));
    fVar1 = fStack_10;
    if (fVar5 < (float10)_DAT_00432004) {
      fStack_8 = fStack_10;
      fVar1 = fStack_4;
    }
    fStack_4 = fVar1;
    iVar2 = iVar2 + 1;
  } while ((float)_DAT_00432028 < ABS((float)fVar5));
  return (float10)fStack_10;
}


