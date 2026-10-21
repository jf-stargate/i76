/*
 * Program: i76.exe
 * Function: get_effect_target_transformed_position_radius
 * Entry: 00457650
 * Signature: undefined __cdecl get_effect_target_transformed_position_radius(float * param_1, int * param_2)
 */


/* [cgpt i76.exe effect/damage/blit rename v18; confidence=HIGH] Transforms an effect target's local
   offset into world coordinates and copies the target radius from record +0x10. */

void __cdecl get_effect_target_transformed_position_radius(float *param_1,int *param_2)

{
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_4 = (float)param_2[4];
  transform_vec3_array_by_matrix(&local_10,(float *)(param_2 + 1),1,(float *)(*param_2 + 0x18));
  *param_1 = local_10;
  param_1[1] = local_c;
  param_1[2] = local_8;
  param_1[3] = local_4;
  return;
}


