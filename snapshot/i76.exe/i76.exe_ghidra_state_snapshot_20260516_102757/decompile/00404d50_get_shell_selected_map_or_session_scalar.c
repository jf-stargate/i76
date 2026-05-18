/*
 * Program: i76.exe
 * Function: get_shell_selected_map_or_session_scalar
 * Entry: 00404d50
 * Signature: undefined4 __stdcall get_shell_selected_map_or_session_scalar(void)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Returns the shell-selected
   map/session scalar copied from launch config offset +0x6c. */

undefined4 get_shell_selected_map_or_session_scalar(void)

{
  return g_shell_selected_map_or_session_scalar;
}


