/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d5f0
 * Entry: 00401438
 * Signature: float10 __cdecl thunk_FUN_0040d5f0(int * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __cdecl thunk_FUN_0040d5f0(int *param_1,float param_2,float param_3)

{
  float *pfVar1;
  int iVar2;
  float fStack_4;
  
  fStack_4 = 0.0;
  iVar2 = *param_1;
  if (0 < iVar2) {
    fStack_4 = 0.0;
    pfVar1 = (float *)param_1[1];
    do {
      iVar2 = iVar2 + -1;
      fStack_4 = (pfVar1[2] - pfVar1[4]) /
                 (((pfVar1[1] - param_3) * (pfVar1[1] - param_3) +
                  (*pfVar1 - param_2) * (*pfVar1 - param_2)) * pfVar1[3] + _DAT_004320cc) + fStack_4
      ;
      pfVar1 = pfVar1 + 5;
    } while (iVar2 != 0);
  }
  if (0x457ff000 < (int)fStack_4) {
    fStack_4 = 4095.0;
  }
  if (0x80000000 < (uint)fStack_4) {
    fStack_4 = 0.0;
  }
  return (float10)fStack_4;
}


