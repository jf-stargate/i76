/*
 * Program: i76.exe
 * Function: resolve_optional_win32_apis
 * Entry: 00446020
 * Signature: bool __stdcall resolve_optional_win32_apis(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_00446020
   suggested_name: resolve_optional_win32_apis
   basis: Resolves optional Win32 APIs via GetModuleHandle/GetProcAddress. */

bool resolve_optional_win32_apis(void)

{
  HMODULE hModule;
  int iVar1;
  bool bVar2;
  char local_10 [4];
  char local_c [4];
  char local_8 [4];
  char local_4;
  
  local_c = (char  [4])s_I7_SFRCE_DLL_004f2500._4_4_;
  local_10 = (char  [4])s_I7_SFRCE_DLL_004f2500._0_4_;
  local_8 = (char  [4])s_I7_SFRCE_DLL_004f2500._8_4_;
  local_4 = s_I7_SFRCE_DLL_004f2500[0xc];
  hModule = GetModuleHandleA(local_10);
  if (hModule == (HMODULE)0x0) {
    hModule = LoadLibraryA(local_10);
    bVar2 = hModule < (HMODULE)0x20;
    if (!bVar2) goto LAB_00446073;
  }
  else {
    bVar2 = hModule < (HMODULE)0x20;
LAB_00446073:
    if (!bVar2 && hModule != (HMODULE)0x20) {
      DAT_0052bbdc = GetProcAddress(hModule,s_I7FF_InitSystem_004f24f0);
      DAT_0052bbe0 = GetProcAddress(hModule,s_I7FF_ExitSystem_004f24e0);
      DAT_0052bbe4 = GetProcAddress(hModule,s_I7FF_SIM_Effect_004f24d0);
      if (((DAT_0052bbdc != (FARPROC)0x0) && (DAT_0052bbe0 != (FARPROC)0x0)) &&
         (DAT_0052bbe4 != (FARPROC)0x0)) goto LAB_004460bc;
    }
  }
  hModule = (HMODULE)0x0;
LAB_004460bc:
  if (hModule != (HMODULE)0x0) {
    iVar1 = -0x7ffbfaf1;
    if (DAT_0052bbdc != (FARPROC)0x0) {
      _s_l_004f2328 = 0x16c;
      iVar1 = (*DAT_0052bbdc)(s_l_004f2328);
    }
    if (iVar1 < 0) {
      OutputDebugStringA(s_Unable_to_get_SWForce_object__004f2494);
    }
    return -1 < iVar1;
  }
  OutputDebugStringA(s_Error_loading_i7_SFRCE_dll_004f24b4);
  return false;
}


