/*
 * Program: I76EDIT.EXE
 * Function: _rand
 * Entry: 00423850
 * Signature: int __cdecl _rand(void)
 */


/* Library Function - Single Match
    _rand
   
   Library: Visual Studio 1998 Release */

int __cdecl _rand(void)

{
  DAT_00437ba0 = DAT_00437ba0 * 0x343fd + 0x269ec3;
  return (DAT_00437ba0 & 0x7fff0000) >> 0x10;
}


