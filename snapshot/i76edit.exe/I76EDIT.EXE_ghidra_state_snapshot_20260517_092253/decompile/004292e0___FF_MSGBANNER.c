/*
 * Program: I76EDIT.EXE
 * Function: __FF_MSGBANNER
 * Entry: 004292e0
 * Signature: void __cdecl __FF_MSGBANNER(void)
 */


/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 1998 Release */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_00437e40 == 1) || ((DAT_00437e40 == 0 && (DAT_00437e44 == 1)))) {
    __NMSG_WRITE(0xfc);
    if (DAT_00438f30 != (code *)0x0) {
      (*DAT_00438f30)();
    }
    __NMSG_WRITE(0xff);
  }
  return;
}


