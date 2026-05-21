/*
 * Program: i76shell.dll
 * Function: read_user_vehicle_lookup_table
 * Entry: 10017630
 * Signature: undefined4 __stdcall read_user_vehicle_lookup_table(void)
 */


undefined4 read_user_vehicle_lookup_table(void)

{
  FILE *_File;
  int iVar1;
  undefined *_DstBuf;
  char local_1c [28];
  
  sprintf(local_1c,s__s_10047b64,s_I76UVEH_def_10047b58);
  _File = fopen(local_1c,s_rb_10047b68);
  if (_File == (FILE *)0x0) {
    log_or_report_shell_ddraw_error_candidate(s_Could_not_read_user_vehicle_look_10047b6c);
    return 1;
  }
  fread(&DAT_100cf3e0,4,1,_File);
  iVar1 = 0;
  if (0 < DAT_100cf3e0) {
    _DstBuf = &DAT_100d0384;
    do {
      fread(_DstBuf + -4000,0x14,1,_File);
      fread(_DstBuf,0x14,1,_File);
      fread(_DstBuf + 4000,0xd,1,_File);
      iVar1 = iVar1 + 1;
      _DstBuf = _DstBuf + 200;
    } while (iVar1 < DAT_100cf3e0);
  }
  fclose(_File);
  initialize_builtin_vehicle_catalog();
  return 1;
}


