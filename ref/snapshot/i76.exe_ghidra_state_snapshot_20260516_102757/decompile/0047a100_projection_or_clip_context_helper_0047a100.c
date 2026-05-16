/*
 * Program: i76.exe
 * Function: projection_or_clip_context_helper_0047a100
 * Entry: 0047a100
 * Signature: undefined4 __cdecl projection_or_clip_context_helper_0047a100(char * param_1, void * param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: projection or clip context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl projection_or_clip_context_helper_0047a100(char *param_1,void *param_2)

{
  FILE *_File;
  char local_80;
  char local_7f;
  char local_7d;
  
  _File = fopen(param_1,&DAT_004c2098);
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fread(&local_80,0x80,1,_File);
  if (((local_80 != '\n') && (local_7f != '\x05')) && (local_7d != '\b')) {
    fclose(_File);
    return 0;
  }
  fseek(_File,-0x300,2);
  fread(param_2,0x100,3,_File);
  return 1;
}


