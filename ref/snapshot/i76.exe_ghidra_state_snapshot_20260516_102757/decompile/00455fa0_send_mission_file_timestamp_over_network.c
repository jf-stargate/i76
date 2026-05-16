/*
 * Program: i76.exe
 * Function: send_mission_file_timestamp_over_network
 * Entry: 00455fa0
 * Signature: undefined __cdecl send_mission_file_timestamp_over_network(undefined4 param_1, undefined4 param_2)
 */


/* i76 first-pass rename
   old_name: FUN_00455fa0
   suggested_name: send_mission_file_timestamp_over_network
   basis: Uses CreateFileA/GetFileTime/CloseHandle and sends file timestamp/state over network path.
   
   i76 second-pass rename
   old_name: send_mission_file_timestamp_over_network
   suggested_name: send_mission_file_timestamp_over_network
   basis: Already identified; keeps name stable if script rerun. */

void __cdecl send_mission_file_timestamp_over_network(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  HANDLE hFile;
  undefined2 extraout_var_00;
  float10 fVar2;
  char *_Format;
  undefined2 local_ac;
  undefined1 local_aa;
  float local_a8;
  undefined4 local_a4;
  char local_a0 [4];
  char local_9c;
  char local_98 [30];
  char local_7a [18];
  undefined4 local_68;
  _FILETIME local_64 [2];
  char local_50 [80];
  
  fVar2 = get_gameplay_runtime_seconds();
  local_a8 = (float)fVar2;
  local_ac = 0x4f4a;
  local_aa = 0;
  copy_multiplayer_session_status_name_string(local_7a);
  local_68 = get_shell_selected_map_or_session_scalar();
  local_a4 = param_2;
  bVar1 = get_global_heap_handle();
  if (CONCAT31(extraout_var,bVar1) == 0) {
    _Format = s_miss8__s_004f5bd4;
  }
  else {
    _Format = s_miss16__s_004f5be0;
  }
  sprintf(local_50,_Format,local_7a);
  copy_shell_session_text_block(local_98);
  local_a0[0] = s_1_00_004f5bcc[0];
  local_a0[1] = s_1_00_004f5bcc[1];
  local_a0[2] = s_1_00_004f5bcc[2];
  local_a0[3] = s_1_00_004f5bcc[3];
  local_9c = s_1_00_004f5bcc[4];
  hFile = CreateFileA(local_50,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  GetFileTime(hFile,(LPFILETIME)0x0,(LPFILETIME)0x0,local_64);
  CloseHandle(hFile);
  dpSend(DAT_00541024,CONCAT22(extraout_var_00,DAT_00541028),param_1,0,&local_ac,0x50);
  return;
}


