/*
 * Program: I76EDIT.EXE
 * Function: __ltoa
 * Entry: 0042d5f0
 * Signature: char * __cdecl __ltoa(long _Value, char * _Dest, int _Radix)
 */


/* Library Function - Single Match
    __ltoa
   
   Library: Visual Studio 1998 Release */

char * __cdecl __ltoa(long _Value,char *_Dest,int _Radix)

{
  int iVar1;
  
  if ((_Radix == 10) && (_Value < 0)) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  xtoa(_Value,_Dest,_Radix,iVar1);
  return _Dest;
}


