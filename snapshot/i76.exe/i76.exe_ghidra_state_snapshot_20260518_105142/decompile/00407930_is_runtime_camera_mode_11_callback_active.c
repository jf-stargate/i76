/*
 * Program: i76.exe
 * Function: is_runtime_camera_mode_11_callback_active
 * Entry: 00407930
 * Signature: bool __stdcall is_runtime_camera_mode_11_callback_active(void)
 */


/* cgpt rename v5 runtime camera cluster: Returns whether the current runtime camera callback equals
   LAB_00407680, the callback installed by camera mode 0x11. */

bool is_runtime_camera_mode_11_callback_active(void)

{
  return g_runtime_display_mode_change_callback == &LAB_00407680;
}


