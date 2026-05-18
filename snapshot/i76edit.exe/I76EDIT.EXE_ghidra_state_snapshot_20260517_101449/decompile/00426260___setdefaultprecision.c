/*
 * Program: I76EDIT.EXE
 * Function: __setdefaultprecision
 * Entry: 00426260
 * Signature: undefined __stdcall __setdefaultprecision(void)
 */


/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 1998 Release */

void __setdefaultprecision(void)

{
  __controlfp(0x10000,0x30000);
  return;
}


