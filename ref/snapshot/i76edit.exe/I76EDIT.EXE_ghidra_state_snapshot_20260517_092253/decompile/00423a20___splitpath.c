/*
 * Program: I76EDIT.EXE
 * Function: __splitpath
 * Entry: 00423a20
 * Signature: void __cdecl __splitpath(char * _FullPath, char * _Drive, char * _Dir, char * _Filename, char * _Ext)
 */


/* Library Function - Single Match
    __splitpath
   
   Library: Visual Studio 1998 Release */

void __cdecl __splitpath(char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext)

{
  byte bVar1;
  byte *_Source;
  size_t sVar2;
  byte *pbVar3;
  byte *local_4;
  
  local_4 = (byte *)0x0;
  if (_FullPath[1] == ':') {
    if (_Drive != (char *)0x0) {
      __mbsnbcpy((uchar *)_Drive,(uchar *)_FullPath,2);
      _Drive[2] = '\0';
    }
    _FullPath = _FullPath + 2;
  }
  else if (_Drive != (char *)0x0) {
    *_Drive = '\0';
  }
  _Source = (byte *)0x0;
  bVar1 = *_FullPath;
  pbVar3 = (byte *)_FullPath;
  while (bVar1 != 0) {
    bVar1 = *pbVar3;
    if ((*(byte *)((int)&DAT_00438a70 + bVar1 + 1) & 4) == 0) {
      if ((bVar1 == 0x2f) || (bVar1 == 0x5c)) {
        _Source = pbVar3 + 1;
      }
      else if (bVar1 == 0x2e) {
        local_4 = pbVar3;
      }
    }
    else {
      pbVar3 = pbVar3 + 1;
    }
    pbVar3 = pbVar3 + 1;
    bVar1 = *pbVar3;
  }
  if (_Source == (byte *)0x0) {
    _Source = (byte *)_FullPath;
    if (_Dir != (char *)0x0) {
      *_Dir = '\0';
    }
  }
  else if (_Dir != (char *)0x0) {
    sVar2 = (int)_Source - (int)_FullPath;
    if (0xfe < sVar2) {
      sVar2 = 0xff;
    }
    __mbsnbcpy((uchar *)_Dir,(uchar *)_FullPath,sVar2);
    _Dir[sVar2] = '\0';
  }
  if ((local_4 == (byte *)0x0) || (local_4 < _Source)) {
    if (_Filename != (char *)0x0) {
      sVar2 = (int)pbVar3 - (int)_Source;
      if (0xfe < sVar2) {
        sVar2 = 0xff;
      }
      __mbsnbcpy((uchar *)_Filename,_Source,sVar2);
      _Filename[sVar2] = '\0';
    }
    if (_Ext != (char *)0x0) {
      *_Ext = '\0';
    }
  }
  else {
    if (_Filename != (char *)0x0) {
      sVar2 = (int)local_4 - (int)_Source;
      if (0xfe < sVar2) {
        sVar2 = 0xff;
      }
      __mbsnbcpy((uchar *)_Filename,_Source,sVar2);
      _Filename[sVar2] = '\0';
    }
    if (_Ext != (char *)0x0) {
      sVar2 = (int)pbVar3 - (int)local_4;
      if (0xfe < sVar2) {
        sVar2 = 0xff;
      }
      __mbsnbcpy((uchar *)_Ext,local_4,sVar2);
      _Ext[sVar2] = '\0';
      return;
    }
  }
  return;
}


