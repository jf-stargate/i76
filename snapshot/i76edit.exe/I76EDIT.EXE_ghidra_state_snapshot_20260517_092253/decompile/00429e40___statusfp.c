/*
 * Program: I76EDIT.EXE
 * Function: __statusfp
 * Entry: 00429e40
 * Signature: uint __cdecl __statusfp(void)
 */


/* Library Function - Single Match
    __statusfp
   
   Library: Visual Studio 1998 Release */

uint __cdecl __statusfp(void)

{
  uint uVar1;
  ushort in_FPUStatusWord;
  
  uVar1 = __abstract_sw(in_FPUStatusWord);
  return uVar1;
}


