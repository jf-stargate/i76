/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494c80
 * Entry: 00494c80
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00494c80(float * param_1, float * param_2, float * param_3, float * param_4)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494c80. Remove
   duplicated zone_satellite_map wording. */

void __cdecl
zone_satellite_map_context_helper_00494c80
          (float *param_1,float *param_2,float *param_3,float *param_4)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  
  fVar4 = (param_4[2] - param_2[2]) * (param_3[1] - param_2[1]) -
          (param_4[1] - param_2[1]) * (param_3[2] - param_2[2]);
  fVar2 = (*param_4 - *param_2) * (param_3[2] - param_2[2]) -
          (param_4[2] - param_2[2]) * (*param_3 - *param_2);
  fVar3 = (param_4[1] - param_2[1]) * (*param_3 - *param_2) -
          (*param_4 - *param_2) * (param_3[1] - param_2[1]);
  dVar1 = (double)(fVar3 * fVar3 + fVar2 * fVar2 + fVar4 * fVar4);
  fVar6 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  fVar5 = (float)fVar6;
  *param_1 = fVar4 * fVar5;
  param_1[1] = fVar2 * fVar5;
  param_1[2] = fVar3 * fVar5;
  return;
}


