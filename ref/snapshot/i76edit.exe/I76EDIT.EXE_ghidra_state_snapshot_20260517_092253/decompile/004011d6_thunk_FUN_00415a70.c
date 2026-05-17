/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415a70
 * Entry: 004011d6
 * Signature: undefined4 * __stdcall thunk_FUN_00415a70(void)
 */


undefined4 * thunk_FUN_00415a70(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_00436194;
  if (DAT_00436194 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  DAT_00436194 = (undefined4 *)*DAT_00436194;
  return puVar1;
}


