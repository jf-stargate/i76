/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004929b0
 * Entry: 004929b0
 * Signature: undefined4 __cdecl terrain_map_context_helper_004929b0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004929b0. Remove
   duplicated terrain wording. */

undefined4 __cdecl terrain_map_context_helper_004929b0(int param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  bool bVar5;
  float fVar6;
  double *pdVar7;
  int iVar8;
  double *pdVar9;
  uint uVar10;
  float *pfVar11;
  double *pdVar12;
  uint uVar13;
  float *pfVar14;
  float *pfVar15;
  float10 extraout_ST0;
  float10 fVar16;
  uint local_1ac;
  uint local_1a8;
  double *local_1a4;
  uint local_1a0;
  double *local_19c;
  uint local_198;
  uint local_190;
  int local_17c;
  double local_170;
  undefined4 local_168;
  undefined4 local_164;
  double local_158 [2];
  double local_148;
  double local_140 [2];
  double local_130;
  undefined8 local_128;
  double local_120 [17];
  double local_98 [9];
  undefined4 auStack_50 [19];
  
  pdVar9 = (double *)(param_1 + 0x160);
  local_1a8 = 0x3400;
  local_1ac = 0x3400;
  local_19c = (double *)0xfffff400;
  local_1a0 = 0xfffff400;
  apply_world_object_transform_to_bounds_or_geometry(*pdVar9,*(double *)(param_1 + 0x170));
  if ((float10)*(double *)(param_1 + 0x168) - extraout_ST0 < (float10)_DAT_004be878) {
    return 0;
  }
  fVar6 = _DAT_006442c4 * (float)*(double *)(param_1 + 0x170);
  local_128 = (double)(_DAT_006442c4 * (float)*pdVar9);
  local_120[1] = (double)fVar6;
  local_190 = SUB84((double)(_DAT_006442c4 * (float)*pdVar9 + (float)_DAT_004faf18),0);
  local_120[0] = _DAT_004be850;
  if (-0xc00 < (int)local_190) {
    local_19c = (double *)local_190;
  }
  local_198 = SUB84((double)(fVar6 + (float)_DAT_004faf18),0);
  if (-0xc00 < (int)local_198) {
    local_1a0 = local_198;
  }
  if ((int)local_190 < 0x3400) {
    local_1a8 = local_190;
  }
  if ((int)local_198 < 0x3400) {
    local_1ac = local_198;
  }
  uVar10 = (int)local_120 - (int)pdVar9;
  bVar5 = true;
  pdVar12 = local_120 + 2;
  pdVar7 = (double *)(param_1 + 0x180);
  local_17c = 4;
  do {
    dVar1 = *pdVar7;
    dVar2 = pdVar7[1];
    *pdVar12 = (double)(_DAT_006442c4 * (float)pdVar7[-1]);
    *(double *)(uVar10 + (int)pdVar7) = (double)(_DAT_006442c4 * (float)dVar2);
    *(undefined4 *)((int)&local_128 + -(int)pdVar9 + (int)pdVar7) = 0;
    *(undefined4 *)((int)&local_128 + -(int)pdVar9 + 4 + (int)pdVar7) = 0;
    if (_DAT_004be850 < dVar1) {
      bVar5 = false;
    }
    local_190 = SUB84(_DAT_004faf18 + *pdVar12,0);
    if ((int)local_19c < (int)local_190) {
      local_19c = (double *)local_190;
    }
    local_198 = SUB84(_DAT_004faf18 + *(double *)(uVar10 + (int)pdVar7),0);
    if ((int)local_1a0 < (int)local_198) {
      local_1a0 = local_198;
    }
    if ((int)local_190 < (int)local_1a8) {
      local_1a8 = local_190;
    }
    if ((int)local_198 < (int)local_1ac) {
      local_1ac = local_198;
    }
    pdVar12 = pdVar12 + 3;
    pdVar7 = pdVar7 + 3;
    local_17c = local_17c + -1;
  } while (local_17c != 0);
  if (bVar5) {
    local_190 = SUB84(local_128 + _DAT_004faf18,0);
    local_1a8 = 0x3400;
    local_1ac = 0x3400;
    local_19c = (double *)0xfffff400;
    local_1a0 = 0xfffff400;
    if (-0xc00 < (int)local_190) {
      local_19c = (double *)local_190;
    }
    local_198 = SUB84(local_120[1] + _DAT_004faf18,0);
    if (-0xc00 < (int)local_198) {
      local_1a0 = local_198;
    }
    if ((int)local_190 < 0x3400) {
      local_1a8 = local_190;
    }
    if ((int)local_198 < 0x3400) {
      local_1ac = local_198;
    }
    pdVar12 = local_120 + 2;
    pdVar7 = (double *)(param_1 + 0x180);
    local_1a4 = (double *)0x4;
    do {
      dVar3 = ((double)_DAT_006442c4 * *pdVar7) / (*(double *)(param_1 + 0x168) - *pdVar7);
      dVar1 = pdVar7[1];
      dVar2 = *(double *)(param_1 + 0x170);
      *pdVar12 = (pdVar7[-1] - *pdVar9) * dVar3 + *pdVar12;
      dVar1 = (dVar1 - dVar2) * dVar3 + *(double *)((int)pdVar7 + uVar10);
      *(double *)((int)pdVar7 + uVar10) = dVar1;
      local_190 = SUB84(_DAT_004faf18 + *pdVar12,0);
      if ((int)local_19c < (int)local_190) {
        local_19c = (double *)local_190;
      }
      local_198 = SUB84(_DAT_004faf18 + dVar1,0);
      if ((int)local_1a0 < (int)local_198) {
        local_1a0 = local_198;
      }
      if ((int)local_190 < (int)local_1a8) {
        local_1a8 = local_190;
      }
      if ((int)local_198 < (int)local_1ac) {
        local_1ac = local_198;
      }
      pdVar7 = pdVar7 + 3;
      pdVar12 = pdVar12 + 3;
      local_1a4 = (double *)((int)local_1a4 + -1);
    } while (local_1a4 != (double *)0x0);
  }
  DAT_006442e0 = (local_1a8 & 0xffffffe0) - 0x20;
  DAT_006442e4 = (local_1ac & 0xffffffe0) - 0x20;
  iVar8 = (int)local_19c - DAT_006442e0;
  if ((int)local_19c - DAT_006442e0 < (int)(local_1a0 - DAT_006442e4)) {
    iVar8 = local_1a0 - DAT_006442e4;
  }
  DAT_006442e8 = 0;
  for (; iVar8 != 0; iVar8 = iVar8 >> 1) {
    DAT_006442e8 = DAT_006442e8 + 1;
  }
  local_1a4 = local_98;
  local_1ac = 0;
  local_1a8 = 1;
  pdVar9 = (double *)&local_128;
  do {
    bVar5 = true;
    if ((int)local_1a8 < 5) {
      pdVar7 = pdVar9 + 5;
      uVar13 = local_1a8;
      do {
        if ((*pdVar9 - pdVar7[-2]) * (*pdVar9 - pdVar7[-2]) +
            (pdVar9[2] - *pdVar7) * (pdVar9[2] - *pdVar7) < _DAT_004be880) {
          bVar5 = false;
          break;
        }
        uVar13 = uVar13 + 1;
        pdVar7 = pdVar7 + 3;
      } while ((int)uVar13 < 5);
    }
    if (bVar5) {
      pdVar7 = pdVar9;
      pdVar12 = local_1a4;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined4 *)pdVar12 = *(undefined4 *)pdVar7;
        pdVar7 = (double *)((int)pdVar7 + 4);
        pdVar12 = (double *)((int)pdVar12 + 4);
      }
      local_1ac = local_1ac + 1;
      local_1a4 = local_1a4 + 3;
    }
    pdVar9 = pdVar9 + 3;
    bVar5 = 4 < (int)local_1a8;
    local_1a8 = local_1a8 + 1;
    if (bVar5) {
      if ((int)local_1ac < 3) {
        return 0;
      }
      iVar8 = 0;
      if (0 < (int)local_1ac) {
        pdVar9 = local_98 + 2;
        dVar1 = _DAT_004be888;
        do {
          if (*pdVar9 <= dVar1) {
            dVar1 = *pdVar9;
            uVar10 = iVar8;
          }
          iVar8 = iVar8 + 1;
          pdVar9 = pdVar9 + 3;
        } while (iVar8 < (int)local_1ac);
      }
      local_1a8 = 0;
      pdVar9 = local_98 + uVar10 * 3;
      pdVar7 = local_98 + local_1ac * 3;
      for (iVar8 = 6; pdVar12 = local_98, uVar13 = local_1a8, dVar1 = _DAT_004be850, iVar8 != 0;
          iVar8 = iVar8 + -1) {
        *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
        pdVar9 = (double *)((int)pdVar9 + 4);
        pdVar7 = (double *)((int)pdVar7 + 4);
      }
      do {
        local_1a8 = uVar13;
        pdVar9 = pdVar12;
        pdVar7 = &local_170;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
          pdVar9 = (double *)((int)pdVar9 + 4);
          pdVar7 = (double *)((int)pdVar7 + 4);
        }
        pdVar9 = local_98 + uVar10 * 3;
        pdVar7 = pdVar12;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
          pdVar9 = (double *)((int)pdVar9 + 4);
          pdVar7 = (double *)((int)pdVar7 + 4);
        }
        pdVar9 = &local_170;
        pdVar7 = local_98 + uVar10 * 3;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
          pdVar9 = (double *)((int)pdVar9 + 4);
          pdVar7 = (double *)((int)pdVar7 + 4);
        }
        uVar13 = local_1a8 + 1;
        uVar10 = local_1ac;
        dVar2 = _DAT_004be890;
        if ((int)uVar13 < (int)(local_1ac + 1)) {
          pdVar9 = pdVar12;
          pdVar7 = local_158;
          for (iVar8 = 6; local_1a0 = uVar13, local_19c = pdVar12 + 3, iVar8 != 0;
              iVar8 = iVar8 + -1) {
            *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
            pdVar9 = (double *)((int)pdVar9 + 4);
            pdVar7 = (double *)((int)pdVar7 + 4);
          }
          do {
            pdVar9 = local_19c;
            pdVar7 = local_140;
            for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
              *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
              pdVar9 = (double *)((int)pdVar9 + 4);
              pdVar7 = (double *)((int)pdVar7 + 4);
            }
            dVar3 = (double)((float10)local_140[0] - (float10)local_158[0]);
            dVar4 = (double)((float10)local_130 - (float10)local_148);
            fVar16 = (float10)fpatan((float10)local_130 - (float10)local_148,
                                     (float10)local_140[0] - (float10)local_158[0]);
            if (fVar16 < (float10)_DAT_004be850) {
              fVar16 = fVar16 - (float10)_DAT_004be868;
            }
            dVar3 = (double)(((float10)dVar4 * (float10)dVar4 + (float10)dVar3 * (float10)dVar3) -
                            fVar16 * (float10)_DAT_004be870);
            if ((dVar1 < dVar3) && (dVar3 < dVar2)) {
              uVar10 = local_1a0;
              dVar2 = dVar3;
            }
            local_1a0 = local_1a0 + 1;
            local_19c = local_19c + 3;
          } while ((int)local_1a0 < (int)(local_1ac + 1));
        }
        dVar1 = dVar2;
        pdVar12 = pdVar12 + 3;
      } while (uVar10 != local_1ac);
      dVar1 = _DAT_004be850;
      dVar2 = _DAT_004be850;
      if (0 < (int)uVar13) {
        pdVar9 = local_98 + 2;
        iVar8 = uVar13;
        do {
          dVar1 = pdVar9[-2] + dVar1;
          iVar8 = iVar8 + -1;
          dVar2 = dVar2 + *pdVar9;
          pdVar9 = pdVar9 + 3;
        } while (iVar8 != 0);
      }
      dVar3 = (double)_DAT_004be830;
      iVar8 = 0;
      if (0 < (int)uVar13) {
        local_1ac = 0;
        pfVar14 = (float *)&DAT_00644308;
        uVar10 = local_1a8 * 0x18;
        local_1a4 = (double *)uVar13;
        do {
          pdVar9 = (double *)((int)local_98 + local_1ac);
          pdVar7 = &local_170;
          for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
            *(undefined4 *)pdVar7 = *(undefined4 *)pdVar9;
            pdVar9 = (double *)((int)pdVar9 + 4);
            pdVar7 = (double *)((int)pdVar7 + 4);
          }
          local_168 = 0;
          local_164 = 0x40240000;
          pfVar11 = (float *)terrain_map_context_helper_00492890
                                       ((undefined4 *)local_158,
                                        (double *)((int)local_98 + local_1ac),
                                        (double *)((int)local_98 + uVar10),&local_170);
          pfVar15 = pfVar14;
          for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
            *pfVar15 = *pfVar11;
            pfVar11 = pfVar11 + 1;
            pfVar15 = pfVar15 + 1;
          }
          if (pfVar14[2] * (float)(dVar2 * (dVar3 / (double)(int)uVar13)) +
              *pfVar14 * (float)(dVar1 * (dVar3 / (double)(int)uVar13)) +
              (float)*(double *)((int)&DAT_00644318 + local_1ac) < (float)_DAT_004be850) {
            *pfVar14 = -*pfVar14;
            pfVar14[2] = -pfVar14[2];
            *(double *)(pfVar14 + 4) = -*(double *)(pfVar14 + 4);
          }
          pfVar14 = pfVar14 + 6;
          local_1a4 = (double *)((int)local_1a4 + -1);
          uVar10 = local_1ac;
          iVar8 = uVar13;
          local_1ac = local_1ac + 0x18;
        } while (local_1a4 != (double *)0x0);
      }
      DAT_006442f0 = iVar8;
      return 1;
    }
  } while( true );
}


