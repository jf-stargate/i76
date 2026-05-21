/*
 * Program: i76.exe
 * Function: is_world_object_class_geometry_or_light_range
 * Entry: 00458c30
 * Signature: undefined4 __cdecl is_world_object_class_geometry_or_light_range(int param_1)
 */


/* [cgpt i76.exe texture/resource-cache rename v9; confidence=medium] Predicate true for class 4 or
   class range 0x5a..0x5b. Exact class names remain provisional; likely geometry/light/special
   renderable range. */

undefined4 __cdecl is_world_object_class_geometry_or_light_range(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x6c);
  if ((iVar1 != 4) && ((iVar1 < 0x5a || (0x5b < iVar1)))) {
    return 0;
  }
  return 1;
}


