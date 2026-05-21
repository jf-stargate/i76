/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00493ca0
 * Entry: 00493ca0
 * Signature: undefined __cdecl zone_satellite_map_context_helper_00493ca0(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float * param_7, float * param_8)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00493ca0. Remove
   duplicated zone_satellite_map wording. */

void __cdecl
zone_satellite_map_context_helper_00493ca0
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float *param_7,float *param_8)

{
  float fVar1;
  
  fVar1 = (param_6 * param_3 + param_5 * param_2 + param_4 * param_1) /
          (param_6 * param_6 + param_5 * param_5 + param_4 * param_4);
  *param_7 = fVar1 * param_4;
  param_7[1] = param_5 * fVar1;
  param_7[2] = param_6 * fVar1;
  *param_8 = param_1 - fVar1 * param_4;
  param_8[1] = param_2 - param_5 * fVar1;
  param_8[2] = param_3 - param_6 * fVar1;
  return;
}


