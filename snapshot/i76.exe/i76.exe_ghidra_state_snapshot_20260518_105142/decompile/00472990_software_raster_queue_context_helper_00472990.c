/*
 * Program: i76.exe
 * Function: software_raster_queue_context_helper_00472990
 * Entry: 00472990
 * Signature: undefined __cdecl software_raster_queue_context_helper_00472990(int param_1, float * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: software raster queue context helper
   based on adjacent named subsystem context. */

void __cdecl software_raster_queue_context_helper_00472990(int param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  undefined4 *puVar8;
  float *pfVar9;
  double *pdVar10;
  int iVar11;
  undefined4 *puVar12;
  int local_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  double local_60;
  double local_58;
  double local_50;
  float local_48 [17];
  
  local_7c = 4;
  *(float *)(param_1 + 0x160) = param_2[10];
  *(float *)(param_1 + 0x164) = param_2[0xb];
  *(float *)(param_1 + 0x168) = param_2[0xc];
  local_78 = *(undefined4 *)(param_1 + 0x160);
  *(float *)(param_1 + 0x16c) = param_2[0xd];
  uStack_74 = *(undefined4 *)(param_1 + 0x164);
  local_58 = *(double *)(param_2 + 0xe);
  uStack_6c = *(undefined4 *)(param_1 + 0x16c);
  local_70 = *(undefined4 *)(param_1 + 0x168);
  local_60 = *(double *)(param_1 + 0x168);
  *(double *)(param_1 + 0x170) = local_58;
  pdVar10 = (double *)(param_1 + 0x178);
  pfVar9 = (float *)(param_1 + 0x134);
  local_68 = local_78;
  uStack_64 = uStack_74;
  local_50 = local_58;
  do {
    *pdVar10 = (double)(pfVar9[1] * param_2[6] + *pfVar9 * param_2[3] + *param_2 * pfVar9[-1] +
                       (float)*(double *)(param_2 + 10));
    pdVar10[1] = (double)(pfVar9[1] * param_2[7] + pfVar9[-1] * param_2[1] + *pfVar9 * param_2[4] +
                         (float)*(double *)(param_2 + 0xc));
    fVar1 = *pfVar9 * param_2[5] + pfVar9[1] * param_2[8] + pfVar9[-1] * param_2[2] +
            (float)*(double *)(param_2 + 0xe);
    pdVar10[2] = (double)fVar1;
    dVar3 = _DAT_004be5c0;
    if (*pdVar10 < (double)CONCAT44(uStack_64,local_68)) {
      local_68 = *(undefined4 *)pdVar10;
      uStack_64 = *(undefined4 *)((int)pdVar10 + 4);
    }
    if (pdVar10[1] < local_60) {
      local_60 = pdVar10[1];
    }
    if (fVar1 < (float)local_50) {
      local_50 = (double)fVar1;
    }
    if ((double)CONCAT44(uStack_74,local_78) < *pdVar10) {
      local_78 = *(undefined4 *)pdVar10;
      uStack_74 = *(undefined4 *)((int)pdVar10 + 4);
    }
    if ((double)CONCAT44(uStack_6c,local_70) < pdVar10[1]) {
      local_70 = *(undefined4 *)(pdVar10 + 1);
      uStack_6c = *(undefined4 *)((int)pdVar10 + 0xc);
    }
    if ((float)local_58 < fVar1) {
      local_58 = (double)fVar1;
    }
    pfVar9 = pfVar9 + 3;
    pdVar10 = pdVar10 + 3;
    local_7c = local_7c + -1;
  } while (local_7c != 0);
  dVar2 = ((double)CONCAT44(uStack_74,local_78) + (double)CONCAT44(uStack_64,local_68)) *
          _DAT_004be5e8;
  dVar7 = ((double)CONCAT44(uStack_6c,local_70) + local_60) * _DAT_004be5e8;
  dVar5 = (local_58 + local_50) * _DAT_004be5e8;
  *(double *)(param_1 + 0x80) = dVar2;
  pdVar10 = (double *)(param_1 + 0x168);
  iVar11 = 5;
  *(double *)(param_1 + 0x88) = dVar7;
  *(double *)(param_1 + 0x90) = dVar5;
  local_50 = dVar3;
  do {
    dVar3 = dVar2 - pdVar10[-1];
    dVar6 = dVar7 - *pdVar10;
    dVar4 = dVar5 - pdVar10[1];
    dVar3 = dVar4 * dVar4 + dVar6 * dVar6 + dVar3 * dVar3;
    if (local_50 < dVar3) {
      local_50 = dVar3;
    }
    pdVar10 = pdVar10 + 3;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  *(double *)(param_1 + 0x98) = SQRT(local_50);
  puVar8 = (undefined4 *)compose_matrix_or_transform_b(param_2,local_48);
  puVar12 = (undefined4 *)(param_1 + 0x40);
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar12 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar12 = puVar12 + 1;
  }
  return;
}


