/*
 * Program: i76.exe
 * Function: init_directdraw
 * Entry: 00432900
 * Signature: undefined4 __cdecl init_directdraw(byte param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00432900
   suggested_name: init_directdraw
   basis: Calls DirectDrawEnumerateA/DirectDrawCreate; captures system palette; stores DirectDraw
   object globally. */

undefined4 __cdecl init_directdraw(byte param_1)

{
  HDC hdc;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_4;
  
  local_4 = 0;
  if ((param_1 & 4) == 0) {
    DAT_005fdc0c = DirectDrawEnumerateA(&LAB_00432850,&local_4);
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_DirectDrawEnumerate_failed___s_004f0d48);
      return 0;
    }
    DAT_005fdc0c = 0;
  }
  iVar1 = local_4;
  if (local_4 == 0) {
    DAT_006080bc = 1;
    DAT_005fdc0c = DirectDrawCreate(0,&DAT_006080b8,0);
    iVar1 = DAT_006080b8;
    if (DAT_005fdc0c != 0) {
      directdraw_error_to_string(DAT_005fdc0c);
      set_directdraw_error_message(s_DirectDrawCreate_failed___s_004f0d2c);
      return 0;
    }
  }
  DAT_006080b8 = iVar1;
  hdc = GetDC((HWND)0x0);
  GetSystemPaletteEntries(hdc,0,0x100,(LPPALETTEENTRY)&DAT_005fd100);
  puVar2 = &DAT_005fd100;
  puVar3 = &DAT_005fd520;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  ReleaseDC((HWND)0x0,hdc);
  return 1;
}


