/*
 * Program: i76.exe
 * Function: release_vehicle_radar_or_weapon_target_object
 * Entry: 00461570
 * Signature: LPVOID __cdecl release_vehicle_radar_or_weapon_target_object(int param_1, int param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Releases/clears a retained radar or
   weapon target object reference. */

LPVOID __cdecl release_vehicle_radar_or_weapon_target_object(int param_1,int param_2)

{
  int iVar1;
  LPVOID pvVar2;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    if (param_2 == 1) {
      pvVar2 = release_world_object_tree_reference(*(LPVOID *)(iVar1 + 0x68),s_radar_004f7694);
      return pvVar2;
    }
    if (param_2 == 2) {
      pvVar2 = release_world_object_tree_reference(*(LPVOID *)(iVar1 + 0x6c),s_radar_004f7694);
      return pvVar2;
    }
    if (param_2 == 8) {
      pvVar2 = release_world_object_tree_reference(*(LPVOID *)(iVar1 + 0x70),s_radar_004f7694);
      return pvVar2;
    }
    if (param_2 == 0x10) {
      pvVar2 = release_world_object_tree_reference(*(LPVOID *)(iVar1 + 0x74),s_radar_004f7694);
      return pvVar2;
    }
  }
  return (LPVOID)0x0;
}


