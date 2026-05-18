/*
 * Program: I76EDIT.EXE
 * Function: __ioinit
 * Entry: 004283a0
 * Signature: int __cdecl __ioinit(void)
 */


/* Library Function - Single Match
    __ioinit
   
   Library: Visual Studio 1998 Release */

int __cdecl __ioinit(void)

{
  undefined4 *puVar1;
  DWORD DVar2;
  HANDLE hFile;
  byte *pbVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  UINT UVar7;
  UINT UVar8;
  int iVar9;
  UINT *pUVar10;
  _STARTUPINFOA local_44;
  
  puVar1 = _malloc(0x100);
  if (puVar1 == (undefined4 *)0x0) {
    __amsg_exit(0x1b);
  }
  DAT_016424ec = 0x20;
  DAT_016423b0 = puVar1;
  if (puVar1 < puVar1 + 0x40) {
    do {
      *(undefined1 *)(puVar1 + 1) = 0;
      puVar6 = puVar1 + 2;
      *puVar1 = 0xffffffff;
      *(undefined1 *)((int)puVar1 + 5) = 10;
      puVar1 = puVar6;
    } while (puVar6 < DAT_016423b0 + 0x40);
  }
  GetStartupInfoA(&local_44);
  if ((local_44.cbReserved2 != 0) && ((UINT *)local_44.lpReserved2 != (UINT *)0x0)) {
    UVar7 = *(UINT *)local_44.lpReserved2;
    pUVar10 = (UINT *)((int)local_44.lpReserved2 + 4);
    pbVar3 = (byte *)(UVar7 + (int)pUVar10);
    if (0x7ff < (int)UVar7) {
      UVar7 = 0x800;
    }
    UVar8 = UVar7;
    if ((int)DAT_016424ec < (int)UVar7) {
      piVar4 = &DAT_016423b4;
      do {
        puVar1 = _malloc(0x100);
        UVar8 = DAT_016424ec;
        if (puVar1 == (undefined4 *)0x0) break;
        *piVar4 = (int)puVar1;
        DAT_016424ec = DAT_016424ec + 0x20;
        if (puVar1 < puVar1 + 0x40) {
          do {
            *(undefined1 *)(puVar1 + 1) = 0;
            puVar6 = puVar1 + 2;
            *puVar1 = 0xffffffff;
            *(undefined1 *)((int)puVar1 + 5) = 10;
            puVar1 = puVar6;
          } while (puVar6 < (undefined4 *)(*piVar4 + 0x100));
        }
        piVar4 = piVar4 + 1;
        UVar8 = UVar7;
      } while ((int)DAT_016424ec < (int)UVar7);
    }
    uVar5 = 0;
    if (0 < (int)UVar8) {
      do {
        if (((*(HANDLE *)pbVar3 != (HANDLE)0xffffffff) && ((*pUVar10 & 1) != 0)) &&
           (((*pUVar10 & 8) != 0 || (DVar2 = GetFileType(*(HANDLE *)pbVar3), DVar2 != 0)))) {
          puVar1 = (undefined4 *)
                   (*(int *)((int)&DAT_016423b0 + ((int)(uVar5 & 0xffffffe7) >> 3)) +
                   (uVar5 & 0x1f) * 8);
          *puVar1 = *(undefined4 *)pbVar3;
          *(byte *)(puVar1 + 1) = (byte)*pUVar10;
        }
        uVar5 = uVar5 + 1;
        pUVar10 = (UINT *)((int)pUVar10 + 1);
        pbVar3 = pbVar3 + 4;
      } while ((int)uVar5 < (int)UVar8);
    }
  }
  iVar9 = 0;
  do {
    piVar4 = DAT_016423b0 + iVar9 * 2;
    if (*piVar4 == -1) {
      DVar2 = 0xfffffff6;
      *(undefined1 *)(piVar4 + 1) = 0x81;
      if (iVar9 != 0) {
        DVar2 = (iVar9 == 1) - 0xc;
      }
      hFile = GetStdHandle(DVar2);
      if ((hFile == (HANDLE)0xffffffff) || (DVar2 = GetFileType(hFile), DVar2 == 0)) {
        *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x40;
      }
      else {
        *piVar4 = (int)hFile;
        if ((DVar2 & 0xff) == 2) {
          *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x40;
        }
        else if ((DVar2 & 0xff) == 3) {
          *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 8;
        }
      }
    }
    else {
      *(byte *)(piVar4 + 1) = *(byte *)(piVar4 + 1) | 0x80;
    }
    iVar9 = iVar9 + 1;
  } while (iVar9 < 3);
  UVar7 = SetHandleCount(DAT_016424ec);
  return UVar7;
}


