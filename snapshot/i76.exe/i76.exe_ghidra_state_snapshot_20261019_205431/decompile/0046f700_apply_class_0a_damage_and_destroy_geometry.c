/*
 * Program: i76.exe
 * Function: apply_class_0a_damage_and_destroy_geometry
 * Entry: 0046f700
 * Signature: undefined4 __cdecl apply_class_0a_damage_and_destroy_geometry(int param_1, int param_2)
 */


undefined4 __cdecl apply_class_0a_damage_and_destroy_geometry(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint local_14;
  uint local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar2 = 0;
  local_14 = 0;
  local_10 = 0;
  piVar3 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
      if (*(int *)(iVar1 + 0xc) < *piVar3) {
        *(undefined4 *)(iVar1 + 0xc) = 0;
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
      *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) - *piVar3;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 4);
  return 0;
}


