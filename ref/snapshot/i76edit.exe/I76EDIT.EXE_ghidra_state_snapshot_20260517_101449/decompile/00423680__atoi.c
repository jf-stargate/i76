/*
 * Program: I76EDIT.EXE
 * Function: _atoi
 * Entry: 00423680
 * Signature: int __cdecl _atoi(char * _Str)
 */


/* Library Function - Single Match
    _atoi
   
   Library: Visual Studio 1998 Release */

int __cdecl _atoi(char *_Str)

{
  long lVar1;
  
  lVar1 = _atol(_Str);
  return lVar1;
}


