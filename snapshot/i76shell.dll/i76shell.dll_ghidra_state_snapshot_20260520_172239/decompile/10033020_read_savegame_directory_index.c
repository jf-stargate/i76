/*
 * Program: i76shell.dll
 * Function: read_savegame_directory_index
 * Entry: 10033020
 * Signature: undefined __cdecl read_savegame_directory_index(int param_1)
 */


void __cdecl read_savegame_directory_index(int param_1)

{
  FILE *_File;
  LPVOID _DstBuf;
  FILE *_File_00;
  int local_28;
  int local_24;
  CHAR local_20 [32];
  
  _File = fopen(s_savegame_dir_1004cd20,s_rb_1004cd1c);
  if (_File != (FILE *)0x0) {
    fread(&local_24,4,1,_File);
    local_28 = 0;
    if (0 < local_24) {
      do {
        _DstBuf = HeapAlloc(DAT_10051c50,1,0x3c);
        fread(_DstBuf,0x3c,1,_File);
        wsprintfA(local_20,s__s_cmp_1004cd30,(int)_DstBuf + 0x24);
        _File_00 = fopen(local_20,s_rb_1004cd18);
        if (_File_00 == (FILE *)0x0) {
          if (_DstBuf != (LPVOID)0x0) {
            HeapFree(DAT_10051c50,1,_DstBuf);
          }
        }
        else {
          fclose(_File_00);
          insert_pointer_list_item_sorted_or_append(param_1,(int)_DstBuf,(undefined *)0x0);
        }
        local_28 = local_28 + 1;
      } while (local_28 < local_24);
    }
    fclose(_File);
  }
  return;
}


