/*
 * Program: i76.exe
 * Function: effect_target_list_scan_context_helper_00438810
 * Entry: 00438810
 * Signature: undefined __cdecl effect_target_list_scan_context_helper_00438810(float * param_1, float param_2, float param_3, float param_4, int param_5)
 */


/* cgpt label refinement v18: was effect_target_scan_target_list_scan_helper_00438810. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl
effect_target_list_scan_context_helper_00438810
          (float *param_1,float param_2,float param_3,float param_4,int param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 local_78 [6];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_3c [15];
  
  fVar1 = 0.0;
  fVar2 = 0.0;
  fVar3 = 0.0;
  for (iVar7 = param_5; iVar7 != 0; iVar7 = get_parent_if_current_is_last_child_link(iVar7)) {
    puVar6 = (undefined4 *)build_world_object_class_damage_transform(local_3c,iVar7);
    puVar9 = local_78;
    for (iVar8 = 0xf; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar9 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar9 = puVar9 + 1;
    }
    fVar4 = (local_4c * param_3 - local_50 * param_4) + fVar1;
    fVar5 = (local_54 * param_4 - local_4c * param_2) + fVar2;
    fVar3 = (local_50 * param_2 - local_54 * param_3) + fVar3;
    fVar1 = *(float *)(iVar7 + 0x24) * fVar5 +
            *(float *)(iVar7 + 0x30) * fVar3 + fVar4 * *(float *)(iVar7 + 0x18) + local_60;
    fVar2 = *(float *)(iVar7 + 0x1c) * fVar4 +
            *(float *)(iVar7 + 0x34) * fVar3 + *(float *)(iVar7 + 0x28) * fVar5 + local_5c;
    fVar3 = *(float *)(iVar7 + 0x20) * fVar4 +
            *(float *)(iVar7 + 0x2c) * fVar5 + *(float *)(iVar7 + 0x38) * fVar3 + local_58;
    transform_vec3_array_by_matrix(&param_2,&param_2,1,(float *)(iVar7 + 0x18));
  }
  *param_1 = fVar1;
  param_1[1] = fVar2;
  param_1[2] = fVar3;
  return;
}


