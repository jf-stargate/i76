/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f4b0
 * Entry: 00401483
 * Signature: undefined __cdecl thunk_FUN_0040f4b0(undefined4 * param_1, int param_2)
 */


void __cdecl thunk_FUN_0040f4b0(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(*(int *)(param_2 + 8) + 0x78);
  for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


