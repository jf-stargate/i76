/*
 * Program: I76EDIT.EXE
 * Function: _fread
 * Entry: 00423140
 * Signature: size_t __cdecl _fread(void * _DstBuf, size_t _ElementSize, size_t _Count, FILE * _File)
 */


/* Library Function - Single Match
    _fread
   
   Library: Visual Studio 1998 Release */

size_t __cdecl _fread(void *_DstBuf,size_t _ElementSize,size_t _Count,FILE *_File)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  uint local_4;
  
  uVar1 = _Count * _ElementSize;
  if (uVar1 == 0) {
    return 0;
  }
  uVar5 = uVar1;
  if ((_File->_flag & 0x10cU) == 0) {
    local_4 = 0x1000;
  }
  else {
    local_4 = _File->_bufsiz;
  }
  while( true ) {
    while( true ) {
      while( true ) {
        if (uVar5 == 0) {
          return _Count;
        }
        if (((_File->_flag & 0x10cU) == 0) || (uVar3 = _File->_cnt, uVar3 == 0)) break;
        uVar4 = uVar5;
        if (uVar3 <= uVar5) {
          uVar4 = uVar3;
        }
        uVar5 = uVar5 - uVar4;
        pcVar6 = _File->_ptr;
        pcVar7 = _DstBuf;
        for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar7 = pcVar7 + 4;
        }
        for (uVar3 = uVar4 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
          *pcVar7 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        }
        _File->_cnt = _File->_cnt - uVar4;
        _File->_ptr = _File->_ptr + uVar4;
        _DstBuf = (char *)((int)_DstBuf + uVar4);
      }
      if (local_4 <= uVar5) break;
      iVar2 = __filbuf(_File);
      if (iVar2 == -1) {
        return (uVar1 - uVar5) / _ElementSize;
      }
      uVar5 = uVar5 - 1;
      *(char *)_DstBuf = (char)iVar2;
      local_4 = _File->_bufsiz;
      _DstBuf = (char *)((int)_DstBuf + 1);
    }
    uVar3 = uVar5;
    if (local_4 != 0) {
      uVar3 = uVar5 - uVar5 % local_4;
    }
    iVar2 = __read(_File->_file,_DstBuf,uVar3);
    if (iVar2 == 0) break;
    if (iVar2 == -1) {
      _File->_flag = _File->_flag | 0x20;
      return (uVar1 - uVar5) / _ElementSize;
    }
    uVar5 = uVar5 - iVar2;
    _DstBuf = (char *)((int)_DstBuf + iVar2);
  }
  _File->_flag = _File->_flag | 0x10;
  return (uVar1 - uVar5) / _ElementSize;
}


