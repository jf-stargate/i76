/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040d580
 * Entry: 0040104b
 * Signature: undefined __stdcall thunk_FUN_0040d580(void)
 */


void thunk_FUN_0040d580(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_004347d0;
  iVar2 = DAT_004347cc;
  if ((DAT_004347cc != -1) && (DAT_004347d0 != -1)) {
    DAT_004347cc = -1;
    DAT_004347d0 = -1;
    iVar1 = iVar1 + iVar2 * 0x32;
    iVar2 = iVar1 * 4;
    (&DAT_0163ce72)[iVar1 * 2] = 0xffff;
    (&DAT_0163ce70)[iVar2] = 0xff;
    (&DAT_0163ce71)[iVar2] = 0xff;
  }
  return;
}


