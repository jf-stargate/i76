/*
 * Program: I76EDIT.EXE
 * Function: i76edit_write_bwd2_exit_chunk
 * Entry: 0041bcb0
 * Signature: undefined4 __cdecl i76edit_write_bwd2_exit_chunk(int param_1)
 */


/* [cgpt_i76edit_level_renames_v4:high] Writes an 8-byte BWD2 EXIT chunk: tag 'EXIT', size=8. Used
   as a section terminator throughout runtime export. */

undefined4 __cdecl i76edit_write_bwd2_exit_chunk(int param_1)

{
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = 0x54495845;
  local_4 = 8;
  __write(param_1,&local_8,8);
  return 8;
}


