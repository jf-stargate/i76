/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409e00
 * Entry: 004011ae
 * Signature: undefined __cdecl thunk_FUN_00409e00(int param_1, int param_2)
 */


void __cdecl thunk_FUN_00409e00(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  (&DAT_00439be8)[param_1] = (&DAT_00439be8)[param_2];
  (&DAT_00439be8)[param_2] = 0;
  for (puVar1 = (undefined4 *)(&DAT_00439be8)[param_1]; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)*puVar1) {
    *(int *)puVar1[2] = param_1;
  }
  return;
}


