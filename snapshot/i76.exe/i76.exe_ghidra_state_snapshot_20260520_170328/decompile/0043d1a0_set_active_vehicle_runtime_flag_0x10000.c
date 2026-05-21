/*
 * Program: i76.exe
 * Function: set_active_vehicle_runtime_flag_0x10000
 * Entry: 0043d1a0
 * Signature: undefined __cdecl set_active_vehicle_runtime_flag_0x10000(int param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Sets or clears bit 0x10000 in the
   active player/camera vehicle runtime flags at +0x454. */

void __cdecl set_active_vehicle_runtime_flag_0x10000(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  iVar1 = *piVar2;
  if (iVar1 != 0) {
    iVar3 = is_vehicle_or_actor_runtime_world_object(iVar1);
    if ((iVar3 != 0) && (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
      if (param_1 != 0) {
        *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x10000;
        return;
      }
      *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) & 0xfffeffff;
    }
  }
  return;
}


