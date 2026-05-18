/*
 * Program: I76EDIT.EXE
 * Function: i76edit_write_bwd2_revision_chunk
 * Entry: 0041bcf0
 * Signature: undefined4 __cdecl i76edit_write_bwd2_revision_chunk(int param_1, undefined4 param_2, undefined4 param_3)
 */


/* [cgpt_i76edit_level_renames_v4:high] Writes a 12-byte BWD2 chunk: uint32 tag, uint32 size=0x0c,
   uint32 revision/version. Called for VER/WREV/RREV/OREV/LREV/AREV. */

undefined4 __cdecl
i76edit_write_bwd2_revision_chunk(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = param_2;
  local_4 = param_3;
  local_8 = 0xc;
  __write(param_1,&local_c,0xc);
  return 0xc;
}


