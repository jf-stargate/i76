/*
 * Program: I76EDIT.EXE
 * Function: __makepath
 * Entry: 00423980
 * Signature: void __cdecl __makepath(char * _Path, char * _Drive, char * _Dir, char * _Filename, char * _Ext)
 */


/* Library Function - Single Match
    __makepath
   
   Library: Visual Studio 1998 Release */

void __cdecl __makepath(char *_Path,char *_Drive,char *_Dir,char *_Filename,char *_Ext)

{
  uchar uVar1;
  uchar *puVar2;
  uchar *puVar3;
  
  if ((_Drive != (char *)0x0) && (*_Drive != '\0')) {
    *_Path = *_Drive;
    _Path[1] = ':';
    _Path = _Path + 2;
  }
  if ((_Dir != (char *)0x0) && (puVar2 = (uchar *)_Dir, *_Dir != '\0')) {
    do {
      puVar3 = (uchar *)_Path;
      uVar1 = *puVar2;
      puVar2 = puVar2 + 1;
      *puVar3 = uVar1;
      _Path = (char *)(puVar3 + 1);
    } while (*puVar2 != '\0');
    puVar2 = __mbsdec((uchar *)_Dir,puVar2);
    if ((*puVar2 != '/') && (*puVar2 != '\\')) {
      *_Path = '\\';
      _Path = (char *)(puVar3 + 2);
    }
  }
  if (_Filename != (char *)0x0) {
    uVar1 = *_Filename;
    while (uVar1 != '\0') {
      uVar1 = *_Filename;
      _Filename = _Filename + 1;
      *_Path = uVar1;
      _Path = _Path + 1;
      uVar1 = *_Filename;
    }
  }
  if (_Ext == (char *)0x0) {
    *_Path = '\0';
  }
  else {
    if ((*_Ext != '\0') && (*_Ext != '.')) {
      *_Path = '.';
      _Path = _Path + 1;
    }
    uVar1 = *_Ext;
    *_Path = uVar1;
    if (uVar1 != '\0') {
      do {
        _Path = _Path + 1;
        _Ext = _Ext + 1;
        uVar1 = *_Ext;
        *_Path = uVar1;
      } while (uVar1 != '\0');
      return;
    }
  }
  return;
}


