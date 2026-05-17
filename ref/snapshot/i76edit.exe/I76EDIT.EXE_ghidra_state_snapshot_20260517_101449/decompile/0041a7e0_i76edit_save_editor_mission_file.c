/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_editor_mission_file
 * Entry: 0041a7e0
 * Signature: undefined __cdecl i76edit_save_editor_mission_file(char * param_1)
 */


/* [cgpt_i76edit_level_renames_v2:high] Editor save path. Evidence: 'Saving Terrain...', 'Saving
   Roads...', 'Saving Objects...' and __open/__write/__close call chain. */

void __cdecl i76edit_save_editor_mission_file(char *param_1)

{
  int _FileHandle;
  undefined4 unaff_ESI;
  undefined2 unaff_DI;
  undefined1 *_Buf;
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 local_4;
  
  _FileHandle = __open(param_1,0x8301,0x80);
  __write(_FileHandle,&DAT_004366ac,4);
  local_4 = 8;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&local_4,4);
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&DAT_01641fc0,0x13e);
  i76edit_set_status_bar_text(s_Saving_Terrain____0043677c);
  local_4 = 5;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&local_4,4);
  uVar2 = 0x454e4f5a;
  __write(_FileHandle,&stack0xfffffff8,4);
  i76edit_save_workspace_terrain_arrays(_FileHandle);
  i76edit_save_extended_zone_records(_FileHandle,unaff_DI,unaff_ESI,uVar2);
  i76edit_set_status_bar_text(s_Saving_Paths____00436768);
  __write(_FileHandle,&stack0xfffffff8,4);
  i76edit_save_path_records();
  i76edit_set_status_bar_text(s_Saving_Roads____00436754);
  uVar2 = 0x44414f52;
  __write(_FileHandle,&stack0xfffffff8,4);
  i76edit_save_road_records(_FileHandle,unaff_DI,unaff_ESI,uVar2);
  i76edit_set_status_bar_text(s_Saving_Objects____0043673c);
  local_4 = 3;
  __write(_FileHandle,&stack0xfffffff8,4);
  __write(_FileHandle,&local_4,4);
  puVar3 = &DAT_004a424f;
  __write(_FileHandle,&stack0xfffffff8,4);
  i76edit_save_object_zone_lists(_FileHandle);
  i76edit_save_linked_object_records(_FileHandle,unaff_DI,unaff_ESI,puVar3);
  i76edit_set_status_bar_text(s_Saving_Elevations____00436720);
  __write(_FileHandle,&stack0xfffffff8,4);
  _Buf = &DAT_0163ce70;
  do {
    puVar1 = _Buf + 200;
    __write(_FileHandle,_Buf,200);
    _Buf = puVar1;
  } while (puVar1 < &DAT_01640cf0);
  __write(_FileHandle,&stack0xfffffff8,4);
  __close(_FileHandle);
  i76edit_set_status_bar_text(s_Ready__00434590);
  return;
}


