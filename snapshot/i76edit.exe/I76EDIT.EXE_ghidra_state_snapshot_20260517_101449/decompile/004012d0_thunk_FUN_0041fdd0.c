/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041fdd0
 * Entry: 004012d0
 * Signature: undefined4 __cdecl thunk_FUN_0041fdd0(HWND param_1, undefined4 param_2, uint param_3)
 */


undefined4 __cdecl thunk_FUN_0041fdd0(HWND param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar8;
  ulonglong uVar7;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 auStack_fc [21];
  int aiStack_a8 [21];
  int aiStack_54 [21];
  
  uStack_10c = 0;
  uStack_108 = 0;
  uStack_104 = 0;
  uStack_100 = 0;
  uVar5 = thunk_FUN_0040c580(param_3 & 0xffff,param_3 >> 0x10);
  uVar6 = (uint)uVar5;
  uVar8 = (uint)((ulonglong)uVar5 >> 0x20);
  uVar1 = i76edit_get_or_create_zone_surface_sample(uVar6,uVar8,99);
  uVar7 = CONCAT44(&uStack_10c,uVar1) & 0xffffffff0000ffff;
  __itoa((int)uVar7,(char *)(uVar7 >> 0x20),10);
  SendDlgItemMessageA(DAT_01642384,0x415,0xc,0,(LPARAM)&uStack_10c);
  if (DAT_004376fc != 0) {
    switch(DAT_004376f4) {
    case 1:
    case 2:
    case 4:
      if (DAT_00437700 != 0) {
        piVar2 = (int *)thunk_FUN_00415a00(auStack_fc,DAT_00437700);
        piVar4 = aiStack_54;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        thunk_FUN_004158b0(DAT_00437700,DAT_00437704,uVar6,uVar8);
        piVar2 = (int *)thunk_FUN_00415a00(auStack_fc,DAT_00437700);
        piVar4 = aiStack_a8;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        thunk_FUN_004058a0(param_1,aiStack_54,aiStack_a8);
      }
      break;
    default:
      return 0;
    case 5:
      if (DAT_00437700 != 0) {
        piVar2 = (int *)thunk_FUN_00415a00(auStack_fc,DAT_00437700);
        piVar4 = aiStack_54;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        thunk_FUN_004158b0(DAT_00437700,DAT_00437704,uVar6,uVar8);
        piVar2 = (int *)thunk_FUN_00415a00(auStack_fc,DAT_00437700);
        piVar4 = aiStack_a8;
        for (iVar3 = 0x15; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        thunk_FUN_004058a0(param_1,aiStack_54,aiStack_a8);
      }
      break;
    case 7:
      thunk_FUN_00420db0(uVar6,uVar8);
      break;
    case 8:
      thunk_FUN_00420ba0(uVar6,uVar8);
      break;
    case 9:
    case 10:
      thunk_FUN_00420cd0(uVar6,uVar8);
    }
  }
  return 1;
}


