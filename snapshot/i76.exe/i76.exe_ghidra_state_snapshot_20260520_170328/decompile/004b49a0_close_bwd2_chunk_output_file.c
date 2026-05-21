/*
 * Program: i76.exe
 * Function: close_bwd2_chunk_output_file
 * Entry: 004b49a0
 * Signature: undefined4 __cdecl close_bwd2_chunk_output_file(FILE * param_1, undefined4 param_2, int param_3)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Optionally writes EXIT chunk and
   closes a writable BWD2 chunk file. */

undefined4 __cdecl close_bwd2_chunk_output_file(FILE *param_1,undefined4 param_2,int param_3)

{
  size_t sVar1;
  undefined4 local_8;
  undefined4 local_4;
  
  if (param_3 != 0) {
    local_8 = 0x54495845;
    local_4 = 0x10;
    sVar1 = fwrite(&local_8,1,8,param_1);
    if (sVar1 != 8) {
      report_error();
    }
  }
  fclose(param_1);
  return 1;
}


