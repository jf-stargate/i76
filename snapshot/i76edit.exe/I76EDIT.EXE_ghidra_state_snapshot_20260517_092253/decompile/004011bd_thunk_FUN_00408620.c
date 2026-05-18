/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408620
 * Entry: 004011bd
 * Signature: undefined __stdcall thunk_FUN_00408620(void)
 */


void thunk_FUN_00408620(void)

{
  HDC hdc;
  HDC hdc_00;
  HBITMAP h;
  HGDIOBJ pvVar1;
  HBRUSH pHVar2;
  HPEN h_00;
  HGDIOBJ h_01;
  undefined4 *puVar3;
  undefined4 *puVar4;
  tagRECT tStack_10;
  
  SetRect(&tStack_10,0,0,0x80,0x80);
  hdc = GetDC(DAT_01641fb4);
  hdc_00 = CreateCompatibleDC(hdc);
  puVar3 = &DAT_01642100;
  do {
    puVar4 = puVar3 + 1;
    h = CreateCompatibleBitmap(hdc,0x80,0x80);
    *puVar3 = h;
    pvVar1 = SelectObject(hdc_00,h);
    pHVar2 = GetStockObject(0);
    FillRect(hdc_00,&tStack_10,pHVar2);
    SelectObject(hdc_00,pvVar1);
    puVar3 = puVar4;
  } while (puVar4 < &DAT_01642240);
  DAT_016423a8 = CreateCompatibleBitmap(hdc,0x80,0x80);
  pvVar1 = SelectObject(hdc_00,DAT_016423a8);
  pHVar2 = GetStockObject(0);
  FillRect(hdc_00,&tStack_10,pHVar2);
  h_00 = CreatePen(0,1,0xff00ff);
  h_01 = SelectObject(hdc_00,h_00);
  MoveToEx(hdc_00,0,0,(LPPOINT)0x0);
  LineTo(hdc_00,0,0x7f);
  LineTo(hdc_00,0x7f,0x7f);
  LineTo(hdc_00,0x7f,0);
  LineTo(hdc_00,0,0);
  SelectObject(hdc_00,h_01);
  SelectObject(hdc_00,pvVar1);
  DeleteObject(h_00);
  DeleteDC(hdc_00);
  ReleaseDC(DAT_01641fb4,hdc);
  return;
}


