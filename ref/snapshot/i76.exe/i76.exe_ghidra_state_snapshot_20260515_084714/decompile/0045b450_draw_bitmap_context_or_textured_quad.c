/*
 * Program: i76.exe
 * Function: draw_bitmap_context_or_textured_quad
 * Entry: 0045b450
 * Signature: undefined __cdecl draw_bitmap_context_or_textured_quad(float * param_1, int * param_2, int param_3, uint * param_4, int param_5, int param_6, uint * param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Draws/blits a bitmap context directly or submits it as a lit textured quad
   depending on render mode. */

void __cdecl
draw_bitmap_context_or_textured_quad
          (float *param_1,int *param_2,int param_3,uint *param_4,int param_5,int param_6,
          uint *param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = param_2[7];
  iVar2 = param_2[8];
  iVar3 = param_2[9];
  iVar4 = param_2[10];
  iVar6 = (iVar3 - iVar1) + 1;
  iVar7 = (iVar4 - iVar2) + 1;
  if (param_5 == 0) {
    param_5 = iVar6;
    param_6 = iVar7;
  }
  piVar5 = (int *)param_1[0xf];
  if (piVar5[2] == 0) {
    if (((param_5 != iVar6) || (param_6 != iVar7)) &&
       ((param_5 != *param_2 || (param_6 != (param_2[1] << 3) >> 3)))) {
      projection_or_clip_context_helper_0047a220
                (piVar5,param_2,param_3,(int)param_4,param_5 + param_3,param_6 + (int)param_4,
                 param_7,'\0');
      return;
    }
    blit_bitmap_surface_context_clipped_with_palette_blend(piVar5,param_2,param_3,param_4,param_7);
    return;
  }
  local_48 = (float)(iVar6 + param_3);
  local_2c = (float)(iVar7 + (int)param_4);
  local_60 = (float)param_3;
  local_5c = (float)(int)param_4;
  local_58 = _DAT_004bdfd8;
  local_40 = _DAT_004bdfd8;
  local_28 = _DAT_004bdfd8;
  local_10 = _DAT_004bdfd8;
  if (param_7 == (uint *)0x5) {
    local_38 = (float)((param_2[1] << 3) >> 3);
    local_20 = (float)iVar4 / local_38;
    local_38 = (float)iVar2 / local_38;
    local_c = (float)iVar1 / (float)*param_2;
    local_24 = (float)iVar3 / (float)*param_2;
  }
  else {
    local_20 = (float)(((param_2[1] << 3) >> 3) + -1);
    local_38 = (float)iVar4 / local_20;
    local_20 = (float)iVar2 / local_20;
    local_c = (float)iVar1 / (float)(*param_2 + -1);
    local_24 = (float)iVar3 / (float)(*param_2 + -1);
  }
  local_20 = _DAT_004bdfd8 - local_20;
  local_38 = _DAT_004bdfd8 - local_38;
  local_4c = _DAT_004bdfd8;
  local_4 = _DAT_004bdfd8;
  local_54 = local_c;
  local_50 = local_38;
  local_44 = local_5c;
  local_3c = local_24;
  local_34 = local_4c;
  local_30 = local_48;
  local_1c = local_4c;
  local_18 = local_60;
  local_14 = local_2c;
  local_8 = local_20;
  if (piVar5[2] != 1) {
    submit_lit_textured_polygon_to_renderer
              (param_1,&local_60,4,(uint *)(param_2[5] + -8),
               (uint)(-(param_7 != (uint *)0x0) & 0x40U | 0xc));
    return;
  }
  log_cache_memory_status
            (param_1,&local_60,(float *)0x4,(uint *)(param_2[5] + -8),
             (float *)(uint)(-(param_7 != (uint *)0x0) & 0x40U | 0xc));
  return;
}


