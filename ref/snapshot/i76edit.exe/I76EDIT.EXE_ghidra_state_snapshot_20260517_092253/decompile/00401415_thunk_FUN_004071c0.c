/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004071c0
 * Entry: 00401415
 * Signature: undefined __cdecl thunk_FUN_004071c0(HWND param_1)
 */


void __cdecl thunk_FUN_004071c0(HWND param_1)

{
  int iVar1;
  int iVar2;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  WNDCLASSA WStack_38;
  tagRECT tStack_10;
  
  if (DAT_004346b4 == 0) {
    WStack_38.cbClsExtra = 0;
    WStack_38.cbWndExtra = 0;
    WStack_38.hIcon = (HICON)0x0;
    WStack_38.hInstance = DAT_016423a4;
    WStack_38.hCursor = (HCURSOR)0x0;
    DAT_004346b4 = 1;
    WStack_38.style = 0x1003;
    WStack_38.lpfnWndProc = (WNDPROC)&LAB_004014dd;
    WStack_38.hbrBackground = GetStockObject(0);
    WStack_38.lpszMenuName = (LPCSTR)0x0;
    WStack_38.lpszClassName = s_ChildWnd_004346f4;
    RegisterClassA(&WStack_38);
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = DAT_016423a4;
  iVar1 = GetSystemMetrics(1);
  iVar1 = iVar1 + -0x5a;
  iVar2 = GetSystemMetrics(0);
  DAT_01641fb4 = CreateWindowExA(0x200,s_ChildWnd_004346f4,s_ChildWnd_004346f4,0x40300000,0,0x1b,
                                 iVar2 + -6,iVar1,param_1,hMenu,hInstance,lpParam);
  ShowWindow(DAT_01641fb4,5);
  UpdateWindow(DAT_01641fb4);
  GetClientRect(DAT_01641fb4,&tStack_10);
  SetScrollRange(DAT_01641fb4,1,0,0x2800 - tStack_10.bottom,0);
  SetScrollRange(DAT_01641fb4,0,0,0x2800 - tStack_10.right,0);
  SetScrollPos(DAT_01641fb4,1,DAT_00433a40,1);
  SetScrollPos(DAT_01641fb4,0,DAT_00433a3c,1);
  return;
}


