/*
 * Program: i76.exe
 * Function: terrain_runtime_record_helper_004922f0
 * Entry: 004922f0
 * Signature: undefined4 __cdecl terrain_runtime_record_helper_004922f0(int param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004922f0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10] proposed=i76_runtime_emit_terrain_polygon_software_path
   :: Terrain primitive render callback for software/path A; prepares polygon vertices and submits
   to clipping/rasterization.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_emit_terrain_polygon_software_path
   :: Software terrain polygon callback. Copies world-space vertex xyz plus shade/depth into polygon
   work record, clips, then bins.
   
   [cgpt_i76exe_terrain_runtime_structs_v12] proposed=i76_runtime_emit_terrain_polygon_software_path
   :: Software terrain polygon callback. Writes polygon work header and variable 0x18-byte vertices;
   calls clip/prep; bins work record.
   
   I76 rename v43: terrain_runtime_record_helper_004922f0
   Terrain runtime helper from adaptive path; semantics still partial. */

undefined4 __cdecl terrain_runtime_record_helper_004922f0(int param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  int *piVar7;
  int iVar8;
  
  iVar4 = param_2;
  piVar3 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
  piVar3[3] = 0;
  piVar3[1] = 0xb4;
  piVar5 = (int *)(param_1 + param_2 * 4);
  if (0 < param_2) {
    piVar7 = piVar3 + 0xc;
    do {
      piVar1 = piVar5 + -1;
      piVar5 = piVar5 + -1;
      piVar1 = (int *)(g_runtime_terrain_vertex_xyz_buffer + *piVar1 * 0xc);
      piVar7[-5] = *piVar1;
      piVar7[-4] = piVar1[1];
      piVar7[-3] = piVar1[2];
      if (g_terrain_cached_high_color_resource_mode != 0) {
        param_3 = *(int *)(g_runtime_terrain_vertex_aux_projected_lighting_buffer + 8 +
                          *piVar5 * 0xc);
      }
      *piVar7 = param_3;
      piVar7 = piVar7 + 6;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  *piVar3 = iVar4;
  fVar2 = (float)piVar3[9];
  if (1 < iVar4) {
    pfVar6 = (float *)(piVar3 + 0xf);
    iVar8 = iVar4 + -1;
    do {
      if (_DAT_004be800 < *pfVar6 - fVar2) {
        fVar2 = *pfVar6;
      }
      pfVar6 = pfVar6 + 6;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  piVar3[4] = (int)fVar2;
  iVar4 = (*(code *)g_geo_raster_clip_prepare_table)(DAT_006442d4,piVar3 + 7,piVar3 + 7,iVar4,0);
  *piVar3 = iVar4;
  if (iVar4 == 0) {
    return 0;
  }
  i76_runtime_bin_terrain_polygon_work_record((float)piVar3[4]);
  piVar3[2] = g_runtime_terrain_software_polygon_flags;
  return 1;
}


