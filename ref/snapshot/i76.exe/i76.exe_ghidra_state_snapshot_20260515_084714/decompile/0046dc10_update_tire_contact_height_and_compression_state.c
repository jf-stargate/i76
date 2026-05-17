/*
 * Program: i76.exe
 * Function: update_tire_contact_height_and_compression_state
 * Entry: 0046dc10
 * Signature: undefined __cdecl update_tire_contact_height_and_compression_state(float param_1, int param_2, float param_3, undefined4 param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Computes tire
   terrain/contact height, compression delta, smoothing, and visual/runtime contact height state. */

void __cdecl
update_tire_contact_height_and_compression_state
          (float param_1,int param_2,float param_3,undefined4 param_4,float param_5)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double *pdVar6;
  uint uVar7;
  uint uVar8;
  float10 fVar9;
  float local_c [3];
  
  fVar5 = param_1;
  iVar2 = *(int *)((int)param_1 + 0x70);
  pdVar6 = (double *)compose_world_object_runtime_transform(local_c,(int)param_1);
  probe_effect_target_surface_height_at_position
            (*pdVar6,*(float *)(pdVar6 + 1),&param_1,(undefined4 *)0x0);
  *(float *)(iVar2 + 0x2c) = param_1;
  uVar7 = ftol();
  uVar8 = ftol();
  fVar9 = get_terrain_material_roughness_scalar((int)param_5);
  param_5 = (float)fVar9;
  iVar1 = (uVar7 & 7) + (uVar8 & 7) * 8;
  fVar3 = param_5 * *(float *)(&DAT_004be398 + iVar1 * 4) + param_1;
  if ((*(int *)(iVar2 + 0x44) != 0) && (param_5 < _DAT_004be4bc)) {
    fVar3 = fVar3 - *(float *)(&DAT_004be398 + iVar1 * 4) * _DAT_004be4c0;
  }
  fVar4 = fVar3 - *(float *)(iVar2 + 0x30);
  if (param_2 == 0) {
    param_1 = param_3 - (fVar4 - *(float *)(iVar2 + 0x34)) * _DAT_004be4c4;
  }
  else {
    param_1 = *(float *)(iVar2 + 0x3c);
  }
  *(int *)(iVar2 + 0x40) = param_2;
  if (param_1 < *(float *)(iVar2 + 0x3c)) {
    *(undefined4 *)(iVar2 + 0x40) = 1;
  }
  *(float *)(iVar2 + 0x30) = fVar3;
  *(float *)(iVar2 + 0x34) = fVar4;
  fVar9 = mission_flow_map_context_helper_0049e1b0((double *)(iVar2 + 0x58),param_1);
  if ((float10)*(float *)(iVar2 + 0x3c) <= fVar9) {
    if ((float10)*(float *)(iVar2 + 0x38) < fVar9) {
      fVar9 = (float10)*(float *)(iVar2 + 0x38);
    }
  }
  else {
    fVar9 = (float10)*(float *)(iVar2 + 0x3c);
  }
  *(float *)(iVar2 + 0x24) = (float)fVar9;
  *(double *)((int)fVar5 + 0x48) = (double)((float10)*(float *)(iVar2 + 0x28) + fVar9);
  return;
}


