/*
 * Program: I76EDIT.EXE
 * Function: i76edit_find_existing_editor_window
 * Entry: 00402290
 * Signature: bool __stdcall i76edit_find_existing_editor_window(void)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References editor title string and FindWindowA; likely
   single-instance guard helper. */

bool i76edit_find_existing_editor_window(void)

{
  HWND pHVar1;
  
  pHVar1 = FindWindowA(s_Interstate__76_Editor_rel_3_06_v_00434034,(LPCSTR)0x0);
  return (bool)('\x01' - (pHVar1 == (HWND)0x0));
}


