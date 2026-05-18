/*
 * Program: i76.exe
 * Function: i76_runtime_compute_plane_or_triangle_normal4
 * Entry: 00494a90
 * Signature: undefined __cdecl i76_runtime_compute_plane_or_triangle_normal4(float * param_1, float * param_2, float * param_3, float * param_4)
 */


/* cgpt label refinement v20: was zone_satellite_map_zone_satellite_map_helper_00494a90. Remove
   duplicated zone_satellite_map wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_compute_plane_or_triangle_normal4
   :: Computes plane/triangle normal and plane value for terrain polygon lighting/backface tests.
   
   [cgpt_i76exe_terrain_runtime_structs_v12] proposed=i76_runtime_compute_plane_or_triangle_normal4
   :: Computes normalized plane normal and plane distance from three terrain/world vertices. */

void __cdecl
i76_runtime_compute_plane_or_triangle_normal4
          (float *param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float10 fVar9;
  
  fVar7 = (param_4[2] - param_2[2]) * (param_3[1] - param_2[1]) -
          (param_4[1] - param_2[1]) * (param_3[2] - param_2[2]);
  fVar5 = (*param_4 - *param_2) * (param_3[2] - param_2[2]) -
          (param_4[2] - param_2[2]) * (*param_3 - *param_2);
  fVar6 = (param_4[1] - param_2[1]) * (*param_3 - *param_2) -
          (*param_4 - *param_2) * (param_3[1] - param_2[1]);
  dVar4 = (double)(fVar6 * fVar6 + fVar5 * fVar5 + fVar7 * fVar7);
  fVar9 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar4,0),(uint)((ulonglong)dVar4 >> 0x20));
  fVar8 = (float)fVar9;
  fVar1 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = *param_2;
  *param_1 = fVar7 * fVar8;
  param_1[1] = fVar5 * fVar8;
  param_1[2] = fVar6 * fVar8;
  param_1[3] = -(fVar3 * fVar7 * fVar8 + fVar6 * fVar8 * fVar2 + fVar5 * fVar8 * fVar1);
  return;
}


