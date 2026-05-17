/*
 * Program: I76EDIT.EXE
 * Function: __stbuf
 * Entry: 00427b70
 * Signature: int __cdecl __stbuf(FILE * _File)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __stbuf
   
   Library: Visual Studio 1998 Release */

int __cdecl __stbuf(FILE *_File)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  void *pvVar4;
  
  iVar3 = __isatty(_File->_file);
  if (iVar3 == 0) {
    return 0;
  }
  if (_File == (FILE *)&DAT_00437bd0) {
    iVar3 = 0;
  }
  else {
    if (_File != (FILE *)&DAT_00437bf0) {
      return 0;
    }
    iVar3 = 1;
  }
  _DAT_00437e30 = _DAT_00437e30 + 1;
  if ((_File->_flag & 0x10cU) != 0) {
    return 0;
  }
  piVar1 = &DAT_00438a68 + iVar3;
  if (*piVar1 == 0) {
    pvVar4 = _malloc(0x1000);
    *piVar1 = (int)pvVar4;
    if (pvVar4 == (void *)0x0) {
      return 0;
    }
  }
  pcVar2 = (char *)*piVar1;
  _File->_base = pcVar2;
  _File->_ptr = pcVar2;
  _File->_bufsiz = 0x1000;
  _File->_cnt = 0x1000;
  _File->_flag = _File->_flag | 0x1102;
  return 1;
}


