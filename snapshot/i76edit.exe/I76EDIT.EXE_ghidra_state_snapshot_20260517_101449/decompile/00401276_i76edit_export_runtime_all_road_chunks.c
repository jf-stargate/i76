/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_all_road_chunks
 * Entry: 00401276
 * Signature: int __cdecl i76edit_export_runtime_all_road_chunks(int param_1)
 */


int __cdecl i76edit_export_runtime_all_road_chunks(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  do {
    iVar1 = i76edit_export_road_records(param_1,DAT_0043c544);
  } while (iVar1 < 0);
  iVar2 = i76edit_write_bwd2_exit_chunk(param_1);
  iVar3 = i76edit_write_bwd2_exit_chunk(param_1);
  iVar4 = i76edit_write_bwd2_exit_chunk(param_1);
  return iVar4 + iVar1 + iVar2 + iVar3;
}


