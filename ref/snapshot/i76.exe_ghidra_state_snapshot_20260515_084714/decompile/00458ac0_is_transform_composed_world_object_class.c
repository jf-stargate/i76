/*
 * Program: i76.exe
 * Function: is_transform_composed_world_object_class
 * Entry: 00458ac0
 * Signature: undefined4 __cdecl is_transform_composed_world_object_class(int param_1)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=medium-high] Class predicate returning true
   for object classes 2,3,4,0xb,0xc,0x5c; used near transform hierarchy helpers. */

undefined4 __cdecl is_transform_composed_world_object_class(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x6c)) {
  case 2:
  case 3:
  case 4:
  case 0xb:
  case 0xc:
  case 0x5c:
    return 1;
  default:
    return 0;
  }
}


