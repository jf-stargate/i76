/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00408c50
 * Entry: 004013f7
 * Signature: undefined4 __cdecl thunk_FUN_00408c50(int param_1, undefined4 * param_2)
 */


undefined4 __cdecl thunk_FUN_00408c50(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 8);
  for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return 1;
}


