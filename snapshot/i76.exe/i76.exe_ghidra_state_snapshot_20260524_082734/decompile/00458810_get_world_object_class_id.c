/*
 * Program: i76.exe
 * Function: get_world_object_class_id
 * Entry: 00458810
 * Signature: undefined __cdecl get_world_object_class_id(int param_1, uint param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small world-object class/id
   accessor used by vehicle damage callback. */

void __cdecl get_world_object_class_id(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 100);
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | param_2;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x60) != 0) {
        world_object_bounds_context_helper_00458790(*(int *)(iVar1 + 0x60),param_2);
      }
      if (*(int *)(iVar1 + 100) != 0) {
        world_object_bounds_context_helper_00458790(*(int *)(iVar1 + 100),param_2);
      }
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | param_2;
    }
  }
  return;
}


