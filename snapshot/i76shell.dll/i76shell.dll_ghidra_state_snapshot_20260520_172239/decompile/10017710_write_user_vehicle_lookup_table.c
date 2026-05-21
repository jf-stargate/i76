/*
 * Program: i76shell.dll
 * Function: write_user_vehicle_lookup_table
 * Entry: 10017710
 * Signature: undefined4 __stdcall write_user_vehicle_lookup_table(void)
 */


undefined4 write_user_vehicle_lookup_table(void)

{
  FILE *_File;
  int iVar1;
  undefined *_Str;
  char local_1c [28];
  
  sprintf(local_1c,s__s_10047bbc,s_I76UVEH_def_10047bb0);
  _File = fopen(local_1c,s_wb_10047bc0);
  if (_File == (FILE *)0x0) {
    log_or_report_shell_ddraw_error_candidate(s_Could_not_save_user_vehicle_look_10047bc4);
    return 1;
  }
  fwrite(&DAT_100cf3e0,4,1,_File);
  iVar1 = 0;
  if (0 < DAT_100cf3e0) {
    _Str = &DAT_100d0384;
    do {
      fwrite(_Str + -4000,0x14,1,_File);
      fwrite(_Str,0x14,1,_File);
      fwrite(_Str + 4000,0xd,1,_File);
      iVar1 = iVar1 + 1;
      _Str = _Str + 200;
    } while (iVar1 < DAT_100cf3e0);
  }
  fclose(_File);
  return 1;
}


