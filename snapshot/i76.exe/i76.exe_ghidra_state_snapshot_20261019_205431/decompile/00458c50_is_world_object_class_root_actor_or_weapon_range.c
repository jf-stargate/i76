/*
 * Program: i76.exe
 * Function: is_world_object_class_root_actor_or_weapon_range
 * Entry: 00458c50
 * Signature: undefined4 __cdecl is_world_object_class_root_actor_or_weapon_range(int param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v9; confidence=medium] Predicate true for class 1 or
   class range 8..9. Exact class names remain provisional. */

undefined4 __cdecl is_world_object_class_root_actor_or_weapon_range(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x6c);
  if ((iVar1 != 1) && ((iVar1 < 8 || (9 < iVar1)))) {
    return 0;
  }
  return 1;
}


