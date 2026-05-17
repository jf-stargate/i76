/*
 * Program: i76.exe
 * Function: release_chunk_manager_runtime
 * Entry: 004a1e40
 * Signature: undefined4 __cdecl release_chunk_manager_runtime(LPVOID param_1, float * param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence chnkmgr */

undefined4 __cdecl release_chunk_manager_runtime(LPVOID param_1,float *param_2,float param_3)

{
  int iVar1;
  float10 fVar2;
  
  if (param_1 == (LPVOID)0x0) {
    return 0;
  }
  set_world_object_class_and_register_runtime((int)param_1,0x35);
  if (*(int *)((int)param_1 + 0x70) == 0) {
    unlink_and_release_world_object_node_refcounted(param_1,s_chnkmgr_004fe71c);
    return 0;
  }
  attach_world_object_as_first_child((int)param_1,DAT_005aaac4);
  if (DAT_005aaac8 == (LPVOID)0x0) {
    DAT_005aaac8 = param_1;
    _DAT_005aaacc = *(undefined4 *)((int)param_1 + 0x70);
  }
  iVar1 = *(int *)((int)param_1 + 0x70);
  fVar2 = get_multiplayer_or_runtime_seconds();
  *(float *)(iVar1 + 0x3c) = (float)(fVar2 + (float10)param_3);
  if (param_2 != (float *)0x0) {
    world_instance_id_lookup_context_helper_004ad2e0((int)param_1,param_2);
  }
  dispatch_queued_world_object_class_callbacks();
  return 1;
}


