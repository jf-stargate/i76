/*
 * Program: i76.exe
 * Function: has_world_object_class_damage_handler
 * Entry: 004620a0
 * Signature: undefined __cdecl has_world_object_class_damage_handler(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small class-descriptor predicate
   near damage dispatch path. */

void __cdecl has_world_object_class_damage_handler(int param_1)

{
  *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}


