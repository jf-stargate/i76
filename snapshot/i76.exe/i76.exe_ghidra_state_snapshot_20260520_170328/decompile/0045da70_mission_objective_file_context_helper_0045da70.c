/*
 * Program: i76.exe
 * Function: mission_objective_file_context_helper_0045da70
 * Entry: 0045da70
 * Signature: int __cdecl mission_objective_file_context_helper_0045da70(int param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, float param_10, undefined4 param_11, double param_12, double param_13, double param_14)
 */


/* cgpt readability rename set B v14: Readability pass set B: mission objective file context helper
   based on prior focused closure context. */

int __cdecl
mission_objective_file_context_helper_0045da70
          (int param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float param_9,float param_10,undefined4 param_11,
          double param_12,double param_13,double param_14)

{
  int iVar1;
  undefined4 *puVar2;
  float local_10 [4];
  
  *(undefined4 *)(g_geo_render_next_record_scratch + 0x40) = 0;
  *(undefined4 *)(g_geo_render_next_record_scratch + 0x44) = 0;
  *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
  *(float *)(g_geo_render_next_record_scratch + 0x24) =
       param_2 * *(float *)(param_1 + 0x34) +
       param_5 * *(float *)(param_1 + 0x38) + param_8 * *(float *)(param_1 + 0x3c) + (float)param_12
  ;
  *(float *)(g_geo_render_next_record_scratch + 0x28) =
       param_3 * *(float *)(param_1 + 0x34) +
       param_6 * *(float *)(param_1 + 0x38) + param_9 * *(float *)(param_1 + 0x3c) + (float)param_13
  ;
  *(float *)(g_geo_render_next_record_scratch + 0x2c) =
       param_4 * *(float *)(param_1 + 0x34) +
       param_7 * *(float *)(param_1 + 0x38) + param_10 * *(float *)(param_1 + 0x3c) +
       (float)param_14;
  puVar2 = (undefined4 *)
           transform_section_centroid_or_plane_by_matrix(local_10,(float *)(param_1 + 0xc),&param_2)
  ;
  iVar1 = g_geo_render_next_record_scratch;
  *(undefined4 *)(g_geo_render_next_record_scratch + 0x30) = *puVar2;
  *(undefined4 *)(iVar1 + 0x34) = puVar2[1];
  *(undefined4 *)(iVar1 + 0x38) = puVar2[2];
  *(undefined4 *)(iVar1 + 0x3c) = puVar2[3];
  *(undefined4 *)(g_geo_render_next_record_scratch + 4) = 0;
  return g_geo_render_next_record_scratch + 0x48;
}


