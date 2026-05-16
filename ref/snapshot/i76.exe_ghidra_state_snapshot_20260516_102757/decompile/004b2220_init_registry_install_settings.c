/*
 * Program: i76.exe
 * Function: init_registry_install_settings
 * Entry: 004b2220
 * Signature: bool __stdcall init_registry_install_settings(void)
 */


/* i76 second-pass rename
   old_name: FUN_004b2220
   suggested_name: init_registry_install_settings
   basis: Uses registry keys under SOFTWARE/Activision/Interstate '76 Gold Edition. */

bool init_registry_install_settings(void)

{
  LSTATUS LVar1;
  HANDLE pvVar2;
  bool bVar3;
  HKEY local_15c;
  BYTE local_158 [8];
  HKEY local_150;
  DWORD local_14c [3];
  _WIN32_FIND_DATAA local_140;
  
  local_14c[1] = 5;
  local_150 = (HKEY)0x0;
  local_15c = (HKEY)0x0;
  bVar3 = true;
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,s_SOFTWARE_Activision_004fff68,0,0x20019,&local_150);
  if (LVar1 == 0) {
    LVar1 = RegCreateKeyExA(local_150,s_Interstate__76_Gold_Edition_004c2680,0,(LPSTR)0x0,0,0xf003f,
                            (LPSECURITY_ATTRIBUTES)0x0,&local_15c,local_14c + 2);
    if (LVar1 == 0) {
      LVar1 = RegQueryValueExA(local_15c,s_Minimum_004fff60,(LPDWORD)0x0,local_14c,local_158,
                               local_14c + 1);
      if (LVar1 == 0) {
        if (local_158[0] == '0') {
          RegCloseKey(local_15c);
          return false;
        }
        if (local_158[0] == '1') {
          RegCloseKey(local_15c);
          return true;
        }
      }
      local_14c[0] = 1;
      pvVar2 = FindFirstFileA((LPCSTR)&DAT_004fff58,&local_140);
      bVar3 = pvVar2 == (HANDLE)0xffffffff;
      if (bVar3) {
        local_158[0] = '1';
      }
      else {
        local_158[0] = '0';
      }
      local_158[1] = 0;
      RegSetValueExA(local_15c,s_Minimum_004fff60,0,local_14c[0],local_158,2);
      RegCloseKey(local_15c);
    }
  }
  return bVar3;
}


