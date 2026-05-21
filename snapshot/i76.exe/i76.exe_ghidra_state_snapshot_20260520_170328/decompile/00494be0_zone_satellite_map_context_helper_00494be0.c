/*
 * Program: i76.exe
 * Function: zone_satellite_map_context_helper_00494be0
 * Entry: 00494be0
 * Signature: undefined __fastcall zone_satellite_map_context_helper_00494be0(float * param_1, float * param_2, undefined4 * param_3)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494be0. Remove
   duplicated zone_satellite_map wording. */

void __fastcall
zone_satellite_map_context_helper_00494be0(float *param_1,float *param_2,undefined4 *param_3)

{
  int iVar1;
  double *pdVar2;
  double local_18;
  double local_10;
  double local_8;
  
  local_18 = (double)(*param_1 * *param_2 + param_2[6] * param_1[2] + param_2[3] * param_1[1] +
                     (float)*(double *)(param_2 + 10));
  local_10 = (double)(param_2[1] * *param_1 + param_2[7] * param_1[2] + param_2[4] * param_1[1] +
                     (float)*(double *)(param_2 + 0xc));
  local_8 = (double)(param_2[2] * *param_1 + param_2[8] * param_1[2] + param_2[5] * param_1[1] +
                    (float)*(double *)(param_2 + 0xe));
  pdVar2 = &local_18;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_3 = *(undefined4 *)pdVar2;
    pdVar2 = (double *)((int)pdVar2 + 4);
    param_3 = param_3 + 1;
  }
  return;
}


