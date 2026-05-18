/*
 * Program: i76.exe
 * Function: effect_target_list_scan_context_helper_004389f0
 * Entry: 004389f0
 * Signature: undefined __cdecl effect_target_list_scan_context_helper_004389f0(float * param_1, float * param_2, float param_3, float param_4, float param_5, float param_6)
 */


/* cgpt label refinement v18: was effect_target_scan_target_list_scan_helper_004389f0. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl
effect_target_list_scan_context_helper_004389f0
          (float *param_1,float *param_2,float param_3,float param_4,float param_5,float param_6)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float local_80 [16];
  float local_40 [16];
  
  pfVar1 = (float *)zone_satellite_map_context_helper_00493e60
                              (local_40,-(param_6 * param_3),-(param_6 * param_4),
                               -(param_6 * param_5),0.0,0.0,0.0);
  pfVar3 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar1 = compose_matrix_or_transform_a(local_40,local_80,param_2);
  pfVar3 = pfVar1;
  pfVar4 = local_80;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


