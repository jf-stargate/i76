/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ced0
 * Entry: 00401267
 * Signature: undefined __cdecl thunk_FUN_0040ced0(int param_1, int param_2)
 */


void __cdecl thunk_FUN_0040ced0(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  
  iVar3 = param_2;
  iVar2 = param_1;
  iVar4 = thunk_FUN_0041e8d0(&param_1,&param_2,1);
  iVar8 = 0;
  pbVar9 = &DAT_0163ce70 + iVar4 * 200;
  do {
    if ((((*(short *)(pbVar9 + 2) != -1) && ((int)(uint)*pbVar9 < param_1 + 2)) &&
        (param_1 + -2 < (int)(uint)*pbVar9)) &&
       (((int)(uint)pbVar9[1] < param_2 + 2 && (param_2 + -2 < (int)(uint)pbVar9[1])))) {
      return;
    }
    pbVar9 = pbVar9 + 4;
    iVar8 = iVar8 + 1;
  } while (iVar8 < 0x32);
  iVar8 = 0;
  psVar5 = &DAT_0163ce72 + iVar4 * 100;
  do {
    if (*psVar5 == -1) break;
    psVar5 = psVar5 + 2;
    iVar8 = iVar8 + 1;
  } while (iVar8 < 0x32);
  if (iVar8 != 0x32) {
    puVar6 = thunk_FUN_00412120(iVar4,0);
    *(short *)((int)puVar6 + (param_2 * 0x80 + param_1) * 2) = (short)DAT_004347c4;
    uVar1 = DAT_004347c4;
    iVar8 = iVar8 + iVar4 * 0x32;
    iVar7 = iVar8 * 4;
    (&DAT_0163ce70)[iVar7] = (undefined1)param_1;
    (&DAT_0163ce71)[iVar7] = (undefined1)param_2;
    (&DAT_0163ce72)[iVar8 * 2] = (short)uVar1;
    thunk_FUN_0040d0f0(iVar2,iVar3);
    thunk_FUN_0041ea60(iVar4);
  }
  return;
}


