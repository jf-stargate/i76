/*
 * Program: i76.exe
 * Function: geometry_projection_context_helper_00479010
 * Entry: 00479010
 * Signature: undefined __cdecl geometry_projection_context_helper_00479010(float param_1, float param_2, float param_3, float * param_4, float * param_5, float * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: geometry projection context helper
   based on adjacent named subsystem context. */

void __cdecl
geometry_projection_context_helper_00479010
          (float param_1,float param_2,float param_3,float *param_4,float *param_5,float *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if ((float)_DAT_004be6a0 <= ABS(param_2)) {
    if (_DAT_004be6d8 <= param_1) {
      param_1 = 0.0;
    }
    fVar1 = param_1 * _DAT_004be6dc;
    floor((double)fVar1);
    iVar4 = ftol();
    fVar1 = fVar1 - (float)iVar4;
    fVar3 = (_DAT_004be6e0 - param_2) * param_3;
    fVar2 = (_DAT_004be6e0 - fVar1 * param_2) * param_3;
    fVar1 = (_DAT_004be6e0 - (_DAT_004be6e0 - fVar1) * param_2) * param_3;
    switch(iVar4) {
    case 0:
      *param_4 = param_3;
      *param_5 = fVar1;
      *param_6 = fVar3;
      return;
    case 1:
      *param_4 = fVar2;
      *param_5 = param_3;
      *param_6 = fVar3;
      return;
    case 2:
      *param_4 = fVar3;
      *param_5 = param_3;
      *param_6 = fVar1;
      return;
    case 3:
      *param_4 = fVar3;
      *param_5 = fVar2;
      *param_6 = param_3;
      return;
    case 4:
      *param_4 = fVar1;
      *param_5 = fVar3;
      *param_6 = param_3;
      return;
    case 5:
      *param_4 = param_3;
      *param_5 = fVar3;
      *param_6 = fVar2;
    }
  }
  else if (param_1 == _DAT_004be6ac) {
    *param_4 = param_3;
    *param_5 = param_3;
    *param_6 = param_3;
    return;
  }
  return;
}


