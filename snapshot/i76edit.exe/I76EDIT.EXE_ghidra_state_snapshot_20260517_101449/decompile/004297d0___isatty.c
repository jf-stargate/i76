/*
 * Program: I76EDIT.EXE
 * Function: __isatty
 * Entry: 004297d0
 * Signature: int __cdecl __isatty(int _FileHandle)
 */


/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 1998 Release */

int __cdecl __isatty(int _FileHandle)

{
  if (DAT_016424ec <= (uint)_FileHandle) {
    return 0;
  }
  return *(byte *)(*(int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3)) + 4 +
                  (_FileHandle & 0x1fU) * 8) & 0x40;
}


