/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_004576a0
 * Entry: 004576a0
 * Signature: undefined __cdecl entity_instance_table_context_helper_004576a0(float * param_1, int param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_004576a0. Remove
   duplicated network/entity wording. */

void __cdecl entity_instance_table_context_helper_004576a0(float *param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_80 [16];
  float local_40 [16];
  
  iVar1 = get_root_ancestor_world_object(param_2);
  iVar4 = 0;
  piVar3 = &g_active_world_object_entries;
  do {
    if (*piVar3 == iVar1) {
      piVar3 = &g_active_world_object_entries + iVar4 * 0x1e;
      goto LAB_004576d6;
    }
    piVar3 = piVar3 + 0x1e;
    iVar4 = iVar4 + 1;
  } while ((int)piVar3 < 0x54a030);
  piVar3 = (int *)0x0;
LAB_004576d6:
  if (piVar3 == (int *)0x0) {
    *param_1 = 0.0;
    param_1[1] = 0.0;
    param_1[2] = 0.0;
    param_1[3] = 0.0;
    return;
  }
  local_90 = (float)piVar3[4];
  if ((*(uint *)(*piVar3 + 0x10) & 0x100) == 0) {
    pfVar2 = (float *)(*piVar3 + 0x18);
  }
  else {
    pfVar2 = (float *)compute_transform_relative_to_ancestor(local_40,param_2,0);
  }
  pfVar5 = local_80;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar5 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar5 = pfVar5 + 1;
  }
  transform_vec3_array_by_matrix(&local_9c,(float *)(piVar3 + 1),1,local_80);
  *param_1 = local_9c;
  param_1[1] = local_98;
  param_1[2] = local_94;
  param_1[3] = local_90;
  return;
}


