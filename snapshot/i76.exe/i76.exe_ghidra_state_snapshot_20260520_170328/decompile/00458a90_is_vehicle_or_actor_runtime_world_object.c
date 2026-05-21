/*
 * Program: i76.exe
 * Function: is_vehicle_or_actor_runtime_world_object
 * Entry: 00458a90
 * Signature: undefined4 __cdecl is_vehicle_or_actor_runtime_world_object(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Predicate for runtime classes 1, 8,
   and 9 used by damage/effect paths. */

undefined4 __cdecl is_vehicle_or_actor_runtime_world_object(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x6c);
  if (((iVar1 != 1) && (iVar1 != 8)) && (iVar1 != 9)) {
    return 0;
  }
  return 1;
}


