/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e870
 * Entry: 004010e6
 * Signature: undefined __stdcall thunk_FUN_0041e870(void)
 */


void thunk_FUN_0041e870(void)

{
  int iVar1;
  
  iVar1 = SendMessageA(DAT_01641fa8,0x418,0,0);
  while (0x19 < iVar1) {
    SendMessageA(DAT_01641fa8,0x416,0x19,0);
    iVar1 = SendMessageA(DAT_01641fa8,0x418,0,0);
  }
  return;
}


