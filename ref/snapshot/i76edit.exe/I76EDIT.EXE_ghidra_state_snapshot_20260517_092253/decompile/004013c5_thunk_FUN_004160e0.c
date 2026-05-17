/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004160e0
 * Entry: 004013c5
 * Signature: undefined __cdecl thunk_FUN_004160e0(HDC param_1)
 */


/* WARNING: Removing unreachable block (ram,0x0041622a) */

void __cdecl thunk_FUN_004160e0(HDC param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  HPEN h;
  int *piVar4;
  HGDIOBJ ho;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  char *pcVar8;
  int *piVar9;
  undefined *color;
  HGDIOBJ pvStack_19c;
  int aiStack_198 [21];
  undefined4 auStack_144 [8];
  char acStack_124 [88];
  undefined4 auStack_cc [30];
  undefined4 auStack_54 [21];
  
  thunk_FUN_0040f420();
  do {
    pvStack_19c = (HGDIOBJ)0x0;
    puVar2 = thunk_FUN_0040f440();
    if (puVar2 == (undefined4 *)0x0) {
      if (DAT_004363c0 != (undefined4 *)0x0) {
        iVar5 = GetROP2(param_1);
        SetROP2(param_1,6);
        piVar4 = (int *)thunk_FUN_0040f4b0(auStack_cc,(int)DAT_004363c0);
        piVar9 = aiStack_198;
        for (iVar6 = 0x15; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar9 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar9 = piVar9 + 1;
        }
        thunk_FUN_00405670(param_1,aiStack_198);
        SetROP2(param_1,iVar5);
      }
      return;
    }
    if (DAT_004363c0 != puVar2) {
      puVar3 = (undefined4 *)thunk_FUN_0040f910(auStack_cc,(int)puVar2);
      puVar7 = auStack_144;
      for (iVar5 = 0x1e; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar7 = puVar7 + 1;
      }
      iVar5 = -1;
      pcVar8 = acStack_124;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      if ((iVar5 == -2) || (iVar5 = thunk_FUN_0041f5d0(acStack_124), iVar5 == 0)) {
        color = &DAT_00ff00ff;
      }
      else {
        color = (undefined *)0xffff;
      }
      h = CreatePen(0,0,(COLORREF)color);
      pvStack_19c = SelectObject(param_1,h);
      piVar4 = (int *)thunk_FUN_0040f4b0(auStack_54,(int)puVar2);
      piVar9 = aiStack_198;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar9 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar9 = piVar9 + 1;
      }
      thunk_FUN_00405670(param_1,aiStack_198);
    }
    if (pvStack_19c != (HGDIOBJ)0x0) {
      ho = SelectObject(param_1,pvStack_19c);
      DeleteObject(ho);
    }
  } while( true );
}


