/*
 * Program: I76EDIT.EXE
 * Function: __get_osfhandle
 * Entry: 004282a0
 * Signature: intptr_t __cdecl __get_osfhandle(int _FileHandle)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __get_osfhandle
   
   Library: Visual Studio 1998 Release */

intptr_t __cdecl __get_osfhandle(int _FileHandle)

{
  intptr_t *piVar1;
  
  if (((uint)_FileHandle < DAT_016424ec) &&
     (piVar1 = (intptr_t *)
               (*(int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3)) +
               (_FileHandle & 0x1fU) * 8), (*(byte *)(piVar1 + 1) & 1) != 0)) {
    return *piVar1;
  }
  _DAT_00437ae4 = 9;
  DAT_00437ae8 = 0;
  return -1;
}


