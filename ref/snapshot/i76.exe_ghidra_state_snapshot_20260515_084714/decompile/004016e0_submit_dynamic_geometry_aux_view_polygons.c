/*
 * Program: i76.exe
 * Function: submit_dynamic_geometry_aux_view_polygons
 * Entry: 004016e0
 * Signature: undefined __stdcall submit_dynamic_geometry_aux_view_polygons(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Dynamic render helper called from the frame renderer; prepares
   auxiliary clipped/lit polygon batches for the active view. */

void submit_dynamic_geometry_aux_view_polygons(void)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  double dVar4;
  bool bVar5;
  undefined3 extraout_var;
  undefined4 *puVar6;
  float *pfVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  float10 fVar12;
  int unaff_retaddr;
  float fStack0000000c;
  undefined8 uStack00000038;
  undefined4 uStack00000040;
  undefined4 uStack00000044;
  double dStack00000048;
  undefined4 uStack00000078;
  undefined4 uStack0000007c;
  double dStack00000080;
  undefined4 uStack00000088;
  undefined4 uStack0000008c;
  int in_stack_00001aac;
  float *pfVar13;
  
  zfsf_error_context_helper_004ba0a0();
  DAT_005049c0 = 0;
  if ((DAT_00654b8c._3_1_ != '\0') && (DAT_00504838 != 0)) {
    bVar5 = get_global_heap_handle();
    if (CONCAT31(extraout_var,bVar5) != 0) {
      DAT_00654b8c._3_1_ = '\x01';
    }
    fVar12 = (float10)fpatan((float10)*(float *)(in_stack_00001aac + 0x2c),(float10)1);
    puVar6 = (undefined4 *)
             software_raster_command_context_helper_00472220
                       ((float *)&stack0x000000d0,*(int *)(in_stack_00001aac + 0x3c),
                        (float)(fVar12 + fVar12),*(undefined4 *)(in_stack_00001aac + 0x30),100000.0,
                        *(float *)(in_stack_00001aac + 0x34));
    puVar11 = &DAT_005dd5a0;
    for (iVar9 = 0x76; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar11 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar11 = puVar11 + 1;
    }
    pfVar7 = (float *)(in_stack_00001aac + 0x40);
    pfVar13 = (float *)&DAT_005dd5e0;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar13 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar13 = pfVar13 + 1;
    }
    uVar3 = *(undefined8 *)(in_stack_00001aac + 0x160);
    fStack0000000c = (float)*(double *)(in_stack_00001aac + 0x170);
    puVar6 = &DAT_004faed8;
    puVar11 = (undefined4 *)&stack0x00000010;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar11 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar11 = puVar11 + 1;
    }
    dStack00000048 = (double)fStack0000000c;
    uStack00000040 = 0;
    uStack00000044 = 0;
    uStack00000038 = uVar3;
    pfVar7 = compose_matrix_or_transform_a
                       ((float *)&stack0x00000090,(float *)&stack0x00000010,
                        (float *)(in_stack_00001aac + 0x40));
    dVar4 = *(double *)(in_stack_00001aac + 0x168);
    fVar1 = *(float *)(in_stack_00001aac + 0x138);
    pfVar13 = (float *)&stack0x00000010;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar13 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar13 = pfVar13 + 1;
    }
    fVar2 = *(float *)(in_stack_00001aac + 0x138);
    puVar6 = &DAT_004faed8;
    puVar11 = (undefined4 *)&stack0x00000050;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar11 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar11 = puVar11 + 1;
    }
    uStack00000078 = 0;
    uStack0000007c = 0;
    uStack00000088 = 0;
    uStack0000008c = 0;
    dStack00000080 =
         -(((double)_DAT_004bc420 - (double)fVar1 * (double)_DAT_004bc440) / (double)fVar2) * dVar4;
    pfVar7 = compose_matrix_or_transform_a
                       ((float *)&stack0x00000090,(float *)&stack0x00000010,
                        (float *)&stack0x00000050);
    pfVar13 = (float *)&stack0x00000010;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      *pfVar13 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar13 = pfVar13 + 1;
    }
    iVar9 = 0;
    if (0 < DAT_00503034) {
      iVar10 = 0;
      do {
        transform_vec3_array_by_matrix
                  ((float *)((int)&DAT_00501828 + iVar10),(float *)((int)&DAT_00503038 + iVar10),1,
                   (float *)&stack0x00000010);
        iVar9 = iVar9 + 1;
        iVar10 = iVar10 + 0x18;
      } while (iVar9 < DAT_00503034);
    }
    if ((DAT_00654b8c._3_1_ != '\0') && (DAT_00654b8c._3_1_ == '\x01')) {
      pfVar7 = (float *)allocate_dynamic_render_pass_vertex_buffer
                                  ((undefined4 *)&stack0x000002a8,in_stack_00001aac,
                                   (int *)&stack0x00000000);
      while (pfVar7 != (float *)0xffffffff) {
        if (pfVar7 != (float *)0x0) {
          DAT_005049c0 = DAT_005049c0 + 1;
          pfVar13 = (float *)0x54;
          if (*(int *)(DAT_005dd5dc + 8) == 1) {
            puVar8 = (uint *)polygon_renderer_context_helper_00471f00
                                       ((int *)(&DAT_00504850 + unaff_retaddr * 0x18),
                                        in_stack_00001aac);
            log_cache_memory_status
                      ((float *)&DAT_005dd5a0,(float *)&stack0x000002a8,pfVar7,puVar8,pfVar13);
          }
          else {
            puVar8 = (uint *)polygon_renderer_context_helper_00471f00
                                       ((int *)(&DAT_00504850 + unaff_retaddr * 0x18),
                                        in_stack_00001aac);
            submit_lit_textured_polygon_to_renderer
                      ((float *)&DAT_005dd5a0,(float *)&stack0x000002a8,(int)pfVar7,puVar8,
                       (uint)pfVar13);
          }
        }
        pfVar7 = (float *)allocate_dynamic_render_pass_vertex_buffer
                                    ((undefined4 *)&stack0x000002a8,in_stack_00001aac,
                                     (int *)&stack0x00000000);
      }
    }
  }
  return;
}


