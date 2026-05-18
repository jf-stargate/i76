/*
 * Program: i76.exe
 * Function: create_bwd2_chunk_output_file
 * Entry: 004b4840
 * Signature: FILE * __cdecl create_bwd2_chunk_output_file(char * param_1, undefined4 param_2)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Creates a writable BWD2 chunk file
   and emits the BWD2 header plus first top-level container tag supplied by caller.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=create_bwd2_chunk_output_file :: Generic BWD2
   writer helper; not the runtime loader path but confirms BWD2 header/revision format. */

FILE * __cdecl create_bwd2_chunk_output_file(char *param_1,undefined4 param_2)

{
  FILE *_File;
  size_t sVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined *local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_14 = 0x32445742;
  local_10 = 8;
  local_c = &DAT_00564552;
  local_8 = 0xc;
  local_4 = param_2;
  _File = fopen(param_1,s_wb_004edf28);
  if (_File == (FILE *)0x0) {
    report_chunk_parse_error();
    return (FILE *)0x0;
  }
  sVar1 = fwrite(&local_14,1,8,_File);
  if (sVar1 == 8) {
    sVar1 = fwrite(&local_c,1,0xc,_File);
    if (sVar1 == 0xc) {
      return _File;
    }
  }
  report_chunk_parse_error();
  fclose(_File);
  return (FILE *)0x0;
}


