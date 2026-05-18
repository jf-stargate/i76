/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00407360
 * Entry: 0040118b
 * Signature: undefined __cdecl thunk_FUN_00407360(HWND param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00407360(HWND param_1)

{
  WNDCLASSA WStack_28;
  
  WStack_28.style = 0x1800;
  WStack_28.hInstance = DAT_016423a4;
  WStack_28.cbClsExtra = 0;
  WStack_28.cbWndExtra = 0;
  WStack_28.hIcon = (HICON)0x0;
  WStack_28.hCursor = (HCURSOR)0x0;
  WStack_28.hbrBackground = GetStockObject(1);
  WStack_28.lpszMenuName = (LPCSTR)0x0;
  WStack_28.lpfnWndProc = (WNDPROC)&DAT_004010d7;
  WStack_28.lpszClassName = s_ElevationToolbox_00434700;
  RegisterClassA(&WStack_28);
  FUN_004074b0(param_1);
  FUN_00407890(param_1);
  FUN_00408110(param_1);
  FUN_00408290(param_1);
  FUN_004084c0(param_1);
  FUN_00407c70(param_1);
  FUN_00407df0(param_1);
  FUN_004079f0(param_1);
  _DAT_016423a0 = 0;
  FlashWindow(DAT_01642384,1);
  FlashWindow(DAT_01642388,1);
  FlashWindow(DAT_01642390,1);
  FlashWindow(DAT_01642394,1);
  FlashWindow(DAT_01642398,1);
  FlashWindow(DAT_0164239c,1);
  FlashWindow(DAT_01642388,1);
  ShowWindow(DAT_01642380,1);
  return;
}


