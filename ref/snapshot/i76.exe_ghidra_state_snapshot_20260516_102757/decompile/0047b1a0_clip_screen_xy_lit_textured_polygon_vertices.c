/*
 * Program: i76.exe
 * Function: clip_screen_xy_lit_textured_polygon_vertices
 * Entry: 0047b1a0
 * Signature: uint * __cdecl clip_screen_xy_lit_textured_polygon_vertices(int param_1, void * param_2, float * param_3, uint * param_4)
 */


/* [cgpt i76.exe GEO raster table renames v35; confidence=high] Screen-space X/Y clipper preserving
   0x18-byte lit textured vertex attributes x,y,z,u,v,light. */

uint * __cdecl
clip_screen_xy_lit_textured_polygon_vertices(int param_1,void *param_2,float *param_3,uint *param_4)

{
  float fVar1;
  bool bVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  uint uVar7;
  float *pfVar8;
  float *pfVar9;
  uint *puVar10;
  float *pfVar11;
  float *pfVar12;
  float local_ca4 [6];
  float local_c8c [798];
  float local_14;
  uint local_10;
  uint *local_c;
  float *local_8;
  
  puVar3 = param_4;
  local_c = &local_10;
  local_8 = &local_14;
  uVar4 = 0xff;
  local_10 = 0;
  pfVar9 = param_3;
  puVar10 = param_4;
  do {
    fVar1 = *pfVar9;
    pfVar6 = pfVar9 + 1;
    pfVar9 = pfVar9 + 6;
    uVar7 = (((uint)(fVar1 < *(float *)(param_1 + 0x1c)) * 2 +
             (uint)(fVar1 < *(float *)(param_1 + 0x24))) * 2 +
            (uint)(*pfVar6 < *(float *)(param_1 + 0x20))) * 2 +
            (uint)(*pfVar6 < *(float *)(param_1 + 0x28)) ^ 5;
    uVar4 = uVar4 & uVar7;
    local_10 = local_10 | uVar7;
    puVar10 = (uint *)((int)puVar10 + -1);
  } while (puVar10 != (uint *)0x0);
  if (uVar4 != 0) {
    return (uint *)0x0;
  }
  if (local_10 != 0) {
    pfVar9 = local_ca4;
    if ((local_10 & 8) != 0) {
      param_4 = (uint *)0x0;
      if (0 < (int)puVar3) {
        local_8 = local_c8c;
        local_c = puVar3;
        pfVar6 = pfVar9;
        pfVar8 = param_3 + (int)puVar3 * 6 + -6;
        do {
          bVar2 = *pfVar8 < *(float *)(param_1 + 0x1c);
          if (*param_3 < *(float *)(param_1 + 0x1c)) {
            pfVar9 = pfVar6;
            if (!bVar2) {
              fVar1 = (*(float *)(param_1 + 0x1c) - *pfVar8) / (*param_3 - *pfVar8);
              *pfVar6 = *(float *)(param_1 + 0x1c);
              pfVar9 = pfVar6 + 6;
              local_8 = local_8 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              pfVar6[1] = (param_3[1] - pfVar8[1]) * fVar1 + pfVar8[1];
              pfVar6[2] = (param_3[2] - pfVar8[2]) * fVar1 + pfVar8[2];
              pfVar6[3] = (param_3[3] - pfVar8[3]) * fVar1 + pfVar8[3];
              pfVar6[4] = (param_3[4] - pfVar8[4]) * fVar1 + pfVar8[4];
              pfVar6[5] = (param_3[5] - pfVar8[5]) * fVar1 + pfVar8[5];
            }
          }
          else {
            iVar5 = 6;
            pfVar9 = param_3;
            pfVar12 = local_8;
            pfVar11 = pfVar6;
            if (bVar2) {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar12 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar12 = pfVar12 + 1;
              }
              fVar1 = (*(float *)(param_1 + 0x1c) - *pfVar8) / (*param_3 - *pfVar8);
              *pfVar6 = *(float *)(param_1 + 0x1c);
              local_8 = local_8 + 0xc;
              pfVar6[1] = (param_3[1] - pfVar8[1]) * fVar1 + pfVar8[1];
              pfVar6[2] = (param_3[2] - pfVar8[2]) * fVar1 + pfVar8[2];
              pfVar6[3] = (param_3[3] - pfVar8[3]) * fVar1 + pfVar8[3];
              pfVar6[4] = (param_3[4] - pfVar8[4]) * fVar1 + pfVar8[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar6[5] = (param_3[5] - pfVar8[5]) * fVar1 + pfVar8[5];
              pfVar9 = pfVar6 + 0xc;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar11 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar11 = pfVar11 + 1;
              }
              local_8 = local_8 + 6;
              param_4 = (uint *)((int)param_4 + 1);
              pfVar9 = pfVar6 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          pfVar6 = pfVar9;
          pfVar8 = param_3;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
        local_c = (uint *)0x0;
      }
      if (param_4 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar9 + (int)param_4 * -6;
    }
    puVar3 = param_4;
    puVar10 = param_4;
    if ((local_10 & 2) != 0) {
      iVar5 = (int)param_4 * 6;
      param_4 = (uint *)0x0;
      puVar10 = (uint *)0x0;
      if (0 < (int)puVar3) {
        local_c = puVar3;
        local_8 = pfVar9 + 6;
        pfVar6 = param_3 + iVar5 + -6;
        pfVar8 = pfVar9;
        do {
          bVar2 = pfVar6[1] < *(float *)(param_1 + 0x20);
          if (param_3[1] < *(float *)(param_1 + 0x20)) {
            pfVar9 = pfVar8;
            if (!bVar2) {
              fVar1 = (*(float *)(param_1 + 0x20) - pfVar6[1]) / (param_3[1] - pfVar6[1]);
              pfVar8[1] = *(float *)(param_1 + 0x20);
              pfVar9 = pfVar8 + 6;
              *pfVar8 = (*param_3 - *pfVar6) * fVar1 + *pfVar6;
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
            }
          }
          else {
            iVar5 = 6;
            pfVar9 = param_3;
            pfVar12 = local_8;
            pfVar11 = pfVar8;
            if (bVar2) {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar12 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar12 = pfVar12 + 1;
              }
              fVar1 = (*(float *)(param_1 + 0x20) - pfVar6[1]) / (param_3[1] - pfVar6[1]);
              pfVar8[1] = *(float *)(param_1 + 0x20);
              local_8 = local_8 + 0xc;
              *pfVar8 = (*param_3 - *pfVar6) * fVar1 + *pfVar6;
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
              pfVar9 = pfVar8 + 0xc;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar11 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar11 = pfVar11 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar9 = pfVar8 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          puVar10 = param_4;
          pfVar6 = param_3;
          pfVar8 = pfVar9;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
      }
      if (puVar10 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar9 + (int)puVar10 * -6;
    }
    puVar3 = puVar10;
    if ((local_10 & 4) != 0) {
      param_4 = (uint *)0x0;
      puVar3 = (uint *)0x0;
      if (0 < (int)puVar10) {
        local_c = puVar10;
        local_8 = pfVar9 + 6;
        pfVar6 = param_3 + (int)puVar10 * 6 + -6;
        pfVar8 = pfVar9;
        do {
          bVar2 = *(float *)(param_1 + 0x24) <= *pfVar6;
          if (*(float *)(param_1 + 0x24) <= *param_3) {
            pfVar9 = pfVar8;
            if (!bVar2) {
              fVar1 = (*(float *)(param_1 + 0x24) - *pfVar6) / (*param_3 - *pfVar6);
              *pfVar8 = *(float *)(param_1 + 0x24);
              pfVar9 = pfVar8 + 6;
              pfVar8[1] = (param_3[1] - pfVar6[1]) * fVar1 + pfVar6[1];
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
            }
          }
          else {
            iVar5 = 6;
            pfVar9 = param_3;
            pfVar12 = local_8;
            pfVar11 = pfVar8;
            if (bVar2) {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar12 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar12 = pfVar12 + 1;
              }
              fVar1 = (*(float *)(param_1 + 0x24) - *pfVar6) / (*param_3 - *pfVar6);
              *pfVar8 = *(float *)(param_1 + 0x24);
              local_8 = local_8 + 0xc;
              pfVar8[1] = (param_3[1] - pfVar6[1]) * fVar1 + pfVar6[1];
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
              pfVar9 = pfVar8 + 0xc;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar11 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar11 = pfVar11 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar9 = pfVar8 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          puVar3 = param_4;
          pfVar6 = param_3;
          pfVar8 = pfVar9;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
      }
      if (puVar3 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar9 + (int)puVar3 * -6;
    }
    param_4 = puVar3;
    if ((local_10 & 1) != 0) {
      param_4 = (uint *)0x0;
      puVar10 = (uint *)0x0;
      if (0 < (int)puVar3) {
        local_c = puVar3;
        local_8 = pfVar9 + 6;
        pfVar6 = param_3 + (int)puVar3 * 6 + -6;
        pfVar8 = pfVar9;
        do {
          bVar2 = *(float *)(param_1 + 0x28) <= pfVar6[1];
          if (*(float *)(param_1 + 0x28) <= param_3[1]) {
            pfVar9 = pfVar8;
            if (!bVar2) {
              fVar1 = (*(float *)(param_1 + 0x28) - pfVar6[1]) / (param_3[1] - pfVar6[1]);
              pfVar8[1] = *(float *)(param_1 + 0x28);
              pfVar9 = pfVar8 + 6;
              *pfVar8 = (*param_3 - *pfVar6) * fVar1 + *pfVar6;
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
            }
          }
          else {
            iVar5 = 6;
            pfVar9 = param_3;
            pfVar12 = local_8;
            pfVar11 = pfVar8;
            if (bVar2) {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar12 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar12 = pfVar12 + 1;
              }
              fVar1 = (*(float *)(param_1 + 0x28) - pfVar6[1]) / (param_3[1] - pfVar6[1]);
              pfVar8[1] = *(float *)(param_1 + 0x28);
              local_8 = local_8 + 0xc;
              *pfVar8 = (*param_3 - *pfVar6) * fVar1 + *pfVar6;
              pfVar8[2] = (param_3[2] - pfVar6[2]) * fVar1 + pfVar6[2];
              pfVar8[3] = (param_3[3] - pfVar6[3]) * fVar1 + pfVar6[3];
              pfVar8[4] = (param_3[4] - pfVar6[4]) * fVar1 + pfVar6[4];
              param_4 = (uint *)((int)param_4 + 2);
              pfVar8[5] = (param_3[5] - pfVar6[5]) * fVar1 + pfVar6[5];
              pfVar9 = pfVar8 + 0xc;
            }
            else {
              for (; iVar5 != 0; iVar5 = iVar5 + -1) {
                *pfVar11 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar11 = pfVar11 + 1;
              }
              param_4 = (uint *)((int)param_4 + 1);
              local_8 = local_8 + 6;
              pfVar9 = pfVar8 + 6;
            }
          }
          local_c = (uint *)((int)local_c + -1);
          puVar10 = param_4;
          pfVar6 = param_3;
          pfVar8 = pfVar9;
          param_3 = param_3 + 6;
        } while (local_c != (uint *)0x0);
      }
      if (puVar10 == (uint *)0x0) {
        return (uint *)0x0;
      }
      param_3 = pfVar9 + (int)puVar10 * -6;
      param_4 = puVar10;
    }
  }
  memmove(param_2,param_3,(int)param_4 * 0x18);
  return param_4;
}


