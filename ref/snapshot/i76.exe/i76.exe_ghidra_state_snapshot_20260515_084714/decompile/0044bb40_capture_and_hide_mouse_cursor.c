/*
 * Program: i76.exe
 * Function: capture_and_hide_mouse_cursor
 * Entry: 0044bb40
 * Signature: undefined __stdcall capture_and_hide_mouse_cursor(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0044bb40
   suggested_name: capture_and_hide_mouse_cursor
   basis: Gets client rect/cursor position, clips cursor, recenters/hides mouse. */

void capture_and_hide_mouse_cursor(void)

{
  HWND pHVar1;
  int iVar2;
  uint uVar3;
  tagPOINT local_8;
  
  if (DAT_005dcf7c == (HWND)0x0) {
    _DAT_00609300 = 0;
    _DAT_00609304 = 0;
    _DAT_00609308 = 0;
    _DAT_0060930c = 0;
  }
  else {
    local_8.y = 0;
    local_8.x = 0;
    ClientToScreen(DAT_005dcf7c,&local_8);
    _DAT_00609300 = local_8.x;
    _DAT_00609304 = local_8.y;
    local_8.y = DAT_005dcf30 + -1;
    local_8.x = DAT_005dcf2c + -1;
    ClientToScreen(DAT_005dcf7c,&local_8);
    _DAT_00609308 = local_8.x;
    _DAT_0060930c = local_8.y;
  }
  pHVar1 = GetFocus();
  if (pHVar1 == DAT_005dcf7c) {
    GetCursorPos(&local_8);
    ScreenToClient(DAT_005dcf7c,&local_8);
    if (0 < DAT_005dcf30) {
      local_8.y = DAT_005dcf30 / 2;
    }
    ClientToScreen(DAT_005dcf7c,&local_8);
    SetCursorPos(local_8.x,local_8.y);
    iVar2 = ShowCursor(0);
    DAT_00535f74 = iVar2 + 1;
    ShowCursor(1);
  }
  pHVar1 = GetFocus();
  if (pHVar1 == DAT_005dcf7c) {
    GetCursorPos(&local_8);
    ScreenToClient(DAT_005dcf7c,&local_8);
    ClientToScreen(DAT_005dcf7c,&local_8);
    SetCursorPos(local_8.x,local_8.y);
    iVar2 = ShowCursor(0);
    DAT_00535f74 = iVar2 + 1;
    ShowCursor(1);
  }
  DAT_00535f6c = 1;
  iVar2 = ShowCursor(0);
  if (-1 < iVar2) {
    do {
      uVar3 = ShowCursor(0);
    } while (uVar3 < 0x80000000);
  }
  return;
}


