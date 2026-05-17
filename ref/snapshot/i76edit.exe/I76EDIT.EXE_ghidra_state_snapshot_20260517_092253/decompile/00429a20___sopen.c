/*
 * Program: I76EDIT.EXE
 * Function: __sopen
 * Entry: 00429a20
 * Signature: int __cdecl __sopen(char * _Filename, int _OpenFlag, int _ShareFlag, ...)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __sopen
   
   Library: Visual Studio 1998 Release */

int __cdecl __sopen(char *_Filename,int _OpenFlag,int _ShareFlag,...)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  HANDLE hFile;
  long lVar4;
  int iVar5;
  byte bVar6;
  DWORD DVar7;
  bool bVar8;
  uint in_stack_00000010;
  char local_19;
  DWORD local_18;
  uint local_14;
  DWORD local_10;
  _SECURITY_ATTRIBUTES local_c;
  
  local_c.lpSecurityDescriptor = (LPVOID)0x0;
  local_c.nLength = 0xc;
  bVar8 = (_OpenFlag & 0x80U) == 0;
  if (bVar8) {
    bVar6 = 0;
  }
  else {
    bVar6 = 0x10;
  }
  local_c.bInheritHandle = (BOOL)bVar8;
  if (((_OpenFlag & 0x8000U) == 0) && (((_OpenFlag & 0x4000U) != 0 || (DAT_00438fb0 != 0x8000)))) {
    bVar6 = bVar6 | 0x80;
  }
  uVar3 = _OpenFlag & 3;
  if (uVar3 == 0) {
    local_14 = 0x80000000;
  }
  else if (uVar3 == 1) {
    local_14 = 0x40000000;
  }
  else {
    if (uVar3 != 2) {
      _DAT_00437ae4 = 0x16;
      DAT_00437ae8 = 0;
      return -1;
    }
    local_14 = 0xc0000000;
  }
  switch(_ShareFlag) {
  case 0x10:
    local_18 = 0;
    break;
  default:
    _DAT_00437ae4 = 0x16;
    DAT_00437ae8 = 0;
    return -1;
  case 0x20:
    local_18 = 1;
    break;
  case 0x30:
    local_18 = 2;
    break;
  case 0x40:
    local_18 = 3;
  }
  uVar3 = _OpenFlag & 0x700;
  if (uVar3 < 0x101) {
    if (uVar3 == 0x100) {
      local_10 = 4;
      goto LAB_00429bbb;
    }
    if (uVar3 != 0) {
      _DAT_00437ae4 = 0x16;
      DAT_00437ae8 = 0;
      return -1;
    }
LAB_00429b8b:
    local_10 = 3;
    goto LAB_00429bbb;
  }
  if (uVar3 < 0x301) {
    if (uVar3 == 0x300) {
      local_10 = 2;
      goto LAB_00429bbb;
    }
    if (uVar3 != 0x200) {
      _DAT_00437ae4 = 0x16;
      DAT_00437ae8 = 0;
      return -1;
    }
LAB_00429b9f:
    local_10 = 5;
  }
  else {
    if (uVar3 < 0x501) {
      if (uVar3 != 0x500) {
        if (uVar3 != 0x400) {
          _DAT_00437ae4 = 0x16;
          DAT_00437ae8 = 0;
          return -1;
        }
        goto LAB_00429b8b;
      }
    }
    else {
      if (uVar3 == 0x600) goto LAB_00429b9f;
      if (uVar3 != 0x700) {
        _DAT_00437ae4 = 0x16;
        DAT_00437ae8 = 0;
        return -1;
      }
    }
    local_10 = 1;
  }
LAB_00429bbb:
  DVar7 = 0x80;
  if (((_OpenFlag & 0x100U) != 0) && ((~DAT_00437aec & in_stack_00000010 & 0x80) == 0)) {
    DVar7 = 1;
  }
  if ((_OpenFlag & 0x40U) != 0) {
    local_14 = local_14 | 0x10000;
    DVar7 = DVar7 | 0x4000000;
  }
  if ((_OpenFlag & 0x1000U) != 0) {
    DVar7 = DVar7 | 0x100;
  }
  if ((_OpenFlag & 0x20U) == 0) {
    if ((_OpenFlag & 0x10U) != 0) {
      DVar7 = DVar7 | 0x10000000;
    }
  }
  else {
    DVar7 = DVar7 | 0x8000000;
  }
  uVar3 = __alloc_osfhnd();
  if (uVar3 == 0xffffffff) {
    _DAT_00437ae4 = 0x18;
    DAT_00437ae8 = 0;
    return -1;
  }
  hFile = CreateFileA(_Filename,local_14,local_18,&local_c,local_10,DVar7,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    DVar7 = GetLastError();
    __dosmaperr(DVar7);
    return -1;
  }
  DVar7 = GetFileType(hFile);
  if (DVar7 != 0) {
    if (DVar7 == 2) {
      bVar6 = bVar6 | 0x40;
    }
    else if (DVar7 == 3) {
      bVar6 = bVar6 | 8;
    }
    __set_osfhnd(uVar3,(intptr_t)hFile);
    piVar1 = (int *)((int)&DAT_016423b0 + ((int)(uVar3 & 0xffffffe7) >> 3));
    local_14 = (uVar3 & 0x1f) * 8;
    *(byte *)(*piVar1 + 4 + local_14) = bVar6 | 1;
    local_18 = CONCAT31(local_18._1_3_,bVar6) & 0xffffff48;
    if ((((bVar6 & 0x48) == 0) && ((bVar6 & 0x80) != 0)) && ((_OpenFlag & 2U) != 0)) {
      lVar4 = __lseek(uVar3,-1,2);
      if (lVar4 == -1) {
        if (DAT_00437ae8 != 0x83) {
          __close(uVar3);
          return -1;
        }
      }
      else {
        local_19 = '\0';
        iVar5 = __read(uVar3,&local_19,1);
        if (((iVar5 == 0) && (local_19 == '\x1a')) && (iVar5 = __chsize(uVar3,lVar4), iVar5 == -1))
        {
          __close(uVar3);
          return -1;
        }
        lVar4 = __lseek(uVar3,0,0);
        if (lVar4 == -1) {
          __close(uVar3);
          return -1;
        }
      }
    }
    if (((char)local_18 == '\0') && ((_OpenFlag & 8U) != 0)) {
      pbVar2 = (byte *)(*piVar1 + 4 + local_14);
      *pbVar2 = *pbVar2 | 0x20;
    }
    return uVar3;
  }
  CloseHandle(hFile);
  DVar7 = GetLastError();
  __dosmaperr(DVar7);
  return -1;
}


