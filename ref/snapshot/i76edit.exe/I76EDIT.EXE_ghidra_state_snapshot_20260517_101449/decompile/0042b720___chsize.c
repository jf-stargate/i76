/*
 * Program: I76EDIT.EXE
 * Function: __chsize
 * Entry: 0042b720
 * Signature: int __cdecl __chsize(int _FileHandle, long _Size)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __chsize
   
   Library: Visual Studio 1998 Release */

int __cdecl __chsize(int _FileHandle,long _Size)

{
  long _Offset;
  long lVar1;
  uint _MaxCharCount;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint in_stack_00001008;
  int in_stack_0000100c;
  
  FUN_004237d0();
  iVar5 = 0;
  if ((DAT_016424ec <= in_stack_00001008) ||
     ((*(byte *)(*(int *)((int)&DAT_016423b0 + ((int)(in_stack_00001008 & 0xffffffe7) >> 3)) + 4 +
                (in_stack_00001008 & 0x1f) * 8) & 1) == 0)) {
    _DAT_00437ae4 = 9;
    return -1;
  }
  _Offset = __lseek(in_stack_00001008,0,1);
  if ((_Offset == -1) || (lVar1 = __lseek(in_stack_00001008,0,2), lVar1 == -1)) {
    return -1;
  }
  uVar6 = in_stack_0000100c - lVar1;
  if ((int)uVar6 < 1) {
    if ((int)uVar6 < 0) {
      __lseek(in_stack_00001008,in_stack_0000100c,0);
      hFile = (HANDLE)__get_osfhandle(in_stack_00001008);
      BVar3 = SetEndOfFile(hFile);
      iVar5 = -(uint)(BVar3 == 0);
      if (iVar5 == -1) {
        _DAT_00437ae4 = 0xd;
        DAT_00437ae8 = GetLastError();
      }
    }
  }
  else {
    puVar7 = (undefined4 *)register0x00000010;
    for (iVar4 = 0x400; puVar7 = puVar7 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = 0;
    }
    iVar4 = __setmode(in_stack_00001008,0x8000);
    do {
      _MaxCharCount = 0x1000;
      if ((int)uVar6 < 0x1000) {
        _MaxCharCount = uVar6;
      }
      iVar2 = __write(in_stack_00001008,&_FileHandle,_MaxCharCount);
      if (iVar2 == -1) {
        if (DAT_00437ae8 == 5) {
          _DAT_00437ae4 = 0xd;
        }
        iVar5 = -1;
        break;
      }
      uVar6 = uVar6 - iVar2;
    } while (0 < (int)uVar6);
    __setmode(in_stack_00001008,iVar4);
  }
  __lseek(in_stack_00001008,_Offset,0);
  return iVar5;
}


