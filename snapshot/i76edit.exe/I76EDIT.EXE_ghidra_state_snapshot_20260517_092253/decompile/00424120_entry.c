/*
 * Program: I76EDIT.EXE
 * Function: entry
 * Entry: 00424120
 * Signature: undefined __stdcall entry(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  byte bVar1;
  DWORD DVar2;
  int iVar3;
  HMODULE pHVar4;
  byte *pbVar5;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar6;
  _STARTUPINFOA local_74;
  undefined1 *local_1c;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  uStack_14 = *unaff_FS_OFFSET;
  local_8 = 0xffffffff;
  puStack_c = &DAT_00432260;
  puStack_10 = &LAB_00429204;
  *unaff_FS_OFFSET = &uStack_14;
  local_1c = &stack0xffffff80;
  DVar2 = GetVersion();
  _DAT_00437afc = DVar2 >> 8 & 0xff;
  DAT_00437af0 = DVar2 >> 0x10;
  _DAT_00437af8 = DVar2 & 0xff;
  _DAT_00437af4 = _DAT_00437af8 * 0x100 + _DAT_00437afc;
  iVar3 = __heap_init();
  if (iVar3 == 0) {
    __amsg_exit(0x1c);
  }
  local_8 = 0;
  __ioinit();
  ___initmbctable();
  DAT_016424fc = (byte *)GetCommandLineA();
  DAT_00437e34 = ___crtGetEnvironmentStringsA();
  if ((DAT_00437e34 == (LPVOID)0x0) || (DAT_016424fc == (byte *)0x0)) {
                    /* WARNING: Subroutine does not return */
    _exit(-1);
  }
  __setargv();
  __setenvp();
  __cinit(unaff_EDI);
  bVar1 = *DAT_016424fc;
  pbVar5 = DAT_016424fc;
  if (bVar1 == 0x22) {
    pbVar5 = DAT_016424fc + 1;
    if (*pbVar5 != 0x22) {
      do {
        if (*pbVar5 == 0) break;
        iVar3 = __ismbblead((uint)*pbVar5);
        if (iVar3 != 0) {
          pbVar5 = pbVar5 + 1;
        }
        pbVar5 = pbVar5 + 1;
      } while (*pbVar5 != 0x22);
      if (*pbVar5 != 0x22) goto LAB_00424225;
    }
    pbVar5 = pbVar5 + 1;
  }
  else {
    while (0x20 < bVar1) {
      bVar1 = pbVar5[1];
      pbVar5 = pbVar5 + 1;
    }
  }
LAB_00424225:
  bVar1 = *pbVar5;
  while ((bVar1 != 0 && (*pbVar5 < 0x21))) {
    pbVar5 = pbVar5 + 1;
    bVar1 = *pbVar5;
  }
  local_74.dwFlags = 0;
  GetStartupInfoA(&local_74);
  uVar6 = 0;
  pHVar4 = GetModuleHandleA((LPCSTR)0x0);
  iVar3 = thunk_FUN_00401a90(pHVar4,uVar6,(char *)pbVar5);
                    /* WARNING: Subroutine does not return */
  _exit(iVar3);
}


