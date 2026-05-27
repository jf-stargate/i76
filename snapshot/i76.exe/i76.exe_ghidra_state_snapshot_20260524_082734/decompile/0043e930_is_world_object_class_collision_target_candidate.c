/*
 * Program: i76.exe
 * Function: is_world_object_class_collision_target_candidate
 * Entry: 0043e930
 * Signature: undefined4 __cdecl is_world_object_class_collision_target_candidate(int param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Checks whether a world-object
   class/type is in the collision-target candidate range 0x0b..0x0d. */

undefined4 __cdecl is_world_object_class_collision_target_candidate(int param_1)

{
  if ((10 < *(int *)(param_1 + 0x6c)) && (*(int *)(param_1 + 0x6c) < 0xe)) {
    return 1;
  }
  return 0;
}


