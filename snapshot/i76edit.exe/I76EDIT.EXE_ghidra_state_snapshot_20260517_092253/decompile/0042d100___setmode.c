/*
 * Program: I76EDIT.EXE
 * Function: __setmode
 * Entry: 0042d100
 * Signature: int __cdecl __setmode(int _FileHandle, int _Mode)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setmode
   
   Library: Visual Studio 1998 Release */

int __cdecl __setmode(int _FileHandle,int _Mode)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  
  if ((uint)_FileHandle < DAT_016424ec) {
    pbVar1 = (byte *)(*(int *)((int)&DAT_016423b0 + ((int)(_FileHandle & 0xffffffe7U) >> 3)) + 4 +
                     (_FileHandle & 0x1fU) * 8);
    bVar2 = *pbVar1;
    if ((bVar2 & 1) != 0) {
      if (_Mode == 0x8000) {
        bVar3 = bVar2 & 0x7f;
      }
      else {
        if (_Mode != 0x4000) {
          _DAT_00437ae4 = 0x16;
          return -1;
        }
        bVar3 = bVar2 | 0x80;
      }
      *pbVar1 = bVar3;
      return (-(uint)((bVar2 & 0x80) == 0) & 0x4000) + 0x4000;
    }
  }
  _DAT_00437ae4 = 9;
  return -1;
}


