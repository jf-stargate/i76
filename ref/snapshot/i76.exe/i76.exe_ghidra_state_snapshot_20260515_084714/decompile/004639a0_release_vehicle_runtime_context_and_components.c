/*
 * Program: i76.exe
 * Function: release_vehicle_runtime_context_and_components
 * Entry: 004639a0
 * Signature: undefined __cdecl release_vehicle_runtime_context_and_components(LPVOID param_1)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Class-id 1 release callback.
   Releases child/component world objects for engine/brake/suspension/wheels/special parts and then
   releases vehicle runtime context. */

void __cdecl release_vehicle_runtime_context_and_components(LPVOID param_1)

{
  LPVOID pvVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if ((*(uint *)((int)param_1 + 0x454) & 0x80000) != 0) {
    puVar3 = (undefined4 *)((int)param_1 + 0x3a8);
    iVar2 = 0x18;
    do {
      if ((LPVOID)*puVar3 != (LPVOID)0x0) {
        finalize_released_world_object_after_damage((LPVOID)*puVar3,s_vhcl_004f8124);
      }
      puVar3 = puVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  pvVar1 = *(LPVOID *)((int)param_1 + 0x3c4);
  draw_classifier_display(pvVar1);
  unlink_and_release_world_object_node_refcounted(pvVar1,s_vhcl_004f8124);
  pvVar1 = *(LPVOID *)((int)param_1 + 0x3cc);
  *(undefined4 *)((int)param_1 + 0x3c4) = 0;
  draw_classifier_display(pvVar1);
  unlink_and_release_world_object_node_refcounted(pvVar1,s_vhcl_004f8124);
  pvVar1 = *(LPVOID *)((int)param_1 + 0x3c8);
  *(undefined4 *)((int)param_1 + 0x3cc) = 0;
  draw_classifier_display(pvVar1);
  unlink_and_release_world_object_node_refcounted(pvVar1,s_vhcl_004f8124);
  pvVar1 = *(LPVOID *)((int)param_1 + 0x3c0);
  *(undefined4 *)((int)param_1 + 0x3c8) = 0;
  draw_classifier_display(pvVar1);
  unlink_and_release_world_object_node_refcounted(pvVar1,s_vhcl_004f8124);
  *(undefined4 *)((int)param_1 + 0x3c0) = 0;
  release_vehicle_runtime_context(param_1);
  return;
}


