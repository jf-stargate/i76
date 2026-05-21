/*
 * Program: i76.exe
 * Function: copy_world_object_position_vector
 * Entry: 00458f00
 * Signature: undefined4 __cdecl copy_world_object_position_vector(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small transform/position helper
   used by vehicle damage callback. */

undefined4 __cdecl copy_world_object_position_vector(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x68);
  while ((iVar2 = iVar1, iVar2 != 0 && (*(int *)(iVar2 + 100) != param_1))) {
    param_1 = iVar2;
    iVar1 = *(int *)(iVar2 + 0x68);
  }
  iVar1 = *(int *)(param_1 + 0x68);
  if (((iVar1 != 0) && (*(int *)(iVar1 + 0x68) == 0)) && ((*(uint *)(iVar1 + 0x10) & 0x200) == 0)) {
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x200;
    return 1;
  }
  return 0;
}


