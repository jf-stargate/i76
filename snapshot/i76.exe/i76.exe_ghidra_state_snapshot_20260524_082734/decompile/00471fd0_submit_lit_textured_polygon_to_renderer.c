/*
 * Program: i76.exe
 * Function: submit_lit_textured_polygon_to_renderer
 * Entry: 00471fd0
 * Signature: ushort __cdecl submit_lit_textured_polygon_to_renderer(float * param_1, float * param_2, int param_3, uint * param_4, uint param_5)
 */


/* [i76 level/static/material baseline v48]
   name: submit_lit_textured_polygon_to_renderer
   confidence: medium_high
   module: render_submit
   Low-level lit textured polygon submit path. Candidate next trace target for alpha state, keyed
   transparency, and material flags.
   note: Name already matches baseline. */

ushort __cdecl
submit_lit_textured_polygon_to_renderer
          (float *param_1,float *param_2,int param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  ushort in_FPUControlWord;
  ushort local_340;
  float local_31c [192];
  undefined1 *local_1c;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004be598;
  puStack_10 = &DAT_004ba0d0;
  local_14 = ExceptionList;
  local_1c = &stack0xfffffcac;
  if (param_3 == 1) {
    ExceptionList = &local_14;
    local_1c = &stack0xfffffcac;
    uVar2 = submit_single_vertex_or_point_primitive(param_1,param_2,param_4);
    ExceptionList = local_14;
    return uVar2;
  }
  if (param_3 == 2) {
    ExceptionList = &local_14;
    local_1c = &stack0xfffffcac;
    uVar2 = submit_two_vertex_or_line_primitive(param_1,param_2,param_2 + 6,param_4);
    ExceptionList = local_14;
    return uVar2;
  }
  uVar1 = param_5 & 0x1ff;
  if (((param_5 & 4) != 0) && (param_4 == (uint *)0x0)) {
    uVar1 = param_5 & 0x1fb;
  }
  param_5 = uVar1;
  if (((param_5 & 4) != 0) && (((int)(param_4[1] << 3) >> 3 | *param_4) == 1)) {
    param_4 = (uint *)(uint)(byte)param_4[2];
    param_5 = param_5 & 0xfffffffb;
  }
  ExceptionList = &local_14;
  iVar3 = (*(code *)(&g_geo_raster_clip_prepare_table)[param_5])
                    (param_1,local_31c,param_2,param_3,param_5);
  local_340 = 0;
  if (iVar3 != 0) {
    if ((char)(param_5 >> 8) != '\0') {
      param_5 = param_5 & 0xff;
      iVar4 = 0;
      if (0 < iVar3) {
        pfVar5 = local_31c;
        do {
          if ((int)((uint)((float)((((int *)param_1[0xf])[1] << 3) >> 3) - pfVar5[1]) |
                    (uint)((float)*(int *)param_1[0xf] - *pfVar5) | (uint)*pfVar5 | (uint)pfVar5[1])
              < 0) {
            iVar3 = (*(code *)(&g_geo_raster_clip_prepare_table)[param_5])
                              (param_1,local_31c,param_2,iVar3,param_5);
            if (iVar3 == 0) {
              ExceptionList = local_14;
              return 0;
            }
            break;
          }
          iVar4 = iVar4 + 1;
          pfVar5 = pfVar5 + 6;
        } while (iVar4 < iVar3);
      }
    }
    local_340 = in_FPUControlWord & 0xf3ff | 0x800;
    local_8 = 0;
    (*(code *)(&g_geo_raster_draw_submit_table_or_mode_table)[param_5])
              (param_1[0xf],local_31c,iVar3,param_4);
  }
  ExceptionList = local_14;
  return local_340;
}


