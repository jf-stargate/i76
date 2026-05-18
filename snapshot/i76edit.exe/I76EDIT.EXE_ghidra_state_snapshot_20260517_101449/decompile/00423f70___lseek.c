/*
 * Program: I76EDIT.EXE
 * Function: __lseek
 * Entry: 00423f70
 * Signature: long __cdecl __lseek(int _FileHandle, long _Offset, int _Origin)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __lseek
   
   Library: Visual Studio 1998 Release */

long __cdecl __lseek(int _FileHandle,long _Offset,int _Origin)

{
  int *piVar1;
  int iVar2;
  byte *pbVar3;
  HANDLE hFile;
  DWORD DVar4;
  ulong uVar5;
  
  if ((uint)_FileHandle < DAT_016424ec) {
    piVar1 = (int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3));
    iVar2 = (_FileHandle & 0x1fU) * 8;
    if ((*(byte *)(*piVar1 + 4 + iVar2) & 1) != 0) {
      hFile = (HANDLE)__get_osfhandle(_FileHandle);
      if (hFile == (HANDLE)0xffffffff) {
        _DAT_00437ae4 = 9;
        return -1;
      }
      DVar4 = SetFilePointer(hFile,_Offset,(PLONG)0x0,_Origin);
      uVar5 = 0;
      if (DVar4 == 0xffffffff) {
        uVar5 = GetLastError();
      }
      if (uVar5 != 0) {
        __dosmaperr(uVar5);
        return -1;
      }
      pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
      *pbVar3 = *pbVar3 & 0xfd;
      return DVar4;
    }
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


