/*
 * Program: I76EDIT.EXE
 * Function: i76edit_merge_or_normalize_terrain_planes
 * Entry: 00401249
 * Signature: undefined __cdecl i76edit_merge_or_normalize_terrain_planes(int param_1)
 */


void __cdecl i76edit_merge_or_normalize_terrain_planes(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  
  if (param_1 != 0) {
    puVar6 = &DAT_009bc820;
    puVar7 = &DAT_013bcd20;
    for (iVar2 = 0xa0050; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
  }
  iVar2 = 0;
  do {
    if (*(int *)((int)&DAT_009bc820 + iVar2) == 0) {
      return;
    }
    if (param_1 == 0) {
      iVar1 = 0x80;
      iVar3 = iVar2;
      do {
        iVar8 = 0x80;
        iVar4 = iVar3;
        do {
          if (*(short *)((int)&DAT_0043c554 + iVar4) != -0x8000) {
            *(short *)((int)&DAT_009bc824 + iVar4) = *(short *)((int)&DAT_0043c554 + iVar4);
          }
          iVar4 = iVar4 + 0x100;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        iVar3 = iVar3 + 2;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    else if (param_1 == 1) {
      iVar1 = 0x80;
      iVar3 = iVar2;
      do {
        iVar8 = 0x80;
        iVar4 = iVar3;
        do {
          if (*(short *)((int)&DAT_0113cbe4 + iVar4) != -0x8000) {
            *(short *)((int)&DAT_009bc824 + iVar4) = *(short *)((int)&DAT_0113cbe4 + iVar4);
          }
          iVar4 = iVar4 + 0x100;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        iVar3 = iVar3 + 2;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      iVar1 = 0x80;
      iVar3 = iVar2;
      do {
        iVar8 = 0x80;
        iVar4 = iVar3;
        do {
          sVar5 = *(short *)(&DAT_00c3c964 + iVar4);
          if (sVar5 == 199) {
            if (*(ushort *)(&DAT_00ebcaa4 + iVar4) < 100) {
              sVar5 = *(ushort *)(&DAT_00ebcaa4 + iVar4) + 100;
LAB_004126cf:
              *(short *)(&DAT_00ebcaa4 + iVar4) = sVar5;
            }
          }
          else if ((sVar5 != 99) && (sVar5 != 199)) goto LAB_004126cf;
          iVar4 = iVar4 + 0x100;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        iVar3 = iVar3 + 2;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    iVar2 = iVar2 + 0x8004;
    if (0x28013f < iVar2) {
      return;
    }
  } while( true );
}


