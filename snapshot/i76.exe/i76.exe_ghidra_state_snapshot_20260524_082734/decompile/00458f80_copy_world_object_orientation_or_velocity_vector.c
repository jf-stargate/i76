/*
 * Program: i76.exe
 * Function: copy_world_object_orientation_or_velocity_vector
 * Entry: 00458f80
 * Signature: int __cdecl copy_world_object_orientation_or_velocity_vector(int param_1, uint param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small transform/vector helper used
   by vehicle damage callback. */

int __cdecl copy_world_object_orientation_or_velocity_vector(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && ((param_2 & *(uint *)(param_1 + 0x10)) == 0)) {
    for (iVar1 = *(int *)(param_1 + 100); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      iVar2 = copy_world_object_orientation_or_velocity_vector(iVar1,param_2);
      if (iVar2 != 0) {
        return iVar2;
      }
    }
    param_1 = 0;
  }
  return param_1;
}


