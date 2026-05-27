/*
 * Program: i76.exe
 * Function: terrain_runtime_record_helper_004924b0
 * Entry: 004924b0
 * Signature: undefined4 __cdecl terrain_runtime_record_helper_004924b0(int param_1, int param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004924b0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10] proposed=i76_runtime_emit_terrain_polygon_alt_path ::
   Terrain primitive render callback for alternate/D3D-ish path; prepares terrain polygon and
   submits to downstream render binning.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_emit_terrain_polygon_alt_path ::
   Alternate terrain polygon callback. Copies xyz plus projected/scaled vertex fields into polygon
   work record, clips, then bins.
   
   [cgpt_i76exe_terrain_runtime_structs_v12] proposed=i76_runtime_emit_terrain_polygon_alt_path ::
   Alternate terrain polygon callback. Writes xyz plus projected/scaled fields to polygon work
   record; calls indexed clip/prep; bins work record.
   
   I76 rename v43: terrain_runtime_record_helper_004924b0
   Terrain runtime helper from adaptive path; semantics still partial. */

undefined4 __cdecl terrain_runtime_record_helper_004924b0(int param_1,int param_2,float param_3)

{
  int *piVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  
  piVar3 = i76_runtime_alloc_prepare_terrain_polygon_work_record();
  piVar3[3] = 0;
  piVar3[1] = g_runtime_terrain_alt_polygon_material_or_type;
  piVar3[2] = g_runtime_terrain_alt_polygon_flags;
  iVar6 = param_1 + param_2 * 4;
  if (0 < param_2) {
    pfVar5 = (float *)(piVar3 + 10);
    param_1 = param_2;
    do {
      piVar1 = (int *)(iVar6 + -4);
      iVar6 = iVar6 + -4;
      iVar4 = *piVar1 * 0xc;
      pfVar7 = (float *)(g_runtime_terrain_vertex_xyz_buffer + iVar4);
      pfVar5[-3] = *pfVar7;
      pfVar5[-2] = pfVar7[1];
      pfVar5[-1] = pfVar7[2];
      *pfVar5 = *(float *)(g_runtime_terrain_vertex_aux_projected_lighting_buffer + iVar4) -
                _DAT_0059c55c;
      pfVar5[1] = *(float *)(g_runtime_terrain_vertex_aux_projected_lighting_buffer + 4 + iVar4) -
                  _DAT_0059c550;
      if (g_terrain_cached_high_color_resource_mode != 0) {
        param_3 = *(float *)(g_runtime_terrain_vertex_aux_projected_lighting_buffer + 8 + iVar4);
      }
      pfVar5[2] = param_3;
      pfVar5 = pfVar5 + 6;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  *piVar3 = param_2;
  fVar2 = (float)piVar3[9];
  if (1 < param_2) {
    pfVar5 = (float *)(piVar3 + 0xf);
    iVar6 = param_2 + -1;
    do {
      if (_DAT_004be800 < *pfVar5 - fVar2) {
        fVar2 = *pfVar5;
      }
      pfVar5 = pfVar5 + 6;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  piVar3[4] = (int)fVar2;
  iVar6 = (*(code *)(&g_geo_raster_clip_prepare_table)[piVar3[2]])
                    (DAT_006442d4,piVar3 + 7,piVar3 + 7,param_2,piVar3[2]);
  *piVar3 = iVar6;
  if (iVar6 == 0) {
    return 0;
  }
  i76_runtime_bin_terrain_polygon_work_record((float)piVar3[4]);
  piVar3[2] = piVar3[2] & 0xffffffefU | 8;
  return 1;
}


