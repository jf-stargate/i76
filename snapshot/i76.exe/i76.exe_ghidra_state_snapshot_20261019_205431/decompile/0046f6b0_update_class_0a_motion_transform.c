/*
 * Program: i76.exe
 * Function: update_class_0a_motion_transform
 * Entry: 0046f6b0
 * Signature: undefined __cdecl update_class_0a_motion_transform(int param_1)
 */


void __cdecl update_class_0a_motion_transform(int param_1)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  float local_40 [16];
  
  pfVar1 = *(float **)(param_1 + 0x70);
  fVar4 = get_runtime_frame_delta_seconds();
  pfVar1 = (float *)effect_target_list_scan_context_helper_004389f0
                              (local_40,(float *)(param_1 + 0x18),*pfVar1,pfVar1[1],pfVar1[2],
                               (float)fVar4);
  pfVar3 = (float *)(param_1 + 0x18);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  return;
}


