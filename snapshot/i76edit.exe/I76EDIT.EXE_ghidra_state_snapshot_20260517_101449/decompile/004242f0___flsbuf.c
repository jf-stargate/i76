/*
 * Program: I76EDIT.EXE
 * Function: __flsbuf
 * Entry: 004242f0
 * Signature: int __cdecl __flsbuf(int _Ch, FILE * _File)
 */


/* Library Function - Single Match
    __flsbuf
   
   Library: Visual Studio 1998 Release */

int __cdecl __flsbuf(int _Ch,FILE *_File)

{
  uint _FileHandle;
  FILE *_File_00;
  int iVar1;
  undefined *puVar2;
  uint uVar3;
  uint uVar4;
  
  _File_00 = _File;
  _FileHandle = _File->_file;
  uVar3 = _File->_flag;
  if (((uVar3 & 0x82) == 0) || ((uVar3 & 0x40) != 0)) {
    _File->_flag = uVar3 | 0x20;
    return -1;
  }
  if ((uVar3 & 1) != 0) {
    _File->_cnt = 0;
    if ((_File->_flag & 0x10U) == 0) {
      _File->_flag = _File->_flag | 0x20;
      return -1;
    }
    _File->_ptr = _File->_base;
    _File->_flag = _File->_flag & 0xfffffffe;
  }
  uVar3 = _File->_flag;
  uVar4 = 0;
  _File->_flag = uVar3 | 2;
  _File->_flag = uVar3 & 0xffffffef | 2;
  _File->_cnt = 0;
  if ((_File->_flag & 0x10cU) == 0) {
    if ((_File == (FILE *)&DAT_00437bd0) || (_File == (FILE *)&DAT_00437bf0)) {
      iVar1 = __isatty(_FileHandle);
      if (iVar1 != 0) goto LAB_00424374;
    }
    __getbuf(_File_00);
  }
LAB_00424374:
  if ((_File_00->_flag & 0x108U) == 0) {
    uVar3 = 1;
    uVar4 = __write(_FileHandle,&_Ch,1);
  }
  else {
    uVar3 = (int)_File_00->_ptr - (int)_File_00->_base;
    _File_00->_ptr = _File_00->_base + 1;
    _File_00->_cnt = _File_00->_bufsiz + -1;
    if ((int)uVar3 < 1) {
      puVar2 = &DAT_00438df0;
      if (_FileHandle != 0xffffffff) {
        puVar2 = (undefined *)
                 (*(int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7) >> 3)) +
                 (_FileHandle & 0x1f) * 8);
      }
      if ((puVar2[4] & 0x20) != 0) {
        __lseek(_FileHandle,0,2);
      }
    }
    else {
      uVar4 = __write(_FileHandle,_File_00->_base,uVar3);
    }
    *_File_00->_base = (char)_Ch;
  }
  if (uVar4 != uVar3) {
    _File_00->_flag = _File_00->_flag | 0x20;
    return -1;
  }
  return _Ch & 0xff;
}


