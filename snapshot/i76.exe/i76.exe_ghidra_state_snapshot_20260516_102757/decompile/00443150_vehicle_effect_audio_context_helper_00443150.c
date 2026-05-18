/*
 * Program: i76.exe
 * Function: vehicle_effect_audio_context_helper_00443150
 * Entry: 00443150
 * Signature: undefined __cdecl vehicle_effect_audio_context_helper_00443150(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: vehicle effect audio context helper
   based on prior focused closure context. */

void __cdecl vehicle_effect_audio_context_helper_00443150(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  int *piVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  float *pfVar19;
  float *pfVar20;
  float10 fVar21;
  float10 fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  double local_170;
  int local_168;
  float local_15c;
  float local_158;
  float local_154;
  double local_150;
  double local_148;
  double local_140;
  double local_138;
  double local_130;
  double local_110;
  double local_108;
  double local_100;
  float local_c8 [10];
  double local_a0;
  double local_98;
  double local_90;
  undefined4 auStack_88 [16];
  float afStack_48 [17];
  
  if (DAT_0052bae8 != (int *)0x0) {
    iVar17 = -1;
    piVar18 = (int *)0x0;
    piVar15 = DAT_0052bae8;
    do {
      if ((piVar15[2] == param_1) && (iVar17 < piVar15[1])) {
        iVar17 = piVar15[1];
        piVar18 = piVar15;
      }
      piVar15 = (int *)*piVar15;
    } while (piVar15 != DAT_0052bae8);
    if (piVar18 != (int *)0x0) {
      dVar8 = *(double *)(param_1 + 0x40) - *(double *)(piVar18 + 0x10);
      dVar6 = *(double *)(param_1 + 0x48) - *(double *)(piVar18 + 0x12);
      dVar5 = *(double *)(param_1 + 0x50) - *(double *)(piVar18 + 0x14);
      local_15c = *(float *)(param_1 + 0x30);
      local_158 = *(float *)(param_1 + 0x34);
      dVar7 = SQRT(dVar5 * dVar5 + dVar6 * dVar6 + dVar8 * dVar8);
      local_154 = *(float *)(param_1 + 0x38);
      if (_DAT_004bd2d8 <= dVar7) {
        if (local_154 * (float)piVar18[0xf] +
            local_158 * (float)piVar18[0xe] + local_15c * (float)piVar18[0xd] <=
            (float)_DAT_004bd2e0) {
          fVar21 = (float10)dVar7 * (float10)_DAT_004bd2e8;
          local_168 = 2;
          fVar22 = fVar21;
          if ((float10)_DAT_004bd2d8 < fVar21) {
            do {
              fVar22 = fVar22 * (float10)_DAT_004bd2e8;
              local_168 = local_168 << 1;
            } while ((float10)_DAT_004bd2d8 < fVar22);
          }
          dVar6 = _DAT_004bd300 / (double)local_168;
          fVar1 = (float)fVar21;
          fVar22 = (float10)(float)piVar18[0xd] * (float10)fVar1;
          fVar21 = (float10)(float)piVar18[0xe] * (float10)fVar1;
          fVar25 = (float)piVar18[0xf] * fVar1;
          local_15c = local_15c * fVar1;
          local_158 = local_158 * fVar1;
          local_154 = local_154 * fVar1;
          dVar5 = *(double *)(piVar18 + 0x10) - *(double *)(param_1 + 0x40);
          dVar11 = *(double *)(piVar18 + 0x12) - *(double *)(param_1 + 0x48);
          dVar12 = *(double *)(piVar18 + 0x14) - *(double *)(param_1 + 0x50);
          dVar7 = dVar6 * dVar6;
          local_130 = *(double *)(piVar18 + 0x10);
          local_148 = *(double *)(piVar18 + 0x12);
          local_140 = *(double *)(piVar18 + 0x14);
          dVar8 = dVar7 * dVar6;
          dVar9 = dVar7 * (double)(((float10)dVar5 * (float10)_DAT_004bd2f8 - (fVar22 + fVar22)) -
                                  (float10)local_15c);
          dVar10 = dVar8 * (((double)local_15c - dVar5 * _DAT_004bd2f0) + (double)(float)fVar22);
          dVar5 = dVar7 * (double)(((float10)dVar11 * (float10)_DAT_004bd2f8 - (fVar21 + fVar21)) -
                                  (float10)local_158);
          dVar13 = dVar8 * ((double)(float)fVar21 + ((double)local_158 - dVar11 * _DAT_004bd2f0));
          dVar7 = dVar7 * ((dVar12 * _DAT_004bd2f8 - ((double)fVar25 + (double)fVar25)) -
                          (double)local_154);
          dVar8 = dVar8 * ((double)fVar25 + ((double)local_154 - dVar12 * _DAT_004bd2f0));
          dVar11 = dVar10 * _DAT_004bd308;
          dVar12 = dVar13 * _DAT_004bd308;
          fVar1 = *(float *)(param_1 + 0x30);
          dVar14 = dVar8 * _DAT_004bd308;
          fVar2 = *(float *)(param_1 + 0x34);
          fVar3 = *(float *)(param_1 + 0x38);
          local_100 = dVar11 - dVar9 * _DAT_004bd2f0;
          local_150 = dVar12 - dVar5 * _DAT_004bd2f0;
          local_170 = dVar14 - dVar7 * _DAT_004bd2f0;
          local_138 = (double)(fVar25 * (float)dVar6 + (float)dVar8 + (float)dVar7);
          local_110 = (double)((float)fVar21 * (float)dVar6 + (float)dVar13 + (float)dVar5);
          local_108 = (double)((float)fVar22 * (float)dVar6 + (float)dVar10 + (float)dVar9);
          if (0 < local_168) {
            do {
              dVar8 = local_100 + local_108;
              dVar6 = local_150 + local_110;
              dVar7 = local_170 + local_138;
              local_130 = local_108 + local_130;
              local_148 = local_110 + local_148;
              local_140 = local_138 + local_140;
              local_100 = dVar11 + local_100;
              local_150 = dVar12 + local_150;
              local_170 = dVar14 + local_170;
              dVar5 = dVar7 * dVar7 + dVar6 * dVar6 + dVar8 * dVar8;
              fVar22 = zone_satellite_map_context_helper_00495000
                                 (SUB84(dVar5,0),(uint)((ulonglong)dVar5 >> 0x20));
              dVar5 = (double)fVar22;
              fVar25 = (float)((float10)dVar8 * (float10)dVar5);
              fVar4 = (float)((float10)dVar6 * (float10)dVar5);
              fVar24 = (float)((float10)dVar7 * (float10)dVar5);
              if (fVar3 * fVar24 + fVar2 * fVar4 + fVar1 * fVar25 <= (float)_DAT_004bd2e0) {
                fVar23 = fVar3 * fVar4 - fVar2 * fVar24;
                fVar24 = fVar1 * fVar24 - fVar3 * fVar25;
                fVar25 = fVar2 * fVar25 - fVar1 * fVar4;
                dVar5 = (double)(fVar25 * fVar25 + fVar24 * fVar24 + fVar23 * fVar23);
                fVar22 = zone_satellite_map_context_helper_00495000
                                   (SUB84(dVar5,0),(uint)((ulonglong)dVar5 >> 0x20));
                fVar25 = fVar25 * (float)fVar22;
                fVar24 = fVar24 * (float)fVar22;
                fVar23 = fVar23 * (float)fVar22;
                fVar22 = (float10)_CIacos();
                pfVar19 = (float *)zone_satellite_map_context_helper_00494460
                                             (auStack_88,(float)-fVar22,fVar23,fVar24,fVar25);
                pfVar20 = local_c8;
                for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
                  *pfVar20 = *pfVar19;
                  pfVar19 = pfVar19 + 1;
                  pfVar20 = pfVar20 + 1;
                }
                pfVar19 = compose_matrix_or_transform_a
                                    (afStack_48,(float *)(param_1 + 0x18),local_c8);
              }
              else {
                pfVar19 = (float *)(param_1 + 0x18);
              }
              pfVar20 = local_c8;
              for (iVar17 = 0x10; iVar17 != 0; iVar17 = iVar17 + -1) {
                *pfVar20 = *pfVar19;
                pfVar19 = pfVar19 + 1;
                pfVar20 = pfVar20 + 1;
              }
              local_a0 = local_130;
              local_98 = local_148;
              local_90 = local_140;
              vehicle_effect_audio_update_helper_004439a0((int)piVar18,local_c8);
              local_168 = local_168 + -1;
              local_138 = dVar7;
              local_110 = dVar6;
              local_108 = dVar8;
            } while (local_168 != 0);
          }
        }
        else {
          iVar17 = 2;
          dVar9 = dVar7;
          while (dVar9 = dVar9 * _DAT_004bd2e8, _DAT_004bd2d8 < dVar9) {
            iVar17 = iVar17 << 1;
          }
          dVar9 = dVar9 / dVar7;
          pfVar19 = (float *)(param_1 + 0x18);
          pfVar20 = local_c8;
          for (iVar16 = 0x10; iVar16 != 0; iVar16 = iVar16 + -1) {
            *pfVar20 = *pfVar19;
            pfVar19 = pfVar19 + 1;
            pfVar20 = pfVar20 + 1;
          }
          local_a0 = local_a0 - dVar8;
          local_98 = local_98 - dVar6;
          local_90 = local_90 - dVar5;
          if (0 < iVar17) {
            do {
              local_a0 = dVar8 * dVar9 + local_a0;
              local_98 = dVar6 * dVar9 + local_98;
              local_90 = dVar5 * dVar9 + local_90;
              vehicle_effect_audio_update_helper_004439a0((int)piVar18,local_c8);
              iVar17 = iVar17 + -1;
            } while (iVar17 != 0);
          }
        }
      }
      else {
        vehicle_effect_audio_update_helper_004439a0((int)piVar18,(float *)(param_1 + 0x18));
      }
      piVar18[0xd] = (int)local_15c;
      piVar18[0xe] = (int)local_158;
      piVar18[0xf] = (int)local_154;
      piVar18[0x10] = *(int *)(param_1 + 0x40);
      piVar18[0x11] = *(int *)(param_1 + 0x44);
      piVar18[0x12] = *(int *)(param_1 + 0x48);
      piVar18[0x13] = *(int *)(param_1 + 0x4c);
      piVar18[0x14] = *(int *)(param_1 + 0x50);
      piVar18[0x15] = *(int *)(param_1 + 0x54);
    }
  }
  return;
}


