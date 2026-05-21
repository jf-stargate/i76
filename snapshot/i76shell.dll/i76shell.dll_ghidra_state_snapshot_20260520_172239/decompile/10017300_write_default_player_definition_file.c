/*
 * Program: i76shell.dll
 * Function: write_default_player_definition_file
 * Entry: 10017300
 * Signature: undefined4 __cdecl write_default_player_definition_file(void * param_1)
 */


undefined4 __cdecl write_default_player_definition_file(void *param_1)

{
  FILE *_File;
  
  _File = fopen(s_I76DFLT_DEF_10047a1c,s_wb_10047a18);
  if (_File != (FILE *)0x0) {
    fwrite(param_1,0x14,1,_File);
    fclose(_File);
    return 1;
  }
  log_or_report_shell_ddraw_error_candidate(s_Could_not_create_a_new_player_de_10047a28);
                    /* WARNING: Subroutine does not return */
  exit(0);
}


