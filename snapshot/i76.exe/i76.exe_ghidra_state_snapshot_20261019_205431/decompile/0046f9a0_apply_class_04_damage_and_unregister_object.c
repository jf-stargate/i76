/*
 * Program: i76.exe
 * Function: apply_class_04_damage_and_unregister_object
 * Entry: 0046f9a0
 * Signature: undefined4 __cdecl apply_class_04_damage_and_unregister_object(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl apply_class_04_damage_and_unregister_object(int param_1,int param_2)

{
  uint uVar1;
  LPVOID pvVar2;
  int *piVar3;
  int iVar4;
  float local_c;
  float local_8;
  float local_4;
  
  pvVar2 = (LPVOID)get_root_ancestor_world_object(param_1);
  if ((*(byte *)(param_2 + 4) & 10) != 0) {
    **(undefined4 **)((int)pvVar2 + 0x70) = 0;
    uVar1 = *(uint *)(*(int *)((int)pvVar2 + 0x70) + 8);
    piVar3 = get_active_world_object_entry_object((int)pvVar2);
    iVar4 = rand();
    local_c = ((float)iVar4 * _DAT_004be584 - _DAT_004be588) * _DAT_004be58c;
    iVar4 = rand();
    local_8 = (float)iVar4 * _DAT_004be584 * _DAT_004be590;
    iVar4 = rand();
    local_4 = ((float)iVar4 * _DAT_004be584 - _DAT_004be588) * _DAT_004be58c;
    update_chunk_manager_runtime(pvVar2,&local_c,1,(int)piVar3);
    unregister_active_world_object_entry_and_release(piVar3);
    iVar4 = is_damage_side_effects_suppressed();
    if (iVar4 != 0) {
      network_vehicle_message_context_helper_00456710(uVar1);
    }
    return 1;
  }
  return 0;
}


