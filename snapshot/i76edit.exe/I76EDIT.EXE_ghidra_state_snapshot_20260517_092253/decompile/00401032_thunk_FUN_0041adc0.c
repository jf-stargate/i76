/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041adc0
 * Entry: 00401032
 * Signature: undefined __cdecl thunk_FUN_0041adc0(undefined4 * param_1, undefined4 param_2, int param_3, ushort * param_4, uint * param_5, uint * param_6, uint * param_7, uint param_8)
 */


void __cdecl
thunk_FUN_0041adc0(undefined4 *param_1,undefined4 param_2,int param_3,ushort *param_4,uint *param_5,
                  uint *param_6,uint *param_7,uint param_8)

{
  uint *puVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  uint *_FileHandle;
  int iVar6;
  uint uVar7;
  uint uVar8;
  ushort *unaff_EBX;
  int unaff_EBP;
  undefined4 unaff_ESI;
  int iVar9;
  undefined4 *puVar10;
  uint **ppuVar11;
  undefined4 unaff_EDI;
  int iVar12;
  undefined4 *puVar13;
  char *pcVar14;
  char *pcVar15;
  uint *puVar16;
  int unaff_retaddr;
  char cVar17;
  undefined4 *in_stack_00001e4c;
  char *in_stack_00001e50;
  
  FUN_004237d0();
  puVar3 = _malloc(0x2135);
  puVar10 = (undefined4 *)&stack0x0000003c;
  for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar5 = in_stack_00001e50;
  do {
    pcVar15 = pcVar5;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar15 = pcVar5 + 1;
    cVar17 = *pcVar5;
    pcVar5 = pcVar15;
  } while (cVar17 != '\0');
  uVar7 = ~uVar7;
  iVar6 = -1;
  pcVar5 = &stack0x0000003c;
  do {
    pcVar14 = pcVar5;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar14 = pcVar5 + 1;
    cVar17 = *pcVar5;
    pcVar5 = pcVar14;
  } while (cVar17 != '\0');
  pcVar5 = pcVar15 + -uVar7;
  pcVar15 = pcVar14 + -1;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar15 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar15 = pcVar15 + 1;
  }
  *puVar3 = 0x56455254;
  puVar3[1] = 0xc;
  iVar6 = 0;
  iVar9 = 0;
  puVar3[2] = 4;
  cVar17 = '\0';
  do {
    iVar12 = 0;
    do {
      iVar4 = thunk_FUN_00411b30(iVar12,iVar6,0);
      (&stack0x00000545)[iVar9 + iVar12] = (char)iVar4;
      if (iVar4 != -1) {
        cVar17 = cVar17 + '\x01';
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < 0x50);
    iVar9 = iVar9 + 0x50;
    iVar6 = iVar6 + 1;
  } while (iVar9 < 0x1900);
  puVar10 = (undefined4 *)&stack0x0000053c;
  puVar13 = puVar3 + 3;
  for (iVar6 = 0x642; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar13 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar13 = puVar13 + 1;
  }
  *(undefined1 *)puVar13 = *(undefined1 *)puVar10;
  param_7 = (uint *)CONCAT31(param_7._1_3_,(char)iVar4);
  param_5 = (uint *)0x454e4f5a;
  param_6 = (uint *)0x16;
  if (DAT_00433a30 != 0) {
    puVar10 = (undefined4 *)&stack0x0000003c;
    for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar5 = in_stack_00001e50;
    do {
      pcVar15 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar15 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar15;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    iVar6 = -1;
    pcVar5 = &stack0x0000003c;
    do {
      pcVar14 = pcVar5;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar14 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar14;
    } while (cVar2 != '\0');
    pcVar5 = pcVar15 + -uVar7;
    pcVar15 = pcVar14 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar15 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar15 = pcVar15 + 1;
    }
  }
  __splitpath(in_stack_00001e50,&stack0x00000000,&stack0x0000033c,&stack0x0000013c,&stack0x0000043c)
  ;
  __makepath(&stack0x0000002c,&DAT_00434334,&DAT_00434334,&stack0x0000013c,&DAT_004367bc);
  uVar7 = 0xffffffff;
  param_7._0_2_ = (ushort)(byte)param_7;
  pcVar5 = &stack0x0000002c;
  do {
    pcVar15 = pcVar5;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar15 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar15;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar5 = pcVar15 + -uVar7;
  pcVar15 = (char *)((int)&param_7 + 1);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar15 = pcVar15 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar15 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar15 = pcVar15 + 1;
  }
  ppuVar11 = &param_5;
  puVar10 = (undefined4 *)((int)puVar3 + 0x1915);
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar10 = *ppuVar11;
    ppuVar11 = ppuVar11 + 1;
    puVar10 = puVar10 + 1;
  }
  *(undefined2 *)puVar10 = *(undefined2 *)ppuVar11;
  if (DAT_00433a30 != 0) {
    uVar7 = 0xffffffff;
    pcVar5 = (char *)&DAT_004367b4;
    do {
      pcVar15 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar15 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar15;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    iVar6 = -1;
    pcVar5 = &stack0x0000003c;
    do {
      pcVar14 = pcVar5;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar14 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar14;
    } while (cVar2 != '\0');
    pcVar5 = pcVar15 + -uVar7;
    pcVar15 = pcVar14 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar15 = pcVar15 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar15 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar15 = pcVar15 + 1;
    }
    if (DAT_00433a30 != 0) {
      pcVar5 = &stack0x0000003c;
      goto LAB_0041b010;
    }
  }
  pcVar5 = &stack0x0000002c;
LAB_0041b010:
  _FileHandle = (uint *)__open(pcVar5,0x8301);
  puVar16 = (uint *)0x0;
  if ('\0' < cVar17) {
    do {
      puVar1 = (uint *)((int)puVar16 + 1);
      _sprintf(&stack0x0000023c,s_Exporting_Zone__d_of__d__00436794);
      thunk_FUN_0041e120(&stack0x0000023c);
      thunk_FUN_0041aaa0(puVar16,_FileHandle,unaff_EBP,CONCAT44(unaff_ESI,unaff_EDI),unaff_EBX,
                         unaff_retaddr,puVar3,0x56455254,0xc,(ushort *)0x4,param_5,param_6,param_7,
                         param_8);
      puVar16 = puVar1;
    } while ((int)puVar1 < (int)cVar17);
  }
  __close((int)_FileHandle);
  *in_stack_00001e4c = 0x192b;
  return;
}


