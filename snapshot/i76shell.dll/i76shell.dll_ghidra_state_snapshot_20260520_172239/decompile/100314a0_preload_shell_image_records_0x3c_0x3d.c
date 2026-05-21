/*
 * Program: i76shell.dll
 * Function: preload_shell_image_records_0x3c_0x3d
 * Entry: 100314a0
 * Signature: undefined __stdcall preload_shell_image_records_0x3c_0x3d(void)
 */


void preload_shell_image_records_0x3c_0x3d(void)

{
  long local_4;
  
  if (g_shell_ui_image_record_ptr_100f4fb4 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3c,&g_shell_ui_image_record_ptr_100f4fb4,&local_4);
  }
  if (g_shell_ui_image_record_ptr_100f4fb8 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3d,&g_shell_ui_image_record_ptr_100f4fb8,&local_4);
  }
  return;
}


