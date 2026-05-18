/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e990
 * Entry: 004010aa
 * Signature: undefined __stdcall thunk_FUN_0041e990(void)
 */


void thunk_FUN_0041e990(void)

{
  HDC hdc;
  HDC hdc_00;
  HGDIOBJ h;
  HBRUSH hbr;
  undefined4 *puVar1;
  undefined4 *puVar2;
  RECT RStack_10;
  
  hdc = GetDC(DAT_01641fb4);
  hdc_00 = CreateCompatibleDC(hdc);
  SelectObject(hdc_00,DAT_01642100);
  puVar1 = &DAT_01642100;
  do {
    puVar2 = puVar1 + 1;
    SelectObject(hdc_00,(HGDIOBJ)*puVar1);
    h = SelectObject(hdc_00,(HGDIOBJ)*puVar1);
    hbr = GetStockObject(0);
    FillRect(hdc_00,&RStack_10,hbr);
    puVar1 = puVar2;
  } while (puVar2 < &DAT_01642240);
  SelectObject(hdc_00,h);
  DeleteDC(hdc_00);
  ReleaseDC(DAT_01641fb4,hdc);
  InvalidateRgn(DAT_01641fb4,(HRGN)0x0,1);
  return;
}


