/*
 * Program: I76EDIT.EXE
 * Function: __ismbblead
 * Entry: 00428a50
 * Signature: int __cdecl __ismbblead(uint _C)
 */


/* Library Function - Single Match
    __ismbblead
   
   Library: Visual Studio 1998 Release */

int __cdecl __ismbblead(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype((byte)_C,0,4);
  return iVar1;
}


