/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408ec0
 * Entry: 004014ab
 * Signature: undefined __stdcall thunk_FUN_00408ec0(void)
 */


void thunk_FUN_00408ec0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  char *pcVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  uint uVar11;
  undefined4 *puStack00000004;
  undefined4 *puStack00000008;
  undefined4 *puStack0000000c;
  undefined4 uStack00000060;
  int in_stack_00004068;
  
  FUN_004237d0();
  puVar8 = DAT_00439be4;
  for (uVar11 = 0; (puVar8 != (undefined4 *)0x0 && (uVar11 < 0x1000)); uVar11 = uVar11 + 1) {
    *(undefined4 **)(&stack0x00000064 + uVar11 * 4) = puVar8;
    puVar8 = (undefined4 *)*puVar8;
  }
  __write(in_stack_00004068,&stack0x00000000,4);
  puStack00000008 = DAT_00439be4;
  do {
    if (puStack00000008 == (undefined4 *)0x0) {
      return;
    }
    puStack00000004 = (undefined4 *)puStack00000008[2];
    uVar11 = 0xffffffff;
    pcVar7 = (char *)(puStack00000004 + 10);
    do {
      pcVar9 = pcVar7;
      if (uVar11 == 0) break;
      uVar11 = uVar11 - 1;
      pcVar9 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar9;
    } while (cVar1 != '\0');
    uVar11 = ~uVar11;
    pcVar7 = pcVar9 + -uVar11;
    pcVar9 = &stack0x00000038;
    for (uVar4 = uVar11 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
      *pcVar9 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar9 = pcVar9 + 1;
    }
    puVar8 = (undefined4 *)&stack0x00000030;
    puVar10 = puStack00000004 + 8;
    puVar2 = (undefined4 *)&stack0x00000010;
    puVar5 = puStack00000004;
    do {
      puStack0000000c = puVar2;
      *puStack0000000c = *puVar5;
      puStack0000000c[1] = puVar5[1];
      puStack0000000c[2] = puVar5[2];
      piVar6 = (int *)&stack0x00000064;
      *puVar8 = *puVar10;
      iVar3 = 0;
      do {
        if (*piVar6 == puVar10[-2]) {
          puVar8[-2] = iVar3;
          break;
        }
        piVar6 = piVar6 + 1;
        iVar3 = iVar3 + 1;
      } while (piVar6 < &stack0x00004064);
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
      puVar5 = puVar5 + 3;
      puVar2 = puStack0000000c + 3;
    } while (puStack0000000c + 3 < &stack0x00000028);
    uStack00000060 = puStack00000004[0x14];
    __write(in_stack_00004068,&stack0x00000010,0x54);
    puStack00000008 = (undefined4 *)*puStack00000008;
  } while( true );
}


