/*
 * Program: i76.exe
 * Function: get_vehicle_weapon_target_object_by_slot
 * Entry: 00461480
 * Signature: int __cdecl get_vehicle_weapon_target_object_by_slot(int param_1, int param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=high] Returns secondary target object for slot
   selectors, filtering inactive target records. */

int __cdecl get_vehicle_weapon_target_object_by_slot(int param_1,int param_2)

{
  int iVar1;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    if (param_2 == 1) {
      iVar1 = *(int *)(iVar1 + 0x5c);
    }
    else {
      if (param_2 != 2) {
        if (param_2 != 4) {
          return 0;
        }
        iVar1 = *(int *)(iVar1 + 100);
        if (iVar1 != 0) {
          if (*(short *)(iVar1 + 8) != 0) {
            return 0;
          }
          return iVar1;
        }
        return 0;
      }
      iVar1 = *(int *)(iVar1 + 0x60);
    }
    if (iVar1 == 0) {
      return 0;
    }
    if (*(short *)(iVar1 + 8) == 0) {
      return iVar1;
    }
  }
  return 0;
}


