/*
 * Program: i76.exe
 * Function: loaded_resource_cache_find_record_helper_0046f1d0
 * Entry: 0046f1d0
 * Signature: undefined __cdecl loaded_resource_cache_find_record_helper_0046f1d0(int param_1, int param_2, float param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache find record
   helper based on adjacent named subsystem context. */

void __cdecl
loaded_resource_cache_find_record_helper_0046f1d0
          (int param_1,int param_2,float param_3,float param_4)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  float local_80 [16];
  float local_40 [16];
  
  if (((param_2 != 0) && (param_1 != 0)) && (param_4 != _DAT_004be538)) {
    pfVar4 = (float *)(param_2 + 0x18);
    pfVar1 = *(float **)(param_2 + 0x70);
    pfVar3 = pfVar4;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
    if (param_3 == 0.0) {
      fVar5 = (float10)_DAT_004be558;
    }
    else {
      fVar5 = ordnance_target_selection_context_helper_004a8930(param_1,param_3,param_2,param_4);
    }
    pfVar1 = (float *)zone_satellite_map_context_helper_00493e00(local_40,(float)-fVar5);
    pfVar3 = local_80;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar3 = pfVar3 + 1;
    }
    pfVar1 = compose_matrix_or_transform_a(local_40,local_80,pfVar4);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar4 = *pfVar1;
      pfVar1 = pfVar1 + 1;
      pfVar4 = pfVar4 + 1;
    }
  }
  return;
}


