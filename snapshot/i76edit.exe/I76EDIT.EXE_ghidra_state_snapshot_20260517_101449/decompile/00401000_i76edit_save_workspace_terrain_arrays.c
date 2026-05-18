/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_workspace_terrain_arrays
 * Entry: 00401000
 * Signature: undefined __cdecl i76edit_save_workspace_terrain_arrays(int param_1)
 */


void __cdecl i76edit_save_workspace_terrain_arrays(int param_1)

{
  __write(param_1,&DAT_00439ef0,0x1900);
  __write(param_1,&DAT_009bc820,0x280140);
  __write(param_1,&DAT_00ebcaa0,0x280140);
  __write(param_1,&DAT_0113cbe0,0x280140);
  __write(param_1,&DAT_00c3c960,0x280140);
  __write(param_1,&DAT_013bcd20,0x280140);
  return;
}


