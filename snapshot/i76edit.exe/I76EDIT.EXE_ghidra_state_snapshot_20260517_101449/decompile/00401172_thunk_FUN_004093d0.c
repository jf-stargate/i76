/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004093d0
 * Entry: 00401172
 * Signature: undefined4 __cdecl thunk_FUN_004093d0(int * param_1, double * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl thunk_FUN_004093d0(int *param_1,double *param_2)

{
  double dVar1;
  double dVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double *pdVar6;
  double *pdVar7;
  int iVar8;
  double *pdVar9;
  int iVar10;
  int iStack_1c;
  double *pdStack_18;
  int iStack_10;
  int iStack_c;
  double dStack_8;
  
  iVar3 = *param_1;
  iVar4 = param_1[1];
  iStack_1c = 0;
  if (0 < iVar3) {
    iStack_10 = 0;
    pdStack_18 = param_2;
    do {
      pdStack_18 = pdStack_18 + 1;
      dStack_8 = ABS(*(double *)(param_1 + (iStack_10 + iStack_1c) * 2 + 2));
      if (dStack_8 < _DAT_00432080) {
        iVar10 = iStack_1c + 1;
        if (iVar10 < iVar3) {
          pdVar7 = (double *)(param_1 + (iVar4 * iVar10 + iStack_1c) * 2 + 2);
          do {
            dStack_8 = ABS(*pdVar7);
            if (_DAT_00432080 < dStack_8) break;
            pdVar7 = pdVar7 + iVar4;
            iVar10 = iVar10 + 1;
          } while (iVar10 < iVar3);
        }
        if (iVar3 == iVar10) {
          return 0;
        }
        *pdStack_18 = *(double *)(param_1 + iVar10 * 2 + 2) + *pdStack_18;
        iVar8 = 0;
        if (0 < iVar4) {
          iVar5 = iVar4;
          pdVar7 = (double *)(param_1 + iVar4 * iVar10 * 2 + 2);
          do {
            iVar5 = iVar5 + -1;
            dStack_8 = *pdVar7;
            pdVar7 = pdVar7 + 1;
            iVar8 = iVar4;
          } while (iVar5 != 0);
        }
        *(double *)(param_1 + (iStack_10 + iVar8) * 2 + 2) =
             *(double *)(param_1 + (iStack_10 + iVar8) * 2 + 2) + dStack_8;
      }
      dVar1 = *(double *)(param_1 + (iStack_10 + iStack_1c) * 2 + 2);
      *pdStack_18 = (1.0 / dVar1) * *pdStack_18;
      if (0 < iVar4) {
        iVar10 = iVar4;
        pdVar7 = (double *)(param_1 + iStack_10 * 2 + 2);
        while( true ) {
          dVar2 = *pdVar7 * (1.0 / dVar1);
          iVar10 = iVar10 + -1;
          if (iVar10 == 0) break;
          *pdVar7 = dVar2;
          pdVar7 = pdVar7 + 1;
        }
        *pdVar7 = dVar2;
      }
      iVar10 = 0;
      iStack_c = 0;
      pdVar7 = param_2;
      if (0 < iVar3) {
        do {
          pdVar7 = pdVar7 + 1;
          if (iStack_c != iStack_1c) {
            dVar1 = *(double *)(param_1 + (iStack_1c + iVar10) * 2 + 2);
            *pdVar7 = -dVar1 * *pdStack_18 + *pdVar7;
            if (0 < iVar4) {
              pdVar6 = (double *)(param_1 + iStack_10 * 2 + 2);
              iVar8 = iVar4;
              pdVar9 = (double *)(param_1 + iVar10 * 2 + 2);
              while( true ) {
                dVar2 = *pdVar6;
                pdVar6 = pdVar6 + 1;
                iVar8 = iVar8 + -1;
                dVar2 = dVar2 * -dVar1 + *pdVar9;
                if (iVar8 == 0) break;
                *pdVar9 = dVar2;
                pdVar9 = pdVar9 + 1;
              }
              *pdVar9 = dVar2;
            }
          }
          iVar10 = iVar10 + iVar4;
          iStack_c = iStack_c + 1;
        } while (iStack_c < iVar3);
      }
      iStack_10 = iStack_10 + iVar4;
      iStack_1c = iStack_1c + 1;
    } while (iStack_1c < iVar3);
  }
  return 1;
}


