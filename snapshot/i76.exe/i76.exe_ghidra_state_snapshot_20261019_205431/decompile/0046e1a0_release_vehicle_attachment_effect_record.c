/*
 * Program: i76.exe
 * Function: release_vehicle_attachment_effect_record
 * Entry: 0046e1a0
 * Signature: undefined __cdecl release_vehicle_attachment_effect_record(undefined4 * param_1)
 */


void __cdecl release_vehicle_attachment_effect_record(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((LPVOID)*param_1 != (LPVOID)0x0) {
      xfree_global_heap((LPVOID)*param_1);
    }
    if (param_1[2] != 0) {
      iVar1 = get_root_ancestor_world_object(param_1[2]);
      if ((iVar1 != 0) && (*(int *)(iVar1 + 0x70) != 0)) {
        iVar2 = is_vehicle_or_actor_runtime_world_object(iVar1);
        if (iVar2 != 0) {
          iVar1 = *(int *)(iVar1 + 0x70);
          if (param_1[3] == 1) {
            if (*(int *)(iVar1 + 0x400) != 0) {
              *(undefined4 *)(iVar1 + 0x400) = 0;
              xfree_global_heap(param_1);
              return;
            }
          }
          else if ((param_1[3] == 2) && (*(int *)(iVar1 + 0x404) != 0)) {
            *(undefined4 *)(iVar1 + 0x404) = 0;
          }
        }
      }
    }
    xfree_global_heap(param_1);
  }
  return;
}


