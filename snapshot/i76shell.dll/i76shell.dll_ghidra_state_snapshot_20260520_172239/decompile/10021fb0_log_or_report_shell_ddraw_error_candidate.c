/*
 * Program: i76shell.dll
 * Function: log_or_report_shell_ddraw_error_candidate
 * Entry: 10021fb0
 * Signature: undefined __cdecl log_or_report_shell_ddraw_error_candidate(char * param_1)
 */


void __cdecl log_or_report_shell_ddraw_error_candidate(char *param_1)

{
  _vsnprintf(&DAT_100f60e0,0x100,param_1,&stack0x00000008);
  FUN_10008980(&DAT_100f60e0);
  return;
}


