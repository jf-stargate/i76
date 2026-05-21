/*
 * Program: i76.exe
 * Function: transform_section_centroid_or_plane_by_matrix
 * Entry: 00494ef0
 * Signature: undefined __cdecl transform_section_centroid_or_plane_by_matrix(float * param_1, float * param_2, float * param_3)
 */


/* [cgpt i76.exe GEO lighting/render renames v33; confidence=medium-high] Transforms GEO section
   centroid/plane-like sort fields before depth-tree insertion.
   
   I76 rename v43: transform_section_centroid_or_plane
   Transforms section centroid/plane-like data. */

void __cdecl
transform_section_centroid_or_plane_by_matrix(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = param_3[6] * param_2[2] + param_3[3] * param_2[1] + *param_3 * *param_2;
  fVar7 = param_3[7] * param_2[2] + param_3[4] * param_2[1] + param_3[1] * *param_2;
  fVar6 = param_3[8] * param_2[2] + param_3[5] * param_2[1] + param_3[2] * *param_2;
  dVar2 = *(double *)(param_3 + 10);
  dVar3 = *(double *)(param_3 + 0xc);
  dVar4 = *(double *)(param_3 + 0xe);
  *param_1 = fVar5;
  param_1[2] = fVar6;
  fVar1 = param_2[3];
  param_1[1] = fVar7;
  param_1[3] = fVar1 - (fVar6 * (float)dVar4 + fVar5 * (float)dVar2 + fVar7 * (float)dVar3);
  return;
}


