/*
 * Program: i76.exe
 * Function: write_bwd2_chunk_record
 * Entry: 004b4900
 * Signature: bool __cdecl write_bwd2_chunk_record(FILE * param_1, undefined4 param_2, undefined4 param_3, void * param_4, size_t param_5)
 */


/* [cgpt i76.exe chunk/parser/text rename v5; confidence=high] Writes a BWD2 chunk record:
   four-character tag, length = payload size + 8, then optional payload bytes.
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=write_bwd2_chunk_record :: Generic BWD2 chunk
   writer: tag, size=payload+8, optional payload. */

bool __cdecl
write_bwd2_chunk_record
          (FILE *param_1,undefined4 param_2,undefined4 param_3,void *param_4,size_t param_5)

{
  size_t sVar1;
  bool bVar2;
  undefined4 local_8;
  int local_4;
  
  local_8 = CONCAT22(CONCAT11((char)param_3,(char)((uint)param_3 >> 8)),
                     CONCAT11((char)((uint)param_3 >> 0x10),param_3._3_1_));
  local_4 = param_5 + 8;
  bVar2 = false;
  sVar1 = fwrite(&local_8,1,8,param_1);
  if (sVar1 == 8) {
    if (param_4 == (void *)0x0) {
      bVar2 = true;
    }
    else {
      sVar1 = fwrite(param_4,1,param_5,param_1);
      bVar2 = sVar1 == param_5;
    }
  }
  if (!bVar2) {
    report_error();
  }
  return bVar2;
}


