/*
 * Program: i76.exe
 * Function: prepare_adaptive_terrain_render_context
 * Entry: 00490fb0
 * Signature: float10 __cdecl prepare_adaptive_terrain_render_context(int param_1, int param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490fb0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v11]
   proposed=i76_runtime_compute_terrain_lighting_from_neighbor_heights :: Computes terrain
   light/shade value by sampling center and four neighboring height samples.
   
   [cgpt_i76exe_terrain_runtime_structs_v12]
   proposed=i76_runtime_compute_terrain_lighting_from_neighbor_heights :: Computes terrain
   shade/intensity from center and four neighboring height samples plus current light vector.
   
   I76 rename v43: prepare_adaptive_terrain_render_context
   Prepares adaptive terrain render/tessellation context. */

float10 __cdecl prepare_adaptive_terrain_render_context(int param_1,int param_2,float param_3)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  float10 fVar11;
  float10 fVar12;
  
  fVar5 = _DAT_004be820 / DAT_006442c0;
  uVar7 = sample_runtime_terrain_height(param_1,param_2);
  fVar2 = (float)CONCAT22(extraout_var,uVar7) * fVar5;
  uVar7 = sample_runtime_terrain_height(param_1,param_2 + -1);
  uVar8 = sample_runtime_terrain_height(param_1 + 1,param_2);
  uVar9 = sample_runtime_terrain_height(param_1,param_2 + 1);
  uVar10 = sample_runtime_terrain_height(param_1 + -1,param_2);
  fVar3 = (float)CONCAT22(extraout_var_01,uVar8) * fVar5 - fVar2;
  fVar4 = (float)CONCAT22(extraout_var_02,uVar9) * fVar5 - fVar2;
  fVar6 = -((float)CONCAT22(extraout_var_00,uVar7) * fVar5 - fVar2);
  fVar2 = -((float)CONCAT22(extraout_var_03,uVar10) * fVar5 - fVar2);
  fVar2 = (fVar2 + fVar2 + fVar3 + fVar3) * _DAT_004be824;
  fVar3 = (fVar6 + fVar4 + fVar4 + fVar6) * _DAT_004be824;
  dVar1 = (double)((fVar3 * fVar3 + fVar2 * fVar2) - _DAT_004be828);
  zone_satellite_map_context_helper_00495000(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  fVar12 = ((float10)_DAT_0059c57c - (float10)fVar2 * (float10)_DAT_0059c578) -
           (float10)fVar3 * (float10)_DAT_0059c580;
  if (fVar12 < (float10)_DAT_004be800) {
    return (float10)DAT_0059c54c;
  }
  fVar11 = (float10)param_3 * (float10)_DAT_00643600 + (float10)_DAT_006435fc;
  if (fVar11 < (float10)_DAT_004be82c) {
    fVar11 = (float10)_DAT_004be82c;
  }
  if ((float10)_DAT_004be830 < fVar11) {
    fVar11 = (float10)_DAT_004be830;
  }
  fVar12 = fVar12 * fVar11 + (float10)DAT_0059c54c;
  if ((float10)_DAT_004be830 < fVar12) {
    fVar12 = (float10)_DAT_004be830;
  }
  return fVar12;
}


