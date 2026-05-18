/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041dc90
 * Entry: 004012da
 * Signature: undefined __cdecl thunk_FUN_0041dc90(float * param_1, float * param_2, float * param_3)
 */


void __cdecl thunk_FUN_0041dc90(float *param_1,float *param_2,float *param_3)

{
  int iVar1;
  float *pfVar2;
  float afStack_30 [4];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  afStack_30[0] = param_2[1] * param_3[3] + param_3[6] * param_2[2] + *param_3 * *param_2;
  afStack_30[1] = param_3[1] * *param_2 + param_2[1] * param_3[4] + param_2[2] * param_3[7];
  afStack_30[2] = param_3[2] * *param_2 + param_2[2] * param_3[8] + param_3[5] * param_2[1];
  afStack_30[3] = param_2[3] * *param_3 + param_3[3] * param_2[4] + param_2[5] * param_3[6];
  fStack_20 = param_3[4] * param_2[4] + param_3[1] * param_2[3] + param_2[5] * param_3[7];
  fStack_1c = param_3[5] * param_2[4] + param_3[2] * param_2[3] + param_2[5] * param_3[8];
  fStack_18 = param_2[6] * *param_3 + param_2[7] * param_3[3] + param_3[6] * param_2[8];
  fStack_14 = param_2[7] * param_3[4] + param_3[7] * param_2[8] + param_3[1] * param_2[6];
  fStack_10 = param_3[8] * param_2[8] + param_2[6] * param_3[2] + param_3[5] * param_2[7];
  fStack_c = param_2[9] * *param_3 + param_2[10] * param_3[3] + param_3[6] * param_2[0xb] +
             param_3[9];
  fStack_8 = param_2[10] * param_3[4] + param_2[0xb] * param_3[7] + param_2[9] * param_3[1] +
             param_3[10];
  fStack_4 = param_2[9] * param_3[2] + param_3[5] * param_2[10] + param_2[0xb] * param_3[8] +
             param_3[0xb];
  pfVar2 = afStack_30;
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


