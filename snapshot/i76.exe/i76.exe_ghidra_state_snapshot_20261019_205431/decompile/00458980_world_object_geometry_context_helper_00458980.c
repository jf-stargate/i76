/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_00458980
 * Entry: 00458980
 * Signature: undefined __cdecl world_object_geometry_context_helper_00458980(int param_1, float param_2)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00458980.
   Remove duplicated world_object_geometry wording. */

void __cdecl world_object_geometry_context_helper_00458980(int param_1,float param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar2 = mission_flow_map_context_helper_0049d400(param_2);
  uVar1 = (undefined4)((ulonglong)uVar2 >> 0x20);
  *(float *)(param_1 + 0x30) = (float)uVar2;
  *(float *)(param_1 + 0x20) = -(float)uVar2;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}


