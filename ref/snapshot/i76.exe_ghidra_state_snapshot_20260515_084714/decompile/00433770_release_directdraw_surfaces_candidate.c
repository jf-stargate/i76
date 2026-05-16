/*
 * Program: i76.exe
 * Function: release_directdraw_surfaces_candidate
 * Entry: 00433770
 * Signature: undefined4 __stdcall release_directdraw_surfaces_candidate(void)
 */


undefined4 release_directdraw_surfaces_candidate(void)

{
  undefined4 uVar1;
  
  if ((DAT_005fdc00 != (code *)0x0) && (DAT_005fcef0 != 0)) {
    DAT_005fcef0 = DAT_005fcef0 + -1;
    uVar1 = (*DAT_005fdc00)(0);
    return uVar1;
  }
  return 1;
}


