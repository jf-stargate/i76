/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409d90
 * Entry: 00401442
 * Signature: undefined4 * __stdcall thunk_FUN_00409d90(void)
 */


undefined4 * thunk_FUN_00409d90(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_00434760;
  if (DAT_00434760 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  DAT_00434760 = (undefined4 *)*DAT_00434760;
  return puVar1;
}


