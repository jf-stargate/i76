/*
 * Program: i76.exe
 * Function: effect_target_list_scan_context_helper_004384f0
 * Entry: 004384f0
 * Signature: undefined __cdecl effect_target_list_scan_context_helper_004384f0(double * param_1, float * param_2, float * param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was effect_target_scan_target_list_scan_helper_004384f0. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl
effect_target_list_scan_context_helper_004384f0
          (double *param_1,float *param_2,float *param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar1 = *param_3;
  fVar2 = param_3[1];
  fVar3 = param_3[2];
  fVar4 = param_2[1];
  fVar5 = param_2[2];
  fVar6 = fVar2 * param_4 * _DAT_004bd098;
  fVar7 = fVar3 * param_4 * _DAT_004bd098;
  *param_1 = (double)((*param_2 - fVar1 * param_4 * _DAT_004bd098) * param_4 + (float)*param_1);
  param_1[1] = (double)((fVar4 - fVar6) * param_4 + (float)param_1[1]);
  param_1[2] = (double)((fVar5 - fVar7) * param_4 + (float)param_1[2]);
  *param_2 = *param_2 + fVar1 * param_4;
  param_2[1] = param_2[1] + fVar2 * param_4;
  param_2[2] = param_2[2] + fVar3 * param_4;
  return;
}


