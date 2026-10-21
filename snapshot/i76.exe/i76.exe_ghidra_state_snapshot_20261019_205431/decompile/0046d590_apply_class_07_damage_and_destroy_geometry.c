/*
 * Program: i76.exe
 * Function: apply_class_07_damage_and_destroy_geometry
 * Entry: 0046d590
 * Signature: undefined4 __cdecl apply_class_07_damage_and_destroy_geometry(int param_1, int param_2)
 */


undefined4 __cdecl apply_class_07_damage_and_destroy_geometry(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint local_14;
  uint local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar3 = *(int *)(param_1 + 0x70);
  local_14 = 0;
  local_10 = 0;
  if (iVar3 == 0) {
    param_1 = get_root_ancestor_world_object(param_1);
    if (((param_1 == 0) || (*(int *)(param_1 + 0x6c) != 7)) ||
       (iVar3 = *(int *)(param_1 + 0x70), iVar3 == 0)) {
      return 0;
    }
  }
  iVar1 = 0;
  piVar2 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar1 & 0x1f)) != 0) {
      if (*(int *)(iVar3 + 0x98) < *piVar2) {
        *(undefined4 *)(iVar3 + 0x98) = 0;
        release_geometry_variant_recursive(param_1,1);
        or_world_object_and_descendant_status_flags(param_1,0x200);
        copy_world_object_position_vector(param_1);
        spawn_chC_runtime_effect(param_1);
        local_c = (float)*(double *)(param_1 + 0x40);
        local_8 = (float)*(double *)(param_1 + 0x48);
        local_4 = (float)*(double *)(param_1 + 0x50);
        strncpy((char *)&local_14,s_x1_bldx1_004f7d34,8);
        spawn_cached_explosion_runtime_object
                  (local_14,local_10,param_1,local_c,local_8,local_4,param_1);
        dispatch_vehicle_runtime_sound_event(7,param_1,(undefined4 *)0x0);
        return 1;
      }
      *(int *)(iVar3 + 0x98) = *(int *)(iVar3 + 0x98) - *piVar2;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 4);
  return 0;
}


