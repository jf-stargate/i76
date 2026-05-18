/*
 * Program: I76EDIT.EXE
 * Function: __close
 * Entry: 004259b0
 * Signature: int __cdecl __close(int _FileHandle)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __close
   
   Library: Visual Studio 1998 Release */

int __cdecl __close(int _FileHandle)

{
  int *piVar1;
  int iVar2;
  intptr_t iVar3;
  intptr_t iVar4;
  HANDLE hObject;
  BOOL BVar5;
  DWORD DVar6;
  
  if (DAT_016424ec <= (uint)_FileHandle) {
    _DAT_00437ae4 = 9;
    DAT_00437ae8 = 0;
    return -1;
  }
  piVar1 = (int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3));
  iVar2 = (_FileHandle & 0x1fU) * 8;
  if ((*(byte *)(*piVar1 + 4 + iVar2) & 1) == 0) {
    _DAT_00437ae4 = 9;
    DAT_00437ae8 = 0;
    return -1;
  }
  if ((_FileHandle == 1) || (_FileHandle == 2)) {
    iVar3 = __get_osfhandle(2);
    iVar4 = __get_osfhandle(1);
    if (iVar3 != iVar4) goto LAB_00425a0b;
  }
  else {
LAB_00425a0b:
    hObject = (HANDLE)__get_osfhandle(_FileHandle);
    BVar5 = CloseHandle(hObject);
    if (BVar5 == 0) {
      DVar6 = GetLastError();
      goto LAB_00425a2b;
    }
  }
  DVar6 = 0;
LAB_00425a2b:
  __free_osfhnd(_FileHandle);
  if (DVar6 == 0) {
    *(undefined1 *)(*piVar1 + 4 + iVar2) = 0;
    return 0;
  }
  __dosmaperr(DVar6);
  return -1;
}


