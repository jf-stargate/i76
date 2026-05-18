/*
 * Program: I76EDIT.EXE
 * Function: __commit
 * Entry: 00429990
 * Signature: int __cdecl __commit(int _FileHandle)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __commit
   
   Library: Visual Studio 1998 Release */

int __cdecl __commit(int _FileHandle)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  int iVar3;
  
  if (((uint)_FileHandle < DAT_016424ec) &&
     ((*(byte *)(*(int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    hFile = (HANDLE)__get_osfhandle(_FileHandle);
    BVar1 = FlushFileBuffers(hFile);
    DVar2 = 0;
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    iVar3 = 0;
    if (DVar2 != 0) {
      _DAT_00437ae4 = 9;
      DAT_00437ae8 = DVar2;
      return -1;
    }
  }
  else {
    _DAT_00437ae4 = 9;
    iVar3 = -1;
  }
  return iVar3;
}


