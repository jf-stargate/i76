/*
 * Program: i76.exe
 * Function: report_windowed_mode_requires_high_color
 * Entry: 004761a0
 * Signature: undefined4 __cdecl report_windowed_mode_requires_high_color(HWND param_1, int param_2, uint param_3, LPVOID param_4, int param_5, BOOL param_6)
 */


/* cgpt whole-binary semantic rename v1: string evidence 16/24/32 bit color */

undefined4 __cdecl
report_windowed_mode_requires_high_color
          (HWND param_1,int param_2,uint param_3,LPVOID param_4,int param_5,BOOL param_6)

{
  LPRECT lpRect;
  int nHeight;
  HDC hdc;
  LPCSTR pCVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  LONG X;
  int *piVar5;
  DWORD dwStyle;
  HWND pHVar6;
  HMENU hMenu;
  HINSTANCE hInstance;
  int local_c;
  
  if ((param_5 < 0) || (3 < param_5)) {
    piVar5 = &DAT_004fa498;
    param_1[0x107].unused = DAT_004fa4d0;
    param_1[0x108].unused = (int)PTR_world_transform_projection_context_helper_0048e110_004fa4d4;
    param_1[0x109].unused = (int)PTR_LAB_004fa4d8;
    param_1[0x10a].unused = (int)PTR_world_transform_projection_context_helper_0048dc50_004fa4dc;
  }
  else {
    piVar5 = &DAT_004f9dc0;
    param_1[0x107].unused = DAT_004f9df8;
    param_1[0x108].unused = (int)PTR_LAB_004f9dfc;
    param_1[0x109].unused = (int)PTR_LAB_004f9e00;
    param_1[0x10a].unused = (int)PTR_world_transform_projection_context_helper_0048dc50_004f9e04;
  }
  pHVar6 = param_1 + 0xfa;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    pHVar6->unused = *piVar5;
    piVar5 = piVar5 + 1;
    pHVar6 = pHVar6 + 1;
  }
  dwStyle = param_1[0xfc].unused;
  param_1[0xfb].unused = (int)param_4;
  param_1->unused = param_2;
  param_1[1].unused = (param_3 ^ param_1[1].unused) & 0x1fffffff ^ param_1[1].unused;
  lpRect = (LPRECT)(param_1 + 0x31);
  lpRect->left = 0;
  param_1[0x32].unused = 0;
  param_1[0x33].unused = param_2;
  param_1[0x34].unused = param_3;
  param_1[0x1b].unused = param_2;
  param_1[0x1c].unused = param_3;
  AdjustWindowRect(lpRect,dwStyle,param_6);
  iVar4 = param_1[0x33].unused - lpRect->left;
  param_1[0x33].unused = iVar4;
  iVar3 = param_1[0x34].unused - param_1[0x32].unused;
  iVar2 = param_1[0x1d].unused;
  nHeight = param_1[0x1e].unused;
  lpRect->left = iVar2 - iVar4 >> 1;
  param_1[0x34].unused = iVar3;
  param_1[0x32].unused = nHeight - iVar3 >> 1;
  if (param_4 == (LPVOID)0x0) {
    X = 0;
    local_c = 0;
  }
  else {
    local_c = param_1[0x32].unused;
    X = lpRect->left;
    iVar2 = param_1[0x33].unused;
    nHeight = param_1[0x34].unused;
  }
  pHVar6 = param_1;
  if (param_1[0x2f].unused == 0) {
    if (param_4 == (LPVOID)0x0) {
      hInstance = (HINSTANCE)param_1[0x30].unused;
      hMenu = (HMENU)0x0;
      pHVar6 = (HWND)0x0;
      nHeight = GetSystemMetrics(1);
      iVar2 = GetSystemMetrics(0);
      local_c = 0;
      X = 0;
      dwStyle = 0x90080000;
    }
    else {
      hInstance = (HINSTANCE)param_1[0x30].unused;
      param_4 = (LPVOID)0x0;
      hMenu = (HMENU)0x0;
      pHVar6 = (HWND)0x0;
    }
    pHVar6 = CreateWindowExA(0,(LPCSTR)(param_1 + 0x1f),(LPCSTR)(param_1 + 0x1f),dwStyle,X,local_c,
                             iVar2,nHeight,pHVar6,hMenu,hInstance,param_4);
    if (pHVar6 == (HWND)0x0) {
      param_1[0x39].unused = 5;
      return 0;
    }
    param_1[0x2f].unused = (int)pHVar6;
    if (param_1[0xfa].unused == 2) {
      if (param_1[0xfb].unused == 0) {
        SetMenu(pHVar6,(HMENU)0x0);
        ShowWindow(pHVar6,10);
        UpdateWindow(pHVar6);
      }
    }
    else if ((param_1[0xfa].unused == 0) && (param_1[0xfb].unused == 0)) {
      UpdateWindow(pHVar6);
      SetFocus(pHVar6);
    }
  }
  iVar2 = (*(code *)param_1[0xfd].unused)(param_1);
  if (iVar2 != 0) {
    if ((param_1[0xfa].unused == 2) || (param_1[0xfb].unused == 1)) {
      ShowWindow((HWND)param_1[0x2f].unused,5);
    }
    iVar2 = 0x18;
    hdc = GetDC(pHVar6);
    iVar2 = GetDeviceCaps(hdc,iVar2);
    if ((iVar2 != -1) && (param_1[0xfa].unused == 2)) {
      pCVar1 = (LPCSTR)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                     s_Sorry__if_you_wish_to_run_I_76_G_004f9fb0);
      fatal_out_of_memory_message(pCVar1);
    }
    return 1;
  }
  return 0;
}


