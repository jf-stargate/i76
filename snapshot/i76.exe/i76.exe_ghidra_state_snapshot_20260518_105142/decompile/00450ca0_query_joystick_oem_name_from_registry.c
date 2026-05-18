/*
 * Program: i76.exe
 * Function: query_joystick_oem_name_from_registry
 * Entry: 00450ca0
 * Signature: bool __cdecl query_joystick_oem_name_from_registry(int param_1, HKEY param_2, char * param_3, size_t param_4)
 */


/* i76 first-pass rename
   old_name: FUN_00450ca0
   suggested_name: query_joystick_oem_name_from_registry
   basis: Reads joystick OEM/config values from registry. */

bool __cdecl
query_joystick_oem_name_from_registry(int param_1,HKEY param_2,char *param_3,size_t param_4)

{
  LSTATUS LVar1;
  DWORD local_8 [2];
  
  sprintf(&DAT_0053ebb0,s_System_CurrentControlSet_Control_004f5638,param_2);
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,&DAT_0053ebb0,0,1,&param_2);
  if (LVar1 != 0) {
    report_chunk_parse_error();
    return false;
  }
  sprintf(&DAT_0053ebb0,s_Joystick_dOEMName_004f55ec,param_1 + 1);
  local_8[0] = 0x40;
  local_8[1] = 1;
  LVar1 = RegQueryValueExA(param_2,&DAT_0053ebb0,(LPDWORD)0x0,local_8 + 1,&DAT_0053eb70,local_8);
  if (LVar1 == 0) {
    RegCloseKey(param_2);
    sprintf(&DAT_0053ebb0,s_System_CurrentControlSet_Control_004f5598,&DAT_0053eb70);
    LVar1 = RegOpenKeyExA((HKEY)0x80000002,&DAT_0053ebb0,0,1,&param_2);
    if (LVar1 == 0) {
      local_8[0] = 0x40;
      LVar1 = RegQueryValueExA(param_2,s_OEMName_004f5590,(LPDWORD)0x0,local_8 + 1,&DAT_0053eb70,
                               local_8);
      if (LVar1 == 0) {
        strncpy(param_3,&DAT_0053eb70,param_4);
      }
    }
  }
  RegCloseKey(param_2);
  return LVar1 == 0;
}


