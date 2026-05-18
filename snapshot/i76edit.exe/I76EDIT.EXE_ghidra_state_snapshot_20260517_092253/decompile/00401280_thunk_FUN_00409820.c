/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409820
 * Entry: 00401280
 * Signature: undefined __stdcall thunk_FUN_00409820(void)
 */


void thunk_FUN_00409820(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00439be8;
  for (iVar1 = 0x50; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


