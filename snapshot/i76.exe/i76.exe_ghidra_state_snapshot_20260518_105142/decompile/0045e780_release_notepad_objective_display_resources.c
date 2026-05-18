/*
 * Program: i76.exe
 * Function: release_notepad_objective_display_resources
 * Entry: 0045e780
 * Signature: undefined __stdcall release_notepad_objective_display_resources(void)
 */


/* cgpt rename v2: Releases notepad/objective display bitmap surfaces, HDC, font/brush objects, and
   heap buffer. */

void release_notepad_objective_display_resources(void)

{
  HGDIOBJ pvVar1;
  int iVar2;
  undefined4 *puVar3;
  
  release_bitmap_surface_context(&DAT_00609478);
  release_bitmap_surface_context(&DAT_00609444);
  if (DAT_006094dc != (HDC)0x0) {
    pvVar1 = GetStockObject(0xd);
    SelectObject(DAT_006094dc,pvVar1);
    pvVar1 = GetStockObject(5);
    SelectObject(DAT_006094dc,pvVar1);
    DeleteDC(DAT_006094dc);
  }
  if (DAT_006094ac != (LPVOID)0x0) {
    xfree_global_heap(DAT_006094ac);
  }
  if (DAT_006094c0 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_006094c0);
  }
  if (DAT_006094e0 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_006094e0);
  }
  puVar3 = &DAT_00609440;
  for (iVar2 = 0x29; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return;
}


