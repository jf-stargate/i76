/*
 * Program: I76EDIT.EXE
 * Function: __fltout
 * Entry: 0042a830
 * Signature: undefined * __stdcall __fltout(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fltout
   
   Library: Visual Studio 1998 Release */

undefined * __fltout(void)

{
  uint local_c;
  uint local_8;
  ushort local_4;
  
  ___dtold(&local_c,(uint *)&stack0x00000004);
  _DAT_0043c2b8 = _I10_OUTPUT(local_c,local_8,local_4,0x11,0,&DAT_0043c290);
  _DAT_0043c2bc = &DAT_0043c294;
  _DAT_0043c2b0 = (int)DAT_0043c292;
  _DAT_0043c2b4 = (int)DAT_0043c290;
  return &DAT_0043c2b0;
}


