/*
 * Program: i76.exe
 * Function: vehicle_effect_audio_update_helper_004439a0
 * Entry: 004439a0
 * Signature: undefined __cdecl vehicle_effect_audio_update_helper_004439a0(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: vehicle effect audio update helper
   based on prior focused closure context. */

void __cdecl vehicle_effect_audio_update_helper_004439a0(int param_1,float *param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float10 fVar6;
  undefined8 uVar7;
  float local_80 [4];
  undefined4 local_70;
  float local_40 [16];
  
  iVar1 = (&DAT_0052ba88)[*(int *)(param_1 + 0x1c)];
  *(int *)(param_1 + 0x1c) = iVar1;
  if (*(int *)(param_1 + 0x18) == iVar1) {
    *(undefined4 *)(param_1 + 0x18) = (&DAT_0052ba88)[*(int *)(param_1 + 0x18)];
  }
  fVar6 = get_multiplayer_or_runtime_seconds();
  *(float *)(param_1 + 0xc) = (float)(fVar6 - (float10)_DAT_004bd2c8);
  *(float *)(param_1 + 0x14) =
       (float)(&DAT_0052ba5c)[*(int *)(param_1 + 0x10) * 2] + *(float *)(param_1 + 0x14);
  iVar4 = *(int *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x10) = (&DAT_0052ba58)[*(int *)(param_1 + 0x10) * 2];
  pfVar2 = (float *)&DAT_004faed8;
  pfVar5 = local_80;
  for (iVar3 = 0x10; uVar7 = CONCAT44(local_80[0],local_80[1]), iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  if (iVar4 < 3) {
    uVar7 = mission_flow_map_context_helper_0049d400(*(float *)(param_1 + 0x14));
    local_70 = (undefined4)((ulonglong)uVar7 >> 0x20);
    local_80[3] = -(float)uVar7;
  }
  local_80[0] = (float)((ulonglong)uVar7 >> 0x20);
  local_80[1] = (float)uVar7;
  pfVar2 = compose_matrix_or_transform_a(local_40,local_80,param_2);
  pfVar5 = local_80;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  transform_vec3_array_by_matrix
            ((float *)(param_1 + 0x58 + iVar1 * 0x24),(float *)&DAT_004f1c88,3,local_80);
  return;
}


