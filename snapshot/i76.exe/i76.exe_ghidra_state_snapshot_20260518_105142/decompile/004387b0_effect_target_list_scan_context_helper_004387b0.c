/*
 * Program: i76.exe
 * Function: effect_target_list_scan_context_helper_004387b0
 * Entry: 004387b0
 * Signature: undefined __cdecl effect_target_list_scan_context_helper_004387b0(undefined4 * param_1, int * param_2)
 */


/* cgpt label refinement v18: was effect_target_scan_target_list_scan_helper_004387b0. Reduce
   duplicated wording while preserving address-suffixed context label. */

void __cdecl effect_target_list_scan_context_helper_004387b0(undefined4 *param_1,int *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  float local_28 [4];
  undefined4 local_18 [6];
  
  piVar1 = param_2;
  get_world_object_damage_or_target_vectors(*param_2,local_18 + 3,&param_2);
  puVar2 = (undefined4 *)get_effect_target_transformed_position_radius(local_28,piVar1);
  local_18[0] = *puVar2;
  local_18[1] = puVar2[1];
  local_18[2] = puVar2[2];
  puVar2 = local_18;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


