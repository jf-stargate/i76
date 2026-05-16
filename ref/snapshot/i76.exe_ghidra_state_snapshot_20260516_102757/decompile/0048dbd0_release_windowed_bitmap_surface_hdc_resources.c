/*
 * Program: i76.exe
 * Function: release_windowed_bitmap_surface_hdc_resources
 * Entry: 0048dbd0
 * Signature: undefined __cdecl release_windowed_bitmap_surface_hdc_resources(int * param_1)
 */


/* cgpt rename v4: Restores selected GDI objects, deletes bitmap/DC resources, releases nested
   bitmap surface context, and clears HDC state. */

void __cdecl release_windowed_bitmap_surface_hdc_resources(int *param_1)

{
  if (param_1[0x38] != 0) {
    if (DAT_0059c1b0 != (HDC)0x0) {
      SelectObject(DAT_0059c1b0,DAT_0059c1b8);
      DeleteObject(DAT_0059c1b4);
      release_bitmap_surface_context(param_1);
      ReleaseDC((HWND)param_1[0x2f],DAT_0059c1b0);
    }
    DAT_0059c1b0 = (HDC)0x0;
    DAT_0059c1b4 = (HGDIOBJ)0x0;
    param_1[0x38] = 0;
    release_bitmap_surface_context(param_1 + 0xd);
  }
  return;
}


