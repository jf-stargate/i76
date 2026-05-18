/*
 * Program: I76EDIT.EXE
 * Function: __dosmaperr
 * Entry: 00428030
 * Signature: void __cdecl __dosmaperr(ulong param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __dosmaperr
   
   Library: Visual Studio 1998 Release */

void __cdecl __dosmaperr(ulong param_1)

{
  int iVar1;
  ulong *puVar2;
  
  iVar1 = 0;
  puVar2 = &DAT_00438c88;
  DAT_00437ae8 = param_1;
  do {
    if (*puVar2 == param_1) {
      _DAT_00437ae4 = *(undefined4 *)(iVar1 * 8 + 0x438c8c);
      return;
    }
    puVar2 = puVar2 + 2;
    iVar1 = iVar1 + 1;
  } while (puVar2 < &DAT_00438df0);
  if ((0x12 < param_1) && (param_1 < 0x25)) {
    _DAT_00437ae4 = 0xd;
    return;
  }
  if ((0xbb < param_1) && (param_1 < 0xcb)) {
    _DAT_00437ae4 = 8;
    return;
  }
  _DAT_00437ae4 = 0x16;
  return;
}


