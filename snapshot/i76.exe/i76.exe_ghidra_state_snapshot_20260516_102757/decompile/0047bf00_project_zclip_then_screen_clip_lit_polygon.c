/*
 * Program: i76.exe
 * Function: project_zclip_then_screen_clip_lit_polygon
 * Entry: 0047bf00
 * Signature: uint * __cdecl project_zclip_then_screen_clip_lit_polygon(float * param_1, void * param_2, float * param_3, uint * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO raster table renames v35; confidence=high] Near/far Z clip plus perspective
   projection, then compact screen-space clipping. */

uint * __cdecl
project_zclip_then_screen_clip_lit_polygon
          (float *param_1,void *param_2,float *param_3,uint *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  float *pfVar10;
  uint *puVar11;
  float *pfVar12;
  float *pfVar13;
  float local_67c [4];
  uint local_66c [2];
  float local_664 [402];
  float local_1c;
  uint local_18;
  float local_14;
  float local_10;
  uint *local_c;
  float *local_8;
  
  puVar5 = param_4;
  local_14 = param_1[0x42];
  local_c = &local_18;
  local_10 = param_1[0x4e];
  local_8 = &local_1c;
  uVar6 = 0xff;
  local_18 = 0;
  pfVar9 = param_3;
  puVar11 = param_4;
  do {
    pfVar4 = pfVar9 + 2;
    pfVar9 = pfVar9 + 6;
    uVar8 = (uint)(*pfVar4 < param_1[0x42]) * 2 + (uint)(*pfVar4 < param_1[0x4e]) ^ 1;
    uVar6 = uVar6 & uVar8;
    local_18 = local_18 | uVar8;
    puVar11 = (uint *)((int)puVar11 + -1);
  } while (puVar11 != (uint *)0x0);
  if (uVar6 != 0) {
    return (uint *)0x0;
  }
  pfVar9 = param_3;
  if (local_18 != 0) {
    pfVar4 = local_67c;
    if ((local_18 & 2) != 0) {
      param_4 = (uint *)0x0;
      if (0 < (int)puVar5) {
        local_c = puVar5;
        local_8 = local_664;
        pfVar9 = pfVar4;
        pfVar10 = param_3 + (int)puVar5 * 6 + -6;
        do {
          if (param_3[2] < local_14) {
            pfVar4 = pfVar9;
            if (pfVar10[2] >= local_14) {
              fVar1 = (local_14 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar9[2] = local_14;
              pfVar4 = pfVar9 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              *pfVar9 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar9[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar9[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
            }
          }
          else {
            iVar7 = 6;
            pfVar4 = param_3;
            pfVar13 = pfVar9;
            if (pfVar10[2] < local_14) {
              fVar1 = pfVar10[2];
              fVar2 = param_3[2];
              fVar3 = pfVar10[2];
              pfVar13 = local_8;
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar13 = *pfVar4;
                pfVar4 = pfVar4 + 1;
                pfVar13 = pfVar13 + 1;
              }
              fVar1 = (local_14 - fVar1) / (fVar2 - fVar3);
              pfVar9[2] = local_14;
              local_8 = local_8 + 0xc;
              *pfVar9 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar9[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar9[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
              pfVar4 = pfVar9 + 0xc;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar13 = *pfVar4;
                pfVar4 = pfVar4 + 1;
                pfVar13 = pfVar13 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar4 = pfVar9 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          pfVar9 = pfVar4;
          pfVar10 = param_3;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
        local_c = (uint *)0x0;
      }
      if (param_4 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar4 + (int)param_4 * -6;
    }
    puVar5 = param_4;
    pfVar9 = param_3;
    if ((local_18 & 1) != 0) {
      param_4 = (uint *)0x0;
      if (0 < (int)puVar5) {
        local_c = puVar5;
        local_8 = pfVar4 + 6;
        pfVar9 = pfVar4;
        pfVar10 = param_3 + (int)puVar5 * 6 + -6;
        do {
          if (local_10 <= param_3[2]) {
            pfVar4 = pfVar9;
            if (local_10 > pfVar10[2]) {
              fVar1 = (local_10 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar9[2] = local_10;
              pfVar4 = pfVar9 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              *pfVar9 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar9[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar9[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
            }
          }
          else {
            iVar7 = 6;
            pfVar4 = param_3;
            pfVar13 = local_8;
            pfVar12 = pfVar9;
            if (local_10 <= pfVar10[2]) {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar13 = *pfVar4;
                pfVar4 = pfVar4 + 1;
                pfVar13 = pfVar13 + 1;
              }
              fVar1 = (local_10 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar9[2] = local_10;
              local_8 = local_8 + 0xc;
              *pfVar9 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar9[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar9[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
              pfVar4 = pfVar9 + 0xc;
            }
            else {
              for (; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar12 = *pfVar4;
                pfVar4 = pfVar4 + 1;
                pfVar12 = pfVar12 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar4 = pfVar9 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          pfVar9 = pfVar4;
          pfVar10 = param_3;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
      }
      if (param_4 == (uint *)0x0) {
        return (uint *)0x0;
      }
      pfVar9 = pfVar4 + (int)param_4 * -6;
    }
  }
  if (0 < (int)param_4) {
    local_c = (uint *)((int)local_66c - (int)pfVar9);
    param_3 = (float *)param_4;
    pfVar4 = pfVar9 + 1;
    pfVar10 = local_67c;
    do {
      puVar5 = local_c;
      fVar1 = _DAT_004be764 / pfVar4[1];
      pfVar13 = pfVar4 + 6;
      *pfVar10 = pfVar4[-1] * fVar1 * param_1[2] + *param_1;
      *(float *)((int)local_67c + (-0x18 - (int)pfVar9) + (int)pfVar13) =
           fVar1 * param_1[3] * *pfVar4 + param_1[1];
      *(float *)((int)local_67c + (-0x14 - (int)pfVar9) + (int)pfVar13) = fVar1;
      *(float *)((int)(puVar5 + -6) + (int)pfVar13) = pfVar4[4];
      param_3 = (float *)((int)param_3 + -1);
      pfVar4 = pfVar13;
      pfVar10 = pfVar10 + 6;
    } while (param_3 != (float *)0x0);
  }
  puVar5 = clip_screen_xy_lit_polygon_vertices_compact((int)param_1,param_2,local_67c,param_4);
  return puVar5;
}


