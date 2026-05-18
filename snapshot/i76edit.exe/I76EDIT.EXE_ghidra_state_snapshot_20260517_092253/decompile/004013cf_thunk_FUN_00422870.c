/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00422870
 * Entry: 004013cf
 * Signature: undefined __cdecl thunk_FUN_00422870(uint * param_1)
 */


void __cdecl thunk_FUN_00422870(uint *param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  uint *puVar7;
  ushort *puVar8;
  int iVar9;
  uint *puVar10;
  ushort *puVar11;
  ulonglong uVar12;
  longlong lVar13;
  uint *apuStack_5c [4];
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined8 uStack_44;
  uint *puStack_3c;
  uint *puStack_38;
  ushort *puStack_34;
  uint *puStack_30;
  ushort *puStack_2c;
  ushort *puStack_28;
  int iStack_24;
  int iStack_20;
  ushort *puStack_1c;
  uint *puStack_18;
  uint *puStack_14;
  uint *puStack_10;
  uint *puStack_c;
  uint *puStack_8;
  uint *puStack_4;
  
  puStack_1c = (ushort *)thunk_FUN_00412120((int)param_1,1);
  puStack_38 = thunk_FUN_00412120((int)param_1,2);
  apuStack_5c[0] = _malloc(0x208);
  puStack_18 = apuStack_5c[0];
  apuStack_5c[1] = _malloc(0x208);
  puStack_14 = apuStack_5c[1];
  apuStack_5c[2] = _malloc(0x208);
  puStack_10 = apuStack_5c[2];
  puStack_34 = _malloc(0x8000);
  apuStack_5c[3] = param_1;
  uStack_4c = 0;
  uStack_48 = 0;
  iVar6 = -1;
  puStack_28 = puStack_34;
  uStack_44 = thunk_FUN_004121d0((int)param_1,0,0);
  puVar5 = apuStack_5c[0];
  for (iVar3 = 0x82; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0xffffffff;
    puVar5 = puVar5 + 1;
  }
  *apuStack_5c[1] = 0xffffffff;
  *apuStack_5c[2] = 0xffffffff;
  apuStack_5c[1][0x81] = 0xffffffff;
  apuStack_5c[2][0x81] = 0xffffffff;
  iVar3 = (int)uStack_44;
  do {
    iVar9 = -1;
    puStack_3c = (uint *)(uStack_44._4_4_ + iVar6);
    puVar5 = apuStack_5c[iVar6 + 1];
    do {
      uVar2 = iVar9 + iVar3;
      iVar9 = iVar9 + 1;
      uVar2 = thunk_FUN_0041f2b0(uVar2,(uint)puStack_3c,100);
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
    } while (iVar9 < 0x81);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  uStack_4c = 0;
  uStack_48 = 2;
  uStack_44 = thunk_FUN_004121d0((int)apuStack_5c[3],0,2);
  puStack_2c = puStack_1c;
  puStack_30 = puStack_38;
  iStack_20 = 0x80;
  do {
    puVar7 = apuStack_5c[0];
    iStack_24 = 0x80;
    puVar10 = apuStack_5c[1];
    puVar5 = apuStack_5c[2];
    do {
      uVar1 = *puStack_2c;
      if (((uVar1 != 0x8000) && (1 < (ushort)*puStack_30)) && ((ushort)*puStack_30 < 5)) {
        iVar3 = 0;
        apuStack_5c[3] = puVar10 + 2;
        puStack_38 = apuStack_5c[0] + 2;
        puStack_8 = puVar5 + 2;
        uVar2 = apuStack_5c[0][1];
        uVar4 = 0;
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          iVar3 = 1;
          uVar4 = uVar2;
        }
        uVar2 = puVar5[1];
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *apuStack_5c[3];
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *puVar10;
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *puStack_38;
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *apuStack_5c[0];
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *puStack_8;
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        uVar2 = *puVar5;
        if ((-1 < (int)uVar2) && (uVar2 != 0x8000)) {
          uVar4 = uVar4 + uVar2;
          iVar3 = iVar3 + 1;
        }
        if (uVar1 != 0x8000) {
          uVar4 = uVar4 + uVar1;
          iVar3 = iVar3 + 1;
        }
        puStack_3c = puVar10;
        puStack_c = apuStack_5c[0];
        puStack_4 = puVar5;
        if (iVar3 != 0) {
          apuStack_5c[3] = (uint *)((float)(int)uVar4 / (float)iVar3);
          uVar12 = __ftol();
          if ((int)((longlong)((ulonglong)(uint)((int)uVar12 >> 0x1f) << 0x20 | uVar12 & 0xffffffff)
                   % 10) < 5) {
            lVar13 = __ftol();
            uVar1 = (ushort)lVar13;
          }
          else {
            lVar13 = __ftol();
            uVar1 = (short)lVar13 + 1;
          }
        }
      }
      *puStack_34 = uVar1;
      puStack_34 = puStack_34 + 1;
      puStack_30 = (uint *)((int)puStack_30 + 2);
      puStack_2c = puStack_2c + 1;
      iStack_24 = iStack_24 + -1;
      puVar10 = puVar10 + 1;
      puVar5 = puVar5 + 1;
      apuStack_5c[0] = apuStack_5c[0] + 1;
    } while (iStack_24 != 0);
    iVar3 = -1;
    uStack_44 = CONCAT44(uStack_44._4_4_ + 1,(int)uStack_44);
    apuStack_5c[0] = apuStack_5c[1];
    apuStack_5c[1] = apuStack_5c[2];
    apuStack_5c[2] = puVar7;
    iStack_24 = 0;
    do {
      uVar2 = (int)uStack_44 + iVar3;
      iVar3 = iVar3 + 1;
      uVar2 = thunk_FUN_0041f2b0(uVar2,uStack_44._4_4_,100);
      *puVar7 = uVar2;
      puVar7 = puVar7 + 1;
    } while (iVar3 < 0x81);
    iStack_20 = iStack_20 + -1;
  } while (iStack_20 != 0);
  puVar8 = puStack_28;
  puVar11 = puStack_1c;
  for (iVar3 = 0x2000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)puVar11 = *(undefined4 *)puVar8;
    puVar8 = puVar8 + 2;
    puVar11 = puVar11 + 2;
  }
  _free(puStack_28);
  _free(puStack_18);
  _free(puStack_14);
  _free(puStack_10);
  return;
}


