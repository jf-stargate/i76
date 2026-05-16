/*
 * Program: i76.exe
 * Function: ordnance_system_log_tag
 * Entry: 0049f5c0
 * Signature: undefined __stdcall ordnance_system_log_tag(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence ordnc */

void ordnance_system_log_tag(void)

{
  HANDLE hHeap;
  LPVOID pvVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_4;
  
  DAT_005a8108 = 1;
  if ((_DAT_004bea30 != _DAT_004bea34) && (iVar2 = 0, 0 < DAT_005a810c)) {
    puVar3 = &DAT_00655290;
    do {
      update_mission_runtime_object_list_and_release_expired(*(int **)(puVar3[-1] + 100),1.0,0);
      update_mission_runtime_object_list_and_release_expired((int *)*puVar3,1.0,1);
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 0x34;
    } while (iVar2 < DAT_005a810c);
  }
  local_4 = 0;
  if (0 < DAT_005a810c) {
    puVar3 = &DAT_00655284;
    do {
      iVar2 = puVar3[4];
      if ((iVar2 != 0) && (hHeap = (HANDLE)puVar3[5], iVar2 != 0)) {
        if (*(int *)(iVar2 + 100) != 0) {
          release_world_object_subtree_class_payloads(hHeap,*(int *)(iVar2 + 100));
        }
        if (*(int *)(iVar2 + 0x60) != 0) {
          release_world_object_subtree_class_payloads(hHeap,*(int *)(iVar2 + 0x60));
        }
        HeapFree(hHeap,0,*(LPVOID *)(iVar2 + 0x70));
        *(undefined4 *)(iVar2 + 0x70) = 0;
        *(undefined4 *)(iVar2 + 0x5c) = 0;
      }
      entity_instance_id_lookup_or_update((int *)puVar3[1]);
      unlink_and_release_world_object_node_refcounted((LPVOID)puVar3[2],s_ordnc_004fe6f0);
      pvVar1 = (LPVOID)puVar3[4];
      while (pvVar1 != (LPVOID)0x0) {
        puVar3[4] = *(undefined4 *)((int)pvVar1 + 0x60);
        unlink_and_release_world_object_node_refcounted(pvVar1,s_ordnc_004fe6f0);
        pvVar1 = (LPVOID)puVar3[4];
      }
      unlink_and_release_world_object_node_refcounted((LPVOID)*puVar3,s_ordnc_004fe6f0);
      puVar3[-1] = 0;
      *puVar3 = 0;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[6] = 0x32;
      puVar3[7] = 0;
      puVar3[8] = 0;
      puVar3[9] = 0;
      puVar3[10] = 0;
      puVar3[0xb] = 0;
      HeapDestroy((HANDLE)puVar3[5]);
      puVar3[4] = 0;
      puVar3[0xc] = 0;
      puVar3[0xd] = 0x3f800000;
      puVar3[0x15] = 0;
      puVar3[0x16] = 0;
      puVar3[0x18] = 0;
      puVar3[0x19] = 0;
      puVar3[0x1b] = 0;
      puVar3[0x1c] = 0;
      puVar3[0x21] = 0;
      puVar3[0x22] = 0;
      puVar3[0x27] = 0;
      puVar3[0x28] = 0;
      puVar3[0x2d] = 0;
      puVar3[0x2e] = 0;
      puVar3[0x11] = 0;
      puVar3[0x12] = 0;
      local_4 = local_4 + 1;
      puVar3[0x13] = 0;
      puVar3[0x14] = 0;
      iVar2 = DAT_005a810c;
      puVar3[0xe] = 0;
      puVar3[0x10] = 0;
      puVar3[0xf] = 0;
      puVar3 = puVar3 + 0x34;
    } while (local_4 < iVar2);
  }
  DAT_005a810c = 0;
  reset_pending_mission_vehicle_effect_spawn_heap();
  return;
}


