/*
 * Program: i76.exe
 * Function: i76_runtime_bin_terrain_polygon_work_record
 * Entry: 0048fe10
 * Signature: int * __cdecl i76_runtime_bin_terrain_polygon_work_record(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_0048fe10. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_bin_terrain_primitive_for_scan_or_span_render :: Binning helper used after
   polygon submission/render prep.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_bin_terrain_polygon_work_record ::
   Bins prepared/clipped terrain polygon work record into scan/span buckets based on render
   depth/range.
   
   [cgpt_i76exe_terrain_runtime_structs_v12] proposed=i76_runtime_bin_terrain_polygon_work_record ::
   Bins current polygon work record into depth/scan buckets and advances cursor by header +
   vertex_count*0x18 or table-driven fixed size.
   [cgpt-i76-v36 medium] Bins terrain polygon work record into scan/depth buckets. */

int * __cdecl i76_runtime_bin_terrain_polygon_work_record(float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  float *pfVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float local_10;
  float local_c;
  
  iVar3 = *g_runtime_terrain_polygon_work_record_cursor;
  if (param_1 < g_runtime_terrain_render_min_or_near_bound) {
    return g_runtime_terrain_polygon_work_record_cursor;
  }
  local_c = SUB84((double)((param_1 - g_runtime_terrain_render_min_or_near_bound) +
                          (float)_DAT_004faf18),0);
  if (0x1000 < (int)local_c) {
    return g_runtime_terrain_polygon_work_record_cursor;
  }
  if (0x20 < iVar3) {
    return g_runtime_terrain_polygon_work_record_cursor;
  }
  iVar8 = g_runtime_terrain_polygon_work_record_cursor[3];
  if (iVar8 == 0xc) {
    return g_runtime_terrain_polygon_work_record_cursor;
  }
  if (iVar8 == 1) {
    local_10 = (float)g_runtime_terrain_polygon_work_record_cursor[7];
    iVar8 = *g_runtime_terrain_polygon_work_record_cursor;
    if (1 < iVar8) {
      pfVar5 = (float *)(g_runtime_terrain_polygon_work_record_cursor + 0xd);
      iVar7 = iVar8 + -1;
      do {
        if (_DAT_004be7d4 < *pfVar5 - local_10) {
          local_10 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    fVar9 = (float)g_runtime_terrain_polygon_work_record_cursor[7];
    if (1 < iVar8) {
      pfVar5 = (float *)(g_runtime_terrain_polygon_work_record_cursor + 0xd);
      iVar7 = iVar8 + -1;
      do {
        if (*pfVar5 - fVar9 < _DAT_004be7d4) {
          fVar9 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    fVar1 = (float)g_runtime_terrain_polygon_work_record_cursor[9];
    if (1 < iVar8) {
      pfVar5 = (float *)(g_runtime_terrain_polygon_work_record_cursor + 0xf);
      iVar8 = iVar8 + -1;
      do {
        if (_DAT_004be7d4 < *pfVar5 - fVar1) {
          fVar1 = *pfVar5;
        }
        pfVar5 = pfVar5 + 6;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    i76_runtime_add_terrain_scan_bucket_span_entry
              (local_c,param_1,fVar1 - g_runtime_terrain_render_min_or_near_bound,fVar9,local_10);
  }
  else if (iVar8 == 0xb) {
    i76_runtime_add_terrain_scan_bucket_span_entry
              (local_c,param_1,
               ((float)g_runtime_terrain_polygon_work_record_cursor[10] +
               (float)g_runtime_terrain_polygon_work_record_cursor[0xb]) -
               g_runtime_terrain_render_min_or_near_bound,
               (float)g_runtime_terrain_polygon_work_record_cursor[8] -
               (float)g_runtime_terrain_polygon_work_record_cursor[0xb],
               (float)g_runtime_terrain_polygon_work_record_cursor[0xb] +
               (float)g_runtime_terrain_polygon_work_record_cursor[8]);
  }
  else if (1 < iVar8) {
    if (iVar3 == 0) {
      fVar9 = -0.0;
      DAT_006543a8 = (undefined4 *)(g_runtime_terrain_scan_bucket_table + (int)local_c * 0xc);
      pfVar5 = (float *)*DAT_006543a8;
      if (pfVar5 == (float *)0x0) {
        fVar9 = -NAN;
      }
      else {
        do {
          if (((((float)g_runtime_terrain_polygon_work_record_cursor[8] -
                 (float)g_runtime_terrain_polygon_work_record_cursor[0xb] < pfVar5[1]) &&
               (*pfVar5 <=
                (float)g_runtime_terrain_polygon_work_record_cursor[8] -
                (float)g_runtime_terrain_polygon_work_record_cursor[0xb])) ||
              (((float)g_runtime_terrain_polygon_work_record_cursor[8] +
                (float)g_runtime_terrain_polygon_work_record_cursor[0xb] < pfVar5[1] &&
               (*pfVar5 <=
                (float)g_runtime_terrain_polygon_work_record_cursor[8] +
                (float)g_runtime_terrain_polygon_work_record_cursor[0xb])))) &&
             ((uint)pfVar5[2] < (uint)fVar9)) {
            fVar9 = pfVar5[2];
          }
          pfVar5 = (float *)pfVar5[3];
          _DAT_00654390 = pfVar5;
        } while (pfVar5 != (float *)0x0);
      }
    }
    else {
      fVar1 = (float)g_runtime_terrain_polygon_work_record_cursor[7];
      if (1 < iVar3) {
        pfVar5 = (float *)(g_runtime_terrain_polygon_work_record_cursor + 0xd);
        iVar8 = iVar3 + -1;
        do {
          if (_DAT_004be7d4 < *pfVar5 - fVar1) {
            fVar1 = *pfVar5;
          }
          pfVar5 = pfVar5 + 6;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      fVar2 = (float)g_runtime_terrain_polygon_work_record_cursor[7];
      if (1 < iVar3) {
        pfVar5 = (float *)(g_runtime_terrain_polygon_work_record_cursor + 0xd);
        iVar8 = iVar3 + -1;
        do {
          if (*pfVar5 - fVar2 < _DAT_004be7d4) {
            fVar2 = *pfVar5;
          }
          pfVar5 = pfVar5 + 6;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      fVar9 = -0.0;
      DAT_006543a8 = (undefined4 *)(g_runtime_terrain_scan_bucket_table + (int)local_c * 0xc);
      pfVar5 = (float *)*DAT_006543a8;
      if (pfVar5 == (float *)0x0) {
        fVar9 = -NAN;
      }
      else {
        do {
          if ((((fVar2 < pfVar5[1]) && (*pfVar5 <= fVar2)) ||
              ((fVar1 < pfVar5[1] && (*pfVar5 <= fVar1)))) && ((uint)pfVar5[2] < (uint)fVar9)) {
            fVar9 = pfVar5[2];
          }
          pfVar5 = (float *)pfVar5[3];
        } while (pfVar5 != (float *)0x0);
        _DAT_00654390 = (float *)0x0;
      }
    }
    if (0 < (int)fVar9) {
      local_c = fVar9;
    }
  }
  if ((g_runtime_terrain_polygon_work_record_cursor[3] == 5) ||
     (g_runtime_terrain_polygon_work_record_cursor[3] == 6)) {
    iVar8 = 0;
    if (0 < DAT_0059c540) {
      puVar6 = &DAT_0059c4a4;
      do {
        if (*(int *)*puVar6 == g_runtime_terrain_polygon_work_record_cursor[7]) {
          puVar6 = (undefined4 *)(&DAT_0059c4a0 + iVar8 * 8);
          *(float *)((&DAT_0059c4a4)[iVar8 * 2] + 0xc) = local_c;
          goto LAB_0049015c;
        }
        iVar8 = iVar8 + 1;
        puVar6 = puVar6 + 2;
      } while (iVar8 < DAT_0059c540);
    }
    puVar6 = (undefined4 *)0x0;
LAB_0049015c:
    piVar4 = g_runtime_terrain_polygon_work_record_cursor;
    if ((puVar6 != (undefined4 *)0x0) && (*(int *)*puVar6 != 0)) {
      *(int *)(puVar6[1] + 4) = g_runtime_terrain_polygon_work_record_cursor[0xc];
      *(int *)(puVar6[1] + 8) = piVar4[0xd];
      return g_runtime_terrain_polygon_work_record_cursor;
    }
  }
  DAT_00654384 = (int *)(DAT_006543b0 + (int)local_c * 0xc);
  iVar8 = *DAT_00654384;
  if (iVar8 == 0) {
    *DAT_00654384 = (int)g_runtime_terrain_polygon_work_record_cursor;
    DAT_00654384[1] = (int)g_runtime_terrain_polygon_work_record_cursor;
    g_runtime_terrain_polygon_work_record_cursor[6] = 0;
  }
  else if (g_runtime_terrain_polygon_work_record_cursor[3] == 10) {
    DAT_00654394 = *(int *)(iVar8 + 0x14);
    iVar7 = DAT_00654394;
    if (DAT_00654394 != 0) {
      do {
        DAT_00654394 = iVar7;
        if (3 < *(int *)(DAT_00654394 + 0xc)) {
          g_runtime_terrain_polygon_work_record_cursor[4] = (int)param_1;
          *(int **)(iVar8 + 0x14) = g_runtime_terrain_polygon_work_record_cursor;
          g_runtime_terrain_polygon_work_record_cursor[6] = iVar8;
          g_runtime_terrain_polygon_work_record_cursor[5] = DAT_00654394;
          *(int **)(DAT_00654394 + 0x18) = g_runtime_terrain_polygon_work_record_cursor;
          DAT_00654384[2] = DAT_00654384[2] + 1;
          piVar4 = g_runtime_terrain_polygon_work_record_cursor;
          g_runtime_terrain_polygon_work_record_cursor =
               (int *)((int)g_runtime_terrain_polygon_work_record_cursor +
                      *(int *)(&g_runtime_polygon_record_fixed_size_table +
                              g_runtime_terrain_polygon_work_record_cursor[3] * 4) + 0x1c);
          return piVar4;
        }
        iVar7 = *(int *)(DAT_00654394 + 0x14);
        iVar8 = DAT_00654394;
      } while (*(int *)(DAT_00654394 + 0x14) != 0);
      DAT_00654394 = 0;
    }
  }
  else {
    if (((*(float *)(iVar8 + 0x10) < param_1) && (3 < *(int *)(iVar8 + 0xc))) &&
       (*(int *)(iVar8 + 0xc) < 10)) {
      DAT_00654394 = iVar8;
      g_runtime_terrain_polygon_work_record_cursor[4] = (int)param_1;
      g_runtime_terrain_polygon_work_record_cursor[5] = DAT_00654394;
      *(int **)(DAT_00654394 + 0x18) = g_runtime_terrain_polygon_work_record_cursor;
      g_runtime_terrain_polygon_work_record_cursor[6] = 0;
      *DAT_00654384 = (int)g_runtime_terrain_polygon_work_record_cursor;
      if (iVar3 == 0) {
        g_runtime_terrain_polygon_work_record_cursor =
             (int *)((int)g_runtime_terrain_polygon_work_record_cursor +
                    *(int *)(&g_runtime_polygon_record_fixed_size_table +
                            g_runtime_terrain_polygon_work_record_cursor[3] * 4) + 0x1c);
      }
      else {
        g_runtime_terrain_polygon_work_record_cursor =
             g_runtime_terrain_polygon_work_record_cursor + iVar3 * 6 + 7;
      }
      DAT_00654384[2] = DAT_00654384[2] + 1;
      return (int *)*DAT_00654384;
    }
    DAT_00654394 = *(int *)(iVar8 + 0x14);
    iVar7 = DAT_00654394;
    if (DAT_00654394 != 0) {
      do {
        DAT_00654394 = iVar7;
        if (((*(float *)(DAT_00654394 + 0x10) < param_1) && (3 < *(int *)(DAT_00654394 + 0xc))) &&
           (*(int *)(DAT_00654394 + 0xc) < 10)) {
          g_runtime_terrain_polygon_work_record_cursor[4] = (int)param_1;
          *(int **)(iVar8 + 0x14) = g_runtime_terrain_polygon_work_record_cursor;
          g_runtime_terrain_polygon_work_record_cursor[6] = iVar8;
          g_runtime_terrain_polygon_work_record_cursor[5] = DAT_00654394;
          *(int **)(DAT_00654394 + 0x18) = g_runtime_terrain_polygon_work_record_cursor;
          DAT_00654384[2] = DAT_00654384[2] + 1;
          piVar4 = g_runtime_terrain_polygon_work_record_cursor;
          if (iVar3 == 0) {
            g_runtime_terrain_polygon_work_record_cursor =
                 (int *)((int)g_runtime_terrain_polygon_work_record_cursor +
                        *(int *)(&g_runtime_polygon_record_fixed_size_table +
                                g_runtime_terrain_polygon_work_record_cursor[3] * 4) + 0x1c);
            return piVar4;
          }
          g_runtime_terrain_polygon_work_record_cursor =
               g_runtime_terrain_polygon_work_record_cursor + iVar3 * 6 + 7;
          return piVar4;
        }
        iVar7 = *(int *)(DAT_00654394 + 0x14);
        iVar8 = DAT_00654394;
      } while (*(int *)(DAT_00654394 + 0x14) != 0);
      DAT_00654394 = 0;
    }
  }
  g_runtime_terrain_polygon_work_record_active = (int *)DAT_00654384[1];
  DAT_00654384[2] = DAT_00654384[2] + 1;
  g_runtime_terrain_polygon_work_record_cursor[4] = (int)param_1;
  DAT_00654384[1] = (int)g_runtime_terrain_polygon_work_record_cursor;
  *(int **)((int)g_runtime_terrain_polygon_work_record_active + 0x14) =
       g_runtime_terrain_polygon_work_record_cursor;
  if (iVar3 == 0) {
    g_runtime_terrain_polygon_work_record_cursor =
         (int *)((int)g_runtime_terrain_polygon_work_record_cursor +
                *(int *)(&g_runtime_polygon_record_fixed_size_table +
                        g_runtime_terrain_polygon_work_record_cursor[3] * 4) + 0x1c);
  }
  else {
    g_runtime_terrain_polygon_work_record_cursor =
         g_runtime_terrain_polygon_work_record_cursor + iVar3 * 6 + 7;
  }
  g_runtime_terrain_polygon_work_record_active =
       *(int **)((int)g_runtime_terrain_polygon_work_record_active + 0x14);
  g_runtime_terrain_polygon_work_record_active[5] = 0;
  return g_runtime_terrain_polygon_work_record_active;
}


