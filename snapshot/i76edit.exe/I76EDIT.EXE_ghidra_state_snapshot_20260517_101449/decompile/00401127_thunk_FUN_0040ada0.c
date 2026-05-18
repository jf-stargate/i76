/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ada0
 * Entry: 00401127
 * Signature: undefined4 __cdecl thunk_FUN_0040ada0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0040ada0(HWND param_1,undefined4 param_2,uint param_3)

{
  char cVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 extraout_ECX;
  undefined4 uVar6;
  undefined4 extraout_ECX_00;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 extraout_EDX;
  undefined4 uVar10;
  undefined4 extraout_EDX_00;
  undefined4 *puVar11;
  char *pcVar12;
  char *pcVar13;
  int *piVar14;
  undefined8 uVar15;
  longlong lVar16;
  longlong lVar17;
  undefined8 uVar18;
  int *piVar19;
  uint uStack_128;
  uint uStack_124;
  int iStack_120;
  undefined4 auStack_11c [10];
  int aiStack_f4 [11];
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined4 auStack_a8 [21];
  undefined4 auStack_54 [10];
  char acStack_2c [44];
  
  uStack_124 = 0;
  uStack_128 = 0;
  iStack_120 = -1;
  uVar15 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar9 = (undefined4)((ulonglong)uVar15 >> 0x20);
  uVar3 = (undefined4)uVar15;
  uVar6 = 0;
  uVar18 = uVar15;
  if (DAT_0043477c != 0) {
    auStack_a8[0] = uVar3;
    puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,DAT_0043477c);
    puVar11 = auStack_11c;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar11 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar11 = puVar11 + 1;
    }
    SendDlgItemMessageA(DAT_0164238c,0x3f2,0xd,0x28,(LPARAM)aiStack_f4);
    thunk_FUN_00408c50(DAT_0043477c,auStack_11c);
    uVar18 = CONCAT44(extraout_EDX,auStack_a8[0]);
    uVar6 = extraout_ECX;
  }
  uVar10 = (undefined4)((ulonglong)uVar18 >> 0x20);
  auStack_a8[0] = (undefined4)uVar18;
  switch(DAT_00434788) {
  case 1:
    uVar2 = GetAsyncKeyState(0x11);
    if ((uVar2 & 0x8000) == 0) {
      uVar18 = thunk_FUN_004089e0(extraout_ECX_00,extraout_EDX_00,uVar3,uVar9,5,(undefined4 *)0x0,
                                  &uStack_128);
      iStack_120 = (int)uVar18;
      if (uStack_128 != 0) {
        puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,uStack_128);
        puVar11 = auStack_11c;
        for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar11 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar11 = puVar11 + 1;
        }
        lVar16 = __ftol();
        lVar17 = __ftol();
        uVar15 = CONCAT44((int)lVar17,(int)lVar16);
      }
    }
    uStack_c8 = uVar15;
    uStack_c0 = uVar15;
    DAT_00434780 = (int *)thunk_FUN_00408830((int *)&uStack_c8);
    DAT_00434784 = 1;
    if (uStack_128 != 0) {
      thunk_FUN_00408bc0((int)DAT_00434780,0,uStack_128,iStack_120);
    }
    DAT_0043477c = thunk_FUN_004088c0((uint)DAT_00434780);
    break;
  case 2:
    uVar18 = thunk_FUN_00408920(uVar6,uVar10,uVar3,uVar9,10,&DAT_00434780);
    DAT_00434784 = (int)uVar18;
    if (DAT_00434780 != (int *)0x0) {
      DAT_0043477c = thunk_FUN_004088c0((uint)DAT_00434780);
    }
    break;
  case 3:
    uVar18 = thunk_FUN_00408920(uVar6,uVar10,uVar3,uVar9,10,&DAT_00434780);
    DAT_00434784 = (int)uVar18;
    if (DAT_00434780 != (int *)0x0) {
      puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,(int)DAT_00434780);
      puVar11 = auStack_11c;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar11 = puVar11 + 1;
      }
      if ((aiStack_f4[DAT_00434784 + -4] == 0) &&
         (iVar5 = MessageBoxA(param_1,s_Delete_this_path__00434794,s_Delete_Path_004347ac,1),
         iVar5 == 1)) {
        thunk_FUN_00408ac0(DAT_00434780);
      }
      DAT_00434780 = (int *)0x0;
      DAT_00434784 = -1;
    }
    DAT_0043477c = 0;
    break;
  case 4:
    uVar18 = thunk_FUN_00408920(uVar6,uVar10,uVar3,uVar9,10,&uStack_128);
    uStack_c8 = CONCAT44(uStack_c8._4_4_,(int)uStack_c8);
    uStack_c0 = CONCAT44(uStack_c0._4_4_,(undefined4)uStack_c0);
    if (uStack_128 != 0) {
      puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,uStack_128);
      puVar11 = auStack_11c;
      for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar11 = puVar11 + 1;
      }
      if (aiStack_f4[(uint)uVar18 - 4] == 0) {
        uStack_124 = thunk_FUN_004088c0(uStack_128);
        if (uStack_124 != 0) {
          puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,uStack_124);
          puVar11 = auStack_54;
          for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar11 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar11 = puVar11 + 1;
          }
        }
        FUN_0040be10(uStack_128,(uint)uVar18);
        InvalidateRgn(param_1,(HRGN)0x0,0);
      }
      DAT_0043477c = thunk_FUN_004088c0(uStack_128);
      uStack_c8 = CONCAT44(uStack_c8._4_4_,(int)uStack_c8);
      uStack_c0 = CONCAT44(uStack_c0._4_4_,(undefined4)uStack_c0);
      if ((DAT_0043477c != 0) &&
         (uStack_c8 = CONCAT44(uStack_c8._4_4_,(int)uStack_c8),
         uStack_c0 = CONCAT44(uStack_c0._4_4_,(undefined4)uStack_c0), uStack_124 != 0)) {
        puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,DAT_0043477c);
        puVar11 = auStack_11c;
        for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar11 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar11 = puVar11 + 1;
        }
        uVar7 = 0xffffffff;
        pcVar12 = acStack_2c;
        do {
          pcVar13 = pcVar12;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar13 = pcVar12 + 1;
          cVar1 = *pcVar12;
          pcVar12 = pcVar13;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        piVar19 = (int *)(pcVar13 + -uVar7);
        piVar14 = aiStack_f4;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *piVar14 = *piVar19;
          piVar19 = piVar19 + 1;
          piVar14 = piVar14 + 1;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *(char *)piVar14 = (char)*piVar19;
          piVar19 = (int *)((int)piVar19 + 1);
          piVar14 = (int *)((int)piVar14 + 1);
        }
        thunk_FUN_00408c50(DAT_0043477c,auStack_11c);
      }
    }
    break;
  default:
    return 0;
  }
  if (DAT_0043477c == 0) {
    piVar19 = (int *)&DAT_00434334;
  }
  else {
    puVar4 = (undefined4 *)thunk_FUN_00408c30(auStack_a8,DAT_0043477c);
    puVar11 = auStack_11c;
    for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar11 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar11 = puVar11 + 1;
    }
    piVar19 = aiStack_f4;
  }
  SendDlgItemMessageA(DAT_0164238c,0x3f2,0xc,0,(LPARAM)piVar19);
  InvalidateRgn(param_1,(HRGN)0x0,0);
  return 1;
}


