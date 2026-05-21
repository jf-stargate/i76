/*
 * Program: i76.exe
 * Function: create_display_window_mode_a
 * Entry: 0042d0c0
 * Signature: undefined4 __cdecl create_display_window_mode_a(undefined4 * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_0042d0c0
   suggested_name: create_display_window_mode_a
   basis: Alternate CreateWindowExA display/window creation path. */

undefined4 __cdecl create_display_window_mode_a(undefined4 *param_1)

{
  LPRECT lpRect;
  DWORD dwStyle;
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  HWND pHVar11;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  undefined4 local_38 [4];
  byte local_28;
  byte local_24;
  byte local_1c;
  byte local_18;
  byte local_10;
  
  *param_1 = 0x280;
  param_1[1] = param_1[1] & 0xe00001e0 | 0x1e0;
  param_1[0x107] = DAT_004eded0;
  param_1[0x108] = PTR_flip_or_restore_directdraw_front_back_surfaces_004eded4;
  param_1[0x109] = PTR_prepare_smacker_cutscene_display_surface_004eded8;
  param_1[0x10a] = PTR_LAB_004ededc;
  puVar5 = &DAT_004ede98;
  puVar10 = param_1 + 0xfa;
  for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar5;
    puVar5 = puVar5 + 1;
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
  iVar7 = param_1[0x32];
  iVar2 = param_1[0x34];
  iVar9 = param_1[0x33] - lpRect->left;
  param_1[0x34] = iVar2 - iVar7;
  iVar1 = param_1[0x1e];
  hInstance = (HINSTANCE)param_1[0x30];
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  param_1[0x33] = iVar9;
  pHVar11 = (HWND)0x0;
  lpRect->left = param_1[0x1d] - iVar9 >> 1;
  param_1[0x32] = iVar1 - (iVar2 - iVar7) >> 1;
  iVar7 = GetSystemMetrics(1);
  iVar2 = GetSystemMetrics(0);
  pHVar11 = CreateWindowExA(0x40000,(LPCSTR)(param_1 + 0x1f),(LPCSTR)(param_1 + 0x1f),0x90080000,0,0
                            ,iVar2,iVar7,pHVar11,hMenu,hInstance,lpParam);
  if (pHVar11 == (HWND)0x0) {
    return 0;
  }
  param_1[0x2f] = pHVar11;
  ShowWindow(pHVar11,1);
  UpdateWindow(pHVar11);
  iVar7 = create_directdraw_texture_palette(param_1,1);
  if (iVar7 == 0) {
    return 0;
  }
  write_video_driver_log(0x5fde40);
  puVar8 = &DAT_00643621;
  puVar3 = (undefined1 *)((int)&DAT_005fd100 + 1);
  do {
    puVar4 = puVar3 + 4;
    puVar8[-1] = puVar3[-1];
    *puVar8 = *puVar3;
    puVar8[1] = puVar3[1];
    puVar8 = puVar8 + 3;
    puVar3 = puVar4;
  } while ((int)puVar4 < 0x5fd501);
  reset_video_memory_texture_cache_index();
  puVar5 = &DAT_005fe538;
  puVar10 = local_38;
  for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar10 = puVar10 + 1;
  }
  if ((local_18 & 1) == 0) {
    if (param_1[0x18] == 1) {
      release_bitmap_surface_context(param_1 + 0xd);
      release_all_video_memory_texture_cache_records();
      if ((((param_1[2] == 1) && (DAT_005fff34 == 1)) && (DAT_006080cc != (int *)0x0)) &&
         (iVar7 = (**(code **)(*DAT_006080cc + 8))(DAT_006080cc), iVar7 == 0)) {
        DAT_006080cc = (int *)iVar7;
        release_directdraw_direct3d_interfaces();
        return 0;
      }
      goto LAB_0042d3a9;
    }
  }
  else {
    if ((local_18 & 0x20) != 0) {
      DAT_005280d4 = 1;
    }
    if (((((local_18 & 8) != 0) && ((local_10 & 2) != 0)) &&
        (((local_28 & 0x10) != 0 && (((local_24 & 0x20) != 0 && ((local_1c & 2) != 0)))))) &&
       ((local_1c & 8) != 0)) {
      puVar5 = &DAT_004f9e24;
      do {
        *puVar5 = 0;
        puVar5 = puVar5 + 7;
      } while ((int)puVar5 < 0x4f9f04);
      iVar7 = 0;
      piVar6 = &DAT_004f9e38;
      do {
        if ((((piVar6[-2] == 0x280) && (*piVar6 == 0x280)) && (piVar6[-1] == 0x1e0)) &&
           (piVar6[1] == 0x1e0)) {
          (&DAT_004f9e24)[iVar7 * 7] = 1;
          break;
        }
        piVar6 = piVar6 + 7;
        iVar7 = iVar7 + 1;
      } while ((int)piVar6 < 0x4f9f18);
      iVar7 = (*(code *)param_1[0x103])(param_1,0);
      if (iVar7 != 0) {
        return 1;
      }
    }
    if (param_1[0x18] == 1) {
      release_bitmap_surface_context(param_1 + 0xd);
    }
  }
  release_all_video_memory_texture_cache_records();
  if (((param_1[2] == 1) && (DAT_005fff34 == 1)) &&
     ((DAT_006080cc != (int *)0x0 &&
      (iVar7 = (**(code **)(*DAT_006080cc + 8))(DAT_006080cc), iVar7 == 0)))) {
    DAT_006080cc = (int *)0x0;
  }
LAB_0042d3a9:
  release_directdraw_direct3d_interfaces();
  return 0;
}


