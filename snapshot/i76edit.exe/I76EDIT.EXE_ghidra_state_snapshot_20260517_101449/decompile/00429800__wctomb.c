/*
 * Program: I76EDIT.EXE
 * Function: _wctomb
 * Entry: 00429800
 * Signature: int __cdecl _wctomb(char * _MbCh, wchar_t _WCh)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _wctomb
   
   Library: Visual Studio 1998 Release */

int __cdecl _wctomb(char *_MbCh,wchar_t _WCh)

{
  int iVar1;
  BOOL local_4;
  
  if (_MbCh == (char *)0x0) {
    return 0;
  }
  if (DAT_00438f90 == 0) {
    if (0xff < (ushort)_WCh) {
      _DAT_00437ae4 = 0x2a;
      return -1;
    }
    *_MbCh = (char)_WCh;
    return 1;
  }
  local_4 = 0;
  iVar1 = WideCharToMultiByte(DAT_00438fa0,0x220,&_WCh,1,_MbCh,DAT_00438a4c,(LPCSTR)0x0,&local_4);
  if ((iVar1 == 0) || (local_4 != 0)) {
    _DAT_00437ae4 = 0x2a;
    iVar1 = -1;
  }
  return iVar1;
}


