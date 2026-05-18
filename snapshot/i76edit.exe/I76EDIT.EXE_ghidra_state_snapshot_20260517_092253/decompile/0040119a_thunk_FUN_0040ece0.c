/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040ece0
 * Entry: 0040119a
 * Signature: undefined __stdcall thunk_FUN_0040ece0(void)
 */


void thunk_FUN_0040ece0(void)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  bool bVar8;
  undefined4 uStack_4;
  
  puVar3 = DAT_00434964;
  uStack_4 = 0;
  if (DAT_00434964 != (undefined4 *)0x0) {
    iVar2 = DAT_00434964[2];
    FUN_0040f0f0((char *)(iVar2 + 0x20),(char *)(iVar2 + 0x58),(byte *)&uStack_4);
    for (puVar3 = (undefined4 *)*puVar3; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3
        ) {
      pbVar6 = (byte *)(iVar2 + 0x20);
      iVar4 = puVar3[2];
      pbVar7 = (byte *)(iVar4 + 0x20);
      do {
        bVar1 = *pbVar6;
        bVar8 = bVar1 < *pbVar7;
        if (bVar1 != *pbVar7) {
LAB_0040ed49:
          iVar5 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_0040ed4e;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar6[1];
        bVar8 = bVar1 < pbVar7[1];
        if (bVar1 != pbVar7[1]) goto LAB_0040ed49;
        pbVar6 = pbVar6 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_0040ed4e:
      if ((iVar5 != 0) || (*(int *)(iVar2 + 0x1c) != *(int *)(iVar4 + 0x1c))) {
        uStack_4 = 0;
      }
      FUN_0040f0f0((char *)(iVar4 + 0x20),(char *)(iVar4 + 0x58),(byte *)&uStack_4);
      iVar2 = iVar4;
    }
  }
  return;
}


