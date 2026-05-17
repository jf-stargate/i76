/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00403b30
 * Entry: 004014e7
 * Signature: undefined4 __stdcall thunk_FUN_00403b30(undefined4 param_1, undefined4 param_2, uint param_3)
 */


undefined4 thunk_FUN_00403b30(HWND param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  uint uStack_2ec;
  uint uStack_2e8;
  int aiStack_2d0 [30];
  int aiStack_258 [30];
  undefined4 auStack_1e0 [30];
  undefined4 auStack_168 [30];
  undefined4 auStack_f0 [30];
  undefined4 auStack_78 [30];
  
  if ((DAT_004340a0 != (int *)0x0) && (DAT_004340ac != 0)) {
    if (DAT_004340ac == 2) {
      uVar6 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
      piVar2 = (int *)thunk_FUN_00409d20(auStack_1e0,(int)DAT_004340a0);
      piVar5 = aiStack_2d0;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar5 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar5 = piVar5 + 1;
      }
      uStack_2e8 = (uint)((ulonglong)uVar6 >> 0x20);
      uStack_2ec = (uint)uVar6;
      thunk_FUN_00409a90(DAT_004340a0,uStack_2ec,uStack_2e8);
      uVar1 = i76edit_get_or_create_zone_surface_sample(uStack_2ec,uStack_2e8,0);
      thunk_FUN_00409b60((int)DAT_004340a0,uVar1);
      puVar4 = auStack_168;
    }
    else {
      if (DAT_004340ac != 3) {
        return 0;
      }
      uVar6 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
      piVar2 = (int *)thunk_FUN_00409d20(auStack_f0,(int)DAT_004340a0);
      piVar5 = aiStack_2d0;
      for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar5 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar5 = piVar5 + 1;
      }
      uVar7 = i76edit_find_zone_cell_origin_by_zone_id(aiStack_2d0[0],aiStack_2d0[1],aiStack_2d0[2])
      ;
      uStack_2ec = (uint)uVar6;
      uStack_2e8 = (uint)((ulonglong)uVar6 >> 0x20);
      fpatan((float10)(int)-((int)((ulonglong)uVar7 >> 0x20) - uStack_2e8),
             (float10)(int)(uStack_2ec - (int)uVar7));
      lVar8 = __ftol();
      thunk_FUN_00409b80((int)DAT_004340a0,(int)lVar8);
      puVar4 = auStack_78;
    }
    piVar2 = (int *)thunk_FUN_00409d20(puVar4,(int)DAT_004340a0);
    piVar5 = aiStack_258;
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar5 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5 = piVar5 + 1;
    }
    FUN_004043d0(param_1,aiStack_2d0,aiStack_258);
  }
  return 1;
}


