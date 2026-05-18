/*
 * Program: I76EDIT.EXE
 * Function: _exit
 * Entry: 004233c0
 * Signature: noreturn void __cdecl _exit(int _Code)
 */


/* Library Function - Single Match
    _exit
   
   Library: Visual Studio 1998 Release */

void __cdecl _exit(int _Code)

{
  doexit(_Code,0,0);
  return;
}


