/*
 * Program: I76EDIT.EXE
 * Function: i76edit_find_existing_editor_window
 * Entry: 00401366
 * Signature: bool __stdcall i76edit_find_existing_editor_window(void)
 */


bool i76edit_find_existing_editor_window(void)

{
  HWND pHVar1;
  
  pHVar1 = FindWindowA(s_Interstate__76_Editor_rel_3_06_v_00434034,(LPCSTR)0x0);
  return (bool)('\x01' - (pHVar1 == (HWND)0x0));
}


