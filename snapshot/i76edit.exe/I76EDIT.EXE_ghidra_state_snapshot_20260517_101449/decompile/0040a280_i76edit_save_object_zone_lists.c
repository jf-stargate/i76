/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_object_zone_lists
 * Entry: 0040a280
 * Signature: undefined __cdecl i76edit_save_object_zone_lists(int param_1)
 */


/* [cgpt_i76edit_level_renames_v3] Writes object/zone list data during .I76 object save path. */

void __cdecl i76edit_save_object_zone_lists(int param_1)

{
  undefined4 *puVar1;
  long lVar2;
  long _Offset;
  uint local_10;
  int local_c;
  int local_8;
  long local_4;
  
  local_8 = 0;
  local_c = 0;
  local_4 = __tell(param_1);
  __write(param_1,&local_8,4);
  local_10 = 0;
  do {
    if ((&DAT_00439be8)[local_10] != 0) {
      local_8 = local_8 + 1;
      local_c = 0;
      __write(param_1,&local_10,4);
      lVar2 = __tell(param_1);
      __write(param_1,&local_c,4);
      for (puVar1 = (undefined4 *)(&DAT_00439be8)[local_10]; puVar1 != (undefined4 *)0x0;
          puVar1 = (undefined4 *)*puVar1) {
        local_c = local_c + 1;
        __write(param_1,(void *)puVar1[2],0x78);
      }
      _Offset = __tell(param_1);
      __lseek(param_1,lVar2,0);
      __write(param_1,&local_c,4);
      __lseek(param_1,_Offset,0);
    }
    local_10 = local_10 + 1;
  } while (local_10 < 0x50);
  lVar2 = __tell(param_1);
  __lseek(param_1,local_4,0);
  __write(param_1,&local_8,4);
  __lseek(param_1,lVar2,0);
  return;
}


