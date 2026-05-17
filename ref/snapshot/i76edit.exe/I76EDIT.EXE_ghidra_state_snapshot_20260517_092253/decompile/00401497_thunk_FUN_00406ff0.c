/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00406ff0
 * Entry: 00401497
 * Signature: HWND __stdcall thunk_FUN_00406ff0(void)
 */


HWND thunk_FUN_00406ff0(void)

{
  int nHeight;
  int nWidth;
  HCURSOR hCursor;
  HWND pHVar1;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  WNDCLASSA WStack_28;
  
  if (DAT_004346b0 == 0) {
    WStack_28.cbClsExtra = 0;
    WStack_28.cbWndExtra = 0;
    WStack_28.hInstance = DAT_016423a4;
    DAT_004346b0 = 1;
    WStack_28.style = 0x1003;
    WStack_28.lpfnWndProc = (WNDPROC)&LAB_0040146a;
    WStack_28.hIcon = LoadIconA(DAT_016423a4,(LPCSTR)0x66);
    WStack_28.hCursor = (HCURSOR)0x0;
    WStack_28.hbrBackground = GetStockObject(1);
    WStack_28.lpszMenuName = (LPCSTR)0x0;
    WStack_28.lpszClassName = s_Interstate__76_Editor_rel_3_06_v_00434034;
    RegisterClassA(&WStack_28);
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  pHVar1 = (HWND)0x0;
  hInstance = DAT_016423a4;
  nHeight = GetSystemMetrics(1);
  nWidth = GetSystemMetrics(0);
  pHVar1 = CreateWindowExA(0x100,s_Interstate__76_Editor_rel_3_06_v_00434034,
                           s_Interstate__76_Editor_rel_3_06_v_00434034,0xca0000,0,0,nWidth,nHeight,
                           pHVar1,hMenu,hInstance,lpParam);
  if (pHVar1 == (HWND)0x0) {
    return (HWND)0x0;
  }
  DAT_01641ed0 = LoadMenuA(DAT_016423a4,(LPCSTR)0x67);
  SetMenu(pHVar1,DAT_01641ed0);
  thunk_FUN_0041e510();
  hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  SetCursor(hCursor);
  ShowWindow(pHVar1,10);
  UpdateWindow(pHVar1);
  return pHVar1;
}


