/*
 * Program: I76EDIT.EXE
 * Function: __amsg_exit
 * Entry: 004242c0
 * Signature: void __cdecl __amsg_exit(int param_1)
 */


/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Release */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_00437e40 == 1) {
    __FF_MSGBANNER();
  }
  __NMSG_WRITE(param_1);
  (*(code *)PTR___exit_00437e3c)(0xff);
  return;
}


