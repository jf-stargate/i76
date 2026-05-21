/*
 * Program: i76.exe
 * Function: save_player_definition
 * Entry: 00497290
 * Signature: undefined __stdcall save_player_definition(void)
 */


/* i76 second-pass rename
   old_name: FUN_00497290
   suggested_name: save_player_definition
   basis: Writes I76PLYR.DEF. */

void save_player_definition(void)

{
  FILE *_File;
  
  _File = fopen(s_I76PLYR_DEF_004fd7dc,s_wb_004edf28);
  if (_File != (FILE *)0x0) {
    fwrite(&g_player_display_options_block,1,0x60,_File);
    fclose(_File);
  }
  return;
}


