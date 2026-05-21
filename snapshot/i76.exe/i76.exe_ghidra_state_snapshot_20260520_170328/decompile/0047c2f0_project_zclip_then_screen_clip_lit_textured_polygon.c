/*
 * Program: i76.exe
 * Function: project_zclip_then_screen_clip_lit_textured_polygon
 * Entry: 0047c2f0
 * Signature: uint * __cdecl project_zclip_then_screen_clip_lit_textured_polygon(float * param_1, void * param_2, float * param_3, uint * param_4, uint param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO raster table renames v35; confidence=high] Near/far Z clip plus perspective
   projection, then full lit textured screen-space clipping. */

uint * __cdecl
project_zclip_then_screen_clip_lit_textured_polygon
          (float *param_1,void *param_2,float *param_3,uint *param_4,uint param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  uint uVar9;
  float *pfVar10;
  uint *puVar11;
  float *pfVar12;
  float *pfVar13;
  float local_67c [6];
  float local_664 [402];
  float local_1c;
  uint local_18;
  float local_14;
  float local_10;
  uint *local_c;
  float *local_8;
  
  puVar4 = param_4;
  local_14 = param_1[0x42];
  local_c = &local_18;
  local_10 = param_1[0x4e];
  local_8 = &local_1c;
  uVar5 = 0xff;
  local_18 = 0;
  pfVar7 = param_3;
  puVar11 = param_4;
  do {
    pfVar8 = pfVar7 + 2;
    pfVar7 = pfVar7 + 6;
    uVar9 = (uint)(*pfVar8 < param_1[0x42]) * 2 + (uint)(*pfVar8 < param_1[0x4e]) ^ 1;
    uVar5 = uVar5 & uVar9;
    local_18 = local_18 | uVar9;
    puVar11 = (uint *)((int)puVar11 + -1);
  } while (puVar11 != (uint *)0x0);
  if (uVar5 != 0) {
    return (uint *)0x0;
  }
  if (local_18 != 0) {
    pfVar7 = local_67c;
    if ((local_18 & 2) != 0) {
      param_4 = (uint *)0x0;
      if (0 < (int)puVar4) {
        local_c = puVar4;
        local_8 = local_664;
        pfVar8 = pfVar7;
        pfVar10 = param_3 + (int)puVar4 * 6 + -6;
        do {
          if (param_3[2] < local_14) {
            pfVar7 = pfVar8;
            if (pfVar10[2] >= local_14) {
              fVar1 = (local_14 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar8[2] = local_14;
              pfVar7 = pfVar8 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              *pfVar8 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar8[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar8[3] = (param_3[3] - pfVar10[3]) * fVar1 + pfVar10[3];
              pfVar8[4] = (param_3[4] - pfVar10[4]) * fVar1 + pfVar10[4];
              pfVar8[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
            }
          }
          else {
            iVar6 = 6;
            pfVar7 = param_3;
            pfVar13 = pfVar8;
            if (pfVar10[2] < local_14) {
              fVar1 = pfVar10[2];
              fVar2 = param_3[2];
              fVar3 = pfVar10[2];
              pfVar13 = local_8;
              for (; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar13 = *pfVar7;
                pfVar7 = pfVar7 + 1;
                pfVar13 = pfVar13 + 1;
              }
              fVar1 = (local_14 - fVar1) / (fVar2 - fVar3);
              pfVar8[2] = local_14;
              local_8 = local_8 + 0xc;
              *pfVar8 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar8[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar8[3] = (param_3[3] - pfVar10[3]) * fVar1 + pfVar10[3];
              pfVar8[4] = (param_3[4] - pfVar10[4]) * fVar1 + pfVar10[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar8[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
              pfVar7 = pfVar8 + 0xc;
            }
            else {
              for (; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar13 = *pfVar7;
                pfVar7 = pfVar7 + 1;
                pfVar13 = pfVar13 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar7 = pfVar8 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          pfVar8 = pfVar7;
          pfVar10 = param_3;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
        local_c = (uint *)0x0;
      }
      if (param_4 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar7 + (int)param_4 * -6;
    }
    puVar4 = param_4;
    if ((local_18 & 1) != 0) {
      param_4 = (uint *)0x0;
      if (0 < (int)puVar4) {
        local_c = puVar4;
        local_8 = pfVar7 + 6;
        pfVar8 = pfVar7;
        pfVar10 = param_3 + (int)puVar4 * 6 + -6;
        do {
          if (local_10 <= param_3[2]) {
            pfVar7 = pfVar8;
            if (local_10 > pfVar10[2]) {
              fVar1 = (local_10 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar8[2] = local_10;
              pfVar7 = pfVar8 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              *pfVar8 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar8[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar8[3] = (param_3[3] - pfVar10[3]) * fVar1 + pfVar10[3];
              pfVar8[4] = (param_3[4] - pfVar10[4]) * fVar1 + pfVar10[4];
              pfVar8[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
            }
          }
          else {
            iVar6 = 6;
            pfVar7 = param_3;
            pfVar13 = local_8;
            pfVar12 = pfVar8;
            if (local_10 <= pfVar10[2]) {
              for (; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar13 = *pfVar7;
                pfVar7 = pfVar7 + 1;
                pfVar13 = pfVar13 + 1;
              }
              fVar1 = (local_10 - pfVar10[2]) / (param_3[2] - pfVar10[2]);
              pfVar8[2] = local_10;
              local_8 = local_8 + 0xc;
              *pfVar8 = (*param_3 - *pfVar10) * fVar1 + *pfVar10;
              pfVar8[1] = (param_3[1] - pfVar10[1]) * fVar1 + pfVar10[1];
              pfVar8[3] = (param_3[3] - pfVar10[3]) * fVar1 + pfVar10[3];
              pfVar8[4] = (param_3[4] - pfVar10[4]) * fVar1 + pfVar10[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar8[5] = (param_3[5] - pfVar10[5]) * fVar1 + pfVar10[5];
              pfVar7 = pfVar8 + 0xc;
            }
            else {
              for (; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar12 = *pfVar7;
                pfVar7 = pfVar7 + 1;
                pfVar12 = pfVar12 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar7 = pfVar8 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          pfVar8 = pfVar7;
          pfVar10 = param_3;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
      }
      if (param_4 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar7 + (int)param_4 * -6;
    }
  }
  if ((param_5 & 2) == 0) {
    if (0 < (int)param_4) {
      pfVar7 = local_67c + 1;
      local_c = param_4;
      pfVar8 = param_3 + 3;
      do {
        fVar1 = _DAT_004be764 / pfVar8[-1];
        pfVar7[-1] = pfVar8[-3] * fVar1 * param_1[2] + *param_1;
        *pfVar7 = fVar1 * pfVar8[-2] * param_1[3] + param_1[1];
        pfVar7[1] = fVar1;
        if (*pfVar8 < _DAT_004be770) {
          *pfVar8 = 0.0;
        }
        if (pfVar8[1] < _DAT_004be770) {
          pfVar8[1] = 0.0;
        }
        if (_DAT_004be764 < *pfVar8) {
          *pfVar8 = 1.0;
        }
        if (_DAT_004be764 < pfVar8[1]) {
          pfVar8[1] = 1.0;
        }
        pfVar7 = pfVar7 + 6;
        *(float *)((int)pfVar8 + ((int)local_67c - (int)param_3)) = fVar1 * *pfVar8;
        *(float *)((int)pfVar8 + (int)local_67c + (4 - (int)param_3)) = fVar1 * pfVar8[1];
        *(float *)((int)pfVar8 + (int)local_67c + (8 - (int)param_3)) = pfVar8[2];
        local_c = (uint *)((int)local_c + -1);
        pfVar8 = pfVar8 + 6;
      } while (local_c != (uint *)0x0);
    }
  }
  else if (0 < (int)param_4) {
    pfVar7 = local_67c + 1;
    local_c = param_4;
    pfVar8 = param_3 + 3;
    do {
      fVar1 = _DAT_004be764 / pfVar8[-1];
      pfVar7[-1] = pfVar8[-3] * fVar1 * param_1[2] + *param_1;
      *pfVar7 = fVar1 * pfVar8[-2] * param_1[3] + param_1[1];
      pfVar7[1] = fVar1;
      if (*pfVar8 < _DAT_004be768) {
        *pfVar8 = -32.0;
      }
      if (_DAT_004be76c < *pfVar8) {
        *pfVar8 = 32.0;
      }
      if (pfVar8[1] < _DAT_004be768) {
        pfVar8[1] = -32.0;
      }
      if (_DAT_004be76c < pfVar8[1]) {
        pfVar8[1] = 32.0;
      }
      pfVar7 = pfVar7 + 6;
      pfVar10 = pfVar8 + 6;
      *(float *)((int)local_67c + (-0x18 - (int)param_3) + (int)pfVar10) = fVar1 * *pfVar8;
      *(float *)((int)local_67c + (-0x14 - (int)param_3) + (int)pfVar10) = fVar1 * pfVar8[1];
      *(float *)((int)local_67c + (-0x10 - (int)param_3) + (int)pfVar10) = pfVar8[2];
      local_c = (uint *)((int)local_c + -1);
      pfVar8 = pfVar10;
    } while (local_c != (uint *)0x0);
  }
  puVar4 = clip_screen_xy_lit_textured_polygon_vertices((int)param_1,param_2,local_67c,param_4);
  if (((param_5 & 0x10) == 0) && (0 < (int)puVar4)) {
    pfVar7 = (float *)((int)param_2 + 0xc);
    puVar11 = puVar4;
    do {
      fVar1 = _DAT_004be764 / pfVar7[-1];
      puVar11 = (uint *)((int)puVar11 + -1);
      *pfVar7 = fVar1 * *pfVar7;
      pfVar7[1] = fVar1 * pfVar7[1];
      pfVar7 = pfVar7 + 6;
    } while (puVar11 != (uint *)0x0);
  }
  return puVar4;
}


