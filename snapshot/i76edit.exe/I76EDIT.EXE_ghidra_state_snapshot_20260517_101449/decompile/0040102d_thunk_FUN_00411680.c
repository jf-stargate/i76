/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00411680
 * Entry: 0040102d
 * Signature: undefined4 __cdecl thunk_FUN_00411680(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
thunk_FUN_00411680(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                  int param_7)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  
  fVar3 = (float10)fsin((float10)_DAT_00432128);
  fVar1 = (float)param_1 * _DAT_00432120;
  fVar2 = (float)(fVar3 * (float10)_DAT_00432130);
  if (fVar2 < ABS((float)param_2 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  if ((float)((double)fVar3 * _DAT_00432140) < ABS((float)param_3 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  if (fVar2 < ABS((float)param_4 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  if (fVar2 < ABS((float)param_5 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  if ((float)((double)fVar3 * _DAT_00432140) < ABS((float)param_6 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  if (fVar2 < ABS((float)param_7 * _DAT_00432138 + fVar1)) {
    return 1;
  }
  return 0;
}


