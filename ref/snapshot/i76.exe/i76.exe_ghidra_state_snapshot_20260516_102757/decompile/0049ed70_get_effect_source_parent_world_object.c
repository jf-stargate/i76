/*
 * Program: i76.exe
 * Function: get_effect_source_parent_world_object
 * Entry: 0049ed70
 * Signature: undefined4 __cdecl get_effect_source_parent_world_object(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium-high] Returns parent/source object
   associated with the current explosion/effect object. */

undefined4 __cdecl get_effect_source_parent_world_object(int param_1)

{
  if (*(int *)(param_1 + 0x70) != 0) {
    return *(undefined4 *)(*(int *)(param_1 + 0x70) + 0xc);
  }
  return 0;
}


