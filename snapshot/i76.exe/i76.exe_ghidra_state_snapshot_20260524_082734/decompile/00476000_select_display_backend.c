/*
 * Program: i76.exe
 * Function: select_display_backend
 * Entry: 00476000
 * Signature: undefined __cdecl select_display_backend(int * param_1, undefined4 param_2, char * param_3)
 */


/* i76 second-pass rename
   old_name: FUN_00476000
   suggested_name: select_display_backend
   basis: References zglide/zredline/zpowervr/zdx5draw and software/hardware mode diagnostics.
   
   [cgpt_i76exe_render_mode_v13] proposed=select_display_backend_and_fallback_to_software :: Chooses
   software or hardware raster/display backend. Attempts zglide/zredline/zpowervr/zdx5draw hardware
   path when requested; falls back to software on failure. */

void __cdecl select_display_backend(int *param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  HWND__ *pHVar6;
  char *pcVar7;
  HWND__ local_42c [29];
  int local_3b8;
  int local_3b4;
  char local_3b0 [68];
  undefined4 local_36c;
  
  pHVar6 = local_42c;
  for (iVar2 = 0x10b; iVar2 != 0; iVar2 = iVar2 + -1) {
    pHVar6->unused = 0;
    pHVar6 = pHVar6 + 1;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = param_3;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = param_3 + 1;
    cVar1 = *param_3;
    param_3 = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar7 = local_3b0;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  local_36c = param_2;
  local_3b8 = GetSystemMetrics(0);
  local_3b4 = GetSystemMetrics(1);
  if (g_cmdline_hardware_raster_requested == 0) {
    if (g_cmdline_hardware_window_or_hal_requested != 0) {
      iVar2 = create_display_window_mode_a(local_42c);
      goto joined_r0x00476102;
    }
  }
  else {
    iVar2 = _stricmp(&g_selected_raster_plugin_dll_name,s_zglide_dll_004f9fa4);
    if (((iVar2 == 0) ||
        (iVar2 = _stricmp(&g_selected_raster_plugin_dll_name,s_zredline_dll_004f9f94), iVar2 == 0))
       || (iVar2 = _stricmp(&g_selected_raster_plugin_dll_name,s_zpowervr_dll_004f9f84), iVar2 == 0)
       ) {
      iVar2 = 1;
    }
    else {
      iVar2 = _stricmp(&g_selected_raster_plugin_dll_name,s_zdx5draw_dll_004f9f74);
      if (iVar2 != 0) goto LAB_0047611c;
      iVar2 = 0;
    }
    iVar2 = create_display_window_for_mode_selector(iVar2,local_42c);
joined_r0x00476102:
    if (iVar2 != 0) goto LAB_00476170;
    MessageBoxA((HWND)0x0,s_Failed_to_initialize_3D_hardware_004f9f24,
                s_Running_software_emulation_mode_004f9f54,0);
    g_cmdline_hardware_window_or_hal_requested = 0;
  }
LAB_0047611c:
  if (DAT_004f9f20 != 0) {
    iVar2 = 3;
  }
  else {
    iVar2 = 5;
  }
  report_windowed_mode_requires_high_color
            (local_42c,0x280,0x1e0,(LPVOID)(uint)(DAT_004f9f20 == 0),iVar2,0);
  geometry_projection_clip_context_helper_004791e0((int)local_42c,(undefined4 *)0x0);
  matrix_vector_projection_context_helper_00478b30();
LAB_00476170:
  pHVar6 = local_42c;
  for (iVar2 = 0x10b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = pHVar6->unused;
    pHVar6 = pHVar6 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


