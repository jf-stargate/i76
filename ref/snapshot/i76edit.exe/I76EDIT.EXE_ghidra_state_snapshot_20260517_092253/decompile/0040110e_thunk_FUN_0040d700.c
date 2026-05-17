/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d700
 * Entry: 0040110e
 * Signature: undefined __cdecl thunk_FUN_0040d700(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_0040d700(int *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  double *pdVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fStack_10;
  int iStack_c;
  
  piVar5 = (int *)thunk_FUN_00409370(*param_1,*param_1);
  pdVar6 = (double *)thunk_FUN_00409370(*param_1,1);
  iVar8 = 0;
  if (0 < *param_1) {
    iStack_c = 0;
    do {
      fStack_10 = 0.0;
      fVar1 = *(float *)(iStack_c + param_1[1]);
      fVar2 = ((float *)(iStack_c + param_1[1]))[1];
      iVar9 = 0;
      if (0 < *param_1) {
        fStack_10 = 0.0;
        iVar10 = 0;
        do {
          pfVar7 = (float *)(param_1[1] + iVar10);
          fVar3 = *pfVar7 - fVar1;
          fVar4 = pfVar7[1] - fVar2;
          fVar3 = _DAT_004320cc / ((fVar4 * fVar4 + fVar3 * fVar3) * pfVar7[3] + _DAT_004320cc);
          *(double *)(piVar5 + (piVar5[1] * iVar8 + iVar9) * 2 + 2) = (double)fVar3;
          if (iVar8 != iVar9) {
            fStack_10 = *(float *)(param_1[1] + 8 + iVar10) * fVar3 + fStack_10;
          }
          iVar10 = iVar10 + 0x14;
          iVar9 = iVar9 + 1;
        } while (iVar9 < *param_1);
      }
      iVar9 = *(int *)((int)pdVar6 + 4) * iVar8;
      iStack_c = iStack_c + 0x14;
      iVar8 = iVar8 + 1;
      pdVar6[iVar9 + 1] = (double)fStack_10;
    } while (iVar8 < *param_1);
  }
  iVar8 = thunk_FUN_004093d0(piVar5,pdVar6);
  if ((iVar8 == 1) && (iVar8 = 0, 0 < *param_1)) {
    iVar9 = 0;
    do {
      iVar10 = *(int *)((int)pdVar6 + 4) * iVar8;
      iVar9 = iVar9 + 0x14;
      iVar8 = iVar8 + 1;
      *(float *)(param_1[1] + -4 + iVar9) = (float)pdVar6[iVar10 + 1];
    } while (iVar8 < *param_1);
  }
  thunk_FUN_004093b0(pdVar6);
  thunk_FUN_004093b0(piVar5);
  return;
}


