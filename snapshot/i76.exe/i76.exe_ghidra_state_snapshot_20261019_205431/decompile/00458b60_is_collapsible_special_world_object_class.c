/*
 * Program: i76.exe
 * Function: is_collapsible_special_world_object_class
 * Entry: 00458b60
 * Signature: undefined4 __cdecl is_collapsible_special_world_object_class(undefined4 param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Predicate/helper for collapsing
   special object classes to a generic handling class. */

undefined4 __cdecl is_collapsible_special_world_object_class(undefined4 param_1)

{
  switch(param_1) {
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


