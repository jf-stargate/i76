/*
 * Program: i76.exe
 * Function: update_chunk_manager_runtime
 * Entry: 004a1b60
 * Signature: undefined4 __cdecl update_chunk_manager_runtime(LPVOID param_1, float * param_2, int param_3, int param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence chnkmgr repeated */

undefined4 __cdecl
update_chunk_manager_runtime(LPVOID param_1,float *param_2,int param_3,int param_4)

{
  uint uVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  LPVOID pvVar4;
  undefined4 *puVar5;
  LPVOID pvVar6;
  int iVar7;
  undefined4 *puVar8;
  float10 fVar9;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40 [16];
  
  if (param_1 == (LPVOID)0x0) {
    return 0;
  }
  if (param_3 == 0) {
    pvVar4 = allocate_world_object_node(0);
    if (pvVar4 == (LPVOID)0x0) {
      return 0;
    }
    puVar5 = (undefined4 *)compute_transform_relative_to_ancestor(local_40,(int)param_1,0);
    puVar8 = (undefined4 *)((int)pvVar4 + 0x18);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
    }
    uVar1 = *(uint *)((int)param_1 + 0x10);
    *(undefined4 *)((int)pvVar4 + 0x5c) = 0;
    *(uint *)((int)pvVar4 + 0x10) = uVar1 & 1;
    radar_context_setup_helper_0045f310((int)param_1);
    puVar5 = &DAT_004faed8;
    puVar8 = (undefined4 *)((int)param_1 + 0x18);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
    }
    pvVar6 = allocate_world_object_node((int)pvVar4);
    puVar5 = (undefined4 *)((int)param_1 + 0x18);
    puVar8 = (undefined4 *)((int)pvVar6 + 0x18);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
    }
    *(uint *)((int)pvVar6 + 0x10) = *(uint *)((int)param_1 + 0x10) & 1;
    *(undefined4 *)((int)pvVar6 + 0x5c) = 0;
    *(undefined4 *)((int)pvVar6 + 0x6c) = 0;
    *(undefined4 *)((int)pvVar6 + 0x70) = 0;
    cache_add_indexed_entry((int)param_1,(int)pvVar6);
    clone_texture_bindings_to_object((int)param_1,(uint)pvVar6);
    pvVar3 = *(LPVOID *)((int)param_1 + 100);
    while (pvVar3 != (LPVOID)0x0) {
      pvVar2 = *(LPVOID *)((int)pvVar3 + 0x60);
      clone_chunk_manager_world_object_tree_and_release_source(pvVar3,(int)pvVar6);
      pvVar3 = pvVar2;
    }
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    *(LPVOID *)((int)pvVar4 + 100) = pvVar6;
    compute_world_object_transformed_bounds((int)pvVar6,&local_58,&local_4c);
    local_58 = (local_4c + local_58) * _DAT_004bea98;
    *(float *)((int)pvVar4 + 0x84) = local_58;
    local_54 = (local_48 + local_54) * _DAT_004bea98;
    *(float *)((int)pvVar4 + 0x88) = local_54;
    local_50 = (local_44 + local_50) * _DAT_004bea98;
    *(float *)((int)pvVar4 + 0x8c) = local_50;
    fVar9 = compute_world_object_bounding_radius_from_point
                      (*(int *)((int)pvVar4 + 100),local_58,local_54,local_50);
    *(float *)((int)pvVar4 + 0x90) = (float)fVar9;
  }
  else {
    puVar5 = (undefined4 *)compute_transform_relative_to_ancestor(local_40,(int)param_1,0);
    puVar8 = (undefined4 *)((int)param_1 + 0x18);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
    }
    radar_context_setup_helper_0045f310((int)param_1);
    pvVar4 = allocate_world_object_node(0);
    puVar5 = (undefined4 *)((int)param_1 + 0x18);
    puVar8 = (undefined4 *)((int)pvVar4 + 0x18);
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar8 = puVar8 + 1;
    }
    *(uint *)((int)pvVar4 + 0x10) = *(uint *)((int)param_1 + 0x10) & 1;
    *(undefined4 *)((int)pvVar4 + 0x5c) = 0;
    *(undefined4 *)((int)pvVar4 + 0x6c) = 0;
    *(undefined4 *)((int)pvVar4 + 0x70) = 0;
    cache_add_indexed_entry((int)param_1,(int)pvVar4);
    clone_texture_bindings_to_object((int)param_1,(uint)pvVar4);
    pvVar6 = *(LPVOID *)((int)param_1 + 100);
    while (pvVar6 != (LPVOID)0x0) {
      pvVar3 = *(LPVOID *)((int)pvVar6 + 0x60);
      clone_chunk_manager_world_object_tree_and_release_source(pvVar6,(int)pvVar4);
      pvVar6 = pvVar3;
    }
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    if (pvVar4 == (LPVOID)0x0) {
      return 0;
    }
    *(undefined4 *)((int)pvVar4 + 0x84) = *(undefined4 *)(param_4 + 4);
    *(undefined4 *)((int)pvVar4 + 0x88) = *(undefined4 *)(param_4 + 8);
    *(undefined4 *)((int)pvVar4 + 0x8c) = *(undefined4 *)(param_4 + 0xc);
    *(undefined4 *)((int)pvVar4 + 0x90) = *(undefined4 *)(param_4 + 0x10);
  }
  if ((_DAT_004bea9c <= *(float *)((int)pvVar4 + 0x90)) &&
     (set_world_object_class_and_register_runtime((int)pvVar4,0x35),
     *(int *)((int)pvVar4 + 0x70) != 0)) {
    attach_world_object_as_first_child((int)pvVar4,DAT_005aaac4);
    if (DAT_005aaac8 == (LPVOID)0x0) {
      _DAT_005aaacc = *(undefined4 *)((int)pvVar4 + 0x70);
      DAT_005aaac8 = pvVar4;
    }
    if (param_2 != (float *)0x0) {
      world_instance_id_lookup_context_helper_004ad2e0((int)pvVar4,param_2);
    }
    dispatch_queued_world_object_class_callbacks();
    return 1;
  }
  unlink_and_release_world_object_node_refcounted(pvVar4,s_chnkmgr_004fe71c);
  return 0;
}


