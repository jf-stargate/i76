/*
 * Program: i76.exe
 * Function: lzo_adler32
 * Entry: 004badb0
 * Signature: uint __cdecl lzo_adler32(uint param_1, byte * param_2, uint param_3)
 */


/* [cgpt i76.exe LZO1Y labels v24; confidence=high] LZO Adler-32 implementation used by the embedded
   LZO runtime configuration check. */

uint __cdecl lzo_adler32(uint param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  
  uVar2 = param_1 & 0xffff;
  uVar18 = param_1 >> 0x10;
  if (param_2 == (byte *)0x0) {
    return 1;
  }
  while (param_3 != 0) {
    uVar1 = param_3;
    if (0x15af < param_3) {
      uVar1 = 0x15b0;
    }
    param_3 = param_3 - uVar1;
    for (; 0xf < (int)uVar1; uVar1 = uVar1 - 0x10) {
      iVar3 = uVar2 + *param_2;
      iVar4 = iVar3 + (uint)param_2[1];
      iVar5 = iVar4 + (uint)param_2[2];
      iVar6 = iVar5 + (uint)param_2[3];
      iVar7 = iVar6 + (uint)param_2[4];
      iVar8 = iVar7 + (uint)param_2[5];
      iVar9 = iVar8 + (uint)param_2[6];
      iVar10 = iVar9 + (uint)param_2[7];
      iVar11 = iVar10 + (uint)param_2[8];
      iVar12 = iVar11 + (uint)param_2[9];
      iVar13 = iVar12 + (uint)param_2[10];
      iVar14 = iVar13 + (uint)param_2[0xb];
      iVar15 = iVar14 + (uint)param_2[0xc];
      iVar16 = iVar15 + (uint)param_2[0xd];
      iVar17 = iVar16 + (uint)param_2[0xe];
      uVar2 = iVar17 + (uint)param_2[0xf];
      uVar18 = uVar18 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8 + iVar9 + iVar10 + iVar11 +
               iVar12 + iVar13 + iVar14 + iVar15 + iVar16 + iVar17 + uVar2;
      param_2 = param_2 + 0x10;
    }
    if (uVar1 != 0) {
      do {
        uVar2 = uVar2 + *param_2;
        param_2 = param_2 + 1;
        uVar18 = uVar18 + uVar2;
        uVar1 = uVar1 - 1;
      } while (0 < (int)uVar1);
    }
    uVar2 = uVar2 % 0xfff1;
    uVar18 = uVar18 % 0xfff1;
  }
  return uVar18 << 0x10 | uVar2;
}


