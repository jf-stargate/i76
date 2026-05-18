/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00402e70
 * Entry: 00401316
 * Signature: undefined __cdecl thunk_FUN_00402e70(float * param_1, float * param_2, float * param_3, float * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00402e70(float *param_1,float *param_2,float *param_3,float *param_4)

{
  _DAT_01641ec0 = ((*param_2 - *param_3) * _DAT_00432018 - *param_1) + *param_4;
  _DAT_01641ec4 = (*param_2 * _DAT_0043201c + *param_3 + *param_1) * _DAT_00432018;
  _DAT_01641ec8 = (*param_2 - *param_1) * _DAT_00432018;
  _DAT_01641ecc = *param_1;
  _DAT_01641ea0 = ((param_2[1] - param_3[1]) * _DAT_00432018 - param_1[1]) + param_4[1];
  _DAT_01641ea4 = (param_2[1] * _DAT_0043201c + param_3[1] + param_1[1]) * _DAT_00432018;
  _DAT_01641ea8 = (param_2[1] - param_1[1]) * _DAT_00432018;
  _DAT_01641eac = param_1[1];
  return;
}


