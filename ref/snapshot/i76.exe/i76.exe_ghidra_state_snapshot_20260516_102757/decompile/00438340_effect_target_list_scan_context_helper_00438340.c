/*
 * Program: i76.exe
 * Function: effect_target_list_scan_context_helper_00438340
 * Entry: 00438340
 * Signature: undefined __cdecl effect_target_list_scan_context_helper_00438340(float * param_1, float param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was effect_target_scan_target_list_scan_helper_00438340. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl
effect_target_list_scan_context_helper_00438340(float *param_1,float param_2,float param_3)

{
  float fVar1;
  
  fVar1 = _DAT_004bd090;
  *param_1 = param_2;
  if (fVar1 < param_2) {
    param_1[1] = _DAT_004bd094 / param_2;
  }
  fVar1 = _DAT_004bd090;
  param_1[4] = param_3;
  if (fVar1 < param_3) {
    param_1[5] = param_2 / param_3;
    return;
  }
  param_1[5] = 1e+10;
  return;
}


