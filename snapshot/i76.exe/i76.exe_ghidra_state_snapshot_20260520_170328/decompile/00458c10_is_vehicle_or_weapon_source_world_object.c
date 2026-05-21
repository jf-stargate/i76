/*
 * Program: i76.exe
 * Function: is_vehicle_or_weapon_source_world_object
 * Entry: 00458c10
 * Signature: undefined4 __cdecl is_vehicle_or_weapon_source_world_object(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Predicate for classes 1, 7, and 9
   used to classify damage/effect source objects. */

undefined4 __cdecl is_vehicle_or_weapon_source_world_object(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x6c);
  if (((iVar1 != 1) && (iVar1 != 7)) && (iVar1 != 9)) {
    return 0;
  }
  return 1;
}


