/*
 * Program: i76.exe
 * Function: create_raster_fullscreen_window_640x480
 * Entry: 00433df0
 * Signature: undefined4 __cdecl create_raster_fullscreen_window_640x480(undefined4 * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00433df0
   suggested_name: create_raster_fullscreen_window_640x480
   basis: Window creation helper using AdjustWindowRect/CreateWindowExA, likely fullscreen raster
   mode. */

undefined4 __cdecl create_raster_fullscreen_window_640x480(undefined4 *param_1)

{
  LPRECT lpRect;
  undefined1 uVar1;
  undefined1 uVar2;
  DWORD dwStyle;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  undefined1 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  HWND pHVar12;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  DAT_0052b91c = malloc(0x204);
  *DAT_0052b91c = 0x100;
  *param_1 = 0x280;
  param_1[1] = param_1[1] & 0xe00001e0 | 0x1e0;
  param_1[0x107] = DAT_004f1510;
  param_1[0x108] = PTR_LAB_004f1514;
  param_1[0x109] = PTR_load_iseg_tseg_record_table_context_004f1518;
  param_1[0x10a] = PTR_load_iseg_tseg_record_table_context_004f151c;
  puVar6 = &DAT_004f1520;
  puVar10 = param_1 + 0xfa;
  for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar10 = puVar10 + 1;
  }
  dwStyle = param_1[0xfc];
  lpRect = (LPRECT)(param_1 + 0x31);
  lpRect->left = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0x280;
  param_1[0x34] = 0x1e0;
  param_1[0x1b] = 0x280;
  param_1[0x1c] = 0x1e0;
  AdjustWindowRect(lpRect,dwStyle,1);
  iVar8 = param_1[0x32];
  iVar4 = param_1[0x34];
  iVar11 = param_1[0x33] - lpRect->left;
  param_1[0x34] = iVar4 - iVar8;
  iVar3 = param_1[0x1e];
  hInstance = (HINSTANCE)param_1[0x30];
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  param_1[0x33] = iVar11;
  pHVar12 = (HWND)0x0;
  lpRect->left = param_1[0x1d] - iVar11 >> 1;
  param_1[0x32] = iVar3 - (iVar4 - iVar8) >> 1;
  iVar8 = GetSystemMetrics(1);
  iVar4 = GetSystemMetrics(0);
  pHVar12 = CreateWindowExA(0x40000,(LPCSTR)(param_1 + 0x1f),(LPCSTR)(param_1 + 0x1f),0x90080000,0,0
                            ,iVar4,iVar8,pHVar12,hMenu,hInstance,lpParam);
  if (pHVar12 == (HWND)0x0) {
    return 0;
  }
  param_1[0x2f] = pHVar12;
  ShowWindow(pHVar12,1);
  UpdateWindow(pHVar12);
  (*DAT_00608bc0)(9,0);
  iVar8 = initialize_640x480_display_surface_context(param_1,1);
  if (iVar8 == 0) {
    return 0;
  }
  puVar9 = &DAT_00643621;
  puVar5 = (undefined1 *)((int)&DAT_005fd100 + 1);
  do {
    uVar1 = *puVar5;
    puVar9[-1] = puVar5[-1];
    uVar2 = puVar5[1];
    *puVar9 = uVar1;
    puVar9[1] = uVar2;
    puVar5 = puVar5 + 4;
    puVar9 = puVar9 + 3;
  } while ((int)puVar5 < 0x5fd501);
  puVar6 = &DAT_004f9e24;
  do {
    *puVar6 = 0;
    puVar6 = puVar6 + 7;
  } while ((int)puVar6 < 0x4f9f04);
  iVar8 = 0;
  piVar7 = &DAT_004f9e38;
  while ((((piVar7[-2] != 0x280 || (*piVar7 != 0x280)) || (piVar7[-1] != 0x1e0)) ||
         (piVar7[1] != 0x1e0))) {
    piVar7 = piVar7 + 7;
    iVar8 = iVar8 + 1;
    if (0x4f9f17 < (int)piVar7) {
LAB_00433fd1:
      iVar8 = (*(code *)param_1[0x103])(param_1,0);
      if (iVar8 != 0) {
        return 1;
      }
      if (DAT_00608408 != 8) {
        (*DAT_00608bac)();
        return 0;
      }
      release_directdraw_direct3d_interfaces();
      return 0;
    }
  }
  (&DAT_004f9e24)[iVar8 * 7] = 1;
  goto LAB_00433fd1;
}


