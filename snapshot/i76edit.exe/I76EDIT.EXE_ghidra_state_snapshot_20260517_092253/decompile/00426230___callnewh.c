/*
 * Program: I76EDIT.EXE
 * Function: __callnewh
 * Entry: 00426230
 * Signature: int __cdecl __callnewh(size_t _Size)
 */


/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 1998 Release */

int __cdecl __callnewh(size_t _Size)

{
  int iVar1;
  
  if (DAT_0043c158 != (code *)0x0) {
    iVar1 = (*DAT_0043c158)(_Size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}


