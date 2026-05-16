/*
 * Program: i76.exe
 * Function: software_raster_command_context_helper_00472400
 * Entry: 00472400
 * Signature: undefined __cdecl software_raster_command_context_helper_00472400(float * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: software raster command context helper
   based on adjacent named subsystem context. */

void __cdecl software_raster_command_context_helper_00472400(float *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (param_2 < _DAT_004be5b8) {
    param_2 = 0.5;
  }
  if (_DAT_004be5d0 < param_2) {
    param_2 = 8.0;
  }
  param_1[0xd] = param_2;
  fVar3 = (float)((*(int *)((int)param_1[0xf] + 0x24) - *(int *)((int)param_1[0xf] + 0x1c)) + 1) *
          param_2 * _DAT_004be5b8;
  fVar1 = param_1[0xb] * param_1[0xb];
  fVar2 = fVar1 - _DAT_004be5d4;
  fVar4 = param_2 * _DAT_004be5d8;
  fVar1 = fVar1 - _DAT_004be5d4;
  param_1[2] = fVar3 / param_1[0xb];
  param_1[3] = -((param_1[0xc] * fVar3) / param_1[0xb]);
  param_1[5] = SQRT(fVar2 * param_1[4] * param_2 * param_1[4] * param_2);
  param_1[6] = SQRT(fVar1 * fVar4 * fVar4);
  iVar5 = ftol();
  iVar6 = ftol();
  iVar7 = ftol();
  iVar8 = ftol();
  software_raster_command_context_helper_00472530(param_1,iVar8,iVar7,iVar6,iVar5);
  return;
}


