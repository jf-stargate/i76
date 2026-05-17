/*
 * Program: I76EDIT.EXE
 * Function: __mbsdec
 * Entry: 00427c60
 * Signature: uchar * __cdecl __mbsdec(uchar * _Start, uchar * _Pos)
 */


/* Library Function - Single Match
    __mbsdec
   
   Library: Visual Studio 1998 Release */

uchar * __cdecl __mbsdec(uchar *_Start,uchar *_Pos)

{
  byte *pbVar1;
  
  if (_Pos <= _Start) {
    return (uchar *)0x0;
  }
  if (DAT_00438b74 == 0) {
    return _Pos + -1;
  }
  pbVar1 = _Pos + -1;
  if ((*(byte *)((int)&DAT_00438a70 + *pbVar1 + 1) & 4) != 0) {
    return _Pos + -2;
  }
  do {
    pbVar1 = pbVar1 + -1;
    if (pbVar1 < _Start) break;
  } while ((*(byte *)((int)&DAT_00438a70 + *pbVar1 + 1) & 4) != 0);
  return _Pos + (-1 - ((int)_Pos - (int)pbVar1 & 1U));
}


