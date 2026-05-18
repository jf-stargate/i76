/*
 * Program: I76EDIT.EXE
 * Function: __open
 * Entry: 00429a00
 * Signature: int __cdecl __open(char * _Filename, int _OpenFlag, ...)
 */


/* Library Function - Single Match
    __open
   
   Library: Visual Studio 1998 Release */

int __cdecl __open(char *_Filename,int _OpenFlag,...)

{
  int iVar1;
  undefined4 in_stack_0000000c;
  
  iVar1 = __sopen(_Filename,_OpenFlag,0x40,in_stack_0000000c);
  return iVar1;
}


