/*
 * Program: i76shell.dll
 * Function: preload_shell_image_record_0x3e
 * Entry: 10031670
 * Signature: undefined __stdcall preload_shell_image_record_0x3e(void)
 */


void preload_shell_image_record_0x3e(void)

{
  long local_4;
  
  if (g_shell_ui_image_record_ptr_100f4fb0 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x3e,&g_shell_ui_image_record_ptr_100f4fb0,&local_4);
  }
  return;
}


