/*
 * Program: I76EDIT.EXE
 * Function: i76edit_write_bwd2_exit_chunk
 * Entry: 0040114f
 * Signature: undefined4 __cdecl i76edit_write_bwd2_exit_chunk(int param_1)
 */


undefined4 __cdecl i76edit_write_bwd2_exit_chunk(int param_1)

{
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_8 = 0x54495845;
  uStack_4 = 8;
  __write(param_1,&uStack_8,8);
  return 8;
}


