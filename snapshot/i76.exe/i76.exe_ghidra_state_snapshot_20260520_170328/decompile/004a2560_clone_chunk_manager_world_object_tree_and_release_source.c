/*
 * Program: i76.exe
 * Function: clone_chunk_manager_world_object_tree_and_release_source
 * Entry: 004a2560
 * Signature: LPVOID __cdecl clone_chunk_manager_world_object_tree_and_release_source(LPVOID param_1, int param_2)
 */


/* cgpt rename v2: Clones a world-object subtree for the chunk manager, copies transforms/textures,
   then releases the source subtree using the chnkmgr tag. */

LPVOID __cdecl clone_chunk_manager_world_object_tree_and_release_source(LPVOID param_1,int param_2)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (param_1 != (LPVOID)0x0) {
    pvVar3 = allocate_world_object_node(param_2);
    puVar5 = (undefined4 *)((int)param_1 + 0x18);
    puVar6 = (undefined4 *)((int)pvVar3 + 0x18);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    *(uint *)((int)pvVar3 + 0x10) = *(uint *)((int)param_1 + 0x10) & 1;
    *(undefined4 *)((int)pvVar3 + 0x5c) = 0;
    *(undefined4 *)((int)pvVar3 + 0x6c) = 0;
    *(undefined4 *)((int)pvVar3 + 0x70) = 0;
    cache_add_indexed_entry((int)param_1,(int)pvVar3);
    clone_texture_bindings_to_object((int)param_1,(uint)pvVar3);
    pvVar2 = *(LPVOID *)((int)param_1 + 100);
    while (pvVar2 != (LPVOID)0x0) {
      pvVar1 = *(LPVOID *)((int)pvVar2 + 0x60);
      clone_chunk_manager_world_object_tree_and_release_source(pvVar2,(int)pvVar3);
      pvVar2 = pvVar1;
    }
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    return pvVar3;
  }
  return (LPVOID)0x0;
}


