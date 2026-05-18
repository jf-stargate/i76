/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040f910
 * Entry: 004011db
 * Signature: undefined __cdecl thunk_FUN_0040f910(undefined4 * param_1, int param_2)
 */


void __cdecl thunk_FUN_0040f910(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_2 + 8);
  for (iVar1 = 0x1e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


