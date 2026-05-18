/*
 * Program: I76EDIT.EXE
 * Function: __read
 * Entry: 00425d10
 * Signature: int __cdecl __read(int _FileHandle, void * _DstBuf, uint _MaxCharCount)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __read
   
   Library: Visual Studio 1998 Release */

int __cdecl __read(int _FileHandle,void *_DstBuf,uint _MaxCharCount)

{
  int *piVar1;
  int iVar2;
  byte *pbVar3;
  char cVar4;
  int iVar5;
  BOOL BVar6;
  DWORD DVar7;
  byte bVar8;
  void *lpBuffer;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char local_d;
  DWORD local_c;
  DWORD local_8;
  char *local_4;
  
  if ((uint)_FileHandle < DAT_016424ec) {
    piVar1 = (int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3));
    iVar2 = (_FileHandle & 0x1fU) * 8;
    iVar5 = *piVar1 + iVar2;
    if ((*(byte *)(iVar5 + 4) & 1) != 0) {
      local_c = 0;
      if ((_MaxCharCount == 0) || ((*(byte *)(iVar5 + 4) & 2) != 0)) {
        return 0;
      }
      lpBuffer = _DstBuf;
      if (((*(byte *)(iVar5 + 4) & 0x48) != 0) && (*(char *)(iVar5 + 5) != '\n')) {
        *(char *)_DstBuf = *(char *)(iVar5 + 5);
        lpBuffer = (void *)((int)_DstBuf + 1);
        _MaxCharCount = _MaxCharCount - 1;
        local_c = 1;
        *(undefined1 *)(*piVar1 + 5 + iVar2) = 10;
      }
      BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar2),lpBuffer,_MaxCharCount,&local_8,
                       (LPOVERLAPPED)0x0);
      if (BVar6 == 0) {
        DVar7 = GetLastError();
        if (DVar7 == 5) {
          DAT_00437ae8 = DVar7;
          _DAT_00437ae4 = 9;
          return -1;
        }
        if (DVar7 != 0x6d) {
          __dosmaperr(DVar7);
          return -1;
        }
        return 0;
      }
      local_c = local_c + local_8;
      pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
      bVar8 = *pbVar3;
      if ((bVar8 & 0x80) != 0) {
        if ((local_8 == 0) || (*(char *)_DstBuf != '\n')) {
          bVar8 = bVar8 & 0xfb;
        }
        else {
          bVar8 = bVar8 | 4;
        }
        *pbVar3 = bVar8;
        local_4 = (char *)(local_c + (int)_DstBuf);
        pcVar9 = _DstBuf;
        pcVar11 = _DstBuf;
        if (_DstBuf < local_4) {
          do {
            cVar4 = *pcVar9;
            if (cVar4 == '\x1a') {
              pbVar3 = (byte *)(*piVar1 + 4 + iVar2);
              bVar8 = *pbVar3;
              if ((bVar8 & 0x40) == 0) {
                *pbVar3 = bVar8 | 2;
              }
              break;
            }
            if (cVar4 == '\r') {
              if (pcVar9 < local_4 + -1) {
                pcVar10 = pcVar9 + 1;
                if (*pcVar10 == '\n') {
                  pcVar10 = pcVar9 + 2;
                  *pcVar11 = '\n';
                }
                else {
                  *pcVar11 = '\r';
                }
                goto LAB_00425f14;
              }
              pcVar10 = pcVar9 + 1;
              local_c = 0;
              BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar2),&local_d,1,&local_8,(LPOVERLAPPED)0x0);
              if (BVar6 == 0) {
                local_c = GetLastError();
              }
              if ((local_c != 0) || (local_8 == 0)) {
LAB_00425f11:
                *pcVar11 = '\r';
                goto LAB_00425f14;
              }
              if ((*(byte *)(*piVar1 + 4 + iVar2) & 0x48) == 0) {
                if ((pcVar11 == _DstBuf) && (local_d == '\n')) {
                  *pcVar11 = '\n';
                  goto LAB_00425f14;
                }
                __lseek(_FileHandle,-1,1);
                if (local_d != '\n') goto LAB_00425f11;
              }
              else {
                if (local_d == '\n') {
                  *pcVar11 = '\n';
                  goto LAB_00425f14;
                }
                *pcVar11 = '\r';
                pcVar11 = pcVar11 + 1;
                *(char *)(*piVar1 + 5 + iVar2) = local_d;
              }
            }
            else {
              pcVar10 = pcVar9 + 1;
              *pcVar11 = cVar4;
LAB_00425f14:
              pcVar11 = pcVar11 + 1;
            }
            pcVar9 = pcVar10;
          } while (pcVar10 < local_4);
        }
        local_c = (int)pcVar11 - (int)_DstBuf;
      }
      return local_c;
    }
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


