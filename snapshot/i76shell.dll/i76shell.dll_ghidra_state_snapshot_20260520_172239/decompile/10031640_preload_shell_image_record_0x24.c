/*
 * Program: i76shell.dll
 * Function: preload_shell_image_record_0x24
 * Entry: 10031640
 * Signature: undefined __stdcall preload_shell_image_record_0x24(void)
 */


void preload_shell_image_record_0x24(void)

{
  long local_4;
  
  if (g_shell_ui_image_record_ptr_100f4f90 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x24,&g_shell_ui_image_record_ptr_100f4f90,&local_4);
  }
  return;
}


