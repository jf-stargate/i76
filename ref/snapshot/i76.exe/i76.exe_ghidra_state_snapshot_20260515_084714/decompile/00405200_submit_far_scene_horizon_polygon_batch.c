/*
 * Program: i76.exe
 * Function: submit_far_scene_horizon_polygon_batch
 * Entry: 00405200
 * Signature: undefined __stdcall submit_far_scene_horizon_polygon_batch(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Dynamic render helper that builds/submits far-scene or
   horizon-style polygon batches using active display globals. */

void submit_far_scene_horizon_polygon_batch(void)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  byte bVar4;
  bool bVar5;
  undefined4 *puVar6;
  undefined3 extraout_var;
  uint *puVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  float *pfVar11;
  undefined4 *puVar12;
  float10 fVar13;
  int in_stack_00000044;
  undefined4 uStack00000070;
  undefined4 uStack00000074;
  undefined4 uStack00000078;
  undefined4 uStack0000007c;
  undefined4 uStack00000080;
  undefined4 uStack00000084;
  undefined4 *in_stack_00001bbc;
  
  zfsf_error_context_helper_004ba0a0();
  iVar9 = 0;
  bVar4 = (DAT_00654b81 != '\0') + 1;
  DAT_00507ce4 = 0;
  if (DAT_00504c38 == 0) {
    bVar4 = 1;
  }
  puVar6 = in_stack_00001bbc;
  puVar12 = &DAT_005dd3c0;
  for (iVar8 = 0x76; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar12 = puVar12 + 1;
  }
  fVar13 = (float10)fpatan((float10)_DAT_005dd3ec,(float10)1);
  puVar6 = (undefined4 *)
           software_raster_command_context_helper_00472220
                     ((float *)&stack0x000001e0,DAT_005dd3fc,(float)(fVar13 + fVar13),DAT_005dd3f0,
                      100000.0,DAT_005dd3f4);
  puVar12 = (undefined4 *)&stack0x00000008;
  for (iVar8 = 0x76; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar6 = &DAT_005dd400;
  puVar12 = (undefined4 *)&stack0x00000048;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar12 = puVar12 + 1;
  }
  uStack00000070 = 0;
  uStack00000074 = 0;
  uStack00000078 = 0;
  uStack0000007c = 0;
  uStack00000080 = 0;
  uStack00000084 = 0x40590000;
  if (0 < DAT_00507cd4) {
    pfVar11 = (float *)&DAT_00506454;
    pfVar10 = (float *)&DAT_00504c54;
    iVar8 = 0;
    do {
      transform_vec3_array_by_matrix
                ((float *)((int)&DAT_00506448 + iVar8),(float *)((int)&DAT_00504c48 + iVar8),1,
                 (float *)&stack0x00000048);
      *pfVar11 = *pfVar10;
      pfVar11[1] = pfVar10[1];
      pfVar11[2] = pfVar10[2];
      bVar5 = get_global_heap_handle();
      if (CONCAT31(extraout_var,bVar5) == 0) {
        pfVar11[2] = 0.0;
      }
      else {
        pfVar11[2] = 0.8;
      }
      iVar3 = DAT_00507cd4;
      fVar2 = (float)_DAT_00507c50;
      pfVar1 = pfVar11 + 1;
      *pfVar11 = (float)_DAT_00507cd8 + *pfVar11;
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 0x18;
      pfVar10 = pfVar10 + 6;
      pfVar11 = pfVar11 + 6;
      *pfVar1 = fVar2 + *pfVar1;
    } while (iVar9 < iVar3);
  }
  if (bVar4 < 2) {
    pfVar10 = (float *)project_aux_render_vertex_batch_to_scratch
                                 ((undefined4 *)&stack0x000003b8,(int)&stack0x00000008);
    while (pfVar10 != (float *)0xffffffff) {
      if (pfVar10 != (float *)0x0) {
        DAT_00507ce4 = DAT_00507ce4 + 1;
        if (DAT_00504c38 == 0) {
          puVar7 = (uint *)0xef;
        }
        else {
          puVar7 = (uint *)(uint)*(byte *)(DAT_00504c38 + 8);
        }
        if (*(int *)(in_stack_00000044 + 8) == 1) {
          log_cache_memory_status
                    ((float *)&stack0x00000008,(float *)&stack0x000003b8,pfVar10,puVar7,(float *)0x1
                    );
        }
        else {
          submit_lit_textured_polygon_to_renderer
                    ((float *)&stack0x00000008,(float *)&stack0x000003b8,(int)pfVar10,puVar7,1);
        }
      }
      pfVar10 = (float *)project_aux_render_vertex_batch_to_scratch
                                   ((undefined4 *)&stack0x000003b8,(int)&stack0x00000008);
    }
  }
  else if (bVar4 == 2) {
    pfVar10 = (float *)project_aux_render_vertex_batch_to_scratch
                                 ((undefined4 *)&stack0x000003b8,(int)&stack0x00000008);
    while (pfVar10 != (float *)0xffffffff) {
      if (pfVar10 != (float *)0x0) {
        DAT_00507ce4 = DAT_00507ce4 + 1;
        pfVar11 = (float *)0x16;
        if (*(int *)(in_stack_00000044 + 8) == 1) {
          puVar7 = (uint *)polygon_renderer_context_helper_00471f00
                                     (&DAT_00504c38,(int)in_stack_00001bbc);
          log_cache_memory_status
                    ((float *)&stack0x00000008,(float *)&stack0x000003b8,pfVar10,puVar7,pfVar11);
        }
        else {
          puVar7 = (uint *)polygon_renderer_context_helper_00471f00
                                     (&DAT_00504c38,(int)in_stack_00001bbc);
          submit_lit_textured_polygon_to_renderer
                    ((float *)&stack0x00000008,(float *)&stack0x000003b8,(int)pfVar10,puVar7,
                     (uint)pfVar11);
        }
      }
      pfVar10 = (float *)project_aux_render_vertex_batch_to_scratch
                                   ((undefined4 *)&stack0x000003b8,(int)&stack0x00000008);
    }
    if (_DAT_004bc4dc < _DAT_00504c30) {
      fVar13 = (float10)_CIfmod();
      _DAT_00507cd8 = (double)fVar13;
      fVar13 = (float10)_CIfmod();
      _DAT_00507c50 = (double)fVar13;
      return;
    }
  }
  return;
}


