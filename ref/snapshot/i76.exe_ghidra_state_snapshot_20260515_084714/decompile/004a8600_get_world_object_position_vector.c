/*
 * Program: i76.exe
 * Function: get_world_object_position_vector
 * Entry: 004a8600
 * Signature: undefined __cdecl get_world_object_position_vector(float * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Returns or computes the
   world-space position vector for a world object. */

void __cdecl get_world_object_position_vector(float *param_1,float param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  double *pdVar4;
  int iVar5;
  float fVar6;
  float local_10 [2];
  float local_8;
  undefined4 local_4;
  
  fVar3 = param_2;
  pdVar4 = (double *)entity_instance_table_context_helper_004576a0(local_10,(int)param_2);
  local_10[0] = *(float *)pdVar4;
  fVar6 = *(float *)((int)pdVar4 + 4);
  dVar2 = *pdVar4;
  fVar1 = *(float *)(pdVar4 + 1);
  local_4 = *(undefined4 *)((int)pdVar4 + 0xc);
  local_8 = fVar1;
  iVar5 = is_transform_composed_world_object_class((int)fVar3);
  if (iVar5 != 0) {
    probe_effect_target_surface_height_at_position(dVar2,fVar1,&param_2,(undefined4 *)0x0);
    fVar6 = param_2 - _DAT_004beb7c;
  }
  *param_1 = local_10[0];
  param_1[1] = fVar6;
  param_1[2] = local_8;
  return;
}


