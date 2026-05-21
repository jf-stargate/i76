/*
 * Program: i76shell.dll
 * Function: enumerate_savegame_directory
 * Entry: 10032f80
 * Signature: undefined __cdecl enumerate_savegame_directory(int param_1, undefined4 param_2)
 */


void __cdecl enumerate_savegame_directory(int param_1,undefined4 param_2)

{
  int *_Str;
  FILE *_File;
  int iVar1;
  CHAR local_20 [32];
  
  _File = fopen(s_savegame_dir_1004ccf8,s_wb_1004ccf4);
  if (_File != (FILE *)0x0) {
    _Str = (int *)(param_1 + 4);
    fwrite(_Str,4,1,_File);
    iVar1 = 0;
    if (0 < *_Str) {
      do {
        fwrite(*(void **)(*(int *)(param_1 + 8) + iVar1 * 4),0x3c,1,_File);
        iVar1 = iVar1 + 1;
      } while (iVar1 < *_Str);
    }
    fclose(_File);
    wsprintfA(local_20,s_save_3_3d_cmp_1004cd08,param_2);
    write_vehicle_scene_config_file(local_20);
  }
  return;
}


