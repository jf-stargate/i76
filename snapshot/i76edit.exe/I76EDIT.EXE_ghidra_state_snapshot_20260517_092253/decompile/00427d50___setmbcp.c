/*
 * Program: I76EDIT.EXE
 * Function: __setmbcp
 * Entry: 00427d50
 * Signature: int __cdecl __setmbcp(int _CodePage)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setmbcp
   
   Library: Visual Studio 1998 Release */

int __cdecl __setmbcp(int _CodePage)

{
  byte *pbVar1;
  byte bVar2;
  UINT CodePage;
  UINT *pUVar3;
  BOOL BVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  BYTE *pBVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  int local_18;
  _cpinfo local_14;
  
  CodePage = getSystemCP(_CodePage);
  if (CodePage == DAT_00438b74) {
    return 0;
  }
  if (CodePage == 0) {
    setSBCS();
    return 0;
  }
  local_18 = 0;
  pUVar3 = &DAT_00438b98;
  do {
    if (*pUVar3 == CodePage) {
      uVar6 = 0;
      puVar10 = &DAT_00438a70;
      for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar10 = 0;
        puVar10 = puVar10 + 1;
      }
      *(undefined1 *)puVar10 = 0;
      do {
        pbVar9 = &DAT_00438ba8 + (uVar6 + local_18 * 6) * 8;
        bVar2 = *pbVar9;
        while ((bVar2 != 0 && (pbVar9[1] != 0))) {
          uVar7 = (uint)*pbVar9;
          if (uVar7 <= pbVar9[1]) {
            bVar2 = (&DAT_00438b90)[uVar6];
            do {
              pbVar1 = (byte *)((int)&DAT_00438a70 + uVar7 + 1);
              *pbVar1 = *pbVar1 | bVar2;
              uVar7 = uVar7 + 1;
            } while (uVar7 <= pbVar9[1]);
          }
          pbVar9 = pbVar9 + 2;
          bVar2 = *pbVar9;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < 4);
      DAT_00438b74 = CodePage;
      _DAT_00438b78 = _CPtoLCID(CodePage);
      DAT_00438b80 = *(undefined4 *)(&DAT_00438b9c + local_18 * 0x30);
      DAT_00438b84 = *(undefined4 *)(&DAT_00438ba0 + local_18 * 0x30);
      DAT_00438b88 = *(undefined4 *)(local_18 * 0x30 + 0x438ba4);
      return 0;
    }
    pUVar3 = pUVar3 + 0xc;
    local_18 = local_18 + 1;
  } while (pUVar3 < &DAT_00438c88);
  BVar4 = GetCPInfo(CodePage,&local_14);
  if (BVar4 == 1) {
    puVar10 = &DAT_00438a70;
    for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    *(undefined1 *)puVar10 = 0;
    if (local_14.MaxCharSize < 2) {
      _DAT_00438b78 = 0;
      DAT_00438b74 = 0;
    }
    else {
      pBVar8 = local_14.LeadByte;
      while ((local_14.LeadByte[0] != 0 && (pBVar8[1] != 0))) {
        uVar6 = (uint)*pBVar8;
        if (uVar6 <= pBVar8[1]) {
          do {
            pbVar9 = (byte *)((int)&DAT_00438a70 + uVar6 + 1);
            *pbVar9 = *pbVar9 | 4;
            uVar6 = uVar6 + 1;
          } while (uVar6 <= pBVar8[1]);
        }
        pBVar8 = pBVar8 + 2;
        local_14.LeadByte[0] = *pBVar8;
      }
      uVar6 = 1;
      do {
        pbVar9 = (byte *)((int)&DAT_00438a70 + uVar6 + 1);
        *pbVar9 = *pbVar9 | 8;
        uVar6 = uVar6 + 1;
      } while (uVar6 < 0xff);
      DAT_00438b74 = CodePage;
      _DAT_00438b78 = _CPtoLCID(CodePage);
    }
    DAT_00438b80 = 0;
    DAT_00438b84 = 0;
    DAT_00438b88 = 0;
    return 0;
  }
  if (DAT_00438b8c == 0) {
    return -1;
  }
  setSBCS();
  return 0;
}


