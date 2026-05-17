/*
 * Program: i76.exe
 * Function: create_dibsection_8bpp_surface_context_with_game_palette
 * Entry: 00476db0
 * Signature: undefined __cdecl create_dibsection_8bpp_surface_context_with_game_palette(int * param_1, HDC param_2, int param_3, uint param_4, undefined4 * param_5)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=high] Creates top-down 8bpp DIBSection
   surface context using game palette triplets at 004fa170. */

void __cdecl
create_dibsection_8bpp_surface_context_with_game_palette
          (int *param_1,HDC param_2,int param_3,uint param_4,undefined4 *param_5)

{
  BYTE *pBVar1;
  BYTE *pBVar2;
  HBITMAP pHVar3;
  int *piVar4;
  int iVar5;
  BYTE *pBVar6;
  BITMAPINFO *pBVar7;
  void *local_460;
  int local_45c [13];
  BITMAPINFO local_428 [24];
  
  pBVar7 = local_428;
  for (iVar5 = 0x10a; iVar5 != 0; iVar5 = iVar5 + -1) {
    (pBVar7->bmiHeader).biSize = 0;
    pBVar7 = (BITMAPINFO *)&(pBVar7->bmiHeader).biWidth;
  }
  local_428[0].bmiHeader.biHeight = -param_4;
  local_428[0].bmiHeader.biWidth = param_3;
  local_428[0].bmiHeader.biSize = 0x28;
  local_428[0].bmiHeader.biPlanes = 1;
  local_428[0].bmiHeader.biBitCount = 8;
  local_428[0].bmiHeader.biCompression = 0;
  pBVar6 = &local_428[0].bmiColors[0].rgbGreen;
  pBVar1 = (BYTE *)((int)&g_game_8bpp_palette_rgb_triplets + 1);
  do {
    pBVar2 = pBVar1 + 3;
    ((RGBQUAD *)(pBVar6 + -1))->rgbBlue = pBVar1[-1];
    *pBVar6 = *pBVar1;
    pBVar6[1] = pBVar1[1];
    pBVar6[2] = '\0';
    pBVar6 = pBVar6 + 4;
    pBVar1 = pBVar2;
  } while ((int)pBVar2 < 0x4fa471);
  pHVar3 = CreateDIBSection(param_2,local_428,0,&local_460,(HANDLE)0x0,0);
  *param_5 = pHVar3;
  if (pHVar3 == (HBITMAP)0x0) {
    piVar4 = local_45c;
    for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    piVar4 = local_45c;
    for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
      *param_1 = *piVar4;
      piVar4 = piVar4 + 1;
      param_1 = param_1 + 1;
    }
    return;
  }
  RealizePalette(param_2);
  piVar4 = (int *)construct_bitmap_surface_context(local_45c,param_3,param_4,(int)local_460,0);
  for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_1 = *piVar4;
    piVar4 = piVar4 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


