/*
 * Program: i76.exe
 * Function: build_projected_polygon_scanline_spans_impl
 * Entry: 00473960
 * Signature: undefined4 __thiscall build_projected_polygon_scanline_spans_impl(void * this, uint param_1, float * param_2, int param_3, undefined4 * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Builds edge intersections and
   span descriptors for projected polygons. */

undefined4 __thiscall
build_projected_polygon_scanline_spans_impl
          (void *this,uint param_1,float *param_2,int param_3,undefined4 *param_4)

{
  uint *puVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 uVar10;
  int *piVar11;
  void *pvVar12;
  uint uVar13;
  undefined4 *puVar14;
  float *pfVar15;
  uint *puVar16;
  int iVar17;
  float *pfVar18;
  float *pfVar19;
  float *local_38;
  float local_34;
  float local_30;
  float local_2c;
  int local_1c;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbace;
  local_c = ExceptionList;
  local_34 = param_2[1];
  local_38 = param_2;
  pfVar15 = param_2;
  iVar17 = param_3;
  pfVar19 = param_2;
  local_30 = local_34;
  if (0 < param_3) {
    do {
      fVar2 = pfVar15[1];
      if (fVar2 < local_34) {
        local_38 = pfVar15;
        local_34 = fVar2;
      }
      if (local_30 < fVar2) {
        pfVar19 = pfVar15;
        local_30 = fVar2;
      }
      iVar17 = iVar17 + -1;
      pfVar15 = pfVar15 + 6;
    } while (iVar17 != 0);
  }
  _DAT_006439a0 = (double)(local_34 + (float)_DAT_004faf18);
  uVar3 = DAT_006439a0;
  _DAT_006439a0 = (double)(local_30 + (float)_DAT_004faf18);
  uVar6 = DAT_006439a0;
  if (DAT_006439a0 == uVar3) {
    uVar10 = 0;
  }
  else {
    fVar2 = (*pfVar19 - *local_38) / (local_30 - local_34);
    _DAT_0058da20 = (double)fVar2;
    _DAT_0058da60 = (double)(*local_38 - local_34 * fVar2);
    ExceptionList = &local_c;
    if (*(int *)((int)this + 0x38) <= (int)DAT_006439a0) {
      ExceptionList = &local_c;
      grow_raster_scanline_workspace(this,DAT_006439a0 + 1);
    }
    local_30 = 0.0;
    if ((void *)((int)DAT_004f9d80 + param_3 * -0x20) < DAT_004f9d7c) {
      if (DAT_0058dabc == (int *)0x0) {
        piVar11 = operator_new(0xc);
        local_4 = 0;
        if (piVar11 == (int *)0x0) {
          piVar11 = (int *)0x0;
        }
        else {
          *piVar11 = 0;
          pvVar12 = operator_new(0x10000);
          piVar11[1] = (int)pvVar12;
          piVar11[2] = 0x10000;
        }
        local_4 = 0xffffffff;
        DAT_0058dab8 = piVar11;
      }
      else {
        if (*DAT_0058dabc == 0) {
          puVar14 = operator_new(0xc);
          local_4 = 1;
          if (puVar14 == (undefined4 *)0x0) {
            puVar14 = (undefined4 *)0x0;
          }
          else {
            *puVar14 = 0;
            pvVar12 = operator_new(0x10000);
            puVar14[1] = pvVar12;
            puVar14[2] = 0x10000;
          }
          local_4 = 0xffffffff;
          *DAT_0058dabc = (int)puVar14;
        }
        piVar11 = (int *)*DAT_0058dabc;
      }
      DAT_004f9d80 = (void *)(piVar11[2] + piVar11[1] & 0xffffffe0);
      DAT_004f9d7c = (void *)piVar11[1];
      DAT_0058dabc = piVar11;
    }
    local_1c = 0;
    uVar13 = uVar6;
    pfVar8 = pfVar19;
    pvVar12 = DAT_004f9d80;
    pfVar15 = pfVar19;
    while (pfVar9 = pfVar8, pfVar15 = pfVar15 + -6, pfVar15 != local_38 + -6) {
      if (pfVar15 < param_2) {
        pfVar15 = param_2 + param_3 * 6 + -6;
      }
      local_2c = 0.0;
      _DAT_006439a0 = (double)(pfVar15[1] + (float)_DAT_004faf18);
      uVar7 = DAT_006439a0;
      pfVar8 = pfVar9;
      if (((int)DAT_006439a0 <= (int)uVar13) &&
         ((pfVar15 == local_38 ||
          (local_2c = *pfVar15 - (pfVar15[1] * (float)_DAT_0058da20 + (float)_DAT_0058da60),
          _DAT_004be5f4 < local_2c)))) {
        if ((int)local_30 < (int)local_2c) {
          local_30 = local_2c;
          *param_4 = pfVar15;
          pvVar12 = DAT_004f9d80;
        }
        pfVar8 = pfVar15;
        if (uVar7 != uVar13) {
          DAT_004f9d80 = (void *)((int)pvVar12 - 0x20);
          if (DAT_004f9d80 < DAT_004f9d7c) {
            if (DAT_0058dabc == (int *)0x0) {
              piVar11 = operator_new(0xc);
              local_4 = 2;
              if (piVar11 == (int *)0x0) {
                piVar11 = (int *)0x0;
                DAT_0058dab8 = (int *)0x0;
              }
              else {
                *piVar11 = 0;
                pvVar12 = operator_new(0x10000);
                piVar11[1] = (int)pvVar12;
                piVar11[2] = 0x10000;
                DAT_0058dab8 = piVar11;
              }
            }
            else {
              if (*DAT_0058dabc == 0) {
                puVar14 = operator_new(0xc);
                local_4 = 3;
                if (puVar14 == (undefined4 *)0x0) {
                  puVar14 = (undefined4 *)0x0;
                }
                else {
                  *puVar14 = 0;
                  pvVar12 = operator_new(0x10000);
                  puVar14[1] = pvVar12;
                  puVar14[2] = 0x10000;
                }
                *DAT_0058dabc = (int)puVar14;
              }
              piVar11 = (int *)*DAT_0058dabc;
            }
            DAT_004f9d7c = (void *)piVar11[1];
            DAT_004f9d80 = (void *)((piVar11[2] + piVar11[1] & 0xffffffe0U) - 0x20);
            DAT_0058dabc = piVar11;
          }
          local_4 = 4;
          if (DAT_004f9d80 == (void *)0x0) {
            local_1c = 0;
          }
          else {
            local_1c = initialize_raster_edge_record_from_vertex_pair
                                 (DAT_004f9d80,param_1,pfVar15,pfVar9,uVar7,uVar13);
          }
          local_4 = 0xffffffff;
          if (*(int *)((int)this + 0x38) < (int)uVar13) {
            *(uint *)((int)this + 0x38) = uVar13;
          }
          *(undefined4 *)(local_1c + 4) = *(undefined4 *)(*(int *)((int)this + 0x10) + uVar7 * 4);
          *(int *)(*(int *)((int)this + 0x10) + uVar7 * 4) = local_1c;
          uVar13 = uVar7;
          pvVar12 = DAT_004f9d80;
        }
      }
    }
    puVar16 = (uint *)0x0;
    *(int *)(param_1 + 0x24) = local_1c;
    uVar13 = uVar6;
    pfVar8 = pfVar19;
    pfVar9 = pfVar19;
    fVar2 = _DAT_004be5f4;
    pfVar15 = pfVar19;
    while (pfVar5 = pfVar9, pfVar18 = pfVar8, pfVar15 = pfVar15 + 6, _DAT_004be5f4 = fVar2,
          pfVar15 != local_38 + 6) {
      if (pfVar15 == param_2 + param_3 * 6) {
        pfVar15 = param_2;
      }
      local_2c = 0.0;
      _DAT_006439a0 = (double)(pfVar15[1] + (float)_DAT_004faf18);
      uVar7 = DAT_006439a0;
      pfVar8 = pfVar18;
      pfVar9 = pfVar5;
      if (((int)DAT_006439a0 <= (int)uVar13) &&
         ((pfVar15 == local_38 ||
          (local_2c = (pfVar15[1] * (float)_DAT_0058da20 + (float)_DAT_0058da60) - *pfVar15,
          fVar2 < local_2c)))) {
        if ((int)local_30 < (int)local_2c) {
          local_30 = local_2c;
          *param_4 = pfVar15;
        }
        pfVar8 = pfVar15;
        pfVar9 = pfVar15;
        fVar2 = _DAT_004be5f4;
        if (uVar7 != uVar13) {
          DAT_004f9d80 = (void *)((int)DAT_004f9d80 - 0x20);
          if (DAT_004f9d80 < DAT_004f9d7c) {
            if (DAT_0058dabc == (int *)0x0) {
              piVar11 = operator_new(0xc);
              local_4 = 5;
              if (piVar11 == (int *)0x0) {
                piVar11 = (int *)0x0;
                DAT_0058dab8 = (int *)0x0;
              }
              else {
                *piVar11 = 0;
                pvVar12 = operator_new(0x10000);
                piVar11[1] = (int)pvVar12;
                piVar11[2] = 0x10000;
                DAT_0058dab8 = piVar11;
              }
            }
            else {
              if (*DAT_0058dabc == 0) {
                puVar14 = operator_new(0xc);
                local_4 = 6;
                if (puVar14 == (undefined4 *)0x0) {
                  puVar14 = (undefined4 *)0x0;
                }
                else {
                  *puVar14 = 0;
                  pvVar12 = operator_new(0x10000);
                  puVar14[1] = pvVar12;
                  puVar14[2] = 0x10000;
                }
                *DAT_0058dabc = (int)puVar14;
              }
              piVar11 = (int *)*DAT_0058dabc;
            }
            DAT_004f9d7c = (void *)piVar11[1];
            DAT_004f9d80 = (void *)((piVar11[2] + piVar11[1] & 0xffffffe0U) - 0x20);
            pfVar18 = pfVar5;
            DAT_0058dabc = piVar11;
          }
          local_4 = 7;
          if (DAT_004f9d80 == (void *)0x0) {
            puVar16 = (uint *)0x0;
          }
          else {
            puVar16 = (uint *)initialize_raster_edge_record_from_vertex_pair
                                        (DAT_004f9d80,param_1,pfVar15,pfVar18,uVar7,uVar13);
          }
          local_4 = 0xffffffff;
          *puVar16 = *puVar16 | 1;
          if (*(int *)((int)this + 0x38) < (int)uVar13) {
            *(uint *)((int)this + 0x38) = uVar13;
          }
          puVar16[1] = *(uint *)(*(int *)((int)this + 0xc) + uVar7 * 4);
          *(uint **)(*(int *)((int)this + 0xc) + uVar7 * 4) = puVar16;
          uVar13 = uVar7;
          fVar2 = _DAT_004be5f4;
        }
      }
    }
    *(uint **)(param_1 + 0x20) = puVar16;
    if (fVar2 < local_30) {
      *(uint *)(param_1 + 0x30) = uVar6 - uVar3;
      uVar13 = *(uint *)(param_1 + 0x34) & 3;
      if (uVar13 == 0) {
        iVar17 = uVar3 * 4;
        *(uint *)(*(int *)((int)this + 0xc) + iVar17) = puVar16[1];
        puVar16[1] = *(uint *)(iVar17 + *(int *)((int)this + 4));
        *(uint **)(iVar17 + *(int *)((int)this + 4)) = puVar16;
        iVar4 = *(int *)(param_1 + 0x24);
        *(undefined4 *)(*(int *)((int)this + 0x10) + iVar17) = *(undefined4 *)(iVar4 + 4);
        *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar17 + *(int *)((int)this + 8));
        *(int *)(iVar17 + *(int *)((int)this + 8)) = iVar4;
        *(undefined4 *)(param_1 + 0x38) =
             *(undefined4 *)(uVar6 * 4 + -4 + *(int *)((int)this + 0x24));
        *(uint *)(uVar6 * 4 + -4 + *(int *)((int)this + 0x24)) = param_1;
      }
      else if (uVar13 == 1) {
        iVar17 = uVar3 * 4;
        *(uint *)(iVar17 + *(int *)((int)this + 0xc)) = puVar16[1];
        puVar16[1] = *(uint *)(iVar17 + *(int *)((int)this + 0x14));
        *(uint **)(iVar17 + *(int *)((int)this + 0x14)) = puVar16;
        uVar3 = puVar16[7];
        while (uVar3 != uVar6) {
          *(uint *)(*(int *)((int)this + 0xc) + puVar16[0xc] * 4) = puVar16[9];
          puVar16[9] = *(uint *)(puVar16[0xc] * 4 + *(int *)((int)this + 0x1c));
          *(uint **)(puVar16[0xc] * 4 + *(int *)((int)this + 0x1c)) = puVar16 + 8;
          uVar3 = puVar16[0xf];
          puVar16 = puVar16 + 8;
        }
        iVar4 = *(int *)(param_1 + 0x24);
        *(undefined4 *)(iVar17 + *(int *)((int)this + 0x10)) = *(undefined4 *)(iVar4 + 4);
        *(undefined4 *)(iVar4 + 4) = *(undefined4 *)(iVar17 + *(int *)((int)this + 0x18));
        *(int *)(iVar17 + *(int *)((int)this + 0x18)) = iVar4;
        uVar3 = *(uint *)(iVar4 + 0x1c);
        while (uVar3 != uVar6) {
          *(undefined4 *)(*(int *)((int)this + 0x10) + *(int *)(iVar4 + 0x30) * 4) =
               *(undefined4 *)(iVar4 + 0x24);
          iVar17 = *(int *)(iVar4 + 0x30) * 4;
          *(undefined4 *)(iVar4 + 0x24) = *(undefined4 *)(iVar17 + *(int *)((int)this + 0x20));
          *(int *)(iVar17 + *(int *)((int)this + 0x20)) = iVar4 + 0x20;
          uVar3 = *(uint *)(iVar4 + 0x3c);
          iVar4 = iVar4 + 0x20;
        }
        *(undefined4 *)(param_1 + 0x38) =
             *(undefined4 *)(uVar6 * 4 + -4 + *(int *)((int)this + 0x28));
        *(uint *)(uVar6 * 4 + -4 + *(int *)((int)this + 0x28)) = param_1;
      }
      else {
        emit_raster_scanline_span_runs(this,param_1,uVar6);
        if (*(int *)(param_1 + 0x28) == -1) {
          ExceptionList = local_c;
          return 0;
        }
        DAT_004f9d80 = (void *)((uint)DAT_004f9d80 & 0xffffffe0);
        if (DAT_004f9d80 < DAT_004f9d7c) {
          if (DAT_0058dabc == (int *)0x0) {
            piVar11 = operator_new(0xc);
            local_4 = 8;
            if (piVar11 == (int *)0x0) {
              piVar11 = (int *)0x0;
              DAT_0058dab8 = (int *)0x0;
            }
            else {
              *piVar11 = 0;
              pvVar12 = operator_new(0x10000);
              piVar11[1] = (int)pvVar12;
              piVar11[2] = 0x10000;
              DAT_0058dab8 = piVar11;
            }
          }
          else {
            if (*DAT_0058dabc == 0) {
              puVar14 = operator_new(0xc);
              local_4 = 9;
              if (puVar14 == (undefined4 *)0x0) {
                puVar14 = (undefined4 *)0x0;
              }
              else {
                *puVar14 = 0;
                pvVar12 = operator_new(0x10000);
                puVar14[1] = pvVar12;
                puVar14[2] = 0x10000;
              }
              *DAT_0058dabc = (int)puVar14;
            }
            piVar11 = (int *)*DAT_0058dabc;
          }
          DAT_004f9d80 = (void *)(piVar11[2] + piVar11[1] & 0xffffffe0);
          DAT_004f9d7c = (void *)piVar11[1];
          DAT_0058dabc = piVar11;
        }
      }
      **(uint **)((int)this + 0x30) = param_1;
      *(uint *)((int)this + 0x30) = param_1 + 4;
      param_4[1] = local_38;
      param_4[2] = pfVar19;
      uVar10 = 1;
    }
    else {
      puVar16 = puVar16 + 4;
      do {
        *(uint *)(*(int *)((int)this + 0xc) + *puVar16 * 4) = puVar16[-3];
        puVar1 = puVar16 + 3;
        puVar16 = puVar16 + 8;
      } while (*puVar1 != uVar6);
      piVar11 = (int *)(*(int *)(param_1 + 0x24) + 0x10);
      do {
        *(int *)(*(int *)((int)this + 0x10) + *piVar11 * 4) = piVar11[-3];
        puVar16 = (uint *)(piVar11 + 3);
        piVar11 = piVar11 + 8;
      } while (*puVar16 != uVar6);
      uVar10 = 0;
    }
  }
  ExceptionList = local_c;
  return uVar10;
}


