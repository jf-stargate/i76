/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_00458930
 * Entry: 00458930
 * Signature: undefined __cdecl world_object_geometry_context_helper_00458930(undefined4 * param_1, uint param_2, uint param_3)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_00458930.
   Remove duplicated world_object_geometry wording. */

void __cdecl
world_object_geometry_context_helper_00458930(undefined4 *param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 local_c [3];
  
  puVar1 = (undefined4 *)special_equipment_state_context_helper_00469680(local_c,param_2,param_3);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return;
}


