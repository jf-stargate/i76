/*
 * Program: I76EDIT.EXE
 * Function: _fclose
 * Entry: 00422ff0
 * Signature: int __cdecl _fclose(FILE * _File)
 */


/* Library Function - Single Match
    _fclose
   
   Library: Visual Studio 1998 Release */

int __cdecl _fclose(FILE *_File)

{
  int iVar1;
  int iVar2;
  
  iVar2 = -1;
  if ((_File->_flag & 0x40U) != 0) {
    _File->_flag = 0;
    return -1;
  }
  if ((_File->_flag & 0x83U) != 0) {
    iVar2 = __flush(_File);
    __freebuf(_File);
    iVar1 = __close(_File->_file);
    if (iVar1 < 0) {
      iVar2 = -1;
    }
    else if (_File->_tmpfname != (char *)0x0) {
      _free(_File->_tmpfname);
      _File->_tmpfname = (char *)0x0;
    }
  }
  _File->_flag = 0;
  return iVar2;
}


