/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00402290
 * Entry: 00401366
 * Signature: bool __stdcall thunk_FUN_00402290(void)
 */


bool thunk_FUN_00402290(void)

{
  HWND pHVar1;
  
  pHVar1 = FindWindowA(s_Interstate__76_Editor_rel_3_06_v_00434034,(LPCSTR)0x0);
  return (bool)('\x01' - (pHVar1 == (HWND)0x0));
}


