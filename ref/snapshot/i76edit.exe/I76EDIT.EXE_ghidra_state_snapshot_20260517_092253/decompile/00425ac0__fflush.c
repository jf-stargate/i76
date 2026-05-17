/*
 * Program: I76EDIT.EXE
 * Function: _fflush
 * Entry: 00425ac0
 * Signature: int __cdecl _fflush(FILE * _File)
 */


/* Library Function - Single Match
    _fflush
   
   Library: Visual Studio 1998 Release */

int __cdecl _fflush(FILE *_File)

{
  int iVar1;
  
  if (_File == (FILE *)0x0) {
    iVar1 = flsall(0);
    return iVar1;
  }
  iVar1 = __flush(_File);
  if (iVar1 != 0) {
    return -1;
  }
  if ((_File->_flag & 0x4000) != 0) {
    iVar1 = __commit(_File->_file);
    return (iVar1 == 0) - 1;
  }
  return 0;
}


