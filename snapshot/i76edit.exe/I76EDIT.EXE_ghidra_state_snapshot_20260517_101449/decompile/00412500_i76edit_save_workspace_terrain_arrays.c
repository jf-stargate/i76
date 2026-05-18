/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_workspace_terrain_arrays
 * Entry: 00412500
 * Signature: undefined __cdecl i76edit_save_workspace_terrain_arrays(int param_1)
 */


/* [cgpt_i76edit_level_renames_v3] Writes workspace terrain/painter arrays: 0x1900 header/table
   followed by five 0x280140 byte planes.
   
   [cgpt_i76edit_level_renames_v6:high] Workspace terrain-array writer. Writes 00439ef0 size 0x1900,
   then five 0x280140-byte terrain planes at 009bc820, 00ebcaa0, 0113cbe0, 00c3c960, and 013bcd20.
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


