/*
 * Program: i76.exe
 * Function: prepare_world_object_render_state_candidate
 * Entry: 004781d0
 * Signature: undefined __cdecl prepare_world_object_render_state_candidate(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO lighting/render renames v33; confidence=medium-high] Prepares per-object render
   state before geometry traversal; called by primary GEO tree pass. */

void __cdecl prepare_world_object_render_state_candidate(int param_1)

{
  double dVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  undefined8 uVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double *pdVar10;
  double *pdVar11;
  int *piVar12;
  int *piVar13;
  float *pfVar14;
  float10 fVar15;
  float10 fVar16;
  float local_7c [6];
  undefined8 local_64;
  double local_5c [4];
  float local_3c;
  float local_38;
  float local_34;
  double local_30;
  undefined8 local_28;
  undefined8 local_20;
  float local_18;
  float local_14;
  float local_10;
  int *local_c;
  int local_8;
  
  DAT_0058db0c = 0;
  if (*(int *)(&DAT_004fa0b0 + DAT_0058db00 * 0x14) != 1) {
    pfVar6 = (float *)compute_transform_relative_to_ancestor(local_7c,param_1,0);
    pfVar14 = local_7c;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar14 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pfVar14 = pfVar14 + 1;
    }
    local_10 = (float)local_5c[1];
    local_14 = (float)local_5c[2];
    local_18 = (float)local_5c[3];
    DAT_0058db0c = 0;
    param_1 = 4;
    if (DAT_0058db08 < 4) {
      param_1 = DAT_0058db08;
    }
    local_64._0_4_ = 0x80000000;
    local_64._4_4_ = 0xc415af1d;
    local_8 = 0;
    if (0 < DAT_0058db08) {
      local_c = &DAT_0058db24;
      pdVar10 = (double *)&local_64;
      piVar12 = &DAT_0058db10;
      iVar7 = DAT_0058db0c;
      do {
        iVar9 = *local_c;
        local_3c = local_10 - *(float *)(iVar9 + 0x54);
        local_38 = local_14 - *(float *)(iVar9 + 0x58);
        local_34 = local_18 - *(float *)(iVar9 + 0x5c);
        fVar3 = local_34 * local_34 + local_38 * local_38 + local_3c * local_3c;
        local_28 = (double)fVar3;
        fVar3 = (float)_DAT_004be650 / (*(float *)(iVar9 + 0xc) * fVar3 - (float)_DAT_004be620);
        local_30 = (double)fVar3;
        if ((*(byte *)(iVar9 + 4) & 1) != 0) {
          dVar1 = _DAT_004be650 / (SQRT(local_28) - _DAT_004be658);
          local_20 = (double)*(float *)(iVar9 + 8);
          local_28 = ((double)_DAT_004be638 -
                     ((double)local_3c * dVar1 * (double)*(float *)(iVar9 + 0x30) +
                     (double)local_38 * dVar1 * (double)*(float *)(iVar9 + 0x34) +
                     (double)local_34 * dVar1 * (double)*(float *)(iVar9 + 0x38))) *
                     (double)_DAT_004be660;
          fVar4 = _DAT_004be610;
          if (_DAT_004be668 < local_28) {
            fVar16 = (float10)*(float *)(iVar9 + 8) * (float10)local_28;
            local_28._0_4_ = SUB84((double)(fVar16 + (float10)_DAT_004faf18),0);
            fVar15 = (float10)fscale((float10)1,(float10)(int)local_28);
            fVar16 = (float10)f2xm1(fVar16 - (float10)(int)local_28);
            fVar15 = fVar15 * (fVar16 + (float10)1);
            local_28 = (double)fVar15;
            fVar4 = (float)fVar15;
            local_20 = (double)CONCAT44(fVar4,(undefined4)local_20);
          }
          fVar3 = fVar4 * fVar3;
        }
        if ((iVar7 < param_1 + 1) ||
           (pdVar11 = pdVar10, piVar13 = piVar12, DAT_0058db0c = iVar7,
           (float)(double)CONCAT44(local_64._4_4_,(undefined4)local_64) < fVar3)) {
          iVar9 = *local_c;
          DAT_0058db0c = iVar7 + 1;
          *pdVar10 = (double)fVar3;
          uVar5 = CONCAT44(local_64._4_4_,(undefined4)local_64);
          dVar1 = (double)CONCAT44(local_64._4_4_,(undefined4)local_64);
          *piVar12 = iVar9;
          iVar9 = 0;
          local_28 = (double)CONCAT44(DAT_0058db10,(int)local_28);
          local_20 = (double)CONCAT44(pdVar10 + 1,(undefined4)local_20);
          iVar8 = 1;
          if (0x58db14 < (int)(piVar12 + 1)) {
            pdVar11 = local_5c;
            do {
              if (*pdVar11 < dVar1) {
                dVar1 = *pdVar11;
                iVar9 = iVar8;
              }
              iVar8 = iVar8 + 1;
              pdVar11 = pdVar11 + 1;
            } while (iVar8 < DAT_0058db0c);
          }
          local_64._0_4_ = *(undefined4 *)(&local_64 + iVar9);
          uVar2 = (&DAT_0058db10)[iVar9];
          local_64._4_4_ = *(undefined4 *)((int)local_5c + iVar9 * 8 + -4);
          (&local_64)[iVar9] = uVar5;
          (&DAT_0058db10)[iVar9] = DAT_0058db10;
          DAT_0058db10 = uVar2;
          pdVar11 = pdVar10 + 1;
          piVar13 = piVar12 + 1;
          if (DAT_0058db0c == param_1 + 1) {
            pdVar11 = pdVar10;
            piVar13 = piVar12;
            DAT_0058db0c = iVar7;
          }
        }
        local_8 = local_8 + 1;
        local_c = local_c + 1;
        pdVar10 = pdVar11;
        piVar12 = piVar13;
        iVar7 = DAT_0058db0c;
      } while (local_8 < DAT_0058db08);
    }
  }
  return;
}


