/*
 * Program: I76EDIT.EXE
 * Function: __write
 * Entry: 00429550
 * Signature: int __cdecl __write(int _FileHandle, void * _Buf, uint _MaxCharCount)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __write
   
   Library: Visual Studio 1998 Release */

int __cdecl __write(int _FileHandle,void *_Buf,uint _MaxCharCount)

{
  byte bVar1;
  char cVar2;
  BOOL BVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  ulong local_418;
  DWORD local_414;
  int *local_410;
  int local_40c;
  DWORD local_408;
  char local_404 [1028];
  
  if ((uint)_FileHandle < DAT_016424ec) {
    local_410 = (int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3));
    local_40c = (_FileHandle & 0x1fU) * 8;
    bVar1 = *(byte *)(*local_410 + 4 + local_40c);
    if ((bVar1 & 1) != 0) {
      iVar5 = 0;
      local_408 = 0;
      if (_MaxCharCount == 0) {
        return 0;
      }
      if ((bVar1 & 0x20) != 0) {
        __lseek(_FileHandle,0,2);
      }
      if ((*(byte *)((undefined4 *)(local_40c + *local_410) + 1) & 0x80) == 0) {
        BVar3 = WriteFile(*(HANDLE *)(local_40c + *local_410),_Buf,_MaxCharCount,&local_414,
                          (LPOVERLAPPED)0x0);
        if (BVar3 == 0) {
LAB_00429695:
          local_418 = GetLastError();
        }
        else {
          local_418 = 0;
          local_408 = local_414;
        }
      }
      else {
        local_418 = 0;
        pcVar4 = _Buf;
        do {
          if (_MaxCharCount <= (uint)((int)pcVar4 - (int)_Buf)) break;
          pcVar6 = local_404;
          do {
            if (_MaxCharCount <= (uint)((int)pcVar4 - (int)_Buf)) break;
            cVar2 = *pcVar4;
            pcVar4 = pcVar4 + 1;
            if (cVar2 == '\n') {
              *pcVar6 = '\r';
              iVar5 = iVar5 + 1;
              pcVar6 = pcVar6 + 1;
            }
            *pcVar6 = cVar2;
            pcVar6 = pcVar6 + 1;
          } while ((int)pcVar6 - (int)local_404 < 0x400);
          BVar3 = WriteFile(*(HANDLE *)(*local_410 + local_40c),local_404,
                            (int)pcVar6 - (int)local_404,&local_414,(LPOVERLAPPED)0x0);
          if (BVar3 == 0) goto LAB_00429695;
          local_408 = local_408 + local_414;
        } while ((int)pcVar6 - (int)local_404 <= (int)local_414);
      }
      if (local_408 != 0) {
        return local_408 - iVar5;
      }
      if (local_418 == 0) {
        if (((*(byte *)(*local_410 + 4 + local_40c) & 0x40) != 0) && (*(char *)_Buf == '\x1a')) {
          return 0;
        }
        _DAT_00437ae4 = 0x1c;
        DAT_00437ae8 = 0;
        return -1;
      }
      if (local_418 != 5) {
        __dosmaperr(local_418);
        return -1;
      }
      _DAT_00437ae4 = 9;
      DAT_00437ae8 = local_418;
      return -1;
    }
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


