/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00416f80
 * Entry: 00401177
 * Signature: undefined4 __cdecl thunk_FUN_00416f80(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_00416f80(HWND param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined4 *puVar8;
  int aiStack_4c8 [21];
  int aiStack_474 [21];
  undefined4 auStack_420 [21];
  undefined4 auStack_3cc [21];
  undefined4 auStack_378 [21];
  undefined4 auStack_324 [21];
  int aiStack_2d0 [30];
  int aiStack_258 [30];
  undefined4 auStack_1e0 [30];
  undefined4 auStack_168 [30];
  undefined4 auStack_f0 [30];
  undefined4 auStack_78 [30];
  
  uVar6 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar4 = (uint)((ulonglong)uVar6 >> 0x20);
  uVar1 = (uint)uVar6;
  switch(DAT_004363b4) {
  case 1:
  case 2:
  case 4:
    if (DAT_004363c0 == 0) {
      return 1;
    }
    if (DAT_004363bc == 0) {
      return 1;
    }
    piVar2 = (int *)thunk_FUN_0040f4b0(auStack_420,DAT_004363c0);
    piVar5 = aiStack_4c8;
    for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    thunk_FUN_0040f930(DAT_004363c0,DAT_004363c4,uVar1,uVar4);
    piVar2 = (int *)thunk_FUN_0040f4b0(auStack_3cc,DAT_004363c0);
    piVar5 = aiStack_474;
    for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    thunk_FUN_004058a0(param_1,aiStack_4c8,aiStack_474);
    return 1;
  default:
    return 0;
  case 5:
    if (DAT_004363c0 == 0) {
      return 1;
    }
    if (DAT_004363bc == 0) {
      return 1;
    }
    piVar2 = (int *)thunk_FUN_0040f4b0(auStack_378,DAT_004363c0);
    piVar5 = aiStack_4c8;
    for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    thunk_FUN_0040f930(DAT_004363c0,DAT_004363c4,uVar1,uVar4);
    piVar2 = (int *)thunk_FUN_0040f4b0(auStack_324,DAT_004363c0);
    piVar5 = aiStack_474;
    for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    thunk_FUN_004058a0(param_1,aiStack_4c8,aiStack_474);
    return 1;
  case 8:
    if (DAT_004363a8 == (int *)0x0) {
      return 1;
    }
    piVar2 = (int *)thunk_FUN_00409d20(auStack_1e0,(int)DAT_004363a8);
    piVar5 = aiStack_2d0;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    thunk_FUN_00409a90(DAT_004363a8,uVar1,uVar4);
    puVar8 = auStack_168;
    break;
  case 9:
    if (DAT_004363a8 == (int *)0x0) {
      return 1;
    }
    piVar2 = (int *)thunk_FUN_00409d20(auStack_f0,(int)DAT_004363a8);
    piVar5 = aiStack_2d0;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    uVar6 = i76edit_find_zone_cell_origin_by_zone_id(aiStack_2d0[0],aiStack_2d0[1],aiStack_2d0[2]);
    fpatan((float10)(int)-((int)((ulonglong)uVar6 >> 0x20) - uVar4),
           (float10)(int)(uVar1 - (int)uVar6));
    lVar7 = __ftol();
    thunk_FUN_00409b80((int)DAT_004363a8,(int)lVar7);
    puVar8 = auStack_78;
  }
  piVar2 = (int *)thunk_FUN_00409d20(puVar8,(int)DAT_004363a8);
  piVar5 = aiStack_258;
  for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar5 = piVar5 + 1;
  }
  FUN_00417c60(param_1,aiStack_2d0,aiStack_258);
  return 1;
}


