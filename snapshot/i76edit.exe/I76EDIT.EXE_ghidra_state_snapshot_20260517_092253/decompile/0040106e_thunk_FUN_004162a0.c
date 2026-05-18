/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004162a0
 * Entry: 0040106e
 * Signature: undefined __cdecl thunk_FUN_004162a0(int param_1, HDC param_2)
 */


void __cdecl thunk_FUN_004162a0(int param_1,HDC param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  HPEN pHVar5;
  HGDIOBJ ho;
  int iVar6;
  int iVar7;
  HGDIOBJ h;
  char *pcVar8;
  int *piVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined *puVar12;
  int iStack_100;
  int iStack_fc;
  int aiStack_f0 [6];
  int iStack_d8;
  int iStack_d4;
  char acStack_d0 [64];
  uint uStack_90;
  char acStack_8c [9];
  char acStack_83 [11];
  int aiStack_78 [30];
  
  h = (HGDIOBJ)0x0;
  uVar10 = thunk_FUN_0040c580(0,0);
  thunk_FUN_00409d70(param_1);
  do {
    do {
      puVar2 = thunk_FUN_00409d90();
      iStack_100 = (int)uVar10;
      iStack_fc = (int)((ulonglong)uVar10 >> 0x20);
      if (puVar2 == (undefined4 *)0x0) {
        if (DAT_004363ac != (undefined4 *)0x0) {
          piVar3 = (int *)thunk_FUN_00409d20(aiStack_78,(int)DAT_004363ac);
          piVar9 = aiStack_f0;
          for (iVar6 = 0x1e; iVar6 != 0; iVar6 = iVar6 + -1) {
            *piVar9 = *piVar3;
            piVar3 = piVar3 + 1;
            piVar9 = piVar9 + 1;
          }
          if (param_1 == aiStack_f0[0]) {
            aiStack_78[0] = GetROP2(param_2);
            SetROP2(param_2,6);
            uVar10 = thunk_FUN_004121d0(aiStack_f0[0],aiStack_f0[1],aiStack_f0[2]);
            iVar6 = _atoi(acStack_8c);
            iVar6 = iVar6 / 5;
            iVar4 = _atoi(acStack_83);
            iVar4 = iVar4 / 5;
            if ((iVar6 == 0) || (iVar4 == 0)) {
              iVar6 = 4;
              iVar4 = 4;
            }
            thunk_FUN_00412750(param_2,(int)uVar10 - iStack_100,
                               iStack_fc - (int)((ulonglong)uVar10 >> 0x20),iVar4,iVar6,iStack_d8);
            SetROP2(param_2,aiStack_78[0]);
          }
        }
        return;
      }
    } while (DAT_004363ac == puVar2);
    piVar3 = (int *)thunk_FUN_00409d20(aiStack_78,(int)puVar2);
    piVar9 = aiStack_f0;
    for (iVar6 = 0x1e; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar9 = piVar9 + 1;
    }
    if (((uStack_90 & 1) == 0) && (iVar6 = thunk_FUN_0041f5a0(iStack_d4), iVar6 == 0)) {
      iVar6 = _atoi(acStack_8c);
      iVar6 = iVar6 / 5;
      iVar4 = _atoi(acStack_83);
      iVar4 = iVar4 / 5;
      uVar11 = thunk_FUN_004121d0(aiStack_f0[0],aiStack_f0[1],aiStack_f0[2]);
      if ((iVar6 == 0) || (iVar4 == 0)) {
        iVar6 = -1;
        pcVar8 = acStack_d0;
        do {
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        if ((iVar6 == -2) || (iVar6 = thunk_FUN_0041f5d0(acStack_d0), iVar6 == 0)) {
          puVar12 = &DAT_00ff00ff;
        }
        else {
          puVar12 = (undefined *)0xffff;
        }
        pHVar5 = CreatePen(0,0,(COLORREF)puVar12);
        h = SelectObject(param_2,pHVar5);
        iVar6 = 4;
        iVar4 = 4;
      }
      else {
        iVar7 = -1;
        pcVar8 = acStack_d0;
        do {
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        if ((iVar7 == -2) || (iVar7 = thunk_FUN_0041f5d0(acStack_d0), iVar7 == 0)) {
          puVar12 = &DAT_00ff00ff;
        }
        else {
          puVar12 = (undefined *)0xffff;
        }
        pHVar5 = CreatePen(0,0,(COLORREF)puVar12);
        h = SelectObject(param_2,pHVar5);
      }
      thunk_FUN_00412750(param_2,(int)uVar11 - iStack_100,
                         iStack_fc - (int)((ulonglong)uVar11 >> 0x20),iVar4,iVar6,iStack_d8);
    }
    if (h != (HGDIOBJ)0x0) {
      ho = SelectObject(param_2,h);
      DeleteObject(ho);
    }
  } while( true );
}


