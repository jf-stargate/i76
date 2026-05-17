/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004058a0
 * Entry: 00401082
 * Signature: undefined __cdecl thunk_FUN_004058a0(HWND param_1, int * param_2, int * param_3)
 */


void __cdecl thunk_FUN_004058a0(HWND param_1,int *param_2,int *param_3)

{
  HDC hdc;
  HPEN h;
  HGDIOBJ pvVar1;
  
  hdc = GetDC(param_1);
  SetROP2(hdc,6);
  h = CreatePen(0,0,0xff);
  pvVar1 = SelectObject(hdc,h);
  SetMapMode(hdc,7);
  SetWindowExtEx(hdc,100,100,(LPSIZE)0x0);
  SetViewportExtEx(hdc,DAT_00433a44,DAT_00433a44,(LPSIZE)0x0);
  thunk_FUN_00405670(hdc,param_2);
  thunk_FUN_00405670(hdc,param_3);
  pvVar1 = SelectObject(hdc,pvVar1);
  DeleteObject(pvVar1);
  ReleaseDC(param_1,hdc);
  return;
}


