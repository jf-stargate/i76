/*
 * Program: i76.exe
 * Function: initialize_class_07_runtime_from_object_tree
 * Entry: 0046d210
 * Signature: undefined __cdecl initialize_class_07_runtime_from_object_tree(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl initialize_class_07_runtime_from_object_tree(int param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  LPVOID pvVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  if (*(int *)(param_1 + 0x68) == 0) {
    pvVar4 = (LPVOID)0x0;
    for (iVar5 = *(int *)(param_1 + 100); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x60)) {
      pvVar4 = (LPVOID)target_reticle_context_helper_00458f40(iVar5,7);
      if (pvVar4 != (LPVOID)0x0) goto LAB_0046d248;
    }
    if (pvVar4 == (LPVOID)0x0) {
      return;
    }
LAB_0046d248:
    puVar6 = *(undefined4 **)((int)pvVar4 + 0x70);
    puVar7 = *(undefined4 **)(param_1 + 0x70);
    for (iVar5 = 0x28; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    draw_classifier_display(pvVar4);
  }
  else {
    iVar5 = get_root_ancestor_world_object(param_1);
    if (*(int *)(iVar5 + 0x6c) == 7) {
      return;
    }
  }
  dVar1 = *(double *)(param_1 + 0x40);
  iVar5 = *(int *)(param_1 + 0x70);
  dVar2 = *(double *)(param_1 + 0x48);
  dVar3 = *(double *)(param_1 + 0x50);
  *(float *)(iVar5 + 0x84) = (float)dVar1;
  *(float *)(iVar5 + 0x88) = (float)dVar2;
  *(float *)(iVar5 + 0x8c) = (float)dVar3;
  *(float *)(iVar5 + 0x6c) = (float)dVar1;
  *(float *)(iVar5 + 0x70) = (float)dVar2;
  *(float *)(iVar5 + 0x74) = (float)dVar3;
  transform_vec3_array_by_matrix
            ((float *)(iVar5 + 0x78),(float *)(iVar5 + 0x78),1,(float *)(param_1 + 0x18));
  *(float *)(iVar5 + 0x94) = _DAT_004be37c / *(float *)(iVar5 + 0x94);
  return;
}


