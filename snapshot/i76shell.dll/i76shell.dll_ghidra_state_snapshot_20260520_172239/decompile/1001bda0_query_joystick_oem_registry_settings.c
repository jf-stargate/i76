/*
 * Program: i76shell.dll
 * Function: query_joystick_oem_registry_settings
 * Entry: 1001bda0
 * Signature: bool __cdecl query_joystick_oem_registry_settings(int param_1, HKEY param_2, char * param_3, size_t param_4)
 */


bool __cdecl
query_joystick_oem_registry_settings(int param_1,HKEY param_2,char *param_3,size_t param_4)

{
  LSTATUS LVar1;
  DWORD local_8 [2];
  
  sprintf(&DAT_100d1e48,s_System_CurrentControlSet_Control_100492d0,param_2);
  LVar1 = RegOpenKeyExA((HKEY)&DAT_80000002,&DAT_100d1e48,0,1,&param_2);
  if (LVar1 != 0) {
    log_or_report_shell_ddraw_error_candidate(s_Could_not_open_registry_joystick_10049324);
    return false;
  }
  sprintf(&DAT_100d1e48,s_Joystick_dOEMName_1004935c,param_1 + 1);
  local_8[0] = 0x40;
  local_8[1] = 1;
  LVar1 = RegQueryValueExA(param_2,&DAT_100d1e48,(LPDWORD)0x0,local_8 + 1,&DAT_100d1e08,local_8);
  if (LVar1 == 0) {
    RegCloseKey(param_2);
    sprintf(&DAT_100d1e48,s_System_CurrentControlSet_Control_10049370,&DAT_100d1e08);
    LVar1 = RegOpenKeyExA((HKEY)&DAT_80000002,&DAT_100d1e48,0,1,&param_2);
    if (LVar1 == 0) {
      local_8[0] = 0x40;
      LVar1 = RegQueryValueExA(param_2,s_OEMName_100493c4,(LPDWORD)0x0,local_8 + 1,&DAT_100d1e08,
                               local_8);
      if (LVar1 == 0) {
        strncpy(param_3,&DAT_100d1e08,param_4);
      }
    }
  }
  RegCloseKey(param_2);
  return LVar1 == 0;
}


