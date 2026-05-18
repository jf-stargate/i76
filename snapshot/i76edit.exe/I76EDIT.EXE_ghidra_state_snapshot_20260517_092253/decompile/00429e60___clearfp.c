/*
 * Program: I76EDIT.EXE
 * Function: __clearfp
 * Entry: 00429e60
 * Signature: uint __cdecl __clearfp(void)
 */


/* Library Function - Single Match
    __clearfp
   
   Library: Visual Studio 1998 Release */

uint __cdecl __clearfp(void)

{
  uint uVar1;
  ushort in_FPUStatusWord;
  
  uVar1 = __abstract_sw(in_FPUStatusWord);
  return uVar1;
}


