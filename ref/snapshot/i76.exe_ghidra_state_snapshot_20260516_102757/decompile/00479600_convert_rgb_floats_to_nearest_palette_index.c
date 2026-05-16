/*
 * Program: i76.exe
 * Function: convert_rgb_floats_to_nearest_palette_index
 * Entry: 00479600
 * Signature: undefined1 __stdcall convert_rgb_floats_to_nearest_palette_index(void)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Converts three RGB-like float values
   to clamped bytes and resolves a nearest palette/cube index. */

undefined1 convert_rgb_floats_to_nearest_palette_index(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = ftol();
  iVar3 = ftol();
  iVar4 = ftol();
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  else if (0xff < iVar2) {
    iVar2 = 0xff;
  }
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  else if (0xff < iVar3) {
    iVar3 = 0xff;
  }
  if (iVar4 < 0) {
    uVar1 = cache_nearest_palette_cube_index(iVar2,iVar3,0);
    return uVar1;
  }
  if (0xff < iVar4) {
    iVar4 = 0xff;
  }
  uVar1 = cache_nearest_palette_cube_index(iVar2,iVar3,iVar4);
  return uVar1;
}


