/*
 * Program: i76shell.dll
 * Function: preload_shell_ui_image_records
 * Entry: 100316a0
 * Signature: undefined __fastcall preload_shell_ui_image_records(long param_1)
 */


void __fastcall preload_shell_ui_image_records(long param_1)

{
  int iVar1;
  long local_4;
  
  iVar1 = 0;
  local_4 = param_1;
  do {
    if (*(int *)((int)&g_shell_ui_image_record_ptr_100f4f48 + iVar1) == 0) {
      mpack_database_get_item
                (DAT_100cc53c,*(int *)((int)&shell_image_record_table_1004cb90 + iVar1),
                 (undefined4 *)((int)&g_shell_ui_image_record_ptr_100f4f48 + iVar1),&local_4);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x10);
  iVar1 = 0;
  do {
    if (*(int *)((int)&g_shell_ui_image_record_ptr_100f4f60 + iVar1) == 0) {
      mpack_database_get_item
                (DAT_100cc53c,*(int *)((int)&shell_image_record_table_1004cbb0 + iVar1),
                 (undefined4 *)((int)&g_shell_ui_image_record_ptr_100f4f60 + iVar1),&local_4);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x10);
  iVar1 = 0;
  do {
    if (*(int *)((int)&g_shell_ui_image_record_ptr_100f4f70 + iVar1) == 0) {
      mpack_database_get_item
                (DAT_100cc53c,*(int *)((int)&shell_image_record_table_1004cba0 + iVar1),
                 (undefined4 *)((int)&g_shell_ui_image_record_ptr_100f4f70 + iVar1),&local_4);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x10);
  iVar1 = 0;
  do {
    if (*(int *)((int)&g_shell_ui_image_record_ptr_100f4f80 + iVar1) == 0) {
      mpack_database_get_item
                (DAT_100cc53c,*(int *)((int)&shell_image_record_table_1004cbc0 + iVar1),
                 (undefined4 *)((int)&g_shell_ui_image_record_ptr_100f4f80 + iVar1),&local_4);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x10);
  if (g_shell_ui_image_record_ptr_100f4f94 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x35,&g_shell_ui_image_record_ptr_100f4f94,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4f98 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x36,&g_shell_ui_image_record_ptr_100f4f98,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4f9c == 0) {
    mpack_database_get_item(DAT_100cc53c,0x37,&g_shell_ui_image_record_ptr_100f4f9c,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fa0 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x38,&g_shell_ui_image_record_ptr_100f4fa0,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fa4 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x39,&g_shell_ui_image_record_ptr_100f4fa4,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fa8 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3a,&g_shell_ui_image_record_ptr_100f4fa8,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fac == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3b,&g_shell_ui_image_record_ptr_100f4fac,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fbc == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3f,&g_shell_ui_image_record_ptr_100f4fbc,&local_4);
  }
  return;
}


