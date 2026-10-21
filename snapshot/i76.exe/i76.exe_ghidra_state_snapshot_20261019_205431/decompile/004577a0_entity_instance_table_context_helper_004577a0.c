/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_004577a0
 * Entry: 004577a0
 * Signature: undefined __cdecl entity_instance_table_context_helper_004577a0(float * param_1, int * param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_004577a0. Remove
   duplicated network/entity wording. */

void __cdecl entity_instance_table_context_helper_004577a0(float *param_1,int *param_2)

{
  float local_18 [2];
  float local_10;
  float local_4;
  
  local_4 = (float)param_2[4];
  transform_vec3_array_by_matrix(local_18,(float *)(param_2 + 1),1,(float *)(*param_2 + 0x18));
  *param_1 = local_18[0];
  param_1[1] = local_10;
  param_1[2] = local_4;
  return;
}


