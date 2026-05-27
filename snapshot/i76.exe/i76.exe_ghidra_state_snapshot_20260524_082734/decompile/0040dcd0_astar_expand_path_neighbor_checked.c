/*
 * Program: i76.exe
 * Function: astar_expand_path_neighbor_checked
 * Entry: 0040dcd0
 * Signature: undefined __cdecl astar_expand_path_neighbor_checked(float * param_1, int param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Astar ran out of memory - path to long */

void __cdecl astar_expand_path_neighbor_checked(float *param_1,int param_2,int *param_3)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  float *pfVar9;
  int iVar10;
  undefined4 *puVar11;
  float *pfVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  float *pfVar16;
  float *pfVar17;
  float *pfVar18;
  float10 fVar19;
  double *pdVar20;
  float fVar21;
  float fVar22;
  int local_fc;
  float local_e0;
  int local_dc;
  float local_d8;
  float local_d0;
  float local_cc;
  float local_c4;
  float local_c0 [6];
  float local_a8;
  float local_a0;
  double local_98;
  double local_88;
  float local_80 [16];
  float local_40 [16];
  
  iVar13 = 0;
  local_fc = 0;
  if (0 < *param_3 + -1) {
    pfVar18 = param_1 + 4;
    pfVar12 = param_1;
    iVar14 = iVar13;
    pfVar1 = param_1;
    do {
      pfVar16 = pfVar1 + 3;
      if (pfVar12[2] == 2.0) {
        dVar4 = (double)(pfVar12[1] - *pfVar12 * (float)_DAT_004bc660);
        if (DAT_0051f654 == (double *)0x0) {
          uVar8 = 0;
        }
        else if (_DAT_004bc670 <= ABS(*DAT_0051f654 - dVar4)) {
          if (dVar4 <= *DAT_0051f654) {
            pdVar20 = *(double **)(DAT_0051f654 + 4);
          }
          else {
            pdVar20 = *(double **)((int)DAT_0051f654 + 0x1c);
          }
          uVar8 = find_bridge_validation_span_node_by_coordinate(pdVar20,dVar4);
        }
        else {
          uVar8 = ~-(uint)((*(uint *)(*(int *)(DAT_0051f654 + 3) + 0x10) & 0x200) != 0) &
                  (uint)DAT_0051f654;
        }
        iVar13 = *(int *)(uVar8 + 0x18);
        if (iVar13 != 0) {
LAB_0040dda9:
          pfVar9 = compose_matrix_or_transform_a
                             (local_40,(float *)(iVar13 + 0x18),(float *)&DAT_004faed8);
          pfVar15 = pfVar9;
          pfVar17 = local_80;
          for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
            *pfVar17 = *pfVar15;
            pfVar15 = pfVar15 + 1;
            pfVar17 = pfVar17 + 1;
          }
          if (*(int *)(iVar13 + 0x6c) != 0xd) goto code_r0x0040ddde;
          pfVar15 = local_c0;
          for (iVar10 = 0x10; local_dc = iVar13, iVar10 != 0; iVar10 = iVar10 + -1) {
            *pfVar15 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar15 = pfVar15 + 1;
          }
        }
LAB_0040de2e:
        fVar6 = local_c0[2];
        fVar3 = local_c0[0];
        fVar2 = (float)local_98;
        fVar5 = (float)local_88;
        local_c4 = fVar5 + local_a0;
        local_cc = fVar2 + local_a8;
        local_d8 = fVar2 + local_c0[0];
        local_d0 = fVar5 + local_c0[2];
        fVar19 = compute_short_2d_segment_alignment_metric
                           (fVar2,fVar5,local_cc,local_c4,*pfVar12,pfVar12[1]);
        fVar21 = (float)*(undefined8 *)pfVar12;
        fVar22 = (float)((ulonglong)*(undefined8 *)pfVar12 >> 0x20);
        if ((float10)_DAT_004bc680 <= fVar19) {
          fVar19 = compute_short_2d_segment_alignment_metric
                             (fVar2,fVar5,local_d8,local_d0,fVar21,fVar22);
          if (fVar19 <= (float10)_DAT_004bc6c8) {
            if ((float10)_DAT_004bc6c0 <= fVar19) {
              fVar3 = fVar3 * _DAT_004bc6d8;
              fVar6 = fVar6 * _DAT_004bc6d8;
              *pfVar12 = *pfVar12 - fVar3;
              pfVar12[1] = pfVar12[1] - fVar6;
              *pfVar16 = *pfVar16 - fVar3;
              fVar6 = *pfVar18 - fVar6;
            }
            else {
              fVar3 = fVar3 * _DAT_004bc6b8;
              fVar6 = fVar6 * _DAT_004bc6b8;
              *pfVar12 = *pfVar12 - fVar3;
              pfVar12[1] = pfVar12[1] - fVar6;
              *pfVar16 = *pfVar16 - fVar3;
              fVar6 = *pfVar18 - fVar6;
            }
          }
          else {
            fVar3 = fVar3 * _DAT_004bc6d4;
            fVar6 = fVar6 * _DAT_004bc6d4;
            *pfVar12 = *pfVar12 - fVar3;
            pfVar12[1] = pfVar12[1] - fVar6;
            *pfVar16 = *pfVar16 - fVar3;
            fVar6 = *pfVar18 - fVar6;
          }
        }
        else {
          fVar19 = compute_short_2d_segment_alignment_metric
                             (fVar2,fVar5,local_d8,local_d0,fVar21,fVar22);
          if ((float10)_DAT_004bc6c0 <= fVar19) {
            if (fVar19 <= (float10)_DAT_004bc6c8) {
              fVar3 = fVar3 * _DAT_004bc6d0;
              fVar6 = fVar6 * _DAT_004bc6d0;
              *pfVar12 = *pfVar12 - fVar3;
              pfVar12[1] = pfVar12[1] - fVar6;
              *pfVar16 = *pfVar16 - fVar3;
              fVar6 = *pfVar18 - fVar6;
            }
            else {
              fVar3 = fVar3 * _DAT_004bc6cc;
              fVar6 = fVar6 * _DAT_004bc6cc;
              *pfVar12 = *pfVar12 - fVar3;
              pfVar12[1] = pfVar12[1] - fVar6;
              *pfVar16 = *pfVar16 - fVar3;
              fVar6 = *pfVar18 - fVar6;
            }
          }
          else {
            fVar3 = fVar3 * _DAT_004bc6c4;
            fVar6 = fVar6 * _DAT_004bc6c4;
            *pfVar12 = *pfVar12 - fVar3;
            pfVar12[1] = pfVar12[1] - fVar6;
            *pfVar16 = *pfVar16 - fVar3;
            fVar6 = *pfVar18 - fVar6;
          }
        }
        *pfVar18 = fVar6;
        fVar6 = *pfVar16 - *pfVar12;
        fVar5 = *pfVar18 - pfVar12[1];
        fVar2 = fVar5 * fVar5 + fVar6 * fVar6;
        if ((fVar2 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar2)) {
          fVar19 = zone_satellite_map_context_helper_00495000
                             (SUB84((double)fVar2,0),(uint)((ulonglong)(double)fVar2 >> 0x20));
          local_e0 = (float)(fVar19 * (float10)_DAT_004bc6e0);
        }
        else {
          local_e0 = 1e+06;
        }
        fVar21 = _DAT_004bc6e8;
        iVar10 = iVar14 + 1;
        pfVar9 = (float *)(param_2 + iVar14 * 0xc);
        *pfVar9 = *pfVar12;
        pfVar9[1] = pfVar12[1];
        pfVar9[2] = pfVar12[2];
        fVar2 = *pfVar12;
        fVar3 = pfVar12[1];
        if (fVar21 < (*pfVar18 - fVar3) * (*pfVar18 - fVar3) +
                     (*pfVar16 - fVar2) * (*pfVar16 - fVar2)) {
          puVar11 = (undefined4 *)(param_2 + 8 + iVar10 * 0xc);
          do {
            fVar7 = _DAT_004bc6e8;
            fVar2 = fVar2 + local_e0 * fVar6;
            fVar3 = fVar3 + local_e0 * fVar5;
            fVar21 = *pfVar18;
            fVar22 = *pfVar16;
            puVar11[-2] = fVar2;
            iVar10 = iVar10 + 1;
            puVar11[-1] = fVar3;
            *puVar11 = 0x40000000;
            puVar11 = puVar11 + 3;
          } while (fVar7 < (fVar21 - fVar3) * (fVar21 - fVar3) + (fVar22 - fVar2) * (fVar22 - fVar2)
                  );
        }
        iVar13 = iVar10 + 1;
        pfVar9 = (float *)(param_2 + iVar10 * 0xc);
        *pfVar9 = *pfVar16;
        pfVar9[1] = *pfVar18;
        pfVar9[2] = pfVar12[5];
        if (1999 < iVar13) {
          report_error();
        }
        pfVar16 = pfVar1 + 6;
        local_fc = local_fc + 1;
        pfVar12 = pfVar12 + 3;
        pfVar18 = pfVar18 + 3;
      }
      else {
        iVar13 = iVar14 + 1;
        pfVar1 = (float *)(param_2 + iVar14 * 0xc);
        *pfVar1 = *pfVar12;
        pfVar1[1] = pfVar12[1];
        pfVar1[2] = pfVar12[2];
        if (1999 < iVar13) {
          report_error();
        }
      }
      local_fc = local_fc + 1;
      pfVar12 = pfVar12 + 3;
      pfVar18 = pfVar18 + 3;
      iVar14 = iVar13;
      pfVar1 = pfVar16;
    } while (local_fc < *param_3 + -1);
  }
  pfVar18 = (float *)(param_2 + iVar13 * 0xc);
  *pfVar18 = param_1[*param_3 * 3 + -3];
  pfVar18[1] = param_1[*param_3 * 3 + -2];
  pfVar18[2] = param_1[*param_3 * 3 + -1];
  *param_3 = iVar13 + 1;
  return;
code_r0x0040ddde:
  if (((*(int *)(iVar13 + 100) != 0) &&
      (iVar10 = find_bridge_piece_transform_in_object_tree
                          (*(int *)(iVar13 + 100),local_80,&local_dc,local_c0), iVar10 != 0)) ||
     (iVar13 = *(int *)(iVar13 + 0x60), iVar13 == 0)) goto LAB_0040de2e;
  goto LAB_0040dda9;
}


