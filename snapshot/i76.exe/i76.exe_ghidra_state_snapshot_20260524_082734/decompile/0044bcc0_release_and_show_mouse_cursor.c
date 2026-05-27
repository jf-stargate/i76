/*
 * Program: i76.exe
 * Function: release_and_show_mouse_cursor
 * Entry: 0044bcc0
 * Signature: undefined __stdcall release_and_show_mouse_cursor(void)
 */


/* i76 first-pass rename
   old_name: FUN_0044bcc0
   suggested_name: release_and_show_mouse_cursor
   basis: Releases cursor clipping and restores/shows mouse cursor. */

void release_and_show_mouse_cursor(void)

{
  bool bVar1;
  undefined3 extraout_var;
  HCURSOR hCursor;
  HWND pHVar2;
  int iVar3;
  tagPOINT local_8;
  
  bVar1 = is_miss16_high_color_resource_mode();
  if (CONCAT31(extraout_var,bVar1) == 1) {
    hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
    SetCursor(hCursor);
  }
  ClipCursor((RECT *)0x0);
  DAT_00535f6c = 0;
  pHVar2 = GetFocus();
  if (pHVar2 == DAT_005dcf7c) {
    GetCursorPos(&local_8);
    ScreenToClient(DAT_005dcf7c,&local_8);
    if (0 < DAT_005dcf30) {
      local_8.y = DAT_005dcf30 / 2;
    }
    ClientToScreen(DAT_005dcf7c,&local_8);
    SetCursorPos(local_8.x,local_8.y);
    iVar3 = ShowCursor(0);
    DAT_00535f74 = iVar3 + 1;
    ShowCursor(1);
  }
  pHVar2 = GetFocus();
  if (pHVar2 == DAT_005dcf7c) {
    GetCursorPos(&local_8);
    ScreenToClient(DAT_005dcf7c,&local_8);
    ClientToScreen(DAT_005dcf7c,&local_8);
    SetCursorPos(local_8.x,local_8.y);
    iVar3 = ShowCursor(0);
    DAT_00535f74 = iVar3 + 1;
    ShowCursor(1);
  }
  iVar3 = ShowCursor(1);
  while (iVar3 < 0) {
    iVar3 = ShowCursor(1);
  }
  return;
}


