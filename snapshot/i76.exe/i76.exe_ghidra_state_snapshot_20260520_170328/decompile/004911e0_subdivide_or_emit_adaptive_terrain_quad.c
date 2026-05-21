/*
 * Program: i76.exe
 * Function: subdivide_or_emit_adaptive_terrain_quad
 * Entry: 004911e0
 * Signature: undefined __cdecl subdivide_or_emit_adaptive_terrain_quad(undefined2 * param_1, undefined2 * param_2, short * param_3, short * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004911e0. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10] proposed=i76_runtime_subdivide_terrain_quad_for_render
   :: Recursive adaptive quad/diamond subdivision. Emits primitive node or splits edge records and
   recurses into child quads.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_subdivide_terrain_quad_for_render
   :: Adaptive terrain subdivision. Emits primitive node when flat/far/small enough; otherwise
   splits edges, inserts midpoint/center edges, and recurses.
   
   I76 rename v43: subdivide_or_emit_adaptive_terrain_quad
   Exact adaptive terrain LOD predicate: hard half_scale floor, error tests, special-surface scan,
   split/emit. */

void __cdecl
subdivide_or_emit_adaptive_terrain_quad
          (undefined2 *param_1,undefined2 *param_2,short *param_3,short *param_4)

{
  undefined2 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined2 uVar4;
  double dVar5;
  double dVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined2 *puVar10;
  ushort uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  short *psVar15;
  short *psVar16;
  int iVar17;
  ushort *puVar18;
  float *pfVar19;
  int iVar20;
  int iVar21;
  ushort *puVar22;
  uint uVar23;
  ushort *puVar24;
  uint uVar25;
  ushort *puVar26;
  
  do {
    pfVar2 = (float *)(g_runtime_terrain_vertex_xyz_buffer + *param_3 * 0xc);
    iVar20 = g_runtime_terrain_vertex_xyz_buffer + param_4[1] * 0xc;
    iVar12 = ftol();
    dVar5 = (double)iVar12 * _DAT_004be838;
    if ((dVar5 < _DAT_004be848) && (iVar17 = 0, 0 < DAT_006442f0)) {
      pfVar19 = (float *)&DAT_00644310;
      do {
        dVar6 = (double)*pfVar19 * ((double)pfVar2[2] + dVar5) +
                (double)pfVar19[-2] * ((double)*pfVar2 + dVar5) + *(double *)(pfVar19 + 2);
        if ((dVar6 + dVar5 * _DAT_004be840 < _DAT_004be850) &&
           (dVar6 - dVar5 * _DAT_004be840 < _DAT_004be850)) {
          DAT_005a45c0 = DAT_005a45c0 + 1;
          return;
        }
        iVar17 = iVar17 + 1;
        pfVar19 = pfVar19 + 6;
      } while (iVar17 < DAT_006442f0);
    }
    iVar21 = iVar12 >> 1;
    fVar8 = (float)iVar21;
    iVar17 = g_runtime_terrain_vertex_xyz_buffer + *param_4 * 0xc;
    fVar7 = fVar8 + fVar8;
    iVar3 = g_runtime_terrain_vertex_xyz_buffer + param_3[1] * 0xc;
    if (iVar21 < 0x20) {
      if (iVar21 == 0) goto LAB_004917bc;
      fVar9 = (*pfVar2 + fVar8) - _DAT_006442f8;
      fVar8 = (pfVar2[2] + fVar8) - _DAT_00644300;
      fVar8 = fVar8 * fVar8 + fVar9 * fVar9;
      if (fVar7 * fVar7 * _g_runtime_terrain_lod_error_threshold_x < fVar8) goto LAB_004917bc;
      if (fVar7 * fVar7 <= fVar8 + fVar8) {
        fVar8 = (float)((uint)fVar8 & 0xff800000) * _g_runtime_terrain_lod_error_threshold_z;
        iVar12 = iVar12 >> 2;
        iVar13 = ftol();
        iVar13 = iVar13 + iVar21;
        iVar14 = ftol();
        iVar14 = iVar14 + iVar21;
        fVar9 = (pfVar2[1] + *(float *)(iVar20 + 4)) * _DAT_004be85c;
        uVar11 = sample_runtime_terrain_height(iVar13,iVar14);
        if (ABS((fVar9 - (float)CONCAT22(extraout_var,uVar11)) * fVar7) <= fVar8) {
          if (iVar21 == 1) {
LAB_00491541:
            if (fVar7 <= _DAT_004be7f8) {
LAB_004917bc:
              psVar15 = allocate_terrain_leaf_primitive_node(param_1,param_2,param_3,param_4);
              if (g_runtime_terrain_primitive_list_head == (short *)0x0) {
                g_runtime_terrain_primitive_list_head = psVar15;
                g_runtime_terrain_primitive_list_tail = psVar15;
                return;
              }
              *(short **)((int)g_runtime_terrain_primitive_list_tail + 8) = psVar15;
              g_runtime_terrain_primitive_list_tail = psVar15;
              return;
            }
            uVar23 = iVar13 - iVar21;
            uVar25 = iVar14 - iVar21;
            iVar20 = iVar21 * 2 + -1;
            if ((int)(0x2800 - uVar23 | 0x2800 - uVar25 | uVar25 | uVar23) < 0) goto LAB_004917bc;
            iVar12 = ((int)(uVar23 + 0xc00) >> 7) + (uVar25 + 0xc00 & 0xffffff80);
            uVar23 = (uVar25 + 0xc00 & 0x7f) * 0x80 + (uVar23 + 0xc00 & 0x7f);
            if ((((0x3fff < iVar12) || (iVar12 < 0)) || (0x3fff < uVar23)) ||
               (iVar12 = (&g_runtime_terrain_page_pointer_grid)[iVar12] + uVar23 * 2, iVar20 < 0))
            goto LAB_004917bc;
            puVar18 = (ushort *)(iVar20 * 0x100 + iVar12);
            puVar22 = (ushort *)(iVar12 + iVar20 * 2);
            puVar26 = (ushort *)(iVar12 + iVar20 * 0x102);
            puVar24 = (ushort *)(iVar12 + iVar20 * 0x102);
            do {
              if (((((0x3fff < *puVar22) && ((*puVar22 & 0xe000) != 0xa000)) ||
                   ((0x3fff < *puVar26 && ((*puVar26 & 0xe000) != 0xa000)))) ||
                  ((0x3fff < *puVar18 && ((*puVar18 & 0xe000) != 0xa000)))) ||
                 ((0x3fff < *puVar24 && ((*puVar24 & 0xe000) != 0xa000)))) break;
              iVar20 = iVar20 + -1;
              puVar22 = puVar22 + -1;
              puVar26 = puVar26 + -1;
              puVar18 = puVar18 + -0x80;
              puVar24 = puVar24 + -0x80;
            } while (-1 < iVar20);
            if (iVar20 < 0) goto LAB_004917bc;
          }
          else {
            uVar11 = sample_runtime_terrain_height(iVar13 - iVar12,iVar14 + iVar12);
            if (ABS(((float)CONCAT22(extraout_var_00,uVar11) -
                    (*(float *)(iVar17 + 4) + fVar9) * _DAT_004be85c) * fVar7) <= fVar8) {
              uVar11 = sample_runtime_terrain_height(iVar13 + iVar12,iVar14 + iVar12);
              if (ABS(((float)CONCAT22(extraout_var_01,uVar11) -
                      (fVar9 + *(float *)(iVar20 + 4)) * _DAT_004be85c) * fVar7) <= fVar8) {
                uVar11 = sample_runtime_terrain_height(iVar13 - iVar12,iVar14 - iVar12);
                if ((ABS(((float)CONCAT22(extraout_var_02,uVar11) -
                         (fVar9 + pfVar2[1]) * _DAT_004be85c) * fVar7) <= fVar8) &&
                   (uVar11 = sample_runtime_terrain_height(iVar13 + iVar12,iVar14 - iVar12),
                   ABS(((float)CONCAT22(extraout_var_03,uVar11) -
                       (*(float *)(iVar3 + 4) + fVar9) * _DAT_004be85c) * fVar7) <= fVar8))
                goto LAB_00491541;
              }
            }
          }
        }
      }
    }
    split_terrain_edge_midpoint(param_1);
    split_terrain_edge_midpoint(param_2);
    split_terrain_edge_midpoint(param_3);
    split_terrain_edge_midpoint(param_4);
    puVar10 = g_runtime_terrain_arena_cursor;
    uVar4 = *(undefined2 *)(*(int *)(param_3 + 2) + 2);
    puVar1 = g_runtime_terrain_arena_cursor + 1;
    g_runtime_terrain_arena_cursor = g_runtime_terrain_arena_cursor + 6;
    *puVar1 = *(undefined2 *)(*(int *)(param_4 + 2) + 2);
    *puVar10 = uVar4;
    *(undefined4 *)(puVar10 + 2) = 0;
    *(undefined4 *)(puVar10 + 4) = 0;
    g_runtime_terrain_edge_record_count = g_runtime_terrain_edge_record_count + 1;
    split_terrain_edge_midpoint(puVar10);
    psVar15 = (short *)allocate_terrain_edge_record
                                 (*(undefined2 *)(*(int *)(param_1 + 2) + 2),
                                  *(undefined2 *)(*(int *)(puVar10 + 2) + 2));
    psVar16 = (short *)allocate_terrain_edge_record
                                 (*(undefined2 *)(*(int *)(puVar10 + 2) + 2),
                                  *(undefined2 *)(*(int *)(param_2 + 2) + 2));
    subdivide_or_emit_adaptive_terrain_quad
              (*(undefined2 **)(param_1 + 2),*(undefined2 **)(puVar10 + 2),*(short **)(param_3 + 2),
               psVar15);
    subdivide_or_emit_adaptive_terrain_quad
              (*(undefined2 **)(puVar10 + 2),*(undefined2 **)(param_2 + 2),*(short **)(param_3 + 4),
               psVar16);
    subdivide_or_emit_adaptive_terrain_quad
              (*(undefined2 **)(puVar10 + 4),*(undefined2 **)(param_2 + 4),psVar16,
               *(short **)(param_4 + 4));
    param_4 = *(short **)(param_4 + 2);
    param_2 = *(undefined2 **)(puVar10 + 4);
    param_1 = *(undefined2 **)(param_1 + 4);
    param_3 = psVar15;
  } while( true );
}


